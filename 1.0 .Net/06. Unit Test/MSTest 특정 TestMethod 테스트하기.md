기본적인 방법은 [[NUnit 특정 클래스만 테스트하기|NUnitTest]]를 이용한 방법과 거의 동일하다. 다만 MSTest에서는 기본적으로 Console output을 제공하지 않으므로 Console 출력을 표시하려면 `--logger` 옵션을 추가해야한다.
```powershell
dotnet test --filter FullyQualifiedName=MSTest.UnitTest1.TestMethod1 --logger "console;verbosity=detailed"
```

```powershell
function MSTestClassMethodNumberdTest {
  param (
    [Parameter(Mandatory = $true)]
    [int]$class,
    [int]$method
  )
  if (0 -eq $method) {
    dotnet test --filter ClassName=MSTest.UnitTest$class --logger "console;verbosity=detailed"   
  }
  else {
    dotnet test --filter FullyQualifiedName=MSTest.UnitTest$class.TestMethod$method --logger "console;verbosity=detailed"   
  }
}
if ($args[0] -is [int]) {
  MSTestClassMethodNumberdTest $args[0] $args[1]
} 
```
이런식으로 함수를 지정해서 쓰면 `.\test 1 2` 또는 `.\test 1` 요런식으로 특정 테스트를 손쉽게 테스트 할 수 있다. 
이렇게 하려면 Test class는 `UnitTest1` 이런 형식으로, Test method는 `TestMethod1` 이렇게 간단하게 만들면 된다. 사실 이 방식은 기본적으로 MSTest의 기본 템플릿에서 제공하는 이름인데, 이 방식이 가장 사용하기가 간결하고 편리한것같다. 