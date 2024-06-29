```powershell
winget install ajeetdsouza.zoxide
```
설치 후,
```powershell
code $PROFILE
```
`$profile` 파일을 열어서 
```powershell
Invoke-Expression (& { (zoxide init powershell | Out-String) })
Remove-Alias -Name cd
Set-Alias -Name cd -Value z
```
이렇게 추가해준다.