[공식 문서](https://learn.microsoft.com/en-us/dotnet/csharp/language-reference/tokens/interpolated)  [formattings](https://learn.microsoft.com/en-us/dotnet/standard/base-types/composite-formatting)

기본적인 형식은 다음과 같다.
```
{<interpolationExpression>[,<alignment>][:<formatString>]}
```

```csharp
      Arguments = $@"""-Command ""{bz_exe}"" x -o ""{target_dir}"" ""{archive_path}""",
```
이런식으로 동시에 사용할 수 있다. 또한 리터럴 내부에서 double quote를 사용하려면 `"`을 두번 연달아 쓰는 것(`""`)으로 간단히 입력할 수 있다. 

또는 다음처럼 미리 format string을 지정해놓고 나중에 `string.Format`을 이용해서 formatting을 할 수도 있다.
```csharp
  private static readonly string bz_extract_args =
    @"x -y -cp:65001 -consolemode:utf8 -target:name -o:""{0}"" ""{1}""";

      Arguments = string.Format(bz_extract_args, target_dir, archive_path),
```

```csharp
else Console.WriteLine("test number {0:000} is not available.", test_num);
```
이런식으로 `Console.WriteLine`에서는 `0` position에 `test_num`을 넣을 수 있다.