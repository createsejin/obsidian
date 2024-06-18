이 [문서](https://learn.microsoft.com/en-us/dotnet/core/deploying/native-aot/?tabs=net8plus%2Cwindows)를 참고하자.

AOT 빌드란 뭘까. 그러니까 닷넷은 실행파일로 build 되면 IL이라는 중간 언어. CPU와 플랫폼에 종속되지 않은 언어를 생성한다. 이것을 실행파일이 실제 실행될때 JIT라는 컴파일러가 어셈블리어로 변환해서 기계어를 실행하는 방식이다. 문제는 실행시 이 컴파일 과정이 추가적으로 필요하므로 startup 시간에 영향이 있을 수 있다는 것이다. AOT는 이러한 과정을 미리 publish 과정에서 처리해준다. 이러면 변환 과정이 필요가 없어서 실행시간이 매우 짧아지는 효과가 생긴다. 다만 이 경우에는 target에 종속적인 실행파일이 만들어지므로 publish 할때 주의해야한다는 것.
기본적으로 windows x86_64 기준으로 
```
<PropertyGroup>
    <PublishAot>true</PublishAot>
</PropertyGroup>
```
위 코드를 project의 `.csproj` 파일에 추가 후 아래 커맨드로 publish 한다.
```
dotnet publish -r win-x64 --self-contained -c Release
```

그런데 이렇게 해보니 문제점도 발생했다. 
```
C:\Users\creat\Projects\the_cave\collections\tests\file_analysis_test\tests\test001_file_analyse.cs(41,41): warning IL3050: Using member 'System.Linq.Queryable.AsQueryable<TElement>(IEnumerable<TElement>)' which has 'RequiresDynamicCodeAttribute' can break functionality whe
n AOT compiling. Enumerating in-memory collections as IQueryable can require creating new generic types or methods, which requires creating code at runtime. This may not work when AOT compiling. [C:\Users\creat\Projects\the_cave\collections\tests\file_analysis_test\file_ana
lysis_test.csproj]
C:\Users\creat\Projects\the_cave\collections\tests\file_analysis_test\tests\test001_file_analyse.cs(41,41): warning IL2026: Using member 'System.Linq.Queryable.AsQueryable<TElement>(IEnumerable<TElement>)' which has 'RequiresUnreferencedCodeAttribute' can break functionalit
y when trimming application code. Enumerating in-memory collections as IQueryable can require unreferenced code because expressions referencing IQueryable extension methods can get rebound to IEnumerable extension methods. The IEnumerable extension methods could be trimmed
causing the application to fail at runtime. [C:\Users\creat\Projects\the_cave\collections\tests\file_analysis_test\file_analysis_test.csproj]
```
아마도 LinQ의 일부 기능이 정상적으로 동작하지 않을것이라는 경고 메세지다. 그러나 이 경고도 `AsQueryable`를 사용하지 않고 바로 LinQ 메소드를 사용하면 사라진다.\

아무튼, publish 명령을 때리면 `bin/Release/net8.0/win-x64/native`에 실행파일이 하나 담긴다. 이것을 배포하면 되는것으로 보인다.

아무래도 외부에서 쉘을 통해 자주 여러번 실행이 필요한 경우에는 이것을 쓰는게 좋아보인다. 

단점으로는 아무래도 배포되는 실행파일이 플랫폼에 종속되고, .Net runtime이 모두 포함되므로 실행파일 용량이 커진다는 점이다.