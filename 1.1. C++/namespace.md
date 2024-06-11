그러니까 특정 네임스페이스 내부에 있는 함수만 쓰겠다 하면 다음과 같이 하면 된다.
```cpp
using std::cout;
cout << "program start" << std::endl;
```
이런식으로 사용한다. 주의할 점은 `using namespace`라고 하면 안된다는것.

만약 `namespace` alias를 사용하고 싶으면 다음과 같이 한다.
```cpp
using string_v = std::string_view;
```
이걸 이렇게 쓰는 이유는 일단 `string_view`의 경우에는 만약 `<iostream>`과 `<fmt/core.h>`라이브러리를 같이 쓰면 `std`랑 `fmt`에 string_view 인스턴스가 똑같은 이름으로 있기 때문에 컴파일러가 `ambiguous` 에러를 낸다.

아니면 그냥 네임스페이스를 확정해서 `std::string_view`를 쓰면 해결된다.

참고로 using 디렉티브에는 namespace와 enum 이 있는데, 이것을 사용할 때 마지막에 오는 namespace 인자가 정확히 그 디렉티브 type과 매치되어야한다. 