```csharp
class Program
{
  static void Main(string[] args)
  {
    // console 출력을 UTF-8로 지정한다.
    Console.OutputEncoding = System.Text.Encoding.UTF8;
    Console.InputEncoding = System.Text.Encoding.UTF8;
	...skip
```
.Net에서는 이렇게 쉽다. C++에서는 [[한글 입출력 문자 깨짐 현상 해결하기|이렇게]] 한다.