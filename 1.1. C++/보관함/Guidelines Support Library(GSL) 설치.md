[공식 Github 설치 가이드](https://github.com/microsoft/GSL#user-content-fn-2-d28e879bc3a07df3a4136841af39f747)

근데 그냥 vcpkg로 설치해버렸따.. ㅋㅋ 너무나도 귀찮아서 말이지.

어차피 버전 4.0.0 최신버전으로 있고 ㅋㅋ 그게 편했다.

간단히 프로젝트 최상단 Cmake 파일에 

```cmake 
find_package(Microsoft.GSL CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Microsoft.GSL::GSL)
```
해주고, 하위 폴더에도 target_link를 해주었다.

```cmake
target_link_libraries(Study PRIVATE Microsoft.GSL::GSL)
```
그리고 사용법은

```cpp
#include <gsl/gsl>

int i2 = gsl::narrow_cast<int>(3.14);
cout << format("i2 = {}", i2) << endl;
```

요런식이었다.

#cpp #vcpkg