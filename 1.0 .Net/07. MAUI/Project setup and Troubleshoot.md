
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

그런데 또 문제가 있었다. 이제 프로젝트 빌드도 되고 하는데.. 문제는 Debug나 Run에서 빌드는 성공적으로 아무 에러나 경고 없이 됐는데, 문제는 실제 프로그램이 실행되지 않고 <span style="color:#ffc000">계속 디버거만 돌아가는 문제</span>가 있었다.. 이것 역시 앞에서의 문제와 같은 argument 문제였다. 범인은 `-NoExit` argument였다.. 이걸 제거하자 이제야 VSCode에서도 MAUI가 실행되었다!! 하 ㅋㅋ 진짜 어이가 없다. 

아무튼 다행이다.. 아무리 그래도 Visual Studio 2022는 너무너무너무 불편하다..

아무튼 또한가지 주의할 점은 target과 Startup project를 VSCode의 status bar 오른쪽의 `{}`에서 정해주고 Debug를  Run해야한다는 것이다. 
처음 Debug할때에는 `Ctrl+Shift+G`로 Debug 창에 들어가면 'Run and Debug' 버튼이 보일것이다. 그 밑에 'Show all automatic debug configurations'를 눌러서 프로젝트의 이름에 따라 적절한 걸 선택해주면 된다.

또한 0xC0000374 에러가 발생해서 너무 난감한 상황이 있었다. Code 0xC0000374 is STATUS_HEAP_CORRUPTION (A heap has been corrupted.) 라는데.. 
이건 대체 왜 그러는건지 잘 모르겠다. 아마도 내 생각에는 너무 폴더가 깊숙한 장소에 들어가 있어서 파일 이름 길이 때문에 문제가 생긴것 같은데.. 왜냐면 폴더가 놓인 위치에 따라 좀더 상위의 폴더에서는 이 문제가 발생하지 않는다는 점이었다. 아무래도 C 드라이브는 길이 제한이 들어가기 때문에 이런 문제가 발생한걸로 보인다.

그래서 경로 길이 제한을 푸는 방법을 검색해서 시도해보았다. 결과는 왠지 성공적이다.
방법은 실행창을 `win + R`로 열어서 `gpedit.msc`을 실행 후, 컴퓨터 구성 -> 관리 템플릿 -> 시스템 -> 파일 시스템 에서 'Win32 긴 경로 사용'에 들어가서 '사용'을 선택하고 적용, 확인.