보통 `/vcpkg/packages/sqlite3_x64-linux/share/usage`처럼 CMake에 뭘 추가해라 이걸 알려준다. 
sqlite3에 경우에는 다음과 같았다.

```cmake
#sqlite3 provides pkgconfig bindings.
#sqlite3 provides CMake targets:

    find_package(unofficial-sqlite3 CONFIG REQUIRED)
    target_link_libraries(main PRIVATE unofficial::sqlite3::sqlite3)
```
뭐 이런식이다. 이걸 일단 프로젝트 루트 CMakeLists.txt 파일에 적용해주고,
추가적으로 하위 라이브러리 파일에서 써야할 경우 그곳에도 같이 적용해준다.

나는 이런식으로 적용시켰다.

프로젝트 루트 CMakeLists.txt : 
```cmake
set(CMAKE_TOOLCHAIN_FILE "/home/bae/vcpkg/scripts/buildsystems/vcpkg.cmake")
set(CMAKE_PREFIX_PATH "/home/bae/vcpkg/installed/x64-linux" ${CMAKE_PREFIX_PATH})  
cmake_minimum_required(VERSION 3.0.0)
project(CppStudy VERSION 0.1.0 LANGUAGES C CXX) 

include(CTest)
enable_testing() 
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -stdlib=libc++ -fmodules -fbuiltin-module-map") 

find_package(fmt CONFIG REQUIRED)
find_package(Microsoft.GSL CONFIG REQUIRED)
# 이 부분
find_package(unofficial-sqlite3 CONFIG REQUIRED) 

add_executable(CppStudy main.cpp)
#add_compile_options(-fmodules-ts)
#add_compile_options("-fmodule-file=/home/bae/Dropbox/Projects/CppStudy/gcm.cache/usr/include/c++/11/iostream.gcm")
target_include_directories(CppStudy PUBLIC "${PROJECT_BINARY_DIR}")
add_subdirectory(Study)
add_library(cpp_study_compiler_flags INTERFACE)
target_compile_features(cpp_study_compiler_flags INTERFACE cxx_std_20)  
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)
target_link_libraries(${PROJECT_NAME} PRIVATE Microsoft.GSL::GSL)
# 요기
target_link_libraries(${PROJECT_NAME} PRIVATE unofficial::sqlite3::sqlite3)
target_link_libraries(CppStudy PUBLIC Study cpp_study_compiler_flags)
include(CPack)
```
그런다음 서브 다이렉토리 : 
```cmake
#add_library(EmployeeModule OBJECT employee.ixx)
#target_link_libraries(EmployeeModule PUBLIC cpp_study_compiler_flags)

add_library(Study study001.cpp study001.h)
add_library(Employee internal/employee_s.cpp internal/employee_s.h)
add_library(AirlineTicket STATIC internal/airline_ticket.cpp internal/airline_ticket.h)
add_library(AirlineTicket_const STATIC internal/airline_ticket_const.cpp internal/airline_ticket_const.h)
#add_dependencies(Study EmployeeModule)
target_include_directories(Study
INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Study PUBLIC cpp_study_compiler_flags)
target_link_libraries(Study PRIVATE fmt::fmt)
target_link_libraries(Study PRIVATE Microsoft.GSL::GSL)
# 여기
target_link_libraries(Study PRIVATE unofficial::sqlite3::sqlite3)
target_link_libraries(Study PRIVATE AirlineTicket)
target_link_libraries(Study PRIVATE AirlineTicket_const)
```
참고로 서브 다이렉토리에서는 `target_link_libraries(..)`만 적용시키면 된다.

#cmake #vcpkg #cpp 