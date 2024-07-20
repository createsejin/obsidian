최상단에 solution 파일을 두고, [[project workspace|workspce 형식]]으로 project를 구성하는 경우가 있다. 
```
--  .
-- ├──  Commander
-- ├──  main.sln
-- ├──  Monitor
-- ├──  NUnitTest
-- ├──  Operator
-- ├──  MyLib
-- └──  WavManager
```
예를들어서 이런 [[the_cave Operator class relationship.canvas|the_cave]] 프로젝트가 있다고 하면, `MyLib`를 `SharedLib`로 이름을 바꿔보자.
우선 각 sub project들의 명확한 reference 의존 관계를 알아야한다. 이것은 VSCode의 solution explorer를 보면 쉽게 알 수 있는데, 이걸 활성화하려면 최상단의 solution 파일을 VSCode로 열면 된다. 나는 보통 VSCode workspace 파일로 프로젝트를 여는걸 선호한다. 이걸로 열어야 현재 프로젝트의 모든 세부적인 작업 세션을 유지할 수 있기 때문이다. 
아무튼 solution explorer를 열고 각 sub project에서 Dependencies -> Projects 항목을 보면 `MyLib`가 있는 프로젝트들이 있다. 이런식으로 solution explorer에서 `MyLib` 의존적인 프로젝트를 전부 띄워놓으면 편리하다. 
그러면 이제 어떤 sub project들이 `MyLib`를 의존하는지 알았으면, 우선 가장 먼저 해야할 일은 각 프로젝트 폴더로 각각 들어가서 
```powershell
cd .\Commander\
dotnet remove reference ..\MyLib\MyLib.csproj

cd ..\NUnitTest\
dotnet remove reference ..\MyLib\MyLib.csproj

cd ..\Operator\
dotnet remove reference ..\MyLib\MyLib.csproj

cd ..\WavManager\
dotnet remove reference ..\MyLib\MyLib.csproj
```
각각의 sub project에서 `MyLib`의 reference를 remove하는 것이다.

그 후, 다시 최상단으로 가서 solution에서 `MyLib`를 제거한다.
```powershell
cd ..
dotnet sln remove .\MyLib\MyLib.csproj
```

그 후, `MyLib`의 `MyLib.csproj` 파일의 이름과 그 프로젝트의 폴더 이름을 바꾼다.
```powershell
cd .\MyLib\
mv .\MyLib.csproj SharedLib.csproj
cd ..
mv .\MyLib\ SharedLib
```

그리고 다시 최상단에서 솔루션에 `SharedLib`를 추가해준다.
```powershell
dotnet sln add .\SharedLib\SharedLib.csproj
```

각각의 sub project에 들어가서 `SharedLib\SharedLib.csproj` 를 reference로 add해준다.
```powershell
cd .\Commander\
dotnet add reference ..\SharedLib\SharedLib.csproj

cd ..\NUnitTest\
dotnet add reference ..\SharedLib\SharedLib.csproj

cd ..\Operator\
dotnet add reference ..\SharedLib\SharedLib.csproj

cd ..\WavManager\
dotnet add reference ..\SharedLib\SharedLib.csproj
```

그 후, 다시 `SharedLib`로 가서 그 내부에 있는 소스파일에서 namespace를 vscode name refactor로 `SharedLib`로 바꿔주면 알아서 이 프로젝트를 의존하고 있는 다른 sub project들의 소스 using문도 `MyLib`에서 `SharedLib`로 자동으로 바뀐다. 혹시 모르니 workspace explorer를 띄워서 에러가 있는지 체크해준다.