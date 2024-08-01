libarchive 라이브러리는 zip, rar 등을 압축 해제 하거나 압축하는데 쓰이는 C 라이브러리다. 나같은 경우는 [[the_cave Operator class relationship.canvas|the_cave project]]를 위해서 설치했는데, 설치 과정을 정리해보겠다. 

우선 [github release page](https://github.com/libarchive/libarchive/releases)에서 source code를 다운받는다. 나는 내 home 폴더의 librarys 폴더에 담았다. 압축을 해제한다.

CMake가 있어야한다. CMake GUI를 실행한다. source code에 라이브러리 루트를 지정하고, 
build the binaries에 라이브러리 루트 안에 있는 build 폴더를 지정해주고 
Configure를 누르면 Generator를 선택하는 창이 뜨는데, Visual Studio 17 2022를 선택하고 Configure 작업을 실행한다. 
모두 완료가 되면 그 옆에 Generate를 누른뒤 
그 옆에 Open Project를 눌러서 VS2022로 프로젝트를 연다. 
그리고 솔루션 창에서 `ALL_BUILD`를 우클릭하고 build를 한다. 
`RUN_TESTS`도 build를 눌러서 테스트를 진행해준다. 모두 문제없이 되어야한다. 

참고로 VS2022에서 빌드 모드를 선택할 수 있는 도구창이 있는데, 디버그 플레이 버튼 왼쪽에 위치해있다. 이걸 Release로 바꾼뒤 `ALL_BUILD`를 build하는걸 추천한다. 

이렇게 빌드가 완료되면, `build/libarchive/Release`에 `archive.lib`, `archive_static.lib` 파일이 생긴다. 이것이 우리가 필요한 파일이다. 
그런데 만약 동적 라이브러리를 사용할거면, `build/bin/Release`에 있는 `archive.dll`을 내 프로젝트에 추가해주면 되는데, 아마도 `zlib.dll`도 필요한 모양이다.
일단은 헤더파일도 필요하다. `libarchive-3.7.4\libarchive`에 있다. 그러니까 총 3가지 파일 및 폴더가 필요하다. 
먼저 헤더파일들이 있는 `libarchive-3.7.4\libarchive` 폴더, `archive.dll` 파일, `archive.lib` 파일이 필요하다. 
기본적으로 [[dll 라이브러리 사용하기|이 방법]]을 사용해야한다. 

우선 solution에서 Alt + Enter를 눌러서 Properties Pages에 들어간다. C/C++ -> General -> Additional Include Directories에 헤더파일이 있는 위치
`C:\Users\creat\librarys\libarchive\libarchive-3.7.4\libarchive` 를 추가해준다.

그리고 다시 Properties Pages에서 Linker -> Input -> Additional Dependencies -> Edit `archive.lib`를 추가해준다.
Linker -> General -> Additional Library Diretories에 위에서 추가한 .lib 파일이 있는 위치
`C:\Users\creat\librarys\libarchive\libarchive-3.7.4\build\libarchive\Release`를 추가해준다. 

마지막으로 빌드 후 dll을 복사하는 명령을 추가해야한다.
Build Events -> Post-Build Event -> Command Line
```
xcopy /y /d "C:\Users\creat\librarys\libarchive\libarchive-3.7.4\build\bin\Release\archive.dll" "$(OutDir)"
```