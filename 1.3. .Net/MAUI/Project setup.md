
```powershell
cd NamedProject
dotnet new maui
cd ..
dotnet sln add .\NamedProject\NamedProject.csproj
```

VSCode에서 프로젝트를 만들었지만 Android SDK에 대한 라이센스 동의 때문에 에러가 생겼었다.
그래서 직접 Android SDK 설치 폴더의 command line tool 폴더로 들어가서 라이센스 동의를 시도하려고 했으나, Java JDK 버전이 안맞아서 오류가 생겼었다.
[여기](https://www.oracle.com/kr/java/technologies/downloads/#java17)에서 Java 17 버전을 설치하고 환경변수까지 변경해줘야했다. 나같은 경우는 `Path` 최상단에 Java 11 버전이 등록되어 있어서 이것을 삭제하고 
환경 변수중 `JAVA_HOME`을 17버전으로 등록해줬다. 아무래도 Android SDK를 설치할때 자바 17버전이 기본적으로 설치 폴더안에 깔려있어서 그걸 가지고 설정해줬다.
위치는 `C:\Program Files (x86)\Android\openjdk\jdk-17.0.8.101-hotspot`이다.

이제 다음 명령어로 license에 동의할 수 있다. 모두 y를 입력해서 넘기면 된다.
```powershell
cd C:\Program Files (x86)\Android\android-sdk\cmdline-tools\11.0\bin
.\sdkmanager.bat --licenses
```

문제는 VSCode에서 MAUI extension task terminal에서 ParserError가 생겼었다는 것인데.. 이것 때문에 vscode github에 [[vscode extension issue|issue]]를 작성할뻔 했다. 그러나 작성하면서 왠지 뭐가 문제인지 하나씩 체크했는데, 결국 VSCode의 기본 powershell 설정에서 뭔가 에러가 생길만한 부분이 있었다. 그것은 바로 argument 설정이었는데.. 
이걸 수정하자 extension에서 Android licenses를 accept하는게 잘 해결 됐다. 

그런데 또 문제가 있었다. 이제 프로젝트 빌드도 되고 하는데.. 문제는 Debug나 Run에서 빌드는 성공적으로 아무 에러나 경고 없이 됐는데, 문제는 실제 프로그램이 실행되지 않고 계속 디버거만 돌아가는 문제가 있었다.. 이것 역시 앞에서의 문제와 같은 argument 문제였다. 범인은 `-NoExit` argument였다.. 이걸 제거하자 이제야 VSCode에서도 MAUI가 실행되었다!! 하 ㅋㅋ 진짜 어이가 없다. 

아무튼 다행이다.. 아무리 그래도 Visual Studio 2022는 너무너무너무 불편하고 지읒같다. 시벌. 진짜 잠깐만 써도 발암 그자체. VSCode가 훠어어얼씬 편하고 이쁘다. 하..