#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$(cd "${SCRIPT_DIR}/.." && pwd)"

cd "${ROOT_DIR}"

APP_NAME="DX-Ball"
APP_BUNDLE="${ROOT_DIR}/${APP_NAME}.app"

echo "=== 1. Building dxball via CMake ==="
cmake -B build -S .
cmake --build build --parallel 1

echo "=== 2. Creating .app structure ==="
rm -rf "${APP_BUNDLE}"
mkdir -p "${APP_BUNDLE}/Contents/MacOS"
mkdir -p "${APP_BUNDLE}/Contents/Resources"
mkdir -p "${APP_BUNDLE}/Contents/Frameworks"

echo "=== 3. Copying binary and frameworks ==="
cp "build/dxball" "${APP_BUNDLE}/Contents/MacOS/dxball"
cp "build/libdxball_core.dylib" "${APP_BUNDLE}/Contents/Frameworks/libdxball_core.dylib"

SDL_LIB="/opt/homebrew/opt/sdl2-compat/lib/libSDL2-2.0.0.dylib"
if [ ! -f "${SDL_LIB}" ]; then
    SDL_LIB="$(brew --prefix sdl2-compat 2>/dev/null)/lib/libSDL2-2.0.0.dylib" || true
fi
if [ ! -f "${SDL_LIB}" ]; then
    SDL_LIB="$(brew --prefix sdl2 2>/dev/null)/lib/libSDL2-2.0.0.dylib" || true
fi

if [ -f "${SDL_LIB}" ]; then
    echo "Bundling SDL2 from ${SDL_LIB}..."
    cp "${SDL_LIB}" "${APP_BUNDLE}/Contents/Frameworks/libSDL2-2.0.0.dylib"
    chmod 755 "${APP_BUNDLE}/Contents/Frameworks/libSDL2-2.0.0.dylib"
    install_name_tool -id "@rpath/libSDL2-2.0.0.dylib" "${APP_BUNDLE}/Contents/Frameworks/libSDL2-2.0.0.dylib" || true
    install_name_tool -change "${SDL_LIB}" "@rpath/libSDL2-2.0.0.dylib" "${APP_BUNDLE}/Contents/MacOS/dxball" || true
fi

chmod 755 "${APP_BUNDLE}/Contents/Frameworks/libdxball_core.dylib"
install_name_tool -id "@rpath/libdxball_core.dylib" "${APP_BUNDLE}/Contents/Frameworks/libdxball_core.dylib" || true

chmod 755 "${APP_BUNDLE}/Contents/MacOS/dxball"
install_name_tool -add_rpath "@executable_path/../Frameworks" "${APP_BUNDLE}/Contents/MacOS/dxball" 2>/dev/null || true

echo "=== 4. Copying game assets to Resources ==="
cp -R original/* "${APP_BUNDLE}/Contents/Resources/"

echo "=== 5. Setting up App Icon ==="
if [ -f "/tmp/AppIcon.icns" ]; then
    cp "/tmp/AppIcon.icns" "${APP_BUNDLE}/Contents/Resources/AppIcon.icns"
fi

echo "=== 6. Creating Info.plist and PkgInfo ==="
cat << 'EOF' > "${APP_BUNDLE}/Contents/Info.plist"
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
    <key>CFBundleExecutable</key>
    <string>dxball</string>
    <key>CFBundleIconFile</key>
    <string>AppIcon</string>
    <key>CFBundleIdentifier</key>
    <string>com.dxball.dxball</string>
    <key>CFBundleInfoDictionaryVersion</key>
    <string>6.0</string>
    <key>CFBundleName</key>
    <string>DX-Ball</string>
    <key>CFBundlePackageType</key>
    <string>APPL</string>
    <key>CFBundleShortVersionString</key>
    <string>1.07</string>
    <key>CFBundleVersion</key>
    <string>1.07</string>
    <key>LSMinimumSystemVersion</key>
    <string>11.0</string>
    <key>NSHighResolutionCapable</key>
    <true/>
    <key>NSSupportsAutomaticGraphicsSwitching</key>
    <true/>
</dict>
</plist>
EOF

echo -n "APPL????" > "${APP_BUNDLE}/Contents/PkgInfo"

echo "=== 7. Signing .app bundle with ad-hoc signature ==="
codesign --force --deep --sign - "${APP_BUNDLE}"

echo "=== SUCCESS! ${APP_BUNDLE} created successfully! ==="
