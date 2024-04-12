먼저 yum을 이용해서 기본 clang을 설치해줘야한다. 
`sudo yum install clang`

당연히 미리 [[Cmake 설치|cmake]]를 설치해줘야한다. 또한 ninja가 필요하다. 

이 [문서](https://libcxx.llvm.org/BuildingLibcxx.html)를 참조하면 좋다.

우선 [여기](https://github.com/llvm/llvm-project/releases/tag/llvmorg-17.0.6)에서  `llvm-project-17.0.6.src.tar.xz`를 다운 받는다.
`tar -xvf llvm-project-17.0.6.src.tar.xz`으로 압축을 푼다.

그리고 llvm project source code 폴더로 들어가서 우선 build 폴더를 만든다.
```
mkdir build
cd ..
```
그리고 다음 명령어를 실행한다.
```
cmake -S runtimes -B build -G Ninja -DLLVM_ENABLE_RUNTIMES="libcxx;libcxxabi;libunwind" \
-DCMAKE_INSTALL_PREFIX=/usr/local \
-DCMAKE_C_COMPILER=/usr/local/bin/clang -DCMAKE_CXX_COMPILER=/usr/local/bin/clang++
```
정상적으로 됐으면 다음 명령어를 통해 ninja build를 한다.
```
ninja -C build cxx cxxabi unwind
```
여담이지만 LLVM 프로젝트 소스 코드는 반드시 clang으로 빌드하는게 무조건 옳다. gcc로 빌드하면 에러가 생기니 앞선 cmake 명령어에서 반드시 C/C++ 컴파일러를 clang으로 설정해주자.

다음은 설치 명령어인데, 문제는 `sudo ninja`를 하면 ninja 커맨드를 인식하지 못한다. 그래서 우선 현재 사용자를 root 사용자로 바꾸자.
`sudo su`
그러면 쉘이 `$`에서 `#`으로 바뀐다. 근데 이때 환경 변수가 root 사용자의 환경변수가 되므로 ninja를 현재 세션 환경변수에 추가해주어야한다.
`export PATH=$PATH:/usr/local/bin`
ninja가 들어있는 위치를 이렇게 추가해준 뒤에 다음 명령어를 통해 설치 할 수 있다.
`ninja -C build install-cxx install-cxxabi install-unwind`

## 중요사항
참고로 위 명령어에서는 RHEL9에서 기본 제공하는 clang이 16버전으로 컴파일 한 것이다. 그러나 이렇게 하면 실제로 LLVM 17.0.6 버전에서 이 라이브러리를 사용하는 경우에 에러가 반드시 생긴다. 따라서 먼저 clang 17 버전을 제대로 설치한 다음에 다시 libc++을 clang 17버전으로 재 컴파일해서 다시 설치하기 바란다. 꼭!


#redhat, #cmake, #llvm