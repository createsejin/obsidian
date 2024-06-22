windows 용 veracrypt의 커맨드 라인 사용법은 [여기](https://veracrypt.fr/en/Command%20Line%20Usage.html)에 있으니 참고하자.
```
@echo off
chcp 65001 > nul
pushd "G:\내 드라이브\1.창고\정보\Packs"
setlocal
set VERACRYPT="C:\Program Files\VeraCrypt\VeraCrypt.exe"
if "%1" == "-m" (
  if /i "%2" == "f" (
    %VERACRYPT% /quit /silent /auto /v \Device\Harddisk0\Partition2 /letter F /keyfile "M:\Keyfiles\diskF" /tryemptypass /cache no
  ) else if /i "%2" == "p" (
    %VERACRYPT% /quit /silent /auto /v \Device\Harddisk1\Partition2 /letter P /keyfile "M:\Keyfiles\diskP02" /tryemptypass /cache no
  ) else if /i "%2" == "s" (
    %VERACRYPT% /quit /silent /auto /v \Device\Harddisk2\Partition2 /letter S /keyfile "M:\Keyfiles\diskS" /tryemptypass /cache no
  ) else if /i "%2" == "q" (
    powershell -command "Get-Content 'M:\PnQ Key.txt' | Select-Object -Index 3 | Set-Clipboard"
    echo The Q disk password is copied.
    echo You should clean up the clipboard after using this: Using '.\pack.bat -c'.
  ) else if /i "%2" == "rw" (
    %VERACRYPT% /quit /auto /volume "Pack009_2024-01-02_001.hc" /letter M /m rm /protectMemory /cache no
  ) else (
    %VERACRYPT% /quit /auto /volume "Pack009_2024-01-02_001.hc" /letter M /mountoption ro /m rm /protectMemory /cache no
  )
) else if "%1" == "-c" (
  echo off | clip
  echo clipboard cleared.
) else if /i "%1" == "-k" (
  powershell -command "Get-Content 'M:\session3.txt' | Select-Object -Index 0 | Set-Clipboard"
  echo The KeePass password is copied.
  echo You should clean up the clipboard after using this: Using '.\pack.bat -c'.
) else if "%1" == "-d" (
  if /i "%2" == "f" (
    %VERACRYPT% /q /d F
  ) else if /i "%2" == "p" (
    %VERACRYPT% /q /d P
  ) else if /i "%2" == "s" (
    %VERACRYPT% /q /d S
  ) else if /i "%2" == "k" (
    %VERACRYPT% /q /d M
  ) else (
    %VERACRYPT% /q /d M
  )
) else ( Rem help messages
  echo .\pack.bat -m      : mount key capsule readonly mode
  echo .\pack.bat -m rw   : mount key capsule read and write mode
  echo.
  echo Before using following commands, You must mount key capsule.
  echo .\pack.bat -k      : copy KeePass passwd to clipboard
  echo .\pack.bat -m f    : mount F volume
  echo .\pack.bat -m p    : mount P volume
  echo .\pack.bat -m s    : mount S volume
  echo .\pack.bat -m q    : copy Q disk passwd to clipboard
  echo.
  echo .\pack.bat -d      : dismount key capsule
  echo .\pack.bat -d f    : dismount F volume 
)
endlocal
```
주의할점은 이 스크립트와 pack 파일의 위치가 같아야한다. 
또한, `/volume` 옵션은 반드시 상대경로로 써야한다. 절대 경로로 쓰면 지정된 경로를 찾을 수 없다면서 오류가 뜬다. 이것 때문에 스크립트와 pack file들의 위치가 서로 같아야한다.
-> 이 부분은 `C:/Users/creat/mydoc/scripts/.batch` 위치를 환경변수에 추가하고 이 위치에 batch script를 넣어서 맨 윗부분의 코드페이지를 바꾸는것과 `pushd` 명령어로 현재 working directory를 바꾸는 것으로 해결할 수 있다. 이렇게 하면 어떤 위치에서도 `pack.bat`을 이용해서 veracrypt 작업을 처리할 수 있게된다.

또한 여기에서 Q disk는 passwd를 클립보드에 저장하고 있는데, 
```
powershell -command "Get-Content 'M:\PnQ Key.txt' | Select-Object -Index 3 | Set-Clipboard"
```
이러한 명령어를 통해 구현하면 된다. 위 명령어는 `M:/PnQ Key.txt`  파일의 4번째줄(`-Index 3`)을 읽어서 클립보드에 저장한다.
```
) else if "%1" == "-c" (
  echo off | clip
```
이러한 명령어를 통해 클립보드를 비워주는 command를 추가할 수 있다.

사용은 아래처럼 하면 된다.
```
PS G:\내 드라이브\1.창고\정보\Packs> .\pack.bat -m
PS G:\내 드라이브\1.창고\정보\Packs> .\pack.bat -m s
PS G:\내 드라이브\1.창고\정보\Packs> .\pack.bat -m q
The passwd copied. After use this passwd, You should clear the clipboard: Using '.\pack.bat -c'.
PS G:\내 드라이브\1.창고\정보\Packs> .\pack.bat -c
clipboard cleared.
PS G:\내 드라이브\1.창고\정보\Packs> .\pack.bat -m f
PS G:\내 드라이브\1.창고\정보\Packs> .\pack.bat -m p
PS G:\내 드라이브\1.창고\정보\Packs> .\pack.bat -d
```
처음 `-m`만 쓰면 key capsule을 마운트하는것이고 마지막 `-d`만 쓰면 역시 key capsule을 dismount 하는 것이다. 나머지 S, F, P는 veracrypt disk volume들을 마운트하는것이고, 예외적으로 `q`는 veracrypt가 아닌, windows의 bit locker 암호를 클립보드에 붙여넣어서 Q disk를 해제한 후, `-c` 스위치로 클립보드를 clear 한다.
참고로 이 스크립트는 powershell이나 windows의 cmd shell 환경에서만 동작한다. 
```
.\pack.bat -k
```
이것은 KeePass passwd를 clipboard에 저장시킨다.

그러나 [[powershell veracrypt script|이 powershell script]]를 통해 훨씬 더 매끄럽고 readable하며 다양한 case를 handling한 script를 짤 수 있었다. 