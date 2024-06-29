Bash shell에서 `which <command>`를 하면 그 실행 파일의 주소를 알려준다. 이와 마찬가지로 powershell에서도 비슷한 명령어가 있다. 바로 `Get-Command` 명령어다.
```powershell
Get-Command -Name copy-config

CommandType     Name                                               Version    Source
-----------     ----                                               -------    ------
ExternalScript  copy-config.ps1                                               C:\Users\creat\mydoc\scripts\.pwsh\copy-…
```
이런식. 이걸 나중에 powershell profile에 `which`로 alias를 등록해주면 편할 것 같다.

```powershell
function which_func {
  param(
    [Parameter(Mandatory = $true)]
    [string]$command
  )
  Get-Command -Name $command
}
Set-Alias -Name which -Value which_func
```
[powershell profile](https://github.com/createsejin/mydoc/blob/main/win_configs/pwsh_profile/Microsoft.PowerShell_profile.ps1)에 이렇게 등록해줬다.