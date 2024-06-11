아무래도 Clang으로 C++을 코딩할거면 Clang에서 쓰여진 표준 라이브러리를 쓰는게 더 낫다. 그러기 위해서 libc++을 설치하기 위해 여러가지 삽질을 또 했는데..

우선은 LLVM의 [소스코드](https://github.com/llvm/llvm-project/releases/tag/llvmorg-17.0.6)를 다운로드 받아서 풀어줬다. 
그 전에 우리가 참고한 문서는 [여기](https://libcxx.llvm.org/BuildingLibcxx.html)다. 여기 보면 The default build 부분을 따라해야하는데.. 문제는 이게 일반적인 방법으로 먹히지 않았다. 컴파일러 설정이 제대로 안된 것 같았다. 그래서 기본 명령어를 조금 뜯어고쳐야했다. 그리고 resource compiler라는 녀석을 지정해줘야해서 VS를 이용해서 windows SDK에서 rc.exe 컴파일러를 따왔다. 아래는 이런 모든 사항이 적용된 명령어다.
```
cmake -DCMAKE_RC_COMPILER="C:/Program Files (x86)/Windows Kits/10/bin/10.0.22621.0/arm64/rc.exe" -DCMAKE_C_COMPILER="C:/Program Files/LLVM/bin/clang.exe" -DCMAKE_CXX_COMPILER="C:/Program Files/LLVM/bin/clang++.exe" -G Ninja -S runtimes -B build -DLLVM_ENABLE_RUNTIMES="libcxx;libcxxabi;libunwind"
```
또한 그전에 llvm을 다시 설치하는 사태가 발생해서 llvm의 bin 폴더를 환경변수에 추가해줬다. 이렇게 하니까 CLion에서 발생한 configure 오류도 해결됐다. 

아무튼 우리 목표는 MSVC의 `C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.39.33519\include`의 표준 라이브러리를 쓰는게 아니라 LLVM에서 만들어진 clang용 표준 라이브러리를 사용하는 것이다.

다운 받은 LLVM 소스코드를 풀고 그 안으로 들어가서
```
cmake -DCMAKE_INSTALL_PREFIX="C:/Program Files/libcxx" -DCMAKE_RC_COMPILER="C:/Program Files (x86)/Windows Kits/10/bin/10.0.22621.0/arm64/rc.exe" -DCMAKE_C_COMPILER="C:/Program Files/LLVM/bin/clang.exe" -DCMAKE_CXX_COMPILER="C:/Program Files/LLVM/bin/clang++.exe" -G Ninja -S runtimes -B build -DCMAKE_BUILD_TYPE=Release -DLLVM_ENABLE_LIBCXX=ON -DLLVM_ENABLE_RUNTIMES="libcxx;libcxxabi"  
```
이 명령어를 실행해준다. 여기서 각 컴파일러는 현재 시스템 상황에 따라 다르다. 위 명령어에서 빠진건 libunwind인데, 얘까지 설치하면 ninja가 룰이 여러개라며 설치가 안됐다. 다시 시도해보자. 또한 설치 위치에 아마도 폴더가 미리 생성되 있어야하며, 이 경우 Program Files에 설치하므로 반드시 powershell을 관리자 권한으로 실행해야한다.

또한 중간에 테스트를 위해 python을 사용하기도 하니, 반드시 실행 전에 python을 설치해줘야한다. 당연히 path에는 추가해둬야한다.

다시 시도하기 위해 LLVM project 폴더에서 build 폴더 내부를 완전히 [[Remove-Item 명령어|삭제하는 명령어]]는 다음과 같다.
```
Remove-Item -Path .\build\* -Recurse -Force
```
## 씨발
개 빡친다. 아무래도 윈도우즈에서는 libc++은 기대하지 않는게 좋을 것 같다. 어차피 여기에는 windows.h도 없을테니 그냥 윈도우즈에서는 MSVC 표준 라이브러리를 사용해야할것 같다.. 
아무래도 모듈을 쓰려면 그냥 리눅스 시스템에서 쓰는게 가장 속 편한듯. 좆같다. 그냥 메인컴에다가 리눅스 깔아버릴까. 쓰발. 이번에는 아치 리눅스 써볼까 ㅋㅋ

# 그냥 libc++은 리눅스에서 clang이랑 같이 쓰면 된다. Windows? ㅗ ㅗ