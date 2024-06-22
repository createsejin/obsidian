아마도 반디집을 설치하면 기본적으로 `C:/Program Files/Bandizip` 위치가 시스템 환경 변수에 등록되는것으로 보인다.
여기에는 커맨드라인 툴 `bz.exe`가 있는데, 이것을 사용하면 Console 환경에서 반디집을 사용할 수 있게된다.

나는 다음과 같이 powershell `$profile`에 함수와 Alias를 만들어서 사용하고 있다.
```powershell
# unzip compressed archive by bandizip
function band_unzip {
  param(
    [Parameter(Mandatory = $true)]
    [string]$archive,
    [string]$target_dir
  )
  $bz = "C:\Program Files\Bandizip\bz.exe"

  if (-not (Test-Path $archive)) {
    Write-Output "Error: Archive file '$archive' does not exist."
    return
  }

  if ($target_dir -eq "") {
    Write-Output "Target directory not specified, extracting to current directory."
    Start-Process -FilePath "$bz" -Wait -NoNewWindow -WorkingDirectory (Get-Location).Path `
      -ArgumentList "x -aos -y -cp:65001 -target:name -consolemode:utf8 `"$archive`""
    return
  }
  elseif (($target_dir -ne $null) -and -not (Test-Path $target_dir)) {
    Write-Output "Target directory '$target_dir' does not exist. Creating..."
    New-Item -ItemType Directory -Path $target_dir -Force | Out-Null
  }
  elseif (($target_dir -ne $null) -and (Test-Path $target_dir)) {
    Write-Output "Archive extracting to `"$target_dir`""
  }
  Start-Process -FilePath "$bz" -Wait -NoNewWindow -WorkingDirectory (Get-Location).Path `
    -ArgumentList "x -aos -o:`"$target_dir`" -y -cp:65001 -consolemode:utf8 `"$archive`""
}
Set-Alias -Name ban -Value band_unzip
```

사용 방법은 다음과 같다.
```powershell
ban <archive_file> # archive file 이름을 하위 폴더로 압축 해제
ban <archive_file> <target_dir> # target_dir에 압축 해제. 만약 target_dir이 존재하지 않으면 폴더를 만든다.
```
