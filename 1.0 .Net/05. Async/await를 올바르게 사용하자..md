```csharp
  private async void Download(DownloaderTask downloader_task)
  {
    downloader.DownloadQueue.Enqueue(downloader_task.RapidDownloadLinks);
    await downloader.DownloadRapidFilesAsync();
    /*
    DownloadStart @@down*/
    SendResult(downloader_task, 0);
  }
```
이 코드의 문제점이 무엇일까. 특히 `DownloadRapidFilesAsync` 이 부분에서 file download. 즉 네트워크 IO가 발생하게된다. 이때 `await` 키워드는 이 작업이 끝날때까지 대기하겠다는 이야기다. 즉, 아래의 `SendResult`는 의도대로 실행되지 않는다. 원래 의도는 `DownloadRapidFilesAsync`를 비동기로 실행한 후 곧바로 `SendResult`를 실행해서 다운로드가 시작됐다는 알림을 MainMessenger에 보내는 것이다. 이런식으로 처리하려면 아래와 같이 코드를 구현해야한다.

```csharp
  private async void Download(DownloaderTask downloader_task)
  {
    downloader.DownloadQueue.Enqueue(downloader_task.RapidDownloadLinks);
    var async_task = downloader.DownloadRapidFilesAsync();
    /*
    DownloadStart @@down*/
    SendResult(downloader_task, 0);
    await async_task;
  }
```
바로 이런식이다. 일단 `async_task`에서 `DownloadRapidFilesAsync` 메서드가 반환하는 `Task`를 받는다. 그리고 곧바로 그 다음 동작인 `SendResult`를 처리한 후, 마지막 줄에서
`await` 키워드를 이용해서 앞서 받아놓은 `async_task`를 기다리는 것이다. 이렇게 하면 의도대로 코드가 동작한다. 

따라서 `await` 키워드의 [[await 작동 방식|정확한 작동 방식]]을 잘 알 필요가 있다. 만약 비동기 작업을 진행하면서 그 다음 코드가 실행되게 하려면 반드시 저런식으로 코드를 써야한다는 것이다.