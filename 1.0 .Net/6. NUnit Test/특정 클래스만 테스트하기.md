test.ps1
```powershell
if ($args[0] -eq "2") {
  dotnet test --filter "FullyQualifiedName~NUnitTest.Tests.Tests002"
}
elseif ($args[0] -eq "3") {
  if ($args[1]) {
    $method = $args[1]
    dotnet test --filter "FullyQualifiedName~NUnitTest.Tests.Tests003.$method"
  }
  else {
    dotnet test --filter "FullyQualifiedName~NUnitTest.Tests.Tests003"
  }
}
```
이런식으로 script를 만들어 쓰면 유용하다. 
`.\test 3` 이런식으로 입력해서 원하는 namespace의 class만을 테스트 할 수 있다.
여기에서 `=`대신에 `~`가 쓰였는데, [이 문서](https://learn.microsoft.com/en-us/dotnet/core/tools/dotnet-test)에 따르면 Contains라고 한다. `=`는 Exact match

또한 `dotnet test --filter "FullyQualifiedName~NUnitTest.Tests.Tests003.$method"` 이런식으로 뒤에다가 method 이름을 닷 노테이션으로 붙이면 
특정 클래스의 특정 메소드만 테스트할 수도 있다.