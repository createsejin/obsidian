[참고 문헌](https://learn.microsoft.com/en-us/dotnet/csharp/asynchronous-programming/task-asynchronous-programming-model)

![What happens in an async method](https://learn.microsoft.com/en-us/dotnet/csharp/asynchronous-programming/media/task-asynchronous-programming-model/navigation-trace-async-program.png#lightbox)

1. 먼저 비동기 메서드 `GetUrlContentLengthAsync`를 호출 측에서 호출한다.
2. 이 비동기 메서드 바디에서 `client.GetStringAsync` 비동기 메서드를 호출한다. 
3. 비동기 메서드인 `GetStringAsync`의 리턴값을 `Task<string>` type의 변수인 `getStringTask`에 저장한다.
4. 일반적인 메서드 호출이다.
5. 일반 메서드 호출이 끝나고 다시 호출 위치로 리턴한다.
6. 이제 `await` 키워드를 만나서 아직 `getStringTask` 작업이 끝나지 않았으면 여기에서 `GetUrlContentLengthAsync`의 호출 측으로 컨트롤을 넘긴다.
7. 만약 `getStringTask` 작업이 완료되면 `Task<string>`의 Result 값인 `string` type의 객체를 얻는다.
8. 최종적으로 `contents`의 길이를 계산하고 이를 호출 측에 반환한다.