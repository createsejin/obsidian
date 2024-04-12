C++에서 커맨드라인 인자를 파싱하려면, 일반적으로 `std::string`의 멤버 함수인 `find`와 `substr`을 사용하거나, 정규 표현식을 사용할 수 있습니다. 여기서는 `std::string`의 멤버 함수를 사용하여 간단하게 구현해보겠습니다.

1. `main` 함수의 인자를 순회하면서 각 인자가 `--keyboard_hooker_debug=` 또는 `--mouse_hooker_debug=`로 시작하는지 확인합니다.
2. 만약 그렇다면, `=` 이후의 문자열을 추출하여 `true`인지 확인합니다.
3. `true`라면 해당 후커의 디버그 값을 `true`로 설정합니다.

이를 코드로 구현하면 다음과 같습니다:

```cpp
int main(int argc, char* argv[]) {
    cout << "Program start" << endl;

    // Default debug values
    bool debug_keyboard = false;
    bool debug_mouse = false;

    // Parse command line arguments
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg.find("--keyboard_hooker_debug=") == 0) {
            debug_keyboard = (arg.substr(24) == "true");
        } else if (arg.find("--mouse_hooker_debug=") == 0) {
            debug_mouse = (arg.substr(21) == "true");
        }
    }

    // Set the debug values
    keyboard_hooker::set_debug_keyboard(debug_keyboard);
    mouse_hooker::set_debug_mouse(debug_mouse);

    // Start the event loops
    thread eventLoopThread_keyboard(keyboard_hooker::runEventLoop_keyboard);
    thread eventLoopThread_mouse(mouse_hooker::runEventLoop_mouse);

    // ... (do other things in the main thread)

    // Wait for the event loop threads to finish
    eventLoopThread_keyboard.join();
    eventLoopThread_mouse.join();
}
```

이제 실행 파일을 실행할 때 커맨드라인 인자를 통해 디버그 값을 설정할 수 있습니다. 예를 들어, 키보드 후커의 디버그를 활성화하고 마우스 후커의 디버그를 비활성화하려면 다음과 같이 실행하면 됩니다:

```
./gta_c2.exe --keyboard_hooker_debug=true --mouse_hooker_debug=false
```
