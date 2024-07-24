[[ln alias 관리자 권한으로 실행하기|이 방법]]으로는 문제점이, 순수 `pwsh.exe`프로그램으로 실행되다보니 좀 머슥한 점이 없지않아 있었다. 
오늘은 [[wt로 원하는 프로그램을 창을 분리해서 열자.|여기]]에서 한가지 교훈을 얻은것을 바탕으로 새로운 개선된 alias를 작성할 수 있었다. 그것은 바로 `wt`의 `-d` 옵션이다. 
이것은 `wt`가 실행될때 시작 디렉토리를 정해주는 옵션이다. 
개선된 alias는 다음과 같다.
```powershell
# make symbolic link command Alias: ln <link_name> <target>
function mk_sym_link([string]$target_path, [string]$link_name) {
  Start-Process -FilePath "wt" -Verb RunAs -ArgumentList "-d", "$pwd", "pwsh", "-NoExit", "-c", `
    "New-Item -ItemType SymbolicLink -Path `"$link_name`" -Target `"$target_path`""
}
Set-Alias -Name ln -Value mk_sym_link
```

아마도 `Start-Process`에서 `pwsh`을 통해서 두 개 이상의 명령어를 실행하는 방법은 역시 [[ln alias 관리자 권한으로 실행하기|기존 방법]]을 사용할 수 밖에 없는것 같다. 위 명령어처럼 wt 상에서 pwsh을 이용해서 두 개 이상의 명령어를 실행하는건 좀더 연구해볼 필요가 있을것 같다. 