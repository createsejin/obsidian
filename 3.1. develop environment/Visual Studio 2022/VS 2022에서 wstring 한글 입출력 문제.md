main 함수에 다음과 같이 설정해주면 된다.
```cpp
#include <Windows.h>

std::locale::global(std::locale("ko_KR.utf8"));
std::wcout.imbue(std::locale());
std::wcin.imbue(std::locale());
SetConsoleCP(65001);
SetConsoleOutputCP(65001);
```
기본적으로 windows의 콘솔은 utf-8 인코딩을 지원하지 않는것 같다. 반드시 콘솔의 입출력단을 모두 65001 code page로 변경하는 코드가 필요하다.