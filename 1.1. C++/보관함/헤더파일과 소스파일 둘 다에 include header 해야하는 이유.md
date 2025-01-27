>[!question]
아니 근데 이건 왜 소스파일이랑 헤더파일 둘다 \#include \<optional> 추가해야함? 

```cpp
# source file : 
#include <optional>  

std::optional<int> getData(bool giveIt) {

if (giveIt) {

return 42;

}

return std::nullopt; // 또는 그냥 {};

}

  

void study015() { //p.100 1.1.18 std::optional

optional<int> data1{getData(true)};

optional<int> data2{getData(false)};

cout << "data1.has_value = " << data1.has_value() << endl;

if (data2) {

cout << "data2 has a value." << endl;

} else {

cout << "data2 has no value." << endl;

}

}

#header file : 

#include <optional>

std::optional<int> getData(bool giveIt);

void study015();
```
이렇게 해야하고 둘 중에 하나라도 include 없으면 안되네?

>[!answer]
>네, 그렇습니다. 이유는 C++의 컴파일 과정과 헤더 파일(`.h` 또는 `.hpp`)과 소스 파일(`.cpp`)의 관계에 있습니다.
>
C++에서 헤더 파일은 주로 함수와 클래스의 선언(declaration)을 포함하고, 소스 파일은 이들의 정의(definition)를 포함합니다. 컴파일러는 소스 파일을 컴파일할 때 각각을 독립적으로 처리하며, `#include` 지시자를 만나면 해당 헤더 파일의 내용을 그 자리에 복사해 넣습니다.
>
따라서 `std::optional`이 필요한 모든 곳에서 `<optional>` 헤더를 포함해야 합니다. 예를 들어, `getData()` 함수가 `std::optional<int>` 타입을 반환한다고 선언되어 있는 헤더 파일에서는 `<optional>` 헤더가 필요하며, 이 함수를 정의하는 소스 파일에서도 마찬가지로 `<optional>` 헤더가 필요합니다.
>
즉, 둘 중 하나만 `<optional>`을 포함하면 다른 한 쪽에서 `std::optional`이 정의되지 않았다는 오류가 발생할 수 있습니다.
****

독립적으로 처리하므로 둘다 필요하다는 결론이다.

>[!question]
>근데 이렇게 해도 cmake에서 빌드하면 \<optional> 헤더 중복되서 실행파일 만드는건 아니지?


>[!answer]
>아니요, \<optional> 헤더가 여러 파일에서 포함되더라도 중복으로 컴파일되지 않습니다. C++의 헤더 파일은 주로 선언과 템플릿 코드를 포함하며, 이들은 컴파일 시간에 한 번만 처리됩니다.
>
C++의 #include 지시자는 사실상 해당 파일의 내용을 그 자리에 복사해 넣는 역할을 합니다. 따라서 동일한 헤더를 여러 소스 파일에서 포함하더라도, 각 소스 파일이 개별적으로 컴파일되므로 문제가 되지 않습니다.
>
또한 대부분의 C++ 표준 라이브러리 헤더들은 "include guard"라고 하는 기술을 사용하여 같은 컴파일 단위 내에서 여러 번 포함되어도 한 번만 처리되도록 설계되어 있습니다. 이 방식은 #ifndef, #define, #endif 지시자를 사용하여 구현됩니다.
>
따라서 \<optional> 같은 표준 라이브러리 헤더를 여러 곳에서 포함하는 것이 프로그램 크기나 성능에 부정적인 영향을 미치지 않습니다.

