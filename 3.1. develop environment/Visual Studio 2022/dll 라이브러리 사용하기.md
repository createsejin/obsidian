[이 문서](https://learn.microsoft.com/en-us/cpp/build/walkthrough-creating-and-using-a-dynamic-link-library-cpp?view=msvc-170)에서 기본적인 사용방법을 알려준다. 근데 꽤나 복잡하다. 단순히 dll 파일 하나만 가지고는 뭔가 안되는것 같기도 하고. 
헤더파일, lib 파일, dll 파일 등이 필요해보인다. 일단 헤더가 없으면 내 프로젝트에 그 코드를 사용할 수 없을 것이고, lib 파일, dll 파일 둘 다 필요한것으로 보인다.

일단 dll 프로젝트를 빌드하는 방법을 생략하고 실제 프로젝트에서 어떻게 dll을 쓰는지를 추려보면,
우선은 solution properties에서 Configuration Properties -> C/C++ -> General -> Additional Include Directories에 `MathLibrary.h` 헤더파일이 있는 공간인 
`..\..\MathLibrary\MathLibrary`를 추가해줬다.

그리고 
```cpp
#include <iostream>
#include "MathLibrary.h"

using namespace std;

int main()
{
  fibonacci_init(1, 1);
  do {
    cout << fibonacci_index() << ": " << fibonacci_current() << endl;
  } while (fibonacci_next());
  cout << fibonacci_index() + 1 << " Fibonacci sequence values fit in an " <<
        "unsigned 64-bit integer." << endl;
}
```
이런식으로 헤더를 이용해서 main 함수를 작성해주었다. 

그리고 또 해야할것은 `MathLibrary.lib`를 추가해야하는데, 역시 solution Properties에서 Linker -> Input -> Additional Dependencies 에서 Edit을 눌러서 `MathLibrary.lib`를 추가해준다. 
근데 이것만 이렇게 추가하면 컴파일러가 `MathLibrary.lib`를 찾을 방법이 없다. 
따라서 Linker -> General -> Additional Library Diretories에서 Edit 에서 `MathLibrary.lib`가 있는 곳을 추가해준다. `..\..\MathLibrary\MathLibrary\x64\Debug` 

또한 마지막으로 Build Events -> Post-Build Event로 들어가서 build 이후에 dll 파일을 프로젝트로 복사하는 명령을 추가해줘야한다. 
```
xcopy /y /d "..\..\MathLibrary\MathLibrary\x64\Debug\MathLibrary.dll" "$(OutDir)"
```
이런식으로 맨든다. 만약 dll 파일을 수동으로 직접 프로젝트 build binary 폴더에 넣을 수 있다면 그렇게 해도 된다. 
서드파티 라이브러리의 경우 내가 수정할 일이 없기 때문에 업데이트되지 않는한 그냥 복사 붙여넣기 하는것도 방법이다. 

