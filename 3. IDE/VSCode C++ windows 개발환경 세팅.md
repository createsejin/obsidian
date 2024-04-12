기본적으로 C++ 인텔리센스와 디버거, clang-tidy, CMake 익스텐션들이 필요하다. 뭐 그 외에도 여러가지 익스텐션을 설치하면 vscode도 상당히 강력한 개발 툴이 된다.

또한 ninja build가 설치된 위치를 환경변수 Path에 등록해야한다.

그리고 .vscode 폴더에서 여러가지 세팅 폴더들이 필요하다.

기본적으로 `c_cpp_properties.json`에는 다음과 같은 내용이 있어야한다.
```json
{
    "configurations": [
        {
            "name": "Win32",
            "defines": [],
            "cStandard": "c23",
            "cppStandard": "c++23",
            "intelliSenseMode": "windows-clang-x64",
            "compilerPath": "C:/Program Files/LLVM/bin/clang++.exe"
        }
    ],
    "version": 4
}
```
여기에서는 Windows인 경우의 설정이다. 또한 이번에는 C++23 표준을 사용해보기로 했다. 
compilerPath에 LLVM의 clang++.exe c++ 컴파일러 위치를 설정해준다.

또한 `settings.json`파일에는 다음과 같은 내용이 담기면 된다.
```json
{
    "files.associations": {
        "ostream": "cpp",
        "array": "cpp",
        "atomic": "cpp",
        "bit": "cpp",
        "*.tcc": "cpp",
        "bitset": "cpp",
        "cctype": "cpp",
        "chrono": "cpp",
        "clocale": "cpp",
        "cmath": "cpp",
        "codecvt": "cpp",
        "compare": "cpp",
        "concepts": "cpp",
        "cstdarg": "cpp",
        "cstddef": "cpp",
        "cstdint": "cpp",
        "cstdio": "cpp",
        "cstdlib": "cpp",
        "cstring": "cpp",
        "ctime": "cpp",
        "cwchar": "cpp",
        "cwctype": "cpp",
        "deque": "cpp",
        "string": "cpp",
        "unordered_map": "cpp",
        "vector": "cpp",
        "exception": "cpp",
        "algorithm": "cpp",
        "functional": "cpp",
        "iterator": "cpp",
        "memory": "cpp",
        "memory_resource": "cpp",
        "numeric": "cpp",
        "optional": "cpp",
        "random": "cpp",
        "ratio": "cpp",
        "string_view": "cpp",
        "system_error": "cpp",
        "tuple": "cpp",
        "type_traits": "cpp",
        "utility": "cpp",
        "fstream": "cpp",
        "initializer_list": "cpp",
        "iomanip": "cpp",
        "iosfwd": "cpp",
        "iostream": "cpp",
        "istream": "cpp",
        "limits": "cpp",
        "new": "cpp",
        "numbers": "cpp",
        "semaphore": "cpp",
        "sstream": "cpp",
        "stdexcept": "cpp",
        "stop_token": "cpp",
        "streambuf": "cpp",
        "thread": "cpp",
        "typeinfo": "cpp",
        "variant": "cpp",
        "cinttypes": "cpp",
        "*.ixx": "cpp",
        "pointers": "cpp",
        "span": "cpp",
        "charconv": "cpp",
        "string_span": "cpp"
    },
    "C_Cpp.errorSquiggles": "disabled",
    "C_Cpp.default.compilerPath": "C:/Program Files/LLVM/bin/clang++.exe"
}
```
그리고 CMake extension setting을 해야한다.
현재 내가 설정한 VSCode의 설정 파일에서 설정할 수 있는데 다음과 같이 설정한다.
```json
{
    "files.autoSave": "onFocusChange",
    "editor.fontLigatures": true,
    "editor.fontFamily": "'JetBrains Mono', Consolas, 'Courier New', monospace",
    "editor.fontVariations": false,
    "editor.fontWeight": "250",
    "git.autofetch": true,

    "github.copilot.advanced": {
    
    },
    "github.copilot.enable": {
        "*": false,
        "plaintext": false,
        "markdown": false,
        "scminput": false
    },
    "git.enableSmartCommit": true,
    "cmake.showOptionsMovedNotification": false,
    "cmake.generator": "Ninja",
    "cmake.configureOnOpen": true,
}
```
밑에 cmake.generator를 Ninja로 잘 설정해주자. 대소문자까지 모두 일치해야한다.

기본적으로 Cmake나 ninja와 같은 애들은 미리 설치가 되어있어야한다. 물론 LLVM도 windows 버전 pre-compiled 버전으로 컴퓨터에 설치가 되어있어야하며 당연히 이들에 대한 환경 변수 설정은 필수다. 
또한 주의할 점은 만약 환경 변수를 설정했다면 vscode라던가 터미널을 다시 열어야한다. 그렇지 않으면 환경 변수가 적용되지 않은 상태로 터미널이 돌아가기 때문이 반드시 터미널 혹은 VSCode를 재시작을 해줘야한다.

또한 CodeLLDB extension을 설치해줘야한다. 그 후 왼쪽 사이드바에서 Run and Debug 탭으로 간 후, 
create a launch.json file 을 눌러주고 여기에서 LLDB를 선택하면 된다. 그럼 다음과 같이 launch.json file이 만들어진다.
```json
{
    // Use IntelliSense to learn about possible attributes.
    // Hover to view descriptions of existing attributes.
    // For more information, visit: https://go.microsoft.com/fwlink/?linkid=830387
    "version": "0.2.0",
    "configurations": [
        {
            "type": "lldb",
            "request": "launch",
            "name": "Debug",
            "program": "${workspaceFolder}/build/gta_cMecro.exe",
            "args": [],
            "cwd": "${workspaceFolder}"
        }
    ]
}
```
여기에서 program은 실행 파일을 직접 지정을 해줘야한다.

아 쓰발. 그러나 VSCode로 C++을 코딩해버리면 너무나도 많은 에러가 발생해버린다. 도저히 컨트롤하기 어려운 수준으로 에러가 미친듯이 발생해버린다.. 그냥 CLion을 쓰는게 나아보인다.. 어쩔 수 없는듯. ㅋㅋ