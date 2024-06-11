```cpp
key_release_timer_thread(&Timer::key_release_timerLoop, this),  
key_press_timer_thread(&Timer::key_press_timerLoop, this) {  
// 자동으로 resource를 해제하도록 하고 메인 스레드와 분리되어 스레드를 실행하도록 한다.  
key_release_timer_thread.detach();  
key_press_timer_thread.detach();
```
이런식으로 클래스에서 메소드를 thread 함수로 쓰려면 반드시 첫번째 인자에서 `Timer::`처럼 클래스의 이름을 명시해야한다. 그리고 그 다음 매개변수에는 현재 클래스의 인스턴스인 `this`가 들어간다. 그 후에는 만약 콜 함수의 매개변수가 있다면 그 매개변수를 그 이후에 쓰면 된다.

```cpp
std::thread action_thread(&ActionOperator::frame_of_action,    
	  std::ref(key_pattern));  
action_thread.join();
```
이것은 콜 함수가 static인 경우이다. 이럴때에는 클래스의 인스턴스를 참조할 수 없으므로 `this`를 넣으면 안된다. 그리고 이처럼 key_pattern의 참조를 넘겨줘야할 때에는 `std::ref`를 이용해서 전달해야 정상적으로 적용된다. thread는 내부적으로 넘겨받은 매개변수를 복제하기 때문이라고 한다.

"std::thread 생성자는 전달된 인자를 복사하여 새로운 스레드에 전달합니다. 이는 std::thread가 생성되는 시점에서 전달된 인자가 유효한 상태를 보장하기 위한 것입니다. 그러나 이 복사 동작은 const가 아닌 레퍼런스에 대해서는 동작하지 않습니다. 이는 const가 아닌 레퍼런스가 가리키는 객체가 변경될 수 있기 때문입니다.  따라서 std::thread에 const가 아닌 레퍼런스를 전달하려면, std::ref()를 사용하여 레퍼런스를 전달해야 합니다. std::ref()는 std::reference_wrapper를 반환하는데, 이는 복사 가능한 레퍼런스를 제공합니다. 이렇게 하면 std::thread 생성자는 std::reference_wrapper를 복사하여 새로운 스레드에 전달하고, std::reference_wrapper는 원래의 const가 아닌 레퍼런스를 유지합니다."