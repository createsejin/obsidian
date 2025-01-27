멤버 변수가 const가 아니여야한다. 왜냐하면 만약 const가 되면 그 참조는 반드시 최초에 초기화된 변수에 대해서만 유효하기 때문이다. 따라서 = operator가 허용되지 않게 된다. 따라서 이러한 멤버 변수가 const라면 getter 함수에서 그 멤버 변수에 대한 참조를 반환할 수 없다. 왜냐면 이걸 허용하게 되면 assign operator = 를 허용하는것이기 때문이다. 따라서 멤버 변수의 참조를 반환코자 할 경우에는 반드시 멤버 변수를 non-const로 지정해야한다.
또한 이러한 참조를 반환하는 getter 메소드는 반드시 non-const 메소드여야한다.

그런데 이것은 이상하게도 built-in type 하나를 const로 지정해도 문제가 생긴다. 
만약 아래와같이 객체를 가지는 vector를 정렬하는 함수를 쓸 경우에는 말이다.

```cpp
class KeyPattern {  
    std::string action_name;  
    action_operator::Actions action;  
    PatternType pattern_type;  
    bool is_need_blocking;  
    std::vector<CombineKey> key_pattern_vec;  
    std::size_t key_pattern_vec_size;  
public:  
    KeyPattern(std::string_view action_name, action_operator::Actions action, PatternType type,  
        const std::initializer_list<CombineKey>& key_pattern_list,  
        bool is_need_blocking = false);  
    [[nodiscard]] std::size_t get_key_pattern_vec_size() const;  
    [[nodiscard]] auto get_key_pattern_vec() -> std::vector<CombineKey>&;  
    [[nodiscard]] auto get_action_name() -> std::string&;  
    [[nodiscard]] auto get_pattern_type() const -> PatternType;  
};

void PatternManager::sort_key_patterns() {  
    // vector의 sort 함수를 사용해서 key_patterns vector를 정렬한다.  
    ranges::sort(key_patterns,  
        // Key_patterns vector에 든 KeyPattern 객체들을 비교하는 람다함수다.  
     [](KeyPattern& a, KeyPattern& b) {  
         // 만약 두 객체의 패턴 벡터의 크기가 서로 다른 경우,  
         if (a.get_key_pattern_vec_size() != b.get_key_pattern_vec_size()) {  
             // 패턴 벡터의 크기가 큰 객체가 먼저 오도록 한다.  
             return a.get_key_pattern_vec_size() > b.get_key_pattern_vec_size();  
         }  
         // 두 객체의 패턴 벡터의 크기가 같은 경우,  
         // 패턴 벡터의 첫번째 요소인 CombineKey 객체의 첫번째 set bit를 비교해서  
         // 첫 set bit의 인덱스 크기가 작은 객체가 먼저 오도록 한다.  
         return a.get_key_pattern_vec()[0].get_first_set_bit() <  
             b.get_key_pattern_vec()[0].get_first_set_bit();  
     });  
}
```
만약 위처럼 `KeyPattern` 객체를 가지는 vector를 sorting할때에는 `KeyPattern` class는 const 멤버를 가지면 안되는것으로 보인다. 아마도 sort 함수에서 내부적으로 ramdom access 기능 때문에 그런것 같은데.. 일단 sort 한다는것도 뭔가 내부적으로 변경을 하는거라 안되는것 같다. 

```cpp
void PatternManager::pattern_matcher() {
        key_data::KeyboardData& keyboard_data = key_data::KeyboardData::getInstance();
        std::bitset<223> key_state = keyboard_data.get_key_state();
        for (auto& key_pattern : key_patterns) {
            std::bitset<223> first_bit = key_pattern.get_key_pattern_vec()[0].get_key_bit();
        }
    }
```
이걸 보면 또 알 수 있는게, vector의 index 연산자를 쓰려면 아마도 non-const 메소드에, auto& 이쪽 참조자도 non-const여야 한다는 것이다. 

근데 copilot이 중요한 정보를 알려줬다.
	ranges::sort 함수는 정렬을 수행하기 위해 요소들을 교환(swap)합니다. 이는 요소들이 이동 가능(movable)해야 함을 의미합니다. 만약 KeyPattern 클래스의 멤버 변수들을 const로 선언하게 되면, 이 변수들은 더 이상 수정할 수 없게 되므로 KeyPattern 객체들을 교환하는 것이 불가능해집니다. 따라서 ranges::sort 함수는 const 멤버 변수를 가진 KeyPattern 객체들로 이루어진 벡터를 정렬할 수 없게 됩니다.  따라서 action_name, action, pattern_type, is_need_blocking, key_pattern_vec_size를 const로 선언하면 PatternManager의 sort_key_patterns 메서드에서 ranges::sort를 사용하는 데 문제가 생깁니다.

아마도 index 접근자는 상관이 없는것으로 보인다. 왜냐면 const일때에도 접근할 수 있는 인덱스 접근자를 제공하기 때문

# 아니
근데 참조 const로 반환 가능할텐데? 메서드 const로 만들고 반환값 const로 만들면 가능한데 왜?