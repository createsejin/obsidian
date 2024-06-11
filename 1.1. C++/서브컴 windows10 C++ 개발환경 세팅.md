뭐 기본적으로는 Git, vcpkg, Jet brain toolbox, Clion Nova, Cmake, Ninja build, LLVM, Clang, Windows Terminal, Visual Studio 등등을 설치해줬다.

이번 개발 프로젝트는 매우 정확하게 작동하는 이미지 캡쳐 기반 매크로다. 

[[Interception 하드웨어 입력 지원 라이브러리|ineterception]] 이라는 하드웨어 입력을 지원하는 라이브러리를 설치하기 위해 [WDK](https://www.microsoft.com/en-us/download/details.aspx?id=11800)와 visual studio에서 windows 10, 11 SDK 를 설치해줬다.

그리고 CLion에서 몇가지 설정을 해줘야한다. 

일단 가장 중요한건 setting에서 Toolchains에서 + 한뒤 CMake 3.27.. 버전, build tool은 ninja, C compiler와 C++ compiler는 각각 clang.exe, clang++.exe, Debugger는 반드시 LLDB로 선택해줘야한다.

그리고 setting 검색창에 font 입력해줘서 Enable ligatures 체크해주면 ligature 폰트 적용되서 코드가 이뻐진다.

또한, Plugins에서 Github Copilot을 설치해주고 Github에 로그인하고 인증까지 완료하면 가장 중요한 Copilot을 쓸 수 있게 된다.


