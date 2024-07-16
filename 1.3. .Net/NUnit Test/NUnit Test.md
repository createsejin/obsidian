일단 기본적으로 [이 공식 문서](https://learn.microsoft.com/en-us/dotnet/core/testing/unit-testing-with-nunit)를 참조하면, [[library project 구성하기|library project]]에 대한 NUnit Test Project를 만드는 방법을 알려주고 있다. 기본적으로 최상단 폴더를 만든뒤, `dotnet new sln`을 이용해서 solution file을 만든다. 그 뒤, 하위 폴더 `PrimeService`를 만들어서 그 위치에서
`dotnet new classlib`을 통해 library project를 만든다. 그리고 다시 루트 폴더로 돌아가서 
`dotnet sln add PrimeService/PrimeService.csproj`를 해줘서 루트의 솔루션 파일에 `PrimeService`의 project file을 추가해준다.
그후 루트 폴더에서 `PrimeService.Tests` 폴더를 만들어준다. 이 폴더는 NUnit test suit 폴더이다. 
이 폴더로 위치를 변경한 후, `dotnet new nunit` 명령어를 통해 NUnit Test Project를 만들어준다. 그 후, 앞서 만든 lib project를 참조하기 위해 `dotnet add reference ../PrimeService/PrimeService.csproj` 명령어를 통해 lib project의 namespace를 사용할 수 있게 만든다.
그 후 최종적으로 `dotnet sln add ./PrimeService.Tests/PrimeService.Tests.csproj`를 통해 NUnit test Project를 루트 솔루션 파일에 추가해준다. 이렇게 줄글로 써놓으니 나중에 읽으면 너무 어려워질것 같은데, 그럴 경우에는 그냥 위 [공식 문서](https://learn.microsoft.com/en-us/dotnet/core/testing/unit-testing-with-nunit)를 참고하자.

작업 후, 최종적인 폴더 구조는 다음과 같다.
```
/unit-testing-using-nunit
    unit-testing-using-nunit.sln
    /PrimeService
        Source Files
        PrimeService.csproj
    /PrimeService.Tests
        Test Source Files
        PrimeService.Tests.csproj
```

이걸 응용하면 바이너리 프로젝트도 NUnit을 이용해서 unit test가 가능한데, 우선은 나는 심플한 console project를 만들었다.
```
mkdir MyProgram
cd MyProgram
dotnet new console
```
그 후 다시 루트 폴더로 돌아간다.
```
cd ..
dotnet sln add MyProgram\MyProgram.csproj
```
그 후 `PrimeService.Tests`로 들어간다.
```
cd PrimeService.Tests
dotnet add reference ..\MyProgram\MyProgram.csproj
```
이렇게 하면 대략 구조는 다음과 같다.
```
 creat@bae ~\....\unit-testing-using-nunit  master  tree 2       
-N  .
-N ├──  MyProgram
-I │  ├──  bin
-N │  ├── 󰌛 MyProgram.csproj
-I │  ├──  obj
-N │  ├── 󰌛  Program.cs
-N │  └── 󰌛  test001.cs
-- ├──  PrimeService
-I │  ├──  bin
-I │  ├──  obj
-- │  ├── 󰌛  PrimeService.cs
-- │  └── 󰌛 PrimeService.csproj
-M ├──  PrimeService.Tests
-I │  ├──  bin
-I │  ├──  obj
-M │  ├── 󰌛 PrimeService.Tests.csproj
-M │  └── 󰌛  PrimeService_IsPrimeShould.cs
-M └──  unit-testing-using-nunit.sln
```

`MyProgram/test001.cs`에는 아주 간단한 `Add` 메서드를 추가해줬다.
```csharp
namespace MyProgram.test001;

public class MyClass
{
  public static int Add(int x, int y) 
  {
    return x + y;
  }
}
```

`PrimeService.Tests/PrimeService_IsPrimeShould.cs` 는 다음과 같다.
```csharp
using Prime.Services;
using MyProgram.test001;

namespace Prime.UnitTests.Services;

[TestFixture]
public class PrimeService_IsPrimeShould
{
  private PrimeService _primeService;

  [SetUp]
  public void Setup()
  {
    _primeService = new PrimeService();
  }

  [Test]
  public void IsPrime_InputIs1_ReturnFalse()
  {
    var result = _primeService.IsPrime(1);
    Assert.That(result, Is.False, "1 should not be prime");
  }

  [TestCase(-1)]
  [TestCase(0)]
  [TestCase(1)]
  public void IsPrime_ValuesLessThan2_ReturnFalse(int value)
  {
    var result = _primeService?.IsPrime(value);
    Assert.That(result, Is.False, $"{value} should not be prime");
  }

  [Test]
  public void TestAddFunc()
  {
    var result = MyClass.Add(2, 4);
    Assert.That(result, Is.EqualTo(6));
  }
}
```
Test가 총 3개가 있다. 그런데 두번째 Test를 보면 `[TestCase(0)]`이란게 있다. 이것은 `value`가 0, -1, 1 일때를 테스트해준다. 아마도 여러가지 파라미터를 넘기는게 가능해보인다. 이에 대한 자세한 사항은 [NUnit 공식 문서](https://docs.nunit.org/articles/nunit/intro.html)를 참고하자. 
이 중 마지막 Test가 위에서 만든 바이너리 프로젝트의 메소드에 대한 Test이다.

이렇게 작성한 후, 루트 폴더에서 
```
dotnet test
```
를 하면 test 결과가 출력된다. 

참고로 Assertion Model은 [Constraint Model](https://docs.nunit.org/articles/nunit/writing-tests/assertions/assertion-models/constraint.html)을 쓰는것이 권장된다고 한다. Constraints는 [여기](https://docs.nunit.org/articles/nunit/writing-tests/constraints/Constraints.html)에서 확인할 수 있다.