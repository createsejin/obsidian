[git repo](https://github.com/serilog/serilog)
Nuget package는 다음과 같이 설치해준다. `.Console`은 혹시나 console에 로그를 찍을거면 사용한다. File에다가만 찍을거면 `.File` 패키지만 설치해도 된다.
```xml
  <ItemGroup>
    <PackageReference Include="Serilog" Version="4.0.1" />
    <PackageReference Include="Serilog.Sinks.File" Version="6.0.0" />
    <PackageReference Include="Serilog.Sinks.Console" Version="6.0.0" />
  </ItemGroup>
```

다음은 Serilog의 Logger Configuration 메서드이다.
```csharp
    var log_file_name = $"log-{DateTime.Now:yyyy-MM-dd}.txt";
    var log_file_path = Path.Combine(log_folder_dir, log_file_name);
    Log.Logger = new LoggerConfiguration()
      .MinimumLevel.Debug() // set log level
      .WriteTo.File(
        path: log_file_path,
        rollingInterval: RollingInterval.Infinite,
        flushToDiskInterval: TimeSpan.FromMilliseconds(1500),
        outputTemplate: "{Timestamp:HH:mm:ss} [{Level:u3}] {Message}{NewLine}{Exception}",
        shared: true
      )
      .CreateLogger();
```
ASP.NET에서는 DI container에서 Logger를 Serilog logger로 설정하는게 가능하지만, 그게 아니라 일반 console application의 DI container에서는 그렇게 못하는걸로 알고 있다..
그래서 그냥 저런식으로 `Log.Logger`에다가 Logger setting을 하고 `Log.Debug`를 전역적으로 사용해야한다.
`ILogger` interface를 사용하고 싶은 마음이 굴뚝같지만 console app에서는 얄짤없다. 

우선 `path:`를 통해 어떤 로그 파일에 기록할건지 정해야한다. 나는 `log_file_name`을 DateTime의 오늘 날짜를 이용해서 포매팅 했다. 이렇게 하면 자동으로 오늘자 로깅 파일이 만들어진다.
`rollingInterval`은 하루 단위, 한 달 단위 또는 매 분, 매 초마다 등으로 설정해줄 수 있는데, 나는 어차피 앞서서 file_name을 DateTime을 통해 formatting했으므로 그냥 `Infinite`로 설정했다.

참고로 마지막 옵션인 `shared: true`로 해주면 동시에 여러 프로그램이 하나의 로그 파일에 동시 기록하는것이 가능해진다. 
참고참고로 Serilog의 SQLite sink를 이용해봤는데, 이상하게도 여러 프로그램 동시 logging이 잘 안됐다. 왜인지는 나도 모르겠지만 아마도 내부적으로 db에 lock을 걸고 있는것 같기도 하고. 알송달송이다. 그래서 어쩔 수 없이 file 기반 logging을 다시 쓴건데.. 이건 동시에 여러 프로그램 로깅이 잘 되는것으로 보인다.