예를 들어서 다음과 같은 메서드가 있다고 해보자. 
```csharp
  public void TabList()
  {
      searcher.TabTreePrint();
  }
```
이 메서드는 [[the_cave Operator class relationship.canvas|the_cave]] 프로젝트에서 `CommandOperator` 클래스의 메서드이며, `CommandMessenger` thread 위에서 동작한다.

그런데 이 메서드의 안쪽을 보면 `searcher`로부터 메서드를 호출하고 있다. 이 `TabTreePrint()` 메서드는 다음과 같다.
```csharp
  public void TabTreePrint()
  {
    lock (searchOperator.TabRootLock)
    {
      var tab_root = searchOperator.TabRoot;
      TabTree(tab_root);
    }
  }
```
이런식인데, 여기에서 `tab_root`는 `CommandMessenger` thread와 `Searcher` thread 모두 공유하는 자원이기 때문에 lock object를 `SearcherOperator` 클래스에서 만들어서 관리한다. 
이렇게 하면 어떤 문제가 발생할까? 우선 내가 경험한 문제는, `TabTreePrint` 메서드를 다른 thread인 `CommandMessenger` 측에서 이렇게 호출할 경우 데드락 상태에 빠지는걸 보았다. 정확한 이유는 나도 잘 모르겠다. 

하지만 다음과 같이 바꾼다면?
```csharp
  public void TabList()
  {
    lock (searcher.TabRootLock)
    {
      searcher.TabTreePrint();
    }
  }
```

```csharp
  public void TabTreePrint()
  {
    var tab_root = searchOperator.TabRoot;
    TabTree(tab_root);
  }
```
이렇게 하면 lock을 호출 측인 `CommandMessenger`에서 lock을 제대로 걸게 되서 데드락이 발생하지 않는다. 
그러니까 말하자면, 각 스레드가 공유하는 자원의 동시 접근을 제어하기 위해 `lock`을 사용하려면 반드시 그 스레드에서 동작하는 메서드에서 `lock`을 사용해야한다는 것이다. 
앞선 문제의 코드의 경우에는 `lock`을 엉뚱한 다른 스레드 메서드에서 얻고 있었다. 이렇게 사용하면 안된다는 것이다. 