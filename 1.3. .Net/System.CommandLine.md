[공식 문서](https://learn.microsoft.com/en-us/dotnet/standard/commandline/)

CLI 커맨드라인 application을 위해 만들어진 library다. 
본래는 `.\program.exe subcommand --option` 이런식으로 프로그램 실행 매개변수를 통해 입력된 `Main` 함수의 `args` 배열을 받아서 커맨드라인을 파싱하는 역할을 한다.

나같은 경우에는 the_cave 프로젝트에서 [[Pipe communication|pipe]]를 통해 커맨드를 입력하는 프로그램인 `Commander`에서 사용하고 있는데, 여기에서는 프로그램 실행파일에 직접 매개변수를 넣는 방식이 아니라 프로그램을 실행하고 그 내부 프롬프트를 통해 User input을 받아서 그걸 파싱하는데에 이 라이브러리를 사용해봤다.

```csharp
using System.CommandLine;
using System.CommandLine.Parsing;
using System.IO.Pipes;
using MyLib;

class Commander
{
  private readonly string _unzip_work_dir = @"S:\s\download_samples";
  private readonly NamedPipeClientStream _client = new(".", "commander_pipe", PipeDirection.InOut);
  private bool _is_exit = false;
  private readonly RootCommand _rootCommand = [];
```
우선은 이런식으로 `RootCommand`를 멤버로 선언했다. 특이하게도 `[]`로 인스턴스를 만들 수 있었다. 보통은 Array type의 인스턴스를 생성할때 주로 사용하는 방법이다. 
```csharp
  public Commander()
  {
    SetDownloadCommand();
    SetUnzipCommand();
    SetTestCommand();
    SetExitCommand();
    SetTabCommand();
  }
```
이런식으로 각 `Subcommand`를 설정하고 있다.

우선 `SetDownloadCommand`를 보자.
```csharp
  private void SetDownloadCommand()
  {
    var downloadCommand = new Command("down", "Download RJ Collection");
    var rj_num_Args = new Argument<string[]>(name: "RJ number", description: "RJ number to download")
    {
      Arity = ArgumentArity.OneOrMore
    };
    downloadCommand.AddArgument(rj_num_Args);
    downloadCommand.AddAlias("d");
    downloadCommand.SetHandler(invocationContext =>
    {
      string[] rj_nums = invocationContext.ParseResult.GetValueForArgument(rj_num_Args);
      foreach (var rj_num in rj_nums)
      {
        if (RJParser.IsMatch(rj_num))
        {
          Console.WriteLine($"rj_num = {rj_num}");
          SendAndReceive($@"down ""{rj_num}""");
        }
        else 
        {
          Console.WriteLine($"{rj_num} is not matched RJ number format");
        }
      }
    });
    _rootCommand.AddCommand(downloadCommand);
  }
```
우선 먼저 `new Command("down", "Download RJ Collection")`를 통해 `donwloadCommand` sub command 인스턴스를 생성했다.
첫번째 매개변수가 명령어이고, 두번째는 이 명령어에 대한 description이다. 이 두가지는 반드시 들어가야한다.
그 다음 만든것은 `Argument`인데, generic으로 `string[]` 타입이 사용됐다. 이것은 예를들어서 
```
cmd> down RR343534 RR454534 RR23234
```
이런식으로 여러개의 argument들을 입력 가능하게 만들어준다. 또한 `Arity = ArgumentArity.OneOrMore`라는것을 설정해서 이 Argument가 하나 또는 그 이상을 제공해야한다고 조건을 명시하고 있다. 만약 이 조건이 지켜지지 않으면 프로그램은 경고를 내뱉으며 다시 사용자 입력을 받게된다. 이런 경고 메세지는 당연히 자동적으로 제공되므로 개발자가 이를 구현할 필요는 없다.
이제 처음 만든 `downloadCommand` 인스턴스에 `AddArgument(rj_num_Args)`로 argument 인스턴스를 추가해준다.
`AddAlias("d")`는 말 그대로 Alias다. 
```
cmd> d RR343545
cmd> down RR343434
```
이 두 명령어는 동일한 명령이 된다.

이어서 `.SetHandler`를 살펴보자.
```csharp
downloadCommand.SetHandler(invocationContext =>
    {
      string[] rj_nums = invocationContext.ParseResult.GetValueForArgument(rj_num_Args);
      foreach (var rj_num in rj_nums)
      {
        if (RJParser.IsMatch(rj_num))
        {
          Console.WriteLine($"rj_num = {rj_num}");
          SendAndReceive($@"down ""{rj_num}""");
        }
        else 
        {
          Console.WriteLine($"{rj_num} is not matched RJ number format");
        }
      }
    });
```
우선 람다 함수의 매개변수로 `invocationContext`가 쓰였다. 
또한 이 명령어에서 앞서 만들어준 `rj_num_Aargs` Argument array를 얻기 위해 `invocationContext.ParseResult.GetValueForArgument(rj_num_Args)`를 사용했다.
그리고 그 아래에는 이 array를 이용해서 실제 이 명령어에서 구동되는 동작을 구현해줬다. 

또다른 명령어를 설정하고 있는 `SetTestCommand` 메서드를 살펴보자.
```csharp
  private void SetTestCommand()
  {
    var testCommand = new Command("test", "Test somethings");
    var test_num_arg = new Argument<int>("test_number", "test number to Test")
    {
      Arity = ArgumentArity.ExactlyOne
    };
    testCommand.AddArgument(test_num_arg);
    testCommand.SetHandler(invocationContext =>
    {
      int test_num = invocationContext.ParseResult.GetValueForArgument(test_num_arg);
      Console.WriteLine($"test num = {test_num}");
      if (_available_tests.Contains(test_num))
        SendAndReceive($"-t {test_num}");
      else Console.WriteLine("test number {0:000} is not available.", test_num);
    });
    _rootCommand.AddCommand(testCommand);
  }
```
`Argument`의 Object 생성자에서 `Arity = ArgumentArity.ExactlyOne`를 통해 이 Argument는 정확히 하나의 입력값을 입력해야한다고 명시하고 있다. 
여기에서도 `invocationContext.ParseResult.GetValueForArgument(test_num_arg)`을 통해 옵션에서 입력된 값을 받고 있다.
또한 한가지 주의할 점은 이 sub command instance를 반드시 마지막에 `RootCommand`를 통해 `AddCommand`를 해주어야 한다는 것이다.

다음은 `exit` 명령어 set 메서드다.
```csharp
  private void SetExitCommand()
  {
    var exitCommand = new Command("exit", "Exit the program");
    var no_close_browser_option = new Option<bool>("-n", "No close Chrome driver browser");
    exitCommand.AddOption(no_close_browser_option);
    exitCommand.SetHandler(invocationContext =>
    {
      bool no_close_browser = invocationContext
        .ParseResult.GetValueForOption(no_close_browser_option);
      ExitPrograms(no_close_browser);
    });
    _rootCommand.AddCommand(exitCommand);
  }
```
여기에서는 `Option<bool>`이 사용되었다. 
예를들어서
```
cmd> exit -n
```
이런식으로 입력해주면 저 옵션이 `true`가 되는 식이다. 
여기에서도 `invocationContext`를 통해 옵션값을 얻고 있다.
아마도 `Option`은 bool 말고도 다른 값을 지원하는것으로 알고 있다. 