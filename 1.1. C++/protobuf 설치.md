[여기](https://github.com/protocolbuffers/protobuf/releases/latest)에서 `protoc-$VERSION-win64.zip` 를 받는다.
적절한 위치에 압축을 풀고 내부의 `bin` 폴더 위치를 환경변수 `PATH`에 등록해준다.
이것은 windows용 바이너리로, 라이브러리 파일이 여기에는 없다.

따라서 vcpkg에서 protobuf를 따로 설치해주어 이것을 cmake에서 설정해야한다.
`vcpkg install protobuf protobuf:x64-windows`
또는 clion에서 vcpkg 항목에서 `protobuf`를 검색 후 Triplet을 `x64-windows`로 하고 설치해준다.
그리고 다음과 같이 `CMakeLists.txt`를 설정해준다.
```cmake
...skip
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_TOOLCHAIN_FILE C:/Users/creat/.vcpkg-clion/vcpkg3/scripts/buildsystems/vcpkg.cmake)
find_package(protobuf CONFIG REQUIRED)

add_executable(collections main.cpp
        tests/test001_file_analyse.cpp
        tests/test001_file_analyse.h
        tests/test002_protobuf.cpp
        tests/test002_protobuf.h
)

target_link_libraries(collections PRIVATE protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite)
```
순서를 유의해서 작성하기 바란다. find_package는 add_executable 보다 전에 와야하고, target_link_libraries는 그 후에 와야한다.
vcpkg toolchain file은 해당되는 vcpkg의 `vcpkg.cmake`가 있는 저 위치로 설정하면 된다. 자신의 Path에 맞게 설정해주자.
당연히 Project 이름 및 main target은 자신의 프로젝트에 맞게 설정해야한다. 위 경우는 project 이름이 `collections`다.

## .proto file compile by protoc
```
root/
├── main.cpp
└── tests/
    └── addressbook.proto
```
같은 구조로 만들었다면,
```
protoc -I=tests --cpp_out=. tests/addressbook.proto
```
이런식으로 컴파일 해주면 된다. 

그러면 protoc가 만든 파일들이 생성되는데 이 헤더 파일을 `#include`해서 사용하면 된다.
자세한 사용 방법은 이 [튜토리얼](https://protobuf.dev/getting-started/cpptutorial/)을 참고하자.