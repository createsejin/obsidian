protobuf던 Abseil이던 그냥 라이브러리다. 물론 이걸 동적 라이브러리로 컴파일해서 사용하는 방법도 있겠지만, 여기에서는 헤더파일 기반의 라이브러리를 사용하는 기본적인 방법을 서술한다.

[여기](https://github.com/abseil/abseil-cpp)에서 릴리즈 페이지에 들어가서 Abseil 소스코드를 다운로드받아 적당한 위치에 푼다.
마찬가지로 protobuf도 [여기](https://github.com/protocolbuffers/protobuf)에 들어가서 릴리즈 페이지에서 소스코드를 다운받아 적당한 위치에 푼다.

먼저 Abseil의 폴더 구조를 보면 project root에 `absl`이라는 폴더가 보일것이다. 이것이 바로 우리가 필요한 헤더이고, 이 폴더를 포함하고 있는 root diretory를 Cmake에 추가해주면 된다.

역시 protobuf도 마찬가지다. 이것의 프로젝트 폴더에는 src라는 폴더가 있다. 이 안에 우리가 필요한 google로 시작되는 헤더들이 있다.
이걸 역시 Cmake에 추가해주면 된다.
```cmake
...skip

set(ABSEIL_CPP_DIR "C:/Users/creat/librarys/Abseil/abseil-cpp")
set(PROTOBUF_SRC_DIR "C:/Users/creat/librarys/protobuf-27.1/src")

add_executable(collections main.cpp
	...skip
)

# Abseil 및 Protobuf include 디렉토리 추가
target_include_directories(collections PRIVATE ${ABSEIL_CPP_DIR} ${PROTOBUF_SRC_DIR})
```
이런식으로 해주면 cmake가 알아서 해당 헤더들을 프로젝트에 포함해주고 링크해준다.

그렇지만 이 방법에도 ==문제는 있었다..== 
아마도 clang 컴파일러 혹은 submodule 때문인 것으로 보인다.

이 [[gRPC 설치 - Cpp|글]]에서 Windows 환경에 대한 설치 및 사용 방법이 적혀져있다. Windows에서는 이 방법이 유일하게 현재로써 먹힌다.