"""Load one verified native image with test-only sound/RNG/render/lifecycle boundaries.

Fresh default audits keep loading the canonical LOCAL image. CoreNative uses a
byte-identical image with its own inode after this shim enters the GLOBAL scope.
Nothing loads or compiles merely by importing this module.
"""
import argparse
import ctypes as C
import fcntl
import hashlib
import json
import os
from pathlib import Path
import shlex
import shutil
import subprocess
import sys
import tempfile

ROOT = Path(__file__).resolve().parents[1]
SOURCE = ROOT / 'tests/core_gameplay_interposer.c'
ARTIFACT = ROOT / 'build/native/core-gameplay-interposer.so'
IDENTITY = ARTIFACT.with_suffix('.json')
FLAGS = ['-std=c11', '-shared', '-fPIC', '-Wall', '-Wextra', '-Werror',
         '-I' + str(ROOT / 'src')]
IGNORED_COMPILER_ENV = ['CPATH', 'C_INCLUDE_PATH', 'CPLUS_INCLUDE_PATH',
                        'OBJC_INCLUDE_PATH', 'LIBRARY_PATH', 'COMPILER_PATH',
                        'GCC_EXEC_PREFIX', 'LD_RUN_PATH', 'SOURCE_DATE_EPOCH']
_shim = None
_shim_sha256 = None
_copies = {}


class _DlInfo(C.Structure):
    _fields_ = [('filename', C.c_char_p), ('base', C.c_void_p),
                ('symbol', C.c_char_p), ('address', C.c_void_p)]


def _function_owner(address):
    dladdr = C.CDLL(None).dladdr
    dladdr.argtypes, dladdr.restype = [C.c_void_p, C.POINTER(_DlInfo)], C.c_int
    result = _DlInfo()
    if not dladdr(address, C.byref(result)) or not result.filename:
        raise RuntimeError('CoreNative could not identify the real function owner')
    return Path(result.filename.decode()).resolve()


def _sha(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def _compiler():
    found = shutil.which('cc')
    if found is None:
        raise RuntimeError('CoreNative interposer requires the native C compiler cc')
    return Path(found).resolve()


def _recipe():
    compiler = _compiler()
    return {'compiler': str(compiler), 'compiler_sha256': _sha(compiler),
            'flags': FLAGS, 'source': str(SOURCE),
            'cleared_compiler_environment': IGNORED_COMPILER_ENV,
            'loader_sha256': _sha(__file__),
            'limits_sha256': _sha(ROOT / 'scripts/resource_limits.py'),
            'session_lock_sha256': _sha(ROOT / 'scripts/legacy_toolchain.py')}


def _verified_identity(recipe):
    try:
        identity = json.loads(IDENTITY.read_text())
        if identity['recipe'] != recipe or identity['artifact_sha256'] != _sha(ARTIFACT):
            return None
        inputs = identity['input_sha256']
        if str(SOURCE) not in inputs or not inputs:
            return None
        if any(_sha(path) != expected for path, expected in inputs.items()):
            return None
        return identity
    except (OSError, KeyError, ValueError, TypeError):
        return None


def prepare_interposer():
    """Compile only on a cache miss, before an owner holds compiler-session.lock."""
    recipe = _recipe()
    verified = _verified_identity(recipe)
    if verified is not None:
        return verified
    if _shim is not None:
        raise RuntimeError('CoreNative interposer inputs changed after its GLOBAL image was loaded')
    sys.path.insert(0, str(ROOT / 'scripts'))
    from resource_limits import limit_cpu
    from legacy_toolchain import session_lock
    limit_cpu()
    # Several owner scripts hold this lock across fixture construction. Diagnose
    # a missing prebuild instead of waiting forever for that same owner lock.
    lock_path = ROOT / '.tools/compiler-session.lock'
    lock_path.parent.mkdir(exist_ok=True)
    with lock_path.open('a') as availability:
        try:
            fcntl.flock(availability, fcntl.LOCK_EX | fcntl.LOCK_NB)
        except BlockingIOError as error:
            raise RuntimeError('Prepare the CoreNative shim before the owner compiler lock: '
                               'scripts/repo-python tests/core_native_loader.py --prepare-only') from error
        fcntl.flock(availability, fcntl.LOCK_UN)
    with session_lock():
        recipe = _recipe()
        verified = _verified_identity(recipe)
        if verified is not None:
            return verified
        ARTIFACT.parent.mkdir(parents=True, exist_ok=True)
        with tempfile.TemporaryDirectory(prefix='core-shim-build-', dir=ARTIFACT.parent) as directory:
            temporary = Path(directory)
            output, dependencies = temporary / 'shim.so', temporary / 'shim.d'
            command = [recipe['compiler'], *FLAGS, '-MD', '-MF', str(dependencies),
                       str(SOURCE), '-o', str(output)]
            environment = os.environ.copy()
            for name in IGNORED_COMPILER_ENV:
                environment.pop(name, None)
            result = subprocess.run(command, cwd=ROOT, env=environment,
                                    capture_output=True, text=True, timeout=120)
            if result.returncode:
                raise RuntimeError('CoreNative shim compilation failed:\n' + result.stdout + result.stderr)
            # -MD records all actually consumed project and system headers.
            dependency_text = dependencies.read_text().replace('\\\n', '')
            # Preserve dependency symlink paths so retargeting an include is detected.
            paths = {Path(p).absolute() for p in shlex.split(dependency_text.split(':', 1)[1])}
            paths.add(SOURCE)
            identity = {'recipe': recipe,
                        'input_sha256': {str(p): _sha(p) for p in sorted(paths)},
                        'artifact_sha256': _sha(output)}
            output.replace(ARTIFACT)
            receipt = temporary / 'identity.json'
            receipt.write_text(json.dumps(identity, indent=2, sort_keys=True) + '\n')
            receipt.replace(IDENTITY)
    return identity


class _Image:
    def __init__(self, canonical, canonical_sha256, identity):
        self.canonical = canonical
        self.canonical_sha256 = canonical_sha256
        self.shim_identity = identity
        self.directory = tempfile.TemporaryDirectory(prefix='dxball-core-fixture-')
        self.path = Path(self.directory.name) / canonical.name
        shutil.copyfile(canonical, self.path)
        if _sha(self.path) != canonical_sha256 or _sha(canonical) != canonical_sha256:
            raise RuntimeError('Selected native library changed while creating the CoreNative copy')
        if (self.path.stat().st_dev, self.path.stat().st_ino) == (canonical.stat().st_dev, canonical.stat().st_ino):
            raise RuntimeError('CoreNative library copy must have a separate inode')
        self.lib = C.CDLL(str(self.path.resolve()))
        self.function_addresses = {}
        boundaries = [('dxball_effect_ops', 5, 0, 'dxball_runtime_delete'),
                      ('dxball_render_ops', 3, 0, 'dxball_draw_sprite'),
                      ('dxball_effect_ops', 5, 3, 'dxball_draw_reduced_sprite'),
                      ('dxball_gameplay_ops', 6, 2, 'dxball_stop_sound'),
                      ('dxball_gameplay_ops', 6, 1, 'dxball_spawn_brick_effect'),
                      ('dxball_gameplay_ops', 6, 3, 'dxball_play_sound'),
                      ('dxball_gameplay_ops', 6, 4, 'dxball_random_range'),
                      ('dxball_gameplay_ops', 6, 5, 'dxball_spawn_particle'),
                      ('dxball_display_ops', 2, 0, 'dxball_update_sound'),
                      ('dxball_render_ops', 3, 2, 'dxball_invalidate_region'),
                      ('dxball_frame_ops', 12, 6, 'dxball_draw_effect_sprite'),
                      ('dxball_frame_ops', 12, 4, 'dxball_wait_frames'),
                      ('dxball_frame_ops', 12, 0, 'dxball_current_time'),
                      ('dxball_frame_ops', 12, 1, 'dxball_elapsed'),
                      ('dxball_frame_ops', 12, 2, 'dxball_animate_palette'),
                      ('dxball_frame_ops', 12, 3, 'dxball_refresh_score'),
                      ('dxball_frame_ops', 12, 5, 'dxball_restore_regions'),
                      ('dxball_frame_ops', 12, 7, 'dxball_draw_paddle'),
                      ('dxball_frame_ops', 12, 8, 'dxball_last_brick'),
                      ('dxball_frame_ops', 12, 9, 'dxball_draw_last_brick'),
                      ('dxball_frame_ops', 12, 10, 'dxball_present'),
                      ('dxball_frame_ops', 12, 11, 'dxball_restart_round'),
                      ('dxball_effect_ops', 5, 1, 'dxball_generate_bonus'),
                      ('dxball_runtime_ops', 15, 0, 'dxball_load_saved_palette'),
                      ('dxball_runtime_ops', 15, 1, 'dxball_palette_transition'),
                      ('dxball_runtime_ops', 15, 2, 'dxball_clear_surface'),
                      ('dxball_runtime_ops', 15, 3, 'dxball_reset_regions'),
                      ('dxball_runtime_ops', 15, 4, 'dxball_load_pcx'),
                      ('dxball_runtime_ops', 15, 5, 'dxball_load_sprite_bank'),
                      ('dxball_runtime_ops', 15, 6, 'dxball_capture_sprite'),
                      ('dxball_runtime_ops', 15, 7, 'dxball_load_sound'),
                      ('dxball_runtime_ops', 15, 8, 'dxball_bind_board_surface'),
                      ('dxball_runtime_ops', 15, 9, 'dxball_bind_display_surface'),
                      ('dxball_runtime_ops', 15, 10, 'dxball_draw_text'),
                      ('dxball_runtime_ops', 15, 11, 'dxball_draw_centered_text'),
                      ('dxball_runtime_ops', 15, 12, 'dxball_release_sounds'),
                      ('dxball_runtime_ops', 15, 13, 'dxball_release_sprite_banks'),
                      ('dxball_runtime_ops', 15, 14, 'dxball_close_music'),
                      ('dxball_platform_ops', 9, 0, 'dxball_prepare_sound'),
                      ('dxball_platform_ops', 9, 1, 'dxball_initialize_sound'),
                      ('dxball_platform_ops', 9, 2, 'dxball_pause_sound'),
                      ('dxball_platform_ops', 9, 3, 'dxball_resume_music'),
                      ('dxball_platform_ops', 9, 4, 'dxball_pause_music'),
                      ('dxball_platform_ops', 9, 6, 'dxball_release_audio'),
                      ('dxball_platform_ops', 9, 5, 'dxball_close_music'),
                      ('dxball_effect_ops', 5, 2, 'dxball_draw_keyed_sprite')]
        boundaries.append(('dxball_display_ops', 2, 1, 'dxball_recover_surfaces'))
        for table, length, slot, symbol in boundaries:
            defaults = (C.c_void_p * length).in_dll(self.lib, table)
            real = C.cast(getattr(self.lib, symbol), C.c_void_p).value
            intercepted = C.cast(getattr(_shim, symbol), C.c_void_p).value
            if real == intercepted:
                raise RuntimeError('CoreNative real handle resolves to the interposer: ' + symbol)
            if _function_owner(real) != self.path.resolve():
                raise RuntimeError('CoreNative real function comes from a different image: ' + symbol)
            if defaults[slot] != intercepted:
                raise RuntimeError('CoreNative copy did not bind the intended test interposer: ' + symbol)
            self.function_addresses[symbol] = real
        self.effect_region_default = (C.c_void_p * 5).in_dll(self.lib, 'dxball_effect_ops')[4]
        real = C.cast(self.lib.dxball_restore_effect_region, C.c_void_p).value
        intercepted = C.cast(_shim.dxball_restore_effect_region, C.c_void_p).value
        if (real == intercepted or _function_owner(real) != self.path.resolve() or
                not self.effect_region_default or self.effect_region_default in (real, intercepted) or
                _function_owner(self.effect_region_default) != self.path.resolve()):
            raise RuntimeError('CoreNative region body or bounds adapter has a different owner')
        self.function_addresses['dxball_restore_effect_region'] = real
        self.particle_region_slot = C.c_void_p.in_dll(self.lib, 'dxball_particle_region')
        self.particle_region_default = self.particle_region_slot.value
        real = C.cast(self.lib.dxball_queue_region, C.c_void_p).value
        intercepted = C.cast(_shim.dxball_queue_region, C.c_void_p).value
        if (real == intercepted or _function_owner(real) != self.path.resolve() or
                not self.particle_region_default or self.particle_region_default in (real, intercepted) or
                _function_owner(self.particle_region_default) != self.path.resolve()):
            raise RuntimeError('CoreNative queue body or particle-region default has a different owner')
        self.function_addresses['dxball_queue_region'] = real
        # PlatformOps uses a genuine void adapter for this integer-returning
        # API. Keep its identity for a guard until PlatformNative replaces it.
        self.platform_table = (C.c_void_p * 9).in_dll(self.lib, 'dxball_platform_ops')
        self.platform_music_default = self.platform_table[7]
        real = C.cast(self.lib.dxball_load_music, C.c_void_p).value
        intercepted = C.cast(_shim.dxball_load_music, C.c_void_p).value
        if real == intercepted or _function_owner(real) != self.path.resolve():
            raise RuntimeError('CoreNative music function does not belong to its copied image')
        if (not self.platform_music_default or
                self.platform_music_default in (real, intercepted) or
                _function_owner(self.platform_music_default) != self.path.resolve()):
            raise RuntimeError('CoreNative music default is not its genuine void adapter')
        self.function_addresses['dxball_load_music'] = real
        self.display_table = (C.c_void_p * 2).in_dll(self.lib, 'dxball_display_ops')
        self.particle_table = (C.c_void_p * 6).in_dll(self.lib, 'dxball_gameplay_ops')
        self.effect_table = (C.c_void_p * 5).in_dll(self.lib, 'dxball_effect_ops')
        self.render_table = (C.c_void_p * 3).in_dll(self.lib, 'dxball_render_ops')
        # Allocation has an actual size_t adapter in slot 0; its recovered
        # uint32_t entry is interposed only at genuine production references.
        self.new_default = self.particle_table[0]
        adapter = C.cast(self.lib.dxball_new_bytes, C.c_void_p).value
        real = C.cast(self.lib.dxball_runtime_new, C.c_void_p).value
        intercepted = C.cast(_shim.dxball_runtime_new, C.c_void_p).value
        if (self.new_default != adapter or not adapter or
                adapter in (real, intercepted) or
                _function_owner(adapter) != self.path.resolve()):
            raise RuntimeError('CoreNative allocation default is not its genuine size_t adapter')
        if real == intercepted or _function_owner(real) != self.path.resolve():
            raise RuntimeError('CoreNative new body does not belong to its copied image')
        self.function_addresses['dxball_runtime_new'] = real


def fixture_image(library):
    """Return a pinned copied path; all inherited fixtures continue using self.lib."""
    global _shim, _shim_sha256
    canonical = Path(library).resolve()
    canonical_sha256 = _sha(canonical)
    identity = prepare_interposer()
    shim_sha256 = identity['artifact_sha256']
    if _shim is None:
        _shim = C.CDLL(str(ARTIFACT.resolve()), mode=C.RTLD_GLOBAL)
        _shim_sha256 = shim_sha256
        _shim.dxball_test_bind_gameplay_ops.argtypes = [C.c_void_p]
        _shim.dxball_test_bind_gameplay_ops.restype = C.c_int
        _shim.dxball_test_bind_particle_ops.argtypes = [C.c_void_p, C.c_void_p]
        _shim.dxball_test_bind_particle_ops.restype = C.c_int
        _shim.dxball_test_bind_brick_effect_ops.argtypes = [C.c_void_p, C.c_void_p]
        _shim.dxball_test_bind_brick_effect_ops.restype = C.c_int
        _shim.dxball_test_bind_new_ops.argtypes = [C.c_void_p] * 3
        _shim.dxball_test_bind_new_ops.restype = C.c_int
        _shim.dxball_test_bind_effect_render_ops.argtypes = [C.c_void_p] * 7
        _shim.dxball_test_bind_effect_render_ops.restype = C.c_int
        _shim.dxball_test_bind_particle_region.argtypes = [C.c_void_p] * 3
        _shim.dxball_test_bind_particle_region.restype = C.c_int
        _shim.dxball_test_bind_render_frame_ops.argtypes = [C.c_void_p, C.c_void_p, C.c_void_p]
        _shim.dxball_test_bind_render_frame_ops.restype = C.c_int
        _shim.dxball_test_bind_runtime_ops.argtypes = [C.c_void_p]
        _shim.dxball_test_bind_runtime_ops.restype = C.c_int
        _shim.dxball_test_bind_platform_ops.argtypes = [C.c_void_p, C.c_void_p]
        _shim.dxball_test_bind_platform_ops.restype = C.c_int
        _shim.dxball_test_bind_display_ops.argtypes = [C.c_void_p, C.c_void_p]
        _shim.dxball_test_bind_display_ops.restype = C.c_int
    elif _shim_sha256 != shim_sha256:
        raise RuntimeError('CoreNative cannot replace an already loaded GLOBAL interposer')
    # CoreNative passes this same copied path to inherited EntitiesNative.
    # Recognize only an image already pinned by this loader, not a lookalike DSO.
    selected_copy = next((image for image in _copies.values()
                          if image.path.resolve() == canonical), None)
    if selected_copy is not None:
        if (selected_copy.shim_identity != identity or
                selected_copy.canonical_sha256 != canonical_sha256):
            raise RuntimeError('CoreNative selected copied image identity changed')
        canonical = selected_copy.canonical
    key = (str(canonical), canonical_sha256, shim_sha256,
           hashlib.sha256(json.dumps(identity, sort_keys=True).encode()).hexdigest())
    if selected_copy is not None and _copies.get(key) is not selected_copy:
        raise RuntimeError('CoreNative selected copy does not match its canonical cache entry')
    if key not in _copies:
        _copies[key] = _Image(canonical, canonical_sha256, identity)
    image = _copies[key]
    if _sha(image.path) != canonical_sha256 or _sha(canonical) != canonical_sha256:
        raise RuntimeError('CoreNative copied or selected library identity changed')
    actual = C.addressof(C.c_void_p.in_dll(image.lib, 'dxball_platform_ops'))
    if actual != C.addressof(image.platform_table):
        raise RuntimeError('CoreNative platform table does not belong to its copied image')
    # No native work occurs here: later unchanged PlatformNative construction
    # installs its void callback. The C wrapper checks the live slot on each call.
    result = _shim.dxball_test_bind_platform_ops(actual, image.platform_music_default)
    if result != 0:
        raise RuntimeError('CoreNative platform binding rejected: null table or default adapter')
    actual = C.addressof(C.c_void_p.in_dll(image.lib, 'dxball_display_ops'))
    if actual != C.addressof(image.display_table):
        raise RuntimeError('CoreNative display table does not belong to its copied image')
    # DisplayNative supplies the actual callback after inherited construction.
    # The default calls the real body belonging to this same copied image.
    real = C.cast(image.lib.dxball_recover_surfaces, C.c_void_p).value
    if (real != image.function_addresses['dxball_recover_surfaces'] or
            real == C.cast(_shim.dxball_recover_surfaces, C.c_void_p).value or
            _function_owner(real) != image.path.resolve()):
        raise RuntimeError('CoreNative surface recovery body has a different owner')
    result = _shim.dxball_test_bind_display_ops(actual, real)
    if result != 0:
        raise RuntimeError('CoreNative display binding rejected: null table or recursive real body')
    actual = C.addressof(C.c_void_p.in_dll(image.lib, 'dxball_gameplay_ops'))
    if actual != C.addressof(image.particle_table):
        raise RuntimeError('CoreNative particle table does not belong to its copied image')
    real = C.cast(image.lib.dxball_spawn_particle, C.c_void_p).value
    if (real != image.function_addresses['dxball_spawn_particle'] or
            real == C.cast(_shim.dxball_spawn_particle, C.c_void_p).value or
            _function_owner(real) != image.path.resolve()):
        raise RuntimeError('CoreNative particle body does not belong to its copied image')
    # Pin the real owner before unchanged constructors replace slot 5. Each call
    # reads that live slot; an untouched default or null slot uses this body.
    result = _shim.dxball_test_bind_particle_ops(actual, real)
    if result != 0:
        raise RuntimeError('CoreNative particle binding rejected: null or recursive real body')
    real = C.cast(image.lib.dxball_spawn_brick_effect, C.c_void_p).value
    if (real != image.function_addresses['dxball_spawn_brick_effect'] or
            real == C.cast(_shim.dxball_spawn_brick_effect, C.c_void_p).value or
            _function_owner(real) != image.path.resolve()):
        raise RuntimeError('CoreNative brick-effect body does not belong to its copied image')
    # GameNative first supplies its controlled callback; EffectsNative later
    # replaces slot 1 with the actual body. The wrapper reads that current slot.
    result = _shim.dxball_test_bind_brick_effect_ops(actual, real)
    if result != 0:
        raise RuntimeError('CoreNative brick-effect binding rejected: null or recursive real body')
    addresses = []
    for symbol, table in (('dxball_effect_ops', image.effect_table),
                          ('dxball_render_ops', image.render_table)):
        actual = C.addressof(C.c_void_p.in_dll(image.lib, symbol))
        if actual != C.addressof(table):
            raise RuntimeError('CoreNative effect/render table does not belong to its copied image: ' + symbol)
        addresses.append(actual)
    for symbol in ('dxball_runtime_delete', 'dxball_draw_sprite',
                   'dxball_draw_reduced_sprite', 'dxball_restore_effect_region'):
        real = C.cast(getattr(image.lib, symbol), C.c_void_p).value
        if (real != image.function_addresses[symbol] or
                real == C.cast(getattr(_shim, symbol), C.c_void_p).value or
                _function_owner(real) != image.path.resolve()):
            raise RuntimeError('CoreNative effect/render body does not belong to its copied image: ' + symbol)
        addresses.append(real)
    if (_function_owner(image.effect_region_default) != image.path.resolve() or
            image.effect_region_default in (image.function_addresses['dxball_restore_effect_region'],
                C.cast(_shim.dxball_restore_effect_region, C.c_void_p).value)):
        raise RuntimeError('CoreNative region bounds adapter changed owner')
    result = _shim.dxball_test_bind_effect_render_ops(*addresses, image.effect_region_default)
    if result != 0:
        raise RuntimeError('CoreNative effect/render binding rejected: null or recursive real owner')
    slot = C.c_void_p.in_dll(image.lib, 'dxball_particle_region')
    real = C.cast(image.lib.dxball_queue_region, C.c_void_p).value
    if (C.addressof(slot) != C.addressof(image.particle_region_slot) or
            real != image.function_addresses['dxball_queue_region'] or
            real == C.cast(_shim.dxball_queue_region, C.c_void_p).value or
            _function_owner(real) != image.path.resolve()):
        raise RuntimeError('CoreNative particle-region slot or queue body changed owner')
    if _function_owner(image.particle_region_default) != image.path.resolve():
        raise RuntimeError('CoreNative particle bounds adapter changed owner')
    result = _shim.dxball_test_bind_particle_region(C.addressof(slot), real, image.particle_region_default)
    if result != 0:
        raise RuntimeError('CoreNative particle-region binding rejected')
    actual = C.addressof(C.c_void_p.in_dll(image.lib, 'dxball_gameplay_ops'))
    if actual != C.addressof(image.particle_table):
        raise RuntimeError('CoreNative allocation table does not belong to its copied image')
    real = C.cast(image.lib.dxball_runtime_new, C.c_void_p).value
    adapter = C.cast(image.lib.dxball_new_bytes, C.c_void_p).value
    if (real != image.function_addresses['dxball_runtime_new'] or
            real == C.cast(_shim.dxball_runtime_new, C.c_void_p).value or
            _function_owner(real) != image.path.resolve() or
            adapter != image.new_default or
            _function_owner(adapter) != image.path.resolve()):
        raise RuntimeError('CoreNative allocation body or adapter changed owner')
    result = _shim.dxball_test_bind_new_ops(actual, real, adapter)
    if result != 0:
        raise RuntimeError('CoreNative allocation binding rejected: null or recursive real owner')
    return image


def bind_gameplay(image, library, table):
    """Bind the table only after inherited fixture callbacks have been installed."""
    actual = C.addressof(C.c_void_p.in_dll(library, 'dxball_gameplay_ops'))
    if actual != C.addressof(table):
        raise RuntimeError('CoreNative callback table does not belong to its native handle')
    if actual != C.addressof(C.c_void_p.in_dll(image.lib, 'dxball_gameplay_ops')):
        raise RuntimeError('CoreNative fixture did not load its verified copied image')
    result = _shim.dxball_test_bind_gameplay_ops(actual)
    if result != 0:
        reason = {-1: 'null table', -2: 'null sound/RNG callback',
                  -3: 'sound/RNG slot resolves recursively to the interposer'}
        raise RuntimeError('CoreNative callback binding rejected: ' + reason.get(result, str(result)))


def bind_render_frame(image, library, render, frame):
    """Bind current render/frame/effect tables after inherited and frame callbacks."""
    addresses = []
    effect = (C.c_void_p * 5).in_dll(library, 'dxball_effect_ops')
    for symbol, table in (('dxball_render_ops', render), ('dxball_frame_ops', frame),
                          ('dxball_effect_ops', effect)):
        actual = C.addressof(C.c_void_p.in_dll(library, symbol))
        if actual != C.addressof(table):
            raise RuntimeError('CoreNative callback table does not belong to its native handle: ' + symbol)
        if actual != C.addressof(C.c_void_p.in_dll(image.lib, symbol)):
            raise RuntimeError('CoreNative fixture did not load its verified copied image: ' + symbol)
        addresses.append(actual)
    result = _shim.dxball_test_bind_render_frame_ops(*addresses)
    if result != 0:
        reason = {-1: 'null render/frame/effect table', -2: 'null render/frame/effect callback',
                  -3: 'render/frame/effect slot resolves recursively to the interposer'}
        raise RuntimeError('CoreNative render/frame binding rejected: ' + reason.get(result, str(result)))
    image.effect_table = effect


def bind_runtime(image, library, table):
    """Bind the current runtime table after all lifecycle callbacks are installed."""
    actual = C.addressof(C.c_void_p.in_dll(library, 'dxball_runtime_ops'))
    if actual != C.addressof(table):
        raise RuntimeError('RuntimeNative callback table does not belong to its native handle')
    if actual != C.addressof(C.c_void_p.in_dll(image.lib, 'dxball_runtime_ops')):
        raise RuntimeError('RuntimeNative fixture did not load its verified copied image')
    result = _shim.dxball_test_bind_runtime_ops(actual)
    if result != 0:
        reason = {-1: 'null runtime table', -2: 'null lifecycle callback',
                  -3: 'lifecycle slot resolves recursively to the interposer'}
        raise RuntimeError('RuntimeNative callback binding rejected: ' + reason.get(result, str(result)))


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--prepare-only', action='store_true', required=True)
    parser.parse_args()
    print(json.dumps(prepare_interposer(), indent=2, sort_keys=True))
