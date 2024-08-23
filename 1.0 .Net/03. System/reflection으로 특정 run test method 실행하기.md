```csharp
namespace HttpClientTest1;

public class Tests1
{
  private readonly string _testJson = @"Q:\s\ddd.json";
  public Tests1()
  {
  }
  public void Test1()
  {
    ...
  }
}
```
예를 들어서 `HttpClientTest1` namespace에 `Tests1` 클래스가 있고, `Test1` 메서드가 있다고 하자.

```csharp
using System.Reflection;

Console.WriteLine("Test start");
if (int.TryParse(args[0], out int class_num) && int.TryParse(args[1], out int method_num))
{
  string test_class_name = $"HttpClientTest1.Tests{class_num}";
  string test_method_name = $"Test{method_num}";
  Type? classType = Type.GetType(test_class_name);
MethodInfo? methodInfo = classType?.GetMethod(test_method_name);
  if (classType is not null)
  {
    object? test_class = Activator.CreateInstance(classType);
    methodInfo?.Invoke(test_class, null);
  }
}
```
그러면 이런식으로 클래스의 이름을 이용해서 해당 클래스 인스턴스를 생성하고, 메서드의 이름을 통해 그 클래스 내부의 method를 호출할 수 있다. 
`classType`은 네임스페이스가 포함된 클래스의 이름이어야한다. 
	메서드를 호출할때 매개변수가 없으면 `null`을 넘기고, 그게 아니라면 `.Invoke`에서 `null` 자리에 매개변수를 넣을 수 있다.