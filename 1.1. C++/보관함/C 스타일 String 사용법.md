```c
const char *str1 = "안녕";
const char *str1{"안녕"};
char str2[]{"하세요"};
```
```cpp
char *text2 = "abcdef";
```
>[!warning]
warning: ISO C++11 does not allow conversion from string literal to 
`'char *'`[-Wwritable-strings]

`"abcdef"`같은 리터럴은 상수로 취급되기 때문에 비 const 형인 `char *`형으로의 컨버전을 허용하지 않는 것이다. 따라서 char 앞에 `const`키워드를 붙여줘야한다.
만약 다음과 같이 써버리면 프로그램의 동작을 예측할 수 없게 된다.
```cpp
char *ptr{"hello"}; 
ptr[1] = 'a';
```

#cpp