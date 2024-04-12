2023-11-09
- CMake 3.26
- CLion 2023.2
- LLVM 17.0.4
- ninja build 1.11.1
- git for winodws 2.42.0.2
- vcpkg 
를 설치했다.

자꾸 vcpkg 오류가 떴는데, 아마도 드롭박스에서 파일을 제어하기 때문에 CLion과 서로 충돌이 일어난것으로 추정됐다. 따라서 vcpkg는 그냥 드롭박스가 아닌 로컬 home 폴더에 위치시켰다. 
또한 다음의 CMake 코드를 통해 windows와 linux에서 자동으로 vcpkg toolchain 파일을 제대로 인식시키게 설정[^1]하였다.
```cmake
message(STATUS "CMAKE_SYSTEM_NAME: ${CMAKE_HOST_SYSTEM_NAME}")
if (CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
    set(CMAKE_TOOLCHAIN_FILE "C:/Users/creat/Dropbox/Projects/vcpkg_win/scripts/buildsystems/vcpkg.cmake")
elseif (CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
    set(CMAKE_TOOLCHAIN_FILE "/home/bae/.vcpkg-clion/vcpkg/scripts/buildsystems/vcpkg.cmake")
    set(CMAKE_PREFIX_PATH "/home/bae/.vcpkg-clion/vcpkg/installed/x64-linux" ${CMAKE_PREFIX_PATH})
endif ()
```
[^1]: 사실은 이 옵션은 그닥 필요가 없다. Clion을 통해 제대로 vcpkg를 cmake profile에 intergration 했다면 말이다.