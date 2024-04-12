https://www.wxwidgets.org/downloads/ 에서 Download Windows Binaries를 눌러서
맨 첫번째 version에서 Headers Files랑 그 밑에 64bit에서 Development Files랑
Release DLLs 를 모두 받아서 한 폴더에 압축을 unzip 해준다. 
나는 대충 `../project/wxWidget/3.24`에 풀어놓음. s가 빠졌는데 어쨌거나.
그 다음에 `wxWidget/3.24/lib/vc14x_x64_dll` 이 위치를 환경변수 Path에 새로 추가해주자.

그리고 다음과 같이 CMakeLists.txt를 수정해준다.
```cmake
cmake_minimum_required(VERSION 3.26)  
project(gta_c2)  
  
set(CMAKE_CXX_STANDARD 20)  
set(CMAKE_C_SOURCE_FILE_EXTENSIONS sqlite3.c)  

set(wxWidgets_CONFIGURATION mswu)  
set(wxWidgets_ROOT_DIR C:/Users/creat/Projects/wxWidget/3.2.4)  
SET(wxWidgets_USE_LIBS)  
set(wxWidgets_LIB_DIR C:/Users/creat/Projects/wxWidget/3.2.4/lib/vc14x_x64_dll)  
set(wxWidgets_INCLUDE_DIRS C:/Users/creat/Projects/wxWidget/3.2.4/include)  
FIND_PACKAGE(wxWidgets REQUIRED richtext aui adv html core xml net base)  
IF(wxWidgets_FOUND)  
    INCLUDE("${wxWidgets_USE_FILE}")  
    add_executable(gta_c2 main.cpp  
            components/arduino_controller.cpp  
            components/arduino_controller.h  
            components/commander.cpp  
            components/commander.h  
            components/img_processor.cpp  
            components/img_processor.h  
            components/key_patterns.cpp  
            components/key_patterns.h  
            components/keyboard_hooker.cpp  
            components/keyboard_hooker.h  
            components/key_data.cpp  
            components/key_data.h  
            components/mouse_hooker.cpp  
            components/mouse_hooker.h  
            components/action_operator.cpp  
            components/action_operator.h  
            test/test000_capture.cpp  
            test/test000_capture.h  
            test/test001_keyboard.cpp  
            test/test001_keyboard.h  
            test/test002_key_pattern.cpp  
            test/test002_key_pattern.h  
            test/test003_arduino.cpp  
            test/test003_arduino.h  
            components/timer.cpp  
            components/timer.h  
            components/actions.h  
            test/test004_sqlite3.cpp  
            test/test004_sqlite3.h  
            sqlite3.c  
            sqlite3.h  
    )  
    TARGET_LINK_LIBRARIES(gta_c2 ${wxWidgets_LIBRARIES})  
ELSE(wxWidgets_FOUND)  
    #for convenience. When we cannot continue,inform the user  
    MESSAGE("wxWidgets not found!")  
ENDIF(wxWidgets_FOUND)  
  
include_directories(&{PROJECT_SOURCE_DIR}/components)  
include_directories(&{PROJECT_SOURCE_DIR})  
  
target_link_libraries(gta_c2 gdiplus)
```
`FIND_PACKAGE(wxWidgets REQUIRED richtext aui adv html core xml net base)`
여기에서 지금 필요한걸 넣어주면 될듯. 