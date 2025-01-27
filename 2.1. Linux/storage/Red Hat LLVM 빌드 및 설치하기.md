우선 이 [문서](https://llvm.org/docs/GettingStarted.html#getting-the-source-code-and-building-llvm)를 참고하자.

필요한 준비물은 clang 컴파일러, [[Cmake 설치|cmake]], ninja, [[Red Hat에서 libc++ 빌드 및 설치|libc++]], lld 정도
clang은 우선 yum에서 16버전이라도 install 해놓는다. LLVM을 제대로 컴파일 하려면 반드시 gcc가 아닌 clang으로 컴파일해야한다. 또한 yum을 통해 lld도 받아놓는다.

그리고 [여기](https://github.com/llvm/llvm-project/releases/tag/llvmorg-17.0.6)에서 project source code를 다운 받는다. `llvm-17.0.6.src.tar.xz`이걸 받으면 된다.
압축을 풀고 프로젝트 루트 폴더로 cd한다.

우선 cmake 정책을 OLD에서 NEW로 수정해야한다.
`nano cmake/Modules/CMakePolicy.cmake`에서 OLD를 NEW로 전부 바꿔준다.

그리고 다시 프로젝트 루트로 돌아가서 다음 명령어를 통해 cmake build 해준다.
```
cmake -S llvm -B build -G Ninja \
-DLLVM_ENABLE_PROJECTS="clang;clang-tools-extra;lld;lldb" \
-DCMAKE_INSTALL_PREFIX=/usr/local \
-DCMAKE_BUILD_TYPE=release -DLLVM_ENABLE_ASSERTIONS=ON -DLLVM_USE_LINKER=lld \
-DCMAKE_EXPORT_COMPILE_COMMANDS=1 \
-DCMAKE_C_COMPILER=/usr/local/bin/clang -DCMAKE_CXX_COMPILER=/usr/local/bin/clang++
```
여기에서 설치될 위치를 지정해 줄 수 있다.

그리고 다음 명령을 통해 컴파일과 설치를 진행해주면 된다.
```bash
cmake --build build
```
이 명령어는 시간이 무척이나 오래 걸리기 때문에 그 동안에 간단히 차 한잔 마시고 오면 된다.

이제 설치 전에 반드시 `/usr/local`폴더를 [[리눅스 폴더 백업|백업]]해주자.

또한 첫 명령어 옵션에 의해 설치 위치 `/usr/local`에 설치하려면 sudo 권한이 필요한데, 문제는 `sudo cmake ..` 명령어를 쓰면 cmake 명령어가 없다고 나온다.

이럴 때에는 우선
`sudo su`를 통해 root 계정에 로그인 한뒤,
`export PATH="/opt/cmake-3.28.3-linux-x86_64/bin:$PATH"`를 통해 임시 환경 변수를 만들어준뒤
`cmake --install build`를 하면 설치가 완료된다.

`exit`해서 root에서 로그아웃하면 된다.

이제 아마도 clion을 위한 준비는 거의 끝났다. cmake, clang, lld, lldb, ninja, libc++ 등등 모든게 있으니.

#RHEL9 #linux #llvm