서로 다른 역할을 하는 서버들을 여러개 만들거고, 요청을 입력하는 클라이언트를 만들거다.
서로 다른 별도의 프로세스에서 동작한다. 
우선은 `Commander`를 클라이언트로 만들것이다. 이것은 명령어를 입력해서 `Controller`에 전달한다. 
전달 방식은 [명명된 Pipe](https://learn.microsoft.com/en-us/dotnet/api/system.io.pipes.namedpipeclientstream?view=net-8.0)를 이용한다. 
`Controller`는 받은 명령어를 명령어 큐에 저장하고 하나씩 꺼내어 받은 명령을 분석하고 필요한 작업을 다른 서버 프로세스에 파이프로 요청한다. 서버는 `Searcher`, `Unzipper` 등이 있다. `Searcher`는 selenium web driver를 구동해서 요청의 메세지를 받아서 필요한 데이터를 인터넷으로 검색하고 필요한 데이터를 반환한다. `Unzipper`는 요청 받은 file_path를 받아서 unzip을 하고 완료가 되면`Controller`에 보고한다. `Searcher`도 역시 완료된 결과를 `Controller`에 전송한다. `Controller`는 일종의 서버 오케스트레이션 작업을 한다. 여러가지 데이터를 큐로 저장해서 필요할때마다 각 서버에 작업 요청을 한다. 

각 서버는 파이프 데이터를 받을 메세지 루프를 가져야한다. 