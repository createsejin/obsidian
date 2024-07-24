일단은 관리자 powershell을 열어서 
```
cd C:\Program Files\WindowsApps
```
로 간다. 여기에서 `Microsoft.WindowsTerminal_1.20.11781.0_x64__8wekyb3d8bbwe` 과 같은 폴더를 찾는다. 이 안에서 
```
explorer .
```
또는 만약 [[powershell을 bash shell 처럼 커스텀하기|alias]]를 설정했다면 `ex`로 간단히 file explorer를 띄울 수 있다. 여기에서 `wt.exe`를 찾아서 바로가기를 만들어준다.
바로가기를 적당한 위치에 놓자. 나는 주로 `mydoc/scripts`에 넣어둔다. 이 바로가기를 우클릭해서 속성에 들어간다.
대상 input box에서 `\wt.exe" `부분에서 한칸 띄어쓰고 다음과 같이 작성한다. 이것은 [[wt로 원하는 프로그램을 창을 분리해서 열자.|이 방법]]을 활용한 `wt`의 [[wt 명령어 기본|명령어]]다.
```powershell
"C:\Program Files\WindowsApps\Microsoft.WindowsTerminal_1.20.11781.0_x64__8wekyb3d8bbwe\wt.exe" --fullscreen -d "%USERPROFILE%" ; sp -V -s .67 -d "%USERPROFILE%\mydoc" ; sp -V -d "%USERPROFILE%\Projects" ; mf left
```
주의할점은 windows의 바로가기는 cmd 기반이기 때문에 [[wt로 원하는 프로그램을 창을 분리해서 열자.|powershell 스타일]]로 명령어를 구성하면 안된다. 특히 `$home`같은 powershell용 환경변수는 여기서 허용되지 않는다. 따라서 cmd 스타일로 home folder는 `%USERPROFILE%` 변수를 사용해야한다.
뭐 `pwsh -c`로 powershell을 이용해서 띄우는 방법도 있지만 어쨌거나 이렇게 하는게 더 간단하고 직관적이기 때문에 그냥 이렇게 하자. 그 후 이 바로가기를 작업표시줄이나 원하는곳에 등록해주면 된다.

위 명령어를 한번 풀어보자면,
첫번째로 `--fullscreen`을 통해 화면을 전체 화면 모드로 시작하며, `-d` 옵션은 시작 디렉토리다. 
`;`로 구분되는 두번째 명령은 현재 화면을 `sp -V -s .67`을 이용해서 현재 패널에서 67퍼센트에 해당되는 화면을 vertical로 split 한다는 뜻이다. `-d`를 이용해서 `mydoc` 위치를 열고 있다. 
그 다음 명령어도 역시 vertical split이다. 
마지막 명령어는 `mf left`인데, `move-focus` 명령의 단축 명령어다. 말 그대로 현재 포커스를 왼쪽으로 한번 옮겨준다. 

이런식으로 `wt` 커맨드 라인을 이용해서 `wt` 시작을 내가 원하는데로 커스텀할 수 있다. 아주 편리한 기능이다.