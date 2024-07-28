```csharp
public delegate string? GetFileNameDelegate(string? path); 

public interface IPrintUtils
{
  void PrintFileArray<T>(
    IEnumerable<T> array, GetFileNameDelegate getFileNameDelegate);
}

public class PrintUtils : IPrintUtils
{
  public void PrintFileArray<T>(
    IEnumerable<T> array, GetFileNameDelegate? getFileNameDelegate = null)
  {
    GetFileNameDelegate fileNameDelegate = Path.GetFileName;
    if (getFileNameDelegate is not null)
      fileNameDelegate = getFileNameDelegate;
    Console.Write("[");
    foreach (var item in array.SkipLast(1))
    {
      if (item is not null)
      {
        Console.Write($"{fileNameDelegate(item.ToString())}, ");
      }
    }
    Console.Write($"{fileNameDelegate(array.Last()?.ToString())}]\n");
  }
}
```
나의 개인 라이브러리인 [[PrintUtils.StartLine for Debugging|PrintUrils]]에 새로운 메서드를 추가하였다.
여러가지 테크니컬한 코딩 방법이 쓰였다. 우선 `IEnumerable<T>`를 통해 매개변수 `array`가 이것을 구현하는 array 타입을 받고 있다.
또한 `GetFileNameDelegate` delegate를 nullable로 받아서 이 값이 주어질때와 주어지지 않을때에도 모두 메서드가 동작하도록 하였다.
기본적으로 `GetFileNameDelegate`에는 `Path.GetFileName`가 주어지며, 만약 delegate 매개변수가 주어질 경우 주어진 메서드로 file 이름을 다루도록 하였다.
또한 배열을 효과적으로 출력하기 위해 처음에 시작 괄호를 찍어주고, 
루프 내부에서는 마지막을 제외(`array.SkipLast(1)`)하고 콤마를 붙여서 출력한뒤, 루프가 끝나고 `array.Last()`를 출력하고 `\n`을 통해 개행하고 있다.

또한 여기서 알게된 사실은, 만약 이 `MyLib` namespace 안에 전역 변수로 delegate를 어디엔가 프로젝트 내부 파일에 만들었다면 그 delegate는 `MyLib` namespace를 사용하는 그 프로젝트의 어떤 파일에서도 접근할 수 있다는 사실이다. 따라서 전역변수 delegate만을 담는 파일을 따로 만들어서 delegate들을 모아두었다.

delegate는 함수 형식을 가지는 일종의 사용자 지정 함수 타입이라고 보면 된다. 
```csharp
public delegate string? GetFileNameDelegate(string? path);
```
이런식으로 `delegate` keyword를 통해 선억할 수 있으며, 메서드 형식처럼 써주고, 메서드 이름처럼 된 부분이 이 delegate의 타입 이름이다. 
이러한 delegate는 
```csharp
GetFileNameDelegate fileNameDelegate = Path.GetFileName;
```
이런식으로 delegate 변수를 선언할 수 있으며, 변수 할당값에는 이 delegate와 일치하는 메서드가 들어갈 수 있다. 만약 메서드가 여러가지 버전으로 오버라이딩 되어있다면 자동으로 delegate는 해당 delegate에 맞는 버전으로 메서드가 할당된다.
```csharp
fileNameDelegate(item.ToString())
```
delegate는 이런식으로 메서드를 사용하는 것처럼 사용하면 된다. 