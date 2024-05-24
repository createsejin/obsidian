VS Code나 Clion에 내장된 자동화된 cmake config generator를 사용하지 않고 순수하게 cmake cli만을 사용할때의 설정이다. 기본적으로 LLVM windows 버전이 깔려있어야한다. LLVM의 실행 바이너리들은 보통 `C:\Program Files\LLVM\bin`에 깔린다. 또한 이 설정을 실행하기 전에 Ninja build를 설치하고 PATH에 추가해야한다. 환경 변수 추가하는 방법은 알아서.. 별로 어렵지 않다.

```cmake
cmake_minimum_required(VERSION 3.28)
project(win_defender VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED)
set(CMAKE_C_COMPILER "C:/Program Files/LLVM/bin/clang.exe")
set(CMAKE_CXX_COMPILER "C:/Program Files/LLVM/bin/clang++.exe")
set(CMAKE_EXE_LINKER "C:/Program Files/LLVM/bin/lld-link.exe")

add_executable(win_defender main.cpp
)
```
대략 이런식으로 짜면 된다. 굉장히 간단하다. 주의할점은 
```cmake
set(CMAKE_C_COMPILER "C:/Program Files/LLVM/bin/clang.exe")
set(CMAKE_CXX_COMPILER "C:/Program Files/LLVM/bin/clang++.exe")
set(CMAKE_EXE_LINKER "C:/Program Files/LLVM/bin/lld-link.exe")
```
이 부분을 build시 명령어에서 `-DCMAKE_..=` 이 옵션에 추가하면 내부적으로 문제가 발생한다. 특히 경로를 나누어주는 seperator에서 문제가 발생하므로 반드시 이 옵션들은 그냥 `CMakeLists.txt`에 박아넣어야한다. 

명령어는 다음과 같이 해주면 된다.
`cd` 명령어 이후 첫번째 명령어는 script generate 명령어이며, 두번째는 target build 명령어이다.
```
cd build
cmake -G Ninja -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -D CMAKE_BUILD_TYPE=DEBUG ..
cmake --build .
```
