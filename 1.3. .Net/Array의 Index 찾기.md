```csharp
string[] windowHandles = driver.WindowHandles;
string targetWindowHandle = "특정 탭의 핸들 값";

int targetIndex = Array.IndexOf(windowHandles, targetWindowHandle);
```
