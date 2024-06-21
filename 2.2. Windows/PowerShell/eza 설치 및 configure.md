```
winget install eza-community.eza
```
로 간단히 설치할 수 있다.

`code $PROFILE`을 통해 profile 파일을 열고 다음을 추가한다.
```powershell
function ls_func {
  eza --color=always --long --git --no-filesize --icons=always --no-time --no-user --no-permissions @args
}
Set-Alias -Name ls -Value ls_func
function l_func {
  eza -A --long --color=always --icons=always --git @args
}
Set-Alias -Name l -Value l_func
```
