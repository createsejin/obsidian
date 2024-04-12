```cpp
import <iostream>  
  
int main() {  
    std::cout << "Hello, World!" << std::endl;  
    return 0;  
}
```

```cmake
cmake_minimum_required(VERSION 3.26)  
project(CppStudy3)  
  
set(CMAKE_CXX_STANDARD 20)  
set(CMAKE_CXX_COMPILER "clang++")  
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -stdlib=libc++ -fmodules -fbuiltin-module-map")  
  
add_executable(CppStudy3 main.cpp  
        employee.ixx)  
target_link_libraries(CppStudy3 PRIVATE c++ c++abi)
```

```terminal
Hello, World!
```

기본적으로 cmake 프로젝트를 만들면 알아서 잘 만들어준다.
C/C++ Compiler는 clang/clang++로 설정해주었고,

기존에 깔아뒀던 vcpkg인 /home/bae/vcpkg를 여기에 추가시켜야하는데..
CLion 메뉴에서 View > Tool Winodws > Vcpkg를 들어가면 vcpkg를 추가할 수 있는데, 창이 뜨면 +를 누른다.
적당히 설치된 경로를 넣어주고 추가해주면 되고,

![[Pasted image 20231026135336.png|400]]
이런식으로 Add vcpkg integration to existing CMake Profiles에 체크해주면 알아서 CMake에 추가해준다[^1].

```cpp
#include <iostream>  
#include "fmt/core.h"  
  
int main() {  
    std::cout << "Hello, World!" << std::endl;  
    return 0;  
}
```
그 다음에 이런식으로 ``#include "fmt/core.h" `` 해주면 됨.

```cmake
cmake_minimum_required(VERSION 3.26)  
set(CMAKE_TOOLCHAIN_FILE "/home/bae/vcpkg/scripts/buildsystems/vcpkg.cmake")  
  
project(CppStudy2)  
  
set(CMAKE_CXX_STANDARD 20)  
find_package(fmt CONFIG REQUIRED)  
add_executable(CppStudy2 main.cpp)  
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)
```
이런식으로 tool chain 부분을 추가하면 된다.

만약 fmt를 쓸거면 find_pakage에 fmt 저런식으로 추가해주고,
target link libraries로 타겟 프로젝트에 링크하면 된다.

하위 라이브러리에 fmt 추가하는법은.. 추후에 다룬다..

아니 그런데 이거 CLion 너무너무 좋긴한데.. 한달에 13000원은 쫌.. 하.. 쓰읍.. 

결국에는 그냥 다시 VS code로 코드를 옮겼고, 어차피 cmake project라 그냥 대충 옮기기만 하면 다시 작동한다. ㅋㅋ C++ 공부하는데 IDE에만 한달에 9.9달러 쓰는건 레알 개 오바지. dropbox도 비싸 죽겠는데 ㅋㅋ 


[^1]: 이것이 주석이다.