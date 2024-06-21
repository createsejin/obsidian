powershell에서는 `Resolve-Path`를 통해 이 기능을 수행할 수 있다.
`code $profile`을 열고 다음을 추가한다.
```powershell
Set-Alias -Name path -Value Resolve-Path
function Resolve-RelativePath {
  param(
    [Parameter(Mandatory = $true, Position = 0)]
    [string]$Path
  )
  Resolve-Path -Path $Path -Relative
}
Set-Alias -Name rpath -Value Resolve-RelativePath
```
이것을 다음과 같이 사용한다.
```powershell
path <path>
rpath <absolute path>
```
`path`는 절대경로(absolute-path)를 얻고, `rpath`는 현재 위치에 대한 입력된 절대 경로의 상대 경로(relative-path)를 얻는다.