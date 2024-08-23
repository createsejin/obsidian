[공식 문서](https://learn.microsoft.com/en-us/dotnet/core/extensions/dependency-injection)
[[DI container|이 글]]에서는 the_cave project에서 DI가 쓰이게 된 배경에 대해서 설명하고 있다. 또한 순환 의존(defendency circuit)를 피하기 위해서 이런 [[the_cave Operator class relationship.canvas|도식]]을 만들어서 각 클래스간의 의존성을 그래프로 나타내는게 도움이 됐다.

다음은 `Main` 메서드의 DI 컨테이너를 사용하기 위한 Host를 만들고 `Run`하는 코드다.
```csharp
	  HostApplicationBuilder builder = Host.CreateApplicationBuilder(args);
      builder.Services.AddHostedService<ControllerService>();
      builder.Services.AddSingleton<IMainMessenger, MainMessenger>();
      builder.Services.AddSingleton<ICancellationTokenProvider, CancellationTokenProvider>();
      builder.Services.AddSingleton<IController, Controller>();
      builder.Services.AddSingleton<ICommandMessenger, CommandMessenger>();
      builder.Services.AddSingleton<ICommandOperator, CommandOperator>();

      builder.Services.AddHostedService<SearcherService>();
      builder.Services.AddSingleton<ISearcher, Searcher>();
      builder.Services.AddSingleton<ISearchOperator, SearchOperator>();
      builder.Services.AddSingleton<ITabNodeHandler, TabNodeHandler>();
      builder.Services.AddSingleton<ISearcherTaskHandler, SearcherTaskHandler>();
      builder.Services.AddSingleton<IThreadLinkHandler, ThreadLinkHandler>();

      builder.Services.AddHostedService<DuplicatedWavDetactorService>();
      builder.Services.AddSingleton<IDuplicatedWavDetactor, DuplicatedWavDetactor>();
      builder.Services.AddSingleton<IFileAnalyzer, FileAnalyzer>();
      
      using IHost host = builder.Build();
	  host.Run();
```
여기에서 `AddHostedService` 는 
```csharp
public class ControllerService(IController controller,
  ICancellationTokenProvider cancellationTokenProvider) : BackgroundService
{
  protected override Task ExecuteAsync(CancellationToken stoppingToken)
  {
    var linkedTokenSource = CancellationTokenSource
      .CreateLinkedTokenSource(stoppingToken, cancellationTokenProvider.Token);
    return Task.Run(controller.Run, linkedTokenSource.Token);
  }
}
```
이런식으로 `BackgroundService`를 이용해서 Background에서 별도 스레드 위에서 동작하는 서비스를 위해서 만들어졌다. 
주로 `CommandMessenger`, `Searcher`, `DuplicatedWavDetactor`처럼 Thread Event Loop를 가지는 서비스가 이걸 필요로 한다.

또한 나는 여기에 `ICancellationTokenProvider`를 도입해서 여러가지 Thread를 협력적으로 종료하는 코드를 작성했었다.

중요한건 `AddSingleton`에서 각각 interface와 구현체로 묶이는 애들. 
말 그대로 Singleton 서비스 객체 인스턴스들을 DI 컨테이너가 관리해준다.

DI 컨테이너는 좋은점이 의존성 순환(defendency circuit)을 아주 정확하게 detact 해준다. 
적어도 DI 컨테이너를 사용하면 이런 문제를 잘 보여주기 때문에 의존성 순환 문제를 해결하는데 아주 큰 도움이 된다. 

DI 컨테이너를 사용하면 좋은점 중 가장 중요한게 interface를 통한 의존성 클래스의 참조를 이용할 수 있다는 점인데.
```csharp
class CommandMessenger(IMainMessenger main_msger, ICommandOperator commandOperator,
  ICancellationTokenProvider cancellationTokenProvider)
 : ICommandMessenger
{
  private readonly ConcurrentQueue<string> _command_queue = [];
  public ConcurrentQueue<string> CommandQueue
  {
    get => _command_queue;
  }
  private readonly NamedPipeServerStream _server = new("commander_pipe", PipeDirection.InOut);
  private StreamReader? _stream_reader;
  private StreamWriter? _stream_writer;
  public void CommandQueueing()
  {
    while (_command_queue.TryDequeue(out string? cmd))
    {
      if (!string.IsNullOrEmpty(cmd))
        CommandParser(cmd);
    }
  }
  ...
```
이런식으로 Primary Constructor에 interface를 쏙쏙 집어넣으면 class 전체에서 저 interface를 통해서 의존성 클래스의 메서드, 속성 등을 자유롭게 사용할 수 있다.
다만 주의할점은 앞서 말했듯이, Defendency circuit이 발생하지 않게끔 클래스 구조를 잘 짜는 것이 핵심이다. 
나는 기존 코드가 완전히 엉망이었다. DI를 사용하고 circuit을 발견했고, 그것을 해결하는 과정에서 그나마 나은 상태의 클래스 구조를 짤 수 있었다. 
이런 부분은 확실히 좋은점이었다. 왜냐면 의존성 순환은 사실 개발자에게 있어서 발견하기가 되게 힘들다. 개발자는 사람이기 때문에 반드시 실수할 수 있는 부분을
이런 DI framework를 통해 일정 부분 해소할 수 있었던 것. 

게다가 이런식으로 interface를 활용하기 때문에 클래스간 결합도가 낮아지고, 더 유연하게 각 클래스를 사용할 수 있다는점도 좋았다.

가장 좋은점은 클래스 구조의 개편을 통한 데이터 flow의 재편이었다. 클래스의 의존도는 데이터와 컨트롤의 흐름과 유사하다는 생각이 들었다.