windows 용 veracrypt의 커맨드 라인 사용법은 [여기](https://veracrypt.fr/en/Command%20Line%20Usage.html)에 있으니 참고하자.
```
@echo off
setlocal
set VERACRYPT="C:\Program Files\VeraCrypt\VeraCrypt.exe"
if "%1" == "-k" (
  if "%2" == "rw" (
    %VERACRYPT% /quit /auto /volume "Pack009_2024-01-02_001.hc" /letter M /m rm /protectMemory /cache no
  ) else (
    %VERACRYPT% /quit /auto /volume "Pack009_2024-01-02_001.hc" /letter M /mountoption ro /m rm /protectMemory /cache no
  )
) else if "%1" == "-m" (
  if /i "%2" == "f" (
    %VERACRYPT% /quit /silent /auto /v \Device\Harddisk0\Partition2 /letter F /keyfile "M:\Keyfiles\diskF" /tryemptypass /cache no
  ) else if /i "%2" == "p" (
    %VERACRYPT% /quit /silent /auto /v \Device\Harddisk1\Partition2 /letter P /keyfile "M:\Keyfiles\diskP02" /tryemptypass /cache no
  ) else if /i "%2" == "s" (
    %VERACRYPT% /quit /silent /auto /v \Device\Harddisk2\Partition2 /letter S /keyfile "M:\Keyfiles\diskS" /tryemptypass /cache no
  ) else if /i "%2" == "q" (
    powershell -command "Get-Content 'M:\PnQ Key.txt' | Select-Object -Index 3 | Set-Clipboard"
    echo The passwd copied. After use this passwd, You should clear the clipboard: Using '.\pack.bat -c'.
  ) else if /i "%2" == "k" (
    if /i "%3" == "rw" (
      %VERACRYPT% /quit /auto /volume "Pack009_2024-01-02_001.hc" /letter M /m rm /protectMemory /cache no
    ) else (
      %VERACRYPT% /quit /auto /volume "Pack009_2024-01-02_001.hc" /letter M /mountoption ro /m rm /protectMemory /cache no
    )
  )
) else if "%1" == "-c" (
  echo off | clip
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
  echo .\pack.bat -k      : mount key capsule readonly mode
  echo .\pack.bat -k rw   : mount key capsule read and write mode
  echo.
  echo .\pack.bat -m k    : mount key capsule readonly mode
  echo .\pack.bat -m k rw : mount key capsule read and write mode
  echo.
  echo Before using following commands, You must mount key capsule.
  echo .\pack.bat -m f    : mount F volume
  echo .\pack.bat -m p    : mount P volume
  echo .\pack.bat -m s    : mount S volume
  echo .\pack.bat -m q    : Q volume passwd copy to clipboard
  echo.
  echo .\pack.bat -d      : dismount key capsule
  echo .\pack.bat -d f    : dismount F volume 
)
endlocal
```
주의할점은 이 스크립트와 pack 파일의 위치가 같아야한다. 
또한, `/volume` 옵션은 반드시 상대경로로 써야한다. 절대 경로로 쓰면 지정된 경로를 찾을 수 없다면서 오류가 뜬다. 이것 때문에 스크립트와 pack file들의 위치가 서로 같아야한다.

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
