예를 들어 현재 만들고 있는 `Controller`라는 class는 내부 멤버 변수로 `Searcher` class의 인터페이스인 `ISearcher`를 가지고 있다. 이런식으로 interface를 사용하는 이유는 각 클래스간의 결합도 감소와 인터페이스 추상화를 꾀해 `Controller` class에서 `Searcher`의 내부 구현사항과 관계 없이 interface를 통해 `Searcher`를 사용하도록 하는 방법이다. interface로 구성하면 노출될 interface 메서드만 노출시키면 되고, 외부 사용자가 그 구현사항을 알 필요 없이 interface를 통해 그 클래스의 기능을 사용하게 된다. 

```csharp
public class Controller : IController
{
  private readonly ISearcher _searcher;

  public Controller(SearcherFactory searcherFactory)
  {
    _searcher = searcherFactory.Create(this, _main_msger, _wait_for_searcher);
  }
```
또한 여기에서는 Factory 패턴이라는게 사용됐다.  `Controller`에 `searcherFactory`를 주입하고 있다. 
이것을 주입하는 시점은 main method에서 다음과 같이 주입했다.

```csharp
  public static void Main(string[] args)
  {
    SearcherFactory searcherFactory = new();
    Controller controller = new(searcherFactory);
    controller.Run();
  }
```

`Searcher`의 interface인 `ISearcher`, Factory인 `SearcherFactory`, Factory의 interface인 `ISearcherFactory`는 다음과 같이 구현됐다.
```csharp
public interface ISearcherFactory
{
  ISearcher Create(IController controller, MainMessenger main_msger, AutoResetEvent wait);
}
public class SearcherFactory : ISearcherFactory
{
  public ISearcher Create(IController controller, MainMessenger main_msger, AutoResetEvent wait)
  {
    return new Searcher(controller, main_msger, wait);
  }
}

public interface ISearcher
{
  void SearcherLoop();
}
class Searcher : ISearcher
{
  private readonly IController _controller;
  private readonly MainMessenger _main_msger;
  private readonly ChromeDriver _driver;
  private readonly AutoResetEvent _wait;

  public Searcher(IController controller, MainMessenger main_msger, AutoResetEvent wait)
  {
    _controller = controller;
    _main_msger = main_msger;
    _wait = wait;
    _driver = new();
    _driver.Manage().Timeouts().ImplicitWait = TimeSpan.FromSeconds(8);
  }
  public void SearcherLoop()
  {
    while (true)
    {
      _main_msger.EnqueueAndPrint("wait for search command..");
      _wait.WaitOne();
      //@#sear.loop
    }
  }
}
```

이런식으로 interface를 사용하면 클래스간의 결합도를 낮출 수 있고, 사용자 입장에서도 그 클래스의 세부 구현사항을 알 필요 없이 노출된 interface를 통해 사용하므로 코드의 readability도 높아진다.
이렇게 interface를 통해서 외부 클래스를 다루게 되면 직접 클래스를 다루는것보다 조금더 안전해지고 encapsulation된 interface method를 사용하게 되는 것이다.
또한 클래스의 구현사항이 바뀌더라도 인터페이스가 유지되는한 사용자 입장에서 구현사항이 바뀐것에 대해 신경쓸 필요가 없게된다. 구현하는 입장에서도 편리해진다. 구현과 인터페이스는 분명히 구분되기 때문에 구현자 역시 인터페이스를 기준삼아 내부 구현만 다시 refactoring하면 된다.