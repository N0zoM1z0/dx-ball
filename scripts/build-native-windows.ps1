param([string]$OutputDirectory = '', [switch]$Incremental, [switch]$NoLimits)

$ErrorActionPreference = 'Stop'
$ProgressPreference = 'SilentlyContinue'
[Threading.Thread]::CurrentThread.CurrentCulture = [Globalization.CultureInfo]::GetCultureInfo('en-US')
[Threading.Thread]::CurrentThread.CurrentUICulture = [Globalization.CultureInfo]::GetCultureInfo('en-US')
$BundleRoot = $PSScriptRoot
$PackageRoot = Split-Path $BundleRoot -Parent
if (-not $OutputDirectory) { $OutputDirectory = Join-Path $PackageRoot 'build' }
$OutputDirectory = [IO.Path]::GetFullPath($OutputDirectory)
$LogDirectory = Join-Path $OutputDirectory 'logs'
$Stage = 'Initialize build'
$Completed = 0
$Total = 1
$Started = [DateTime]::UtcNow
$Compiled = @()

function Hash-File([string]$Path) {
    return (Get-FileHash -LiteralPath $Path -Algorithm SHA256).Hash.ToLowerInvariant()
}
function Show-Step([string]$Text) {
    $script:Stage = $Text
    $percent = [Math]::Floor(100 * $script:Completed / $script:Total)
    $filled = [Math]::Floor($percent / 4)
    $bar = ('#' * $filled).PadRight(25, '-')
    Write-Host ('[{0}] {1,3}%  {2}' -f $bar, $percent, $Text)
    Write-Progress -Activity 'Building DX-Ball v1.07 from reconstructed source' -Status $Text -PercentComplete $percent
    $script:Completed++
}
function Quote-Argument([string]$Value) {
    if ($Value.Contains('"')) { throw 'An input argument contains an unsupported quotation mark.' }
    return '"' + ($Value -replace '(\\+)$', '$1$1') + '"'
}
function Invoke-CompilerTool([string]$Name, [string[]]$Arguments, [string]$LogName) {
    $info = New-Object Diagnostics.ProcessStartInfo
    $info.FileName = Join-Path $BundleRoot ('toolchain\bin\' + $Name)
    $info.Arguments = ($Arguments | ForEach-Object { Quote-Argument $_ }) -join ' '
    $info.WorkingDirectory = $BundleRoot
    $info.UseShellExecute = $false
    $info.CreateNoWindow = $true
    $info.RedirectStandardOutput = $true
    $info.RedirectStandardError = $true
    if ($Name -eq 'link.exe') {
        # VC4 link 3.00 fails during Pass1 on current Windows without this
        # per-child compatibility layer. Compilation keeps its original context.
        $info.EnvironmentVariables['__COMPAT_LAYER'] = 'WIN7RTM'
    }
    $process = New-Object Diagnostics.Process
    $process.StartInfo = $info
    if (-not $process.Start()) { throw 'The compiler tool could not be started.' }
    $stdout = $process.StandardOutput.ReadToEndAsync()
    $stderr = $process.StandardError.ReadToEndAsync()
    $process.WaitForExit()
    [IO.File]::WriteAllText((Join-Path $LogDirectory $LogName), $stdout.Result + $stderr.Result)
    if ($process.ExitCode -ne 0) {
        throw ('Compiler tool failed: ' + $Name + ', exit code ' + $process.ExitCode + '. See logs/' + $LogName)
    }
}

try {
    New-Item -ItemType Directory -Path $LogDirectory -Force | Out-Null
    $planPath = Join-Path $BundleRoot 'build-plan.json'
    $plan = Get-Content -LiteralPath $planPath -Raw | ConvertFrom-Json
    $Total = $plan.objects.Count + 6
    Write-Host ''
    Write-Host 'DX-BALL v1.07 | RECONSTRUCTION BUILD' -ForegroundColor Cyan
    Write-Host '270 authored game functions recovered exactly; 84,968 authored code bytes.'
    Write-Host 'Native Windows build | Visual C++ 4.0 | No Python or WSL required.'
    Write-Host ('Compiling {0} source units; retaining exactly {1} approved original CRT members.' -f $plan.objects.Count, $plan.original_members.Count)
    Write-Host ''
    Show-Step 'Verify source, compiler and support-file identities'
    $checked = 0
    $inputCount = @($plan.files.PSObject.Properties).Count
    foreach ($entry in $plan.files.PSObject.Properties) {
        $path = Join-Path $BundleRoot $entry.Name
        if (-not (Test-Path -LiteralPath $path -PathType Leaf)) { throw ('Missing build input: ' + $entry.Name) }
        if ((Hash-File $path) -ne $entry.Value) { throw ('Build input changed: ' + $entry.Name) }
        $checked++
        if (($checked % 50) -eq 0) {
            Write-Progress -Activity 'Building DX-Ball v1.07 from reconstructed source' -Status ('Verifying input {0}/{1}' -f $checked, $inputCount) -PercentComplete 0
        }
    }
    if ($plan.objects.Count -ne 141 -or $plan.original_members.Count -ne 19) { throw 'Unexpected source or retained CRT member count.' }

    Show-Step 'Configure serial compiler execution and private build environment'
    if (-not $NoLimits) {
        Add-Type -TypeDefinition @'
using System;
using System.Diagnostics;
using System.Runtime.InteropServices;
public static class DxBallBuildLimits {
 [StructLayout(LayoutKind.Sequential)] struct Basic { public long ProcessTime,JobTime;public uint Flags;public UIntPtr Min,Max;public uint Active;public UIntPtr Affinity;public uint Priority,Scheduling; }
 [StructLayout(LayoutKind.Sequential)] struct Io { public ulong A,B,C,D,E,F; }
 [StructLayout(LayoutKind.Sequential)] struct Extended { public Basic Basic;public Io Io;public UIntPtr ProcessMemory,JobMemory,PeakProcess,PeakJob; }
 [StructLayout(LayoutKind.Sequential)] struct Cpu { public uint Flags,Rate; }
 [DllImport("kernel32.dll",CharSet=CharSet.Unicode)] static extern IntPtr CreateJobObject(IntPtr a,string n);
 [DllImport("kernel32.dll")] static extern bool AssignProcessToJobObject(IntPtr j,IntPtr p);
 [DllImport("kernel32.dll")] static extern bool SetInformationJobObject(IntPtr j,int c,IntPtr p,uint n);
 static IntPtr Job;
 static void Set<T>(int c,T value){int n=Marshal.SizeOf(typeof(T));IntPtr p=Marshal.AllocHGlobal(n);try{Marshal.StructureToPtr(value,p,false);if(!SetInformationJobObject(Job,c,p,(uint)n))throw new Exception("Could not configure the build job.");}finally{Marshal.FreeHGlobal(p);}}
 public static void Apply(){var p=Process.GetCurrentProcess();long mask=p.ProcessorAffinity.ToInt64();long one=mask&-mask;Job=CreateJobObject(IntPtr.Zero,null);if(Job==IntPtr.Zero)throw new Exception("Could not create the build job.");var e=new Extended();e.Basic.Flags=0x200|0x10;e.Basic.Affinity=new UIntPtr((ulong)one);e.JobMemory=new UIntPtr(512UL*1024*1024);Set(9,e);var c=new Cpu();c.Flags=1|4;c.Rate=(uint)Math.Max(1,3500/Environment.ProcessorCount);Set(15,c);if(!AssignProcessToJobObject(Job,p.Handle))throw new Exception("Could not attach the build process to its job.");p.PriorityClass=ProcessPriorityClass.BelowNormal;}
}
'@
        [DxBallBuildLimits]::Apply()
    }
    foreach ($name in @('CL', '_CL_', 'LINK')) { [Environment]::SetEnvironmentVariable($name, $null, 'Process') }
    $env:INCLUDE = Join-Path $BundleRoot 'toolchain\include'
    $env:LIB = Join-Path $BundleRoot 'toolchain\lib'
    $env:PATH = (Join-Path $BundleRoot 'toolchain\bin') + ';' + $env:PATH
    $objectsDirectory = Join-Path $OutputDirectory 'objects'
    $crtDirectory = Join-Path $OutputDirectory 'crt'
    $gameDirectory = Join-Path $OutputDirectory 'game'
    foreach ($dir in @($objectsDirectory, $crtDirectory, $gameDirectory)) { New-Item -ItemType Directory -Path $dir -Force | Out-Null }
    $cachePath = Join-Path $OutputDirectory 'object-cache.json'
    $cacheObjects = @{}
    if ($Incremental -and (Test-Path -LiteralPath $cachePath)) {
        $oldCache = Get-Content -LiteralPath $cachePath -Raw | ConvertFrom-Json
        if ($oldCache.compiler_context_sha256 -eq $plan.compiler_context_sha256) {
            foreach ($item in $oldCache.objects.PSObject.Properties) { $cacheObjects[$item.Name] = $item.Value }
        }
    }

    Show-Step 'Extract the 19 explicitly retained original CRT members'
    $library = [IO.File]::ReadAllBytes((Join-Path $BundleRoot 'toolchain\lib\libc.lib'))
    foreach ($member in $plan.original_members) {
        $offset = [int]$member.header_offset
        $size = [int][Text.Encoding]::ASCII.GetString($library, $offset + 48, 10).Trim()
        $bytes = New-Object byte[] $size
        [Buffer]::BlockCopy($library, $offset + 60, $bytes, 0, $size)
        $destination = Join-Path $crtDirectory ($member.id.Replace('member:', '') + '.obj')
        [IO.File]::WriteAllBytes($destination, $bytes)
        if ((Hash-File $destination) -ne $member.object_sha256) { throw ('CRT member identity mismatch: ' + $member.id) }
    }

    foreach ($unit in $plan.objects) {
        $source = Join-Path $BundleRoot $unit.source
        $object = Join-Path $objectsDirectory $unit.object
        $action = 'compiled'
        if ($Incremental -and $cacheObjects.ContainsKey($unit.object) -and (Test-Path -LiteralPath $object) -and (Hash-File $object) -eq $cacheObjects[$unit.object].sha256) {
            Show-Step ('Reuse verified object: ' + $unit.source)
            $action = 'reused'
        } else {
            Show-Step ('Compile {0}: {1}' -f $unit.owner, $unit.source)
            $arguments = @($unit.flags)
            $arguments += '/Fo' + $object
            $arguments += $source
            Invoke-CompilerTool 'cl.exe' $arguments ($unit.object + '.log')
            if (-not (Test-Path -LiteralPath $object)) { throw ('Compiler produced no object: ' + $unit.object) }
            $cacheObjects[$unit.object] = @{sha256=(Hash-File $object)}
            @{compiler_context_sha256=$plan.compiler_context_sha256;objects=$cacheObjects} | ConvertTo-Json -Depth 6 | Set-Content -LiteralPath $cachePath -Encoding UTF8
        }
        $Compiled += [ordered]@{source=$unit.source;owner=$unit.owner;object=$unit.object;sha256=(Hash-File $object);action=$action}
    }
    $resourceObject = Join-Path $OutputDirectory 'game-resources.obj'
    if ($Incremental -and $cacheObjects.ContainsKey('_game-resources.obj') -and (Test-Path -LiteralPath $resourceObject) -and (Hash-File $resourceObject) -eq $cacheObjects['_game-resources.obj'].sha256) {
        Show-Step 'Reuse the verified original icon resource object'
    } else {
        Show-Step 'Convert the original icon resources'
        Invoke-CompilerTool 'cvtres.exe' @('/NOLOGO', '/MACHINE:IX86', ('/OUT:' + $resourceObject), (Join-Path $BundleRoot 'support\game-resources.res')) 'resources.log'
        $cacheObjects['_game-resources.obj'] = @{sha256=(Hash-File $resourceObject)}
        @{compiler_context_sha256=$plan.compiler_context_sha256;objects=$cacheObjects} | ConvertTo-Json -Depth 6 | Set-Content -LiteralPath $cachePath -Encoding UTF8
    }

    Show-Step 'Link the reconstructed Windows executable'
    $linkArguments = foreach ($argument in $plan.link_arguments) {
        $value = $argument.Replace('{BUILD}', $OutputDirectory).Replace('{ROOT}', $BundleRoot)
        Quote-Argument $value
    }
    $response = Join-Path $OutputDirectory 'link.rsp'
    [IO.File]::WriteAllLines($response, [string[]]$linkArguments, [Text.Encoding]::Default)
    Invoke-CompilerTool 'link.exe' @('@' + $response) 'link.log'

    Show-Step 'Verify the PE32 output and prepare its game files'
    $exe = Join-Path $gameDirectory 'dxball.exe'
    $image = [IO.File]::ReadAllBytes($exe)
    $peOffset = [BitConverter]::ToInt32($image, 60)
    if ($image[0] -ne 77 -or $image[1] -ne 90 -or [BitConverter]::ToUInt32($image, $peOffset) -ne 17744 -or [BitConverter]::ToUInt16($image, $peOffset + 4) -ne 332) { throw 'The linker output is not a valid x86 PE32 executable.' }
    $installedGame = Join-Path $PackageRoot 'game'
    foreach ($asset in $plan.assets) {
        $destination = Join-Path $gameDirectory $asset
        if (-not (Test-Path -LiteralPath $destination)) { Copy-Item -LiteralPath (Join-Path $installedGame $asset) -Destination $destination }
    }
    foreach ($name in @('ddraw.dll', 'ddraw.ini')) { Copy-Item -LiteralPath (Join-Path $BundleRoot ('support\' + $name)) -Destination (Join-Path $gameDirectory $name) -Force }
    $receipt = [ordered]@{status='built';profile='vc40-restored-crt-native-windows';started_utc=$Started.ToString('o');finished_utc=[DateTime]::UtcNow.ToString('o');source_checkpoint=$plan.source_checkpoint;build_plan_sha256=(Hash-File $planPath);source_units=$Compiled;original_crt_members=$plan.original_members;exe=$exe;exe_bytes=$image.Length;exe_sha256=(Hash-File $exe);game_launched=$false;limits_enabled=(-not $NoLimits);scope='All 141 units compiled from source with the pinned VC4 recipes. Nineteen original CRT members are explicit. Build validation does not run the game or certify new live-play coverage.'}
    $receipt | ConvertTo-Json -Depth 10 | Set-Content -LiteralPath (Join-Path $OutputDirectory 'build-report.json') -Encoding UTF8
    $Completed = $Total
    Write-Progress -Activity 'Building DX-Ball v1.07 from reconstructed source' -Completed
    Write-Host ''
    Write-Host '[#########################] 100%  BUILD COMPLETE' -ForegroundColor Green
    Write-Host ('Source units: {0} | Compiled: {1} | Reused: {2} | Original CRT members: {3}' -f $Compiled.Count, @($Compiled | Where-Object {$_.action -eq 'compiled'}).Count, @($Compiled | Where-Object {$_.action -eq 'reused'}).Count, $plan.original_members.Count)
    Write-Host ('Executable: ' + $exe)
    Write-Host ('SHA-256:    ' + $receipt.exe_sha256)
    Write-Host ('Elapsed:    {0:F1} seconds' -f ([DateTime]::UtcNow - $Started).TotalSeconds)
    Write-Host 'The game was not launched. Use Play Rebuilt DX-Ball.cmd when ready.'
    exit 0
} catch {
    Write-Progress -Activity 'Building DX-Ball v1.07 from reconstructed source' -Completed
    Write-Host ''
    Write-Host 'BUILD FAILED' -ForegroundColor Red
    Write-Host ('Step: ' + $Stage)
    Write-Host ('Error category: ' + $_.Exception.GetType().Name)
    if ($_.Exception.Message -match '^[\x20-\x7E]+$') { Write-Host $_.Exception.Message }
    Write-Host ('Compiler logs: ' + $LogDirectory)
    exit 1
}
