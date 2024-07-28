```csharp
string input = "down \"R343545 23\" 'R34354 45' R34354 \"input=\'out\'\"";
string pattern = @"\""([^""]*)\""|\'([^']*)\'\s*|(\S+)";

MatchCollection matches = Regex.Matches(input, pattern);

foreach (Match match in matches)
{
  if (match.Groups[1].Success)
  {
    Console.WriteLine($"Double Quoted string: {match.Groups[1].Value}");
  }
  else if (match.Groups[2].Success)
  {
    Console.WriteLine($"Single Quoted string: {match.Groups[2].Value}");
  }
  else if (match.Groups[3].Success)
  {
    Console.WriteLine($"Unquoted string: {match.Groups[3].Value}");
  }
}
```

output:
```
Commander start.
Unquoted string: down
Double Quoted string: R343545 23
Single Quoted string: R34354 45
Unquoted string: R34354
Double Quoted string: input='out'
```

이것을 classlib로 만들었다.
```csharp
public class CommandParser
{
  private static readonly string _pattern = @"\""([^""]*)\""|\'([^']*)\'\s*|(\S+)";

  public static string[] GetArgs(string input)
  {
    List<string> result = [];
    MatchCollection matches = Regex.Matches(input, _pattern);
    foreach (Match match in matches)
    {
      if (match.Groups[1].Success)
      {
        result.Add(match.Groups[1].Value);
      }
      else if (match.Groups[2].Success)
      {
        result.Add(match.Groups[2].Value);
      }
      else if (match.Groups[3].Success)
      {
        result.Add(match.Groups[3].Value);
      }
    }
    return [.. result];
  }
}
```
이걸 이용하면 `Main` 함수의 `string[] args`가 아닌, 프로그램 내부에서 User input을 기반으로 args를 적절하게 획득할 수 있는 방법이 마련된다. 이것을 `System.CommandLine` 라이브러리와 함께 사용하면 된다. 

이 표현식과 메서드는 [[NUnit Test|NUnit Test]]를 통해 Test됐다.