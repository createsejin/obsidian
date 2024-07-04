[[Interface|이 글]]에서도 일부 다루고 있다. 
Factory pattern의 장점은 외부 의존성을 주입해서 편리하게 인스턴스를 생성할 수 있다는 점이다.
```csharp
public interface IControllerFactory
{
  public Controller Create();
  IMainMessenger CreateMainMessenger();
  ICommandMessenger CreateCommandMessenger(IController controller,
    ConcurrentQueue<string> CommandQ, IMainMessenger main_msger);
}
public class ControllerFactory(ISearcherFactory searcherFactory, IMainMessenger main_msger)
 : IControllerFactory
{
  public Controller Create()
  {
    return new Controller(searcherFactory, this, main_msger);
  }
  public IMainMessenger CreateMainMessenger()
  {
    return new MainMessenger();
  }
  public ICommandMessenger CreateCommandMessenger(IController controller,
  ConcurrentQueue<string> CommandQ, IMainMessenger main_msger)
  {
    return new CommandMessenger(controller, CommandQ, main_msger);
  }
}
```
예를 들어서 현재 진행중인 [[비동기, 동기 방식|the_cave]] 프로젝트의 `ControllerFactory`를 살펴보자. 
의존성 주입이라는건 뭘까. 일단 여기에서는 인스턴스를 생성할때 필요한 외부 인스턴스 참조라던가 값, 또는 객체 등을 말할 수 있겠다. 이것을 설명하기 위해 `ControllerFactory`가 쓰인 다음의 `main` 메서드를 살펴보자.
```csharp
  public static void Main(string[] args)
  {
    MainMessenger main_msger = new();
    SearcherFactory searcherFactory = new(main_msger);
    ControllerFactory controllerFactory = new(searcherFactory, main_msger);
    
    Controller controller = controllerFactory.Create();
    controller.Run();
  }
```
이런식으로 Factory를 만들때 필요한 의존성을 각각 주입한다. 그 후 이 Factory를 이용해서 필요한 인스턴스를 `Create`하여 인스턴스 생성을 간편히 할 수 있다. 의존성 주입, 인스턴스의 간편한 생성. 이 두가지는 적어도 만족하는 것이다. 
인스턴스를 생성할때 여러가지 복잡한 생성자 매개변수를 주입된 의존성을 통해서 처리하는 코드를 내부에 구현하고, 외부에서는 단순히 `Create()`를 호출하면 된다. 이것은 말 그대로 Factory 그 자체다. 사용자는 주문만 하면 알아서 커스텀된 인스턴스가 만들어지기 때문이다.