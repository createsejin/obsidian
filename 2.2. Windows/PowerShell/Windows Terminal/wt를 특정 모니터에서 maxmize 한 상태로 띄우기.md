현재 화면을 PrintScreen으로 찍은 후 그림판을 열어서 빨간색 연필 도구를 선택하여 띄우고 싶은 화면의 왼쪽 위 가장자리를 확대해서 그곳의 좌표를 알아낸다.
나는 오른쪽 모니터의 왼쪽 위 코너 좌료를 얻으니 5360, 0 이었다. 
이 좌표를 다음과 같이 `--pos` 옵션에 설정해준다.
```powershell
  wt --pos 5360,0 --maximized -p "PowerShell" -d "$downloader_path" pwsh -NoExit -c "$downloader" `; `
    sp -V -d "$commander_path" pwsh -NoExit -c "$commander"
```
이렇게 하면 원하는 모니터에서 wt를 띄울 수 있다. 
이 명령어는 [[wt로 원하는 프로그램을 창을 분리해서 열자.|여기]] 글에서 나온다.