batch script는 기본적으로 windows의 `cmd`환경에서 동작한다. 흔히 windows 명령 프롬프트라고 부르는 shell 프로그램이다. 즉, batch script는 `cmd` 명령어를 기반으로 동작하는 shell script다. 
따라서 powershell의 명령어를 사용하려면 script 명령어 앞에 `powershell -command `를 붙여줘야 powershell 명령어가 제대로 실행된다. 
또한 경로상에 한글이나 다른 유니코드 문자가 포함되어있는 Path를 script에서 사용해야한다면 반드시 script 맨 위에
`chcp 65001 > nul`을 추가해야만 제대로 동작한다. 이걸 안하면 유니코드 문자가 깨져서 script를 실행하면 위치를 지정할 수 없다고 에러가 발생한다. 영문으로된 Path는 이 설정이 필요가 없으나, 유니코드 path가 있을 수 있으므로 이 명령으로 쉘의 동작 환경을 UTF-8로 만들어주는게 좋다. 
또한 `cmd`환경이기 때문에 다른 디스크로 이동할때에는  `pushd` 명령어를 사용해야한다. 

대부분은 첫머리에 다음과 같이 쓴다.
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
    %VERACRYPT% /quit /silent /auto /v \Device\Harddisk1\Partition2 /letter P /keyfile "M:\Keyfiles\diskP02" /tryemptypass /cache no ..skip

endlocal
```
이것은 pack.bat [[batch script로 veracrypt CLI로 마운트 하기|스크립트]]의 일부분이다.

local 변수는 `setlocal`과 `endlocal` 사이에 위치해야하며, `set VARIABLE="values"`와 같이 정의할 수 있다.
사용은 `%VARIABLE%`처럼 사용하면 된다.

또한, batch script는 if문에서 `&&`나 `||`연산자를 지원하지 않는다. 대신 AND 조건은
`if "%1" == "-m" "%2" == "k"`이런식으로 띄어쓰기만 해서 같이 쓰면 된다.
OR 연산자는 직접 `if`와 `else if`를 이용해서 구현을 해야한다.