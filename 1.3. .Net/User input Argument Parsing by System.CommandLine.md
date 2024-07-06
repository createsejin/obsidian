[System.CommandLine](https://learn.microsoft.com/en-us/dotnet/standard/commandline/)이라는 라이브러리를 활용한다. 
```
dotnet add package System.CommandLine --version 2.0.0-beta4.22272.1
```

```csharp
  private static string[] ArgumentParser(string input)
  {
    var rootCommand = new RootCommand();
    var argument = new Argument<string[]>("args");
    rootCommand.AddArgument(argument);

    var parseResult = rootCommand.Parse(input);
    return parseResult.GetValueForArgument(argument);
  }
  public void CommandLoop()
  {
    while (true)
    {
      Console.Write("cmd> ");
      var input = Console.ReadLine();
      if (string.IsNullOrEmpty(input))
      {
        Console.WriteLine("input is null or empty.");
      }
      else
      {
        string[] args = ArgumentParser(input);
        _rootCommand.Invoke(args);
        if (_is_exit) break;
      }
    }
  }
```
이런식으로 하면 사용자 input에서 따옴표로 묶은 부분 혹은 single quote로 묶은 부분을 하나의 argument로 파싱해준다.
참고로 .Net의 `Main` 함수의 `string[] args` 매개변수는 이런 기능을 기본적으로 가지고 있다. 따라서 이와 같은 파싱 기능은 프로그램을 실행 후 그 내부적으로 사용자 input을 받을때 활용할 수 있고, 기본적으로 프로그램 실행파일에 argument를 전달하는 방식에서는 구지 이 라이브러리 없이도 여러가지 argument를 자동으로 파싱해준다. 그러나 그런 경우에도 이 라이브러리를 이용해서 커맨드 라인 app을 구성하는게 훨씬 더 좋다. 

그런데 요상하게도 이것은 이상하게 동작했다. 우선 왜 그런건지는 모르겠지만 VSCode의 내부 terminal에서는 한글을 제대로 표현하지 못하였다. 또한 `down 'RJ343434 file.zip'`같은 single quote로 감싸진 인수의 경우에는 제대로 명령줄을 파싱하지 못하였다. 여러가지 대안을 찾아보던 중, 그나마 나은 한가지 방법을 찾아냈다. 그냥 [[User input parsing by RegularExpressions|정규 표현식을 이용]]하는 방법이었다.