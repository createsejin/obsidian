```csharp
public class Controller : IController
{
  private static readonly ConcurrentQueue<Thread> _thread_q = new();
  private static readonly MainMessenger _main_msger = new();
```
static 멤버는 이렇게 선언하자마자 초기화해주는게 좋다.

```csharp
  private ConcurrentQueue<SearcherTask> _searcher_tasks;
  private readonly ConcurrentQueue<string> _command_q;
  
  public Controller()
  {
    _command_q = new();
    _searcher_tasks = new();
```
instance 멤버는 생성자 안에서 초기화해주는게 좋다.

