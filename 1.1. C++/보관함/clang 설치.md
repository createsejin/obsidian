clang 설치 후 clang용 표준 라이브러리도 설치해야함

```bash
sudo apt install libc++-dev
sudo apt install libc++abi-dev # 이게 있어야 링킹이 문제 없이 됨
```

```cmake
cmake_minimum_required(VERSION 3.0.0)

project(CppStudy2 VERSION 0.1.0 LANGUAGES C CXX)

  

include(CTest)

enable_testing()

  

add_executable(CppStudy2 main.cpp)

  

set(CMAKE_CXX_COMPILER "clang++")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -stdlib=libc++ -fmodules -fbuiltin-module-map") 
# 이 옵션이 있어야 module이 사용 가능하다.

  

set(CPACK_PROJECT_NAME ${PROJECT_NAME})

set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

target_link_libraries(CppStudy2 PRIVATE c++ c++abi)
# 이게 있어야 링킹이 제대로 된다.

include(CPack)
```
하지만 나는 모듈을 쓰지 않기로 하였다. 아직 모듈을 완벽하게 지원하는 IDE가 전무하기 때문이다. 특히 리눅스에서는 더더욱 쓰기 어려웠다. 
솔직히 헤더 인클루드를 쓴다고 해서 손해볼건 실행파일의 용량과 컴파일 시간 정도인데.. 아주 초 대규모의 프로젝트를 한다면 모를까. 나의 자작 프로젝트에서는 아무런 영향이 거의 미미하다고 평가된다. 아마도 내년이나 내후년에 vscode의 C++ 인텔리센스가 모듈을 지원하고, clang등에서도 모듈을 완벽하게 공식 지원하면 그때 사용해봐도 늦지 않다고 생각된다.