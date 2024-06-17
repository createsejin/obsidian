```cpp
cout << "command mode" << endl;  
into_command_mode.store(false);  
std::cout << "cmd> ";  
std::string input;  
std::getline(std::cin, input);  
const auto pos = input.find("cmd>");  
if (pos != std::string::npos) {  
    input.erase(pos, 5);  
}  
cout << "input = |" << input << "|" << endl;  
try {  
    main_window::cli.parse(input, false);  
} catch (const CLI::ParseError& e) {  
    std::cout << "Parse error: " << e.what() << std::endl;  
}
```
CLI11을 이용해서 command line interface를 만들기 위해 command prompt를 cout으로 사용했을때
`std::cout << "cmd> ";` 여기에서 마지막 cout 출력의 space가 삭제되는 현상이 있었다. 

이걸 고치려면 `Ctrl+Shift+A`를 눌러서 Clion의 명령줄 도구를 연 다음에 `Registry..`를 열고
`run.processes.with.pty`를 uncheck 해주면 이 문제가 해결된다. 

다만 이렇게 할 경우 Clion에서 Debug run이 아닌 normal run일때 중지 버튼을 누르면 exit -1 코드로 종료되기 때문에 리소스의 적절한 해제를 위해서 지정된 종료 패턴키 F1+F4를 누르거나(cMecro project에서) GUI의 X버튼을 눌러서 종료해주자.