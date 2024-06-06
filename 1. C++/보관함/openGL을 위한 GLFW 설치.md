https://www.glfw.org/docs/3.3/compile.html#compile_deps_wayland
이 문서를 참고했다.

의존성 라이브러리들을 설치해줬다.
```
sudo dnf install libXcursor-devel libXi-devel libXinerama-devel libXrandr-devel
sudo dnf install wayland-devel libxkbcommon-devel wayland-protocols-devel extra-cmake-modules
```
다음은 cmake 명령어이다.
```
cmake -S . -B build -G Ninja -DLLVM_USE_LINKER=lld \
-D CMAKE_INSTALL_PREFIX=/usr/local \
-D CMAKE_C_COMPILER=/usr/bin/clang -D CMAKE_CXX_COMPILER=/usr/bin/clang++ \
-D GLFW_USE_WAYLAND=1

cmake --build build

sudo su
export PATH="/opt/cmake-3.28.3-linux-x86_64/bin:$PATH"
cmake --install build

exit
```
근데 문제는 clang으로 안되더라. 그래서 그냥 위에 의존성 라이브러리만 설치하고 CLion에서 vcpkg로 glfw3 설치해주고 
```cmake
cmake_minimum_required(VERSION 3.28)
project(cuda_test02 CUDA)

set(CMAKE_CUDA_STANDARD 20)
set(CMAKE_C_COMPILER "/usr/local/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/local/bin/clang++")
find_package(glfw3 CONFIG REQUIRED)


add_executable(cuda_test02 main.cu)

set_target_properties(cuda_test02 PROPERTIES
        CUDA_SEPARABLE_COMPILATION ON)
target_link_libraries(cuda_test02 PRIVATE glfw)
```
이런식으로 해주니까 됨. ㅋㅋ