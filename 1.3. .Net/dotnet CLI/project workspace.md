```
-N  root
-N ├──  Commander
-I │  ├──  bin
-N │  ├── 󰌛  Commander.cs
-M │  ├── 󰌛 Commander.csproj
-I │  ├──  obj
-- │  └── 󰌛  Program.cs
-- ├──  Downloader
-I │  ├──  bin
-- │  ├── 󰌛 Downloader.csproj
-- │  ├──  Downloader.sln
-I │  ├──  obj
-- │  ├── 󰌛  Program.cs
-- │  ├── 󰌛  runtest.cs
-- │  ├── 󰌛  searcher.cs
-- │  ├── 󰌛  unzipper.cs
-- │  └── 󰌛  wav_convertor.cs
-M ├──  downloader.sln
-M ├──  Downloader.tests
-I │  ├──  bin
-M │  ├── 󰌛 Downloader.tests.csproj
-I │  ├──  obj
-M │  └── 󰌛  UnitTest1.cs
-N └──  SharedModel
-I    ├──  bin
-I    ├──  obj
-N    ├── 󰌛  SharedModel.cs
-N    └── 󰌛 SharedModel.csproj
```
기본적으로는 구조를 이런식으로 잡을 수 있다. 
최상단에서 
```powershell
dotnet add sln
```
을 통해 최상단 솔루션 파일을 만든다.

```
dotnet new classlib -o SharedModel
```
을 이용해서 클래스 라이브러리 프로젝트를 `SharedModel` 하위폴더로 만든다.

```
dotnet sln add SharedModel\SharedModel.csproj
```
이런식으로 하위 프로젝트를 루트 솔루션 파일에 추가할 수 있다.

```
dotnet new console -o Commander
```
이걸로 바이너리 프로젝트 `Commander`를 하위 폴더에 만든다.
그리고 그 폴더 위치로 가서,
```
cd Commander
dotnet add reference ..\SharedModel\SharedModel.csproj
```
이런식으로 클래스 라이브러리 프로젝트의 참조를 `Commander` project에 추가할 수 있다.

또한 이와 비슷한 방식으로 NUnit test project를 만들 수 있는데 이것은 [[NUnit Test|이 글]]을 참조하자.