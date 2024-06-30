[[mk symbolic link ln alias 설정|기존 방법]]으로는 관리자 권한이 아닌 쉘에서 실행할 경우 관리자 권한을 요구하는 경우가 있어서 좋은 방법은 아니였다. 
그래서 기본적으로 [[Start-Process 관리자 권한으로 실행하기|이 방법]]을 응용해서 다음과 같은 방식으로 alias function을 구현했다. 
```powershell
function mk_sym_link([string]$target_path, [string]$link_name) {
  Start-Process -FilePath "pwsh" -Verb RunAs -ArgumentList "-NoExit", `
    "-Command", "cd '$PWD'; New-Item -ItemType SymbolicLink -Path '$link_name' -Target '$target_path'"
}
Set-Alias -Name ln -Value mk_sym_link
```
일단은 `-ArgumentList`에 배열을 사용했는데 각각의 요소를 콤마로 구분하고 있다.
`-NoExit`는 쉘 명령이 끝난 후 쉘 창을 닫지 않는다. 조금 불편할 수 있지만 제대로 이게 실행됐는지 확인할때에는 이게 좋다.
나중에 불편하면 이 옵션은 빼도 될듯 하다.
`-Command` 뒤 매개 변수에서 첫번째 동작으로 `cd $PWD`를 한 뒤, 세미콜론을 이용해서 다음 명령인 link를 만드는 명령어를 실행해준다. 