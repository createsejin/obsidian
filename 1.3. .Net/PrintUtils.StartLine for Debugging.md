```
----------------------------MatchCounting---------------------------
[16]05.  <- selected
----------------------------match_pairs----------------------------
05.
05.
------------------------------keyword------------------------------
05.
```
이런식으로 가운데 라벨을 가운데 맞춤하여 라인을 내가 원하는 크기에 맞게 출력해주는 내가 만든 Util 라이브러리 인터페이스다.
이걸로 이런식으로 메세지를 구획을 나눠주기 때문에 Debug 할때 혹은 값을 확인하거나 코드가 어떤 부분에 도달했는지 확인할때 매우매우 유용하다.

구현체는 아래와 같다.
```csharp
namespace MyLib;

public delegate void PrintDelegate(string msg);
public interface IPrintUtils
{
  PrintDelegate PrintDelegate_ { get; set; }
  void StartLine(string label, int line_size = 68);
  void EndLine(int line_size = 68);
}
public class PrintUtils : IPrintUtils
{
  public PrintDelegate PrintDelegate_ { get; set; } = Console.WriteLine;
  public void StartLine(string label, int line_size = 68)
  {
    int line_middle = (int)Math.Round((double)(line_size / 2.0), 0, MidpointRounding.ToZero);
    int left_line_num = line_middle - (int)Math.Round((double)(label.Length / 2.0), 0,
      MidpointRounding.ToEven);
    int right_line_num = line_size - ((int)Math.Round((double)(label.Length / 2.0), 0,
      MidpointRounding.AwayFromZero) + line_middle);
    string start_line_str =
      $"{new string('-', left_line_num)}{label}{new string('-', right_line_num)}";
    PrintDelegate_(start_line_str);
  }

  public void EndLine(int line_size = 68)
  {
    string end_line_str = $"{new string('-', line_size)}";
    PrintDelegate_(end_line_str);
  }
}
```

여기에서 한가지 깨달은 사실은 `(double)(label.Length / 2.0)` 이 부분인데 이걸 만약 `(double)(label.Length / 2)` 이런식으로 뒤에다가 `.0`을 안붙이면 아마도 나머지 기반의 나눗셈을 해버리는것 같다. 소수 기반 나눗셈을 위해서는 반드시 나누는 수인 제수 역시 부동소숫점 형식이여야 한다는 것. 앞에 `(double)`로 캐스팅한 이유는 `Math.Round` 함수가 `decimal`과 `double`을 둘 다 받는데 `label.Length / 2.0` 이렇게만 쓰면 둘 중 어느것을 사용할지 컴파일러가 결정할 수 없기 때문에 명시적으로 캐스팅을 해줘야한다.