현재 진행되고 있는 내 프로젝트중 the_cave 프로젝트에서 selenium이나 [[반디집 bz command line tool|unzipper]]와 같은 network IO 또는 file IO가 발생하는 부분에서 [[비동기, 동기 방식|비동기 프로그래밍을 도입하자]]고 얘기한게 있다. 그 부분을 오늘 일부분 완성했는데, 일단은 첫 느낌은 그렇게 막 어려운 부분은 아직은 없었다. 물론 이것을 세밀하게 제어하는데에는 당연히 그에 따른 마땅한 레퍼런스를 참조해서 정확한 인터페이스로 async Task를 처리해야할 것이다. 우선은 오늘 알게된 기본적인 사항을 적어볼까 한다.

우선은 나는 일단 Commander, command 입력 프로그램에서 `NamedPipeClientStream`을 통해 `NamedPipeServerStream`으로 커맨드를 `Controller`의 `CommandMassenger`를 통해 받았다. 이 부분은 지속적인 pipe 통신을 유지하고, 리스닝을 대기하기 위해서 동기적인 방식의 독립 스레드를 사용하였다. 따라서 이부분을 동작하는 코드에서는 `async` 메서드라던가, `await` 구문이 사용되지 않는다. 
```csharp
  public void Commander_pipe_loop()
  {
    while (true)
    {
      var stream_reader = new StreamReader(_server);
      var request = stream_reader.ReadLine();
      if (!string.IsNullOrEmpty(request))
      {
        CommandEnqueue(request);
        _controller.CommandQueueing();
        lock (_is_exit_lock) if (_is_exit) break;
        //@#cmd.loop
      }
      else _main_msger.EnqueueAndPrint("request is null");
    }
  }
  
  private void CommandEnqueue(string command)
  {
    _main_msger.EnqueueAndPrint($"received cmd: |{command}|");
    _command_q.Enqueue(command);
    var writer = new StreamWriter(_server);
    string response = "accepted";
    writer.WriteLine(response);
    writer.Flush();
    //@#cmd.enq
  }

  public void CommandQueueing()
  {
    while (_command_q.TryDequeue(out string? cmd))
    {
      if (!string.IsNullOrEmpty(cmd))
        CommandParserAsync(cmd).Wait();
    }
  }
```
마지막 command queue를 queueing하는 부분에서 `CommandParserAsync(cmd).Wait();`을 주목해보자. 이것은 `async` 메서드인`CommandParserAsync`의 작업이 모두 완료되기까지 기다린다는 코드다.

이제 본격적으로 `await` 키워드가 사용되는 `CommandParserAsync` `async`메서드를 살펴보자.
```csharp
  private async Task CommandParserAsync(string command)
  { // parsing command queue and operate commands
    var trimed_cmd = command.Trim();
    string[] args;
    if (!string.IsNullOrEmpty(trimed_cmd))
    {
      args = trimed_cmd.Split(' ');
      if (args[0] == "down" && args.Length == 2)
      {
        var searcher_task = _searcherFactory.CreateTask(args[0], args[1]);
        _searcher_tasks.Enqueue(searcher_task);
        await _searcher.QueueingTasksAsync();
        //@#ctl.par
      }
      else if (trimed_cmd == "exit")
      {
        await _searcher.QueueingTasksAsync();
        ExitPrograms();
      }
      else if (args[0] == "-t" && args.Length == 2)
      {
        Test(args[1]);
        await _searcher.QueueingTasksAsync();
      }
      else _main_msger.EnqueueAndPrint($"Unhandled request.");
    }
  }
```
 기본적으로 `await` 키워드는 `async` 메서드 호출을 요구한다. 즉 `QueueingTasksAsync()`는 `async`, 즉, 비동기로 동작하는 메서드이며, 이것을 호출할때 `await` 키워드가 사용되는 것이다. 또한 이 메서드처럼 메서드 바디에 `await` 키워드를 통해 하나라도 `async` 메서드를 호출했다면 이 메서드는 `async` 키워드를 사용해야 하며, Task 기반의 비동기 메서드는 리턴 타입을 `Task`로 써야한다.
 `_searcher.QueueingTasksAsync()`는 `await` 키워드를 통해 비동기적으로 작업 흐름이 실행되고 있다. 그러나 나는 이것을 각각의 비동기 작업 스레드가 각각의 인스턴스들이 별도로 실행되는 방식이 아니라, 한 인스턴스(`_searcher`)가 TaskObj Queue(`_searcher_tasks`)에 넣어진 TaskObj를 바탕으로 작업을 진행한다. 이 TaskObj Queue는 `ConcurrentQueue`로, thread safe한 큐이다. 따라서 `_searcher`는 큐에 담긴 TaskObj를 바탕으로 안전하게 순서대로 작업을 진행할 수 있게 된다.

```csharp
  public async Task QueueingTasksAsync()
  {
    while (_controller.SearcherTasks.TryDequeue(out SearcherTask? task))
    {
      if (task.Command == "down")
      {
        if (_is_debug) task.Print();
        // string search_rj = task.RJ_num;
        _driver.Navigate().GoToUrl(_detailed_search);
      }
      else if (task.Command == "test")
      {
        switch (task.Test_num)
        {
          case 2:
            {
              await Test002Async();
              break;
            }
          default: break;
        }
      }
    }
  }
```
아직은 매우매우 약소하다. 그러나 분명히 이 메서드가 하는 일은 `_searcher_tasks` 큐에 담겨진 TaskObj들을 하나씩 처리하는 것이다. 이 부분은 반드시 Network IO가 발생하며 시간적으로 꽤나 큰 비용이 드는 작업이다. 따라서 이것을 비동기로 처리하여 코드 효율성을 꾀했다. 
