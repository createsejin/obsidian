마소의 이 [글](https://learn.microsoft.com/en-us/windows/terminal/tutorials/custom-prompt-setup)을 참조하자.

우선 Nerd Font를 다운로드 받아야한다. [여기](https://www.nerdfonts.com/font-downloads)에서 받자. 
폰트를 설치 후에, Windows Terminal을 열고 
setting(`Ctrl+,`) -> PowerShell -> 모양 -> 글꼴에서 다운받은 Nerd Font를 적용한다. 
보통 3가지가 나오는데 뒤에 `Mono` 혹은 `Propo`말고 그냥 기본 이름만 있는 버전을 선택하면 된다.
나는 `SauceCodePro Nerd Font`를 선택했다.

```
winget install JanDeDobbeleer.OhMyPosh
```
이걸로 설치할 수 있다. 설치 후 `oh-my-posh version`로 잘 설치됐는지 확인하자. `winget upgrade oh-my-posh`으로 업그레이드를 할 수 있다.

```
code $PROFILE
```
로 `C:/Users/creat/OneDrive/문서/PowerShell/Microsoft.PowerShell_profile.ps1` 을 열어서 다음을 적어놓는다.
```
oh-my-posh init pwsh --config "$env:POSH_THEMES_PATH\catppuccin_frappe.omp.json" | Invoke-Expression
```
`catppuccin_frappe.omp.json` 이 부분에서 `catppuccin_frappe` 이게 테마의 이름이다. 
테마는 [이곳](https://ohmyposh.dev/docs/themes)을 참조하자.

그리고 다시 PowerShell을 연다. 프롬프트가 적용이 된걸 확인하자.