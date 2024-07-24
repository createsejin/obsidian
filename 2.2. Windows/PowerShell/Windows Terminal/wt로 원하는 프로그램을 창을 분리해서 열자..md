```powershell
$commander_path = "C:\Users\creat\Projects\the_cave\downloader\Commander\bin\Debug\net8.0"
$commander = "$commander_path\Commander.exe"
$downloader_path = "C:\Users\creat\Projects\the_cave\downloader\Downloader\bin\Debug\net8.0"
$downloader = "$downloader_path\Downloader.exe"

if ($args[0] -eq "cmd") {
  Start-Process -FilePath $commander
} elseif ($args[0] -eq "ctrl") {
  Start-Process -FilePath $downloader
} else {
  wt --maximized -p "PowerShell" -d "$downloader_path" pwsh -NoExit -c "$downloader" `; `
    sp -V -d "$commander_path" pwsh -NoExit -c "$commander"
}
```
마지막 명령어를 주목하자. powershell script에서는 [[wt 명령어 기본|wt 명령어]]를 통해 여러 창을 여는 동작을 구분할때 반드시 백틱과 세미콜론을 붙여서(`` `; ``) 표현해주어야한다. 안그러면 이게 그냥 일반적인 powershell 명령어 구분자로 powershell이 해석하기 때문에 문제가 발생한다. powershell에서 백틱은 일종의 [[powershell script 따옴표 안 따옴표|이스케이프 시퀀스]]로 쓰이기 때문이다. 

옵션을 하나씩 보자면, 첫번째 명령어는 일단 split이나 new-tab 없이 새로운 창을 실행하도록 하고 있고, 
`--maximaized`는 새 창을 열때 윈도우를 최대화 상태로 연다. 
`-p "PowerShell"`은 shell profile을 어떤것으로 선택하는지인데,  이것은 설정창에 가보면 그 이름들을 알 수 있다. 
`-d "path"`는 wt가 실행할 시작주소다.
`pwsh -NoExit -c "$downloader"` powershell로 `-c`를 통해 실행할 커맨드를 지정하고, `-NoExit`로 명령 실행 후 창을 닫지 않는다. 그리고 이어지는 `` `; ` ``를 이용해서 wt의 두번째 명령어를 구분한다. 마지막 백틱은 powershell의 [[명령줄 개행|개행 방법]]이다.
`sp -V` 는 현재 창에서 패널을 vertical로 분리하는 명령어다. 
그 후 다시 `pwsh -NoExit -c ..`을 통해서 새로운 프로그램을 실행하고 있다.
