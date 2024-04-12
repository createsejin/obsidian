```cpp
    void study1() {
        HR::Employee emp{
            .firstInitial = 'S',
            .lastInitial = 'B',
            .employeeNumber = 7,
        };
        cout << format("Employee number : {}, first initial : {}, \
last initial : {} salary : ${}\n", emp.employeeNumber, emp.firstInitial, \
        emp.lastInitial, emp.salary);
    }
```
스트링 리터럴을 코드 줄바꿈 하려면 반드시 저런식으로 들여쓰기를 무시하고 백슬래쉬 뒤의 공백을 제거해야한다.
일반적인 코드는 그냥 백슬레쉬 하고 다음줄을 들여쓰기 해도 상관이 없다.

```cpp
std::cout << "Keyboard hooker debug option is off. "
                         "Raw keyboard debug option is ignored." << std::endl;
```
아니면 이런식으로 리터럴을 나눠서 작성하는 방법이 있다. 이것을 좀더 권장하는 바이다.