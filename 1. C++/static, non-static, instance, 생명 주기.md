`static`과 `non-static`은 C++에서 클래스의 멤버 변수나 멤버 함수를 정의할 때 사용하는 키워드입니다. 이 두 키워드는 멤버 변수나 멤버 함수의 수명과 접근 방식에 영향을 미칩니다.

`static` 멤버 변수나 함수는 클래스의 인스턴스가 아닌 클래스 자체에 속하며, 클래스의 모든 인스턴스가 공유합니다. `static` 멤버는 프로그램이 시작될 때 생성되고, 프로그램이 종료될 때 파괴됩니다. 따라서 `static` 멤버는 프로그램의 실행 동안 계속 존재하며, 클래스의 인스턴스가 없어도 접근할 수 있습니다. `static` 멤버 함수 내에서는 `static` 멤버 변수만 접근할 수 있습니다.

반면에 `non-static` 멤버 변수나 함수는 클래스의 인스턴스에 속하며, 각 인스턴스는 자신만의 `non-static` 멤버를 가집니다. `non-static` 멤버는 인스턴스가 생성될 때 생성되고, 인스턴스가 파괴될 때 파괴됩니다. 따라서 `non-static` 멤버는 인스턴스의 수명 동안만 존재하며, 인스턴스가 없으면 접근할 수 없습니다. `non-static` 멤버 함수 내에서는 `static` 멤버 변수와 `non-static` 멤버 변수 모두 접근할 수 있습니다.

다음은 `static`과 `non-static` 멤버를 사용하는 클래스의 예입니다:

```cpp
class MyClass {
public:
    static int static_var; // static member variable
    int non_static_var; // non-static member variable

    static void static_func() { // static member function
        // Can access static_var, but cannot access non_static_var
        static_var = 10;
    }

    void non_static_func() { // non-static member function
        // Can access both static_var and non_static_var
        static_var = 20;
        non_static_var = 30;
    }
};

// Initialize static member variable
int MyClass::static_var = 0;
```

이 예제에서 `MyClass::static_var`는 `MyClass`의 모든 인스턴스가 공유하는 `static` 멤버 변수이며, `MyClass::static_func()`는 `static` 멤버 함수입니다. 반면에 `MyClass::non_static_var`는 각 `MyClass` 인스턴스가 독립적으로 가지는 `non-static` 멤버 변수이며, `MyClass::non_static_func()`는 `non-static` 멤버 함수입니다.