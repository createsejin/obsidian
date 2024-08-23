는 반드시 Task를 반환하여야한다.
```csharp
  [TestMethod]
  public async Task TestMethod2()
  {
    string broken_string = @"[긚긯긲]귺깛긤깓귽긤궸뾇롌";
    if (await IsBrokenString(broken_string)) Console.WriteLine("broken");
    else Console.WriteLine("non broken");
  }
```