NUnit에서 DI 컨테이너를 이용해서 어플리케이션의 일부 메서드를 테스트하려면 준비할게 좀 있다. 
우선 `DIContainer` 클래스를 하나 만들어야한다. 이렇게 따로 클래스를 만드는 이유는 이 클래스의 객체를 Test 클래스에서 생성하여 수명을 유지하기 위함이다.
```csharp
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using Operator.Components;
using SharedLib;

namespace NUnitTest.Tests;

class DIContainer
{
  public IHost? Host_ { get; }
  public DIContainer()
  {
    string[] args = [];
    HostApplicationBuilder builder = Host.CreateApplicationBuilder(args);

    builder.Services.AddSingleton<IMainMessenger, MainMessenger>();
    builder.Services.AddSingleton<IPrintUtils, PrintUtils>();
    builder.Services.AddSingleton<ICancellationTokenProvider, CancellationTokenProvider>();
    builder.Services.AddSingleton<ICommandOperator, CommandOperator>();

    builder.Services.AddSingleton<ISharedObject, SharedObject>();
    builder.Services.AddSingleton<ISearcher, Searcher>();
    builder.Services.AddSingleton<IDownloadOperator, DownloadOperator>();
    builder.Services.AddSingleton<ITabNodeHandler, TabNodeHandler>();
    builder.Services.AddSingleton<ISearcherTaskHandler, SearcherTaskHandler>();
    builder.Services.AddSingleton<ILinkHandler, LinkHandler>();
    builder.Services.AddSingleton<IMyHtmlParser, MyHtmlParser>();
    
    Host_ = builder.Build();
  }
}
```
이 클래스의 생성자에서 각종 서비스들을 등록해준다. 테스트할 프로젝트는 [[the_cave Operator class relationship.canvas|the_cave]] 프로젝트인데, 한가지 주의할점은 이 테스트는 단순한 `DownloadOperator`의 Run Test이기 때문에 구지 `SearcherService` 백그라운드 서비스를 등록할 필요는 없다는것이다. 다만 초기 설정인 `DriverStart`는 해줘야한다. 또한 원래 프로그램에서는 각 이벤트 루프가 종료되는걸 기다리기 위해 `host.Run()`을 동기적인 방식으로 블로킹을 했다. 그러나 여기에서는 단순히 `DownloadOperator`의 특정 메서드를 실행시키고 그 결과를 출력받는 테스트이기 때문에 구지 이벤트 루프 같은게 필요가 없다. 따라서 `host.Run()`이 아닌, `host.RunAsync()`메서드를 사용해서 host 서비스를 비동기적으로 실행시키고 그 후에 테스트 코드를 실행시키는 방식이다. 이렇게하면 코드가 블로킹되지 않기 때문에 메서드 Run 테스트에는 아주 좋은 방법이다. 

```csharp
public class Tests006
{
  private readonly DIContainer _dIContainer;
  private readonly IHost? _host;
  private readonly IPrintUtils? _printUtils;
  private readonly ICommandOperator? _commandOperator;
  private readonly ISearcher? _searcher;
  private readonly IDownloadOperator? _downloadOperator;
  public Tests006()
  {
    _dIContainer = new();
    if (_dIContainer.Host_ is not null)
    {
      _dIContainer.Host_.RunAsync();
      _host = _dIContainer.Host_;
    }
    if (_host is not null)
    {
      _printUtils = _host.Services.GetRequiredService<IPrintUtils>();
      _commandOperator = _host.Services.GetRequiredService<ICommandOperator>();
      _searcher = _host.Services.GetRequiredService<ISearcher>();
      _downloadOperator = _host.Services.GetRequiredService<IDownloadOperator>();
    }
  }
```
Test 클래스는 이런식으로 만들어둔다. 앞서 만든 DIContainer를 이 Test 클래스에서 인스턴스를 생성해주면 DI 컨테이너의 서비스들이 빌드되고, `_dIContainer.Host_.RunAsync()`을 통해 서비스를 비동기적으로 실행한다. 그 후, 각종 필요한 서비스를 host로부터 얻어서 그 참조를 멤버 변수에 등록해주면 편하다. 필요한것들만 얻어다가 등록해주면 된다.
여기서 주의할점은 서비스의 형태가 `Services.AddSingleton<IDownloadOperator, DownloadOperator>()` 이런식으로 interface와 묶인 서비스라면 반드시 `_host.Services.GetRequiredService<IDownloadOperator>()`이런식으로 인터페이스 객체를 요청해야한다는 것이다. 그게 아니라면 원본 객체를 요청하면 될 것이다.
또한 `GetRequiredService`는 Nullable한 result를 반환하기 때문에 어쩔 수 없이 멤버 변수를 Nullable로 지정해야한다. 
```csharp
  [SetUp]
  public void SetUp()
  {
    // Console input output encoding settings
    _printUtils?.StartLine("setup");
    Console.OutputEncoding = System.Text.Encoding.UTF8;
    Console.InputEncoding = System.Text.Encoding.UTF8;
    _searcher?.DriverStart();
    _downloadOperator?.TabTreePrint();
  }
```
따라서 위와같이 인터페이스를 사용할때 물음표를 붙여서 Nullable한 변수를 사용해야한다.

```csharp
  [Test]
  [TestCase("J219750")]
  public void Test021(string rj_num)
  {
    Console.WriteLine("Test021 start");
    SearchTask task = new()
    {
      Command = "down",
      RJ_num = rj_num
    };
    _downloadOperator?.DownloadRJ(task);
    _downloadOperator?.TabTreePrint();
    _printUtils?.StartLine("task doen");
    Console.WriteLine("\n");
    string[] args = ["exit", "-n"];
    _printUtils?.StartLine("exit program");
    _commandOperator?.ExitPrograms(args);
  }
```
최종적인 테스트코드는 위와 같다. 간단하게 `task`를 생성하고, `DonwloadRJ`를 진행한 후에 프로그램을 종료하는 코드(`ExitPrograms`)로 구성되어있다. 
