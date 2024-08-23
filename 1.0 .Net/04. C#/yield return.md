[문서](https://learn.microsoft.com/en-us/dotnet/csharp/language-reference/statements/yield)
일반적인 return과는 달리 Iterator 안에서 쓰이는데, `yield return`문을 만날때 마다 해당 요소를 리턴하고 다시 Iterating을 해주는 역할인것 같다.
```csharp
foreach (int i in ProduceEvenNumbers(9))
{
    Console.Write(i);
    Console.Write(" ");
}
// Output: 0 2 4 6 8

IEnumerable<int> ProduceEvenNumbers(int upto)
{
    for (int i = 0; i <= upto; i += 2)
    {
        yield return i;
    }
}
```
이런식인데 여기에서 `return`과의 차이점은 `return`은 해당 `return`문을 만나면 그 즉시 이 메서드를 종료시키지만, `yield return`은 메서드를 종료시키지 않고 다음 값을 반환하거나 end of iteration을 반환한다.