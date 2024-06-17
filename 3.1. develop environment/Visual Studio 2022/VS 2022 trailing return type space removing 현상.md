```cpp
[[nodiscard]] auto get_last_name() const->std::string&;
```
에서 `->` 부분 앞 뒤로 space가 제거되는 현상을 해결하려면
Tools -> options -> Text Editor -> C/C++ -> Code Style -> Formatting -> Spacing -> Remove spaces before and after member operators 옵션을 uncheck 해주면 된다.