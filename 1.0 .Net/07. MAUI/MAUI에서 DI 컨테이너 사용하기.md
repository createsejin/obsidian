물론 MAUI는 기본적으로 DI 컨테이너를 기반으로 Defendency injection이 이루어진다. 

우선은 entry point가 되는 `MauiProgram.cs`의 다음 코드를 살펴보자.
```csharp
using Microsoft.Extensions.Logging;
using SharedLib;

namespace MauiApp3;

public static class MauiProgram
{
  public static MauiApp CreateMauiApp()
  {
    var builder = MauiApp.CreateBuilder();
    builder
      .UseMauiApp<App>()
      .ConfigureFonts(fonts =>
      {
        fonts.AddFont("OpenSans-Regular.ttf", "OpenSansRegular");
        fonts.AddFont("OpenSans-Semibold.ttf", "OpenSansSemibold");
      });
    builder.Services.AddSingleton<IFileUtils, FileUtils>();
    /*
    Program @@main*/

#if DEBUG
    builder.Logging.AddDebug();
    builder.Logging.SetMinimumLevel(LogLevel.Debug);
#endif
    return builder.Build();
  }
}
```
여기서 `public static MauiApp CreateMauiApp()`가 MAUI APP의 entry point라고 생각하면 된다. 
`MauiApp.CreateBuilder();`를 통해서 `builder`를 얻고, 이 `builder`를 통해서 `Services` 컨테이너에 내가 등록하고 싶은 클래스들을 등록해준다.
이를 테면 `builder.Services.AddSingleton<IFileUtils, FileUtils>();` 이 부분은 나의 Utils library 중 하나인 `FileUtils`를 인터페이스와 함께 등록해주었다.

이것을 사용하는 코드를 살펴보자.

```csharp
using SharedLib;

namespace MauiApp3;

public partial class MainPage : ContentPage
{
  private int _count;

  public MainPage()
  {
    InitializeComponent();
    
    var fileUtils = Application.Current?.MainPage?.Handler?.MauiContext?
      .Services.GetService<IFileUtils>();
    if (fileUtils is null) return;
    Console.WriteLine("Get fileUtils instance reference");
  }
```
이것은 `MainPage.xaml.cs` 파일의 내용이다. 메인 페이지의 behind code인 것이다. 생성자에서 저런식으로 `Application.Current`를 통해 `MainPage.Handler`를 얻는다. 그리고 이 Handler에서 `Services` 컨테이너를 얻어서 `GetService`를 통해 `IFileUtils`의 인스턴스 참조를 얻을 수 있다는것이다.

[공식 문서](https://learn.microsoft.com/en-us/dotnet/maui/fundamentals/dependency-injection?view=net-maui-8.0#explicit-dependency-resolution)에 따르면 `IServiceProvider`로도 된다고는 하는데, 실제로 이것을 위 `MainPage`에 적용해본 결과, 흔히 발생하는 에러 패턴인 실행이 되지않고 종료 코드가 이상하게 되는 현상을 맞이하게 된다. 따라서 현재로서 작동하는 방식은 이 방식이라고 보면 된다. 

어어 그런데 또 이상한 점은 `App.xaml.cs`의 `App` class에서는 `IServiceProvider`가 올바르게 동작한다는 것이다.
```csharp
using SharedLib;

namespace MauiApp3;

public partial class App : Application
{
  public App(IServiceProvider serviceProvider)
  {
    InitializeComponent();
    var fileUtils = serviceProvider.GetService<IFileUtils>();
    if (fileUtils is null) return;
    Console.WriteLine("App: Get fileUtils instance reference.");
    MainPage = new AppShell();
    /*
    App.cs @@main*/
  }
}
```
참 희안하다.. 일단 두 가지를 써보면서 한스탭 한스탭씩 commit 하면서 무조건 다음 스탭 밟기 전에 테스트하고 테스트 성공하면 커밋하고 이런식으로 해야지 이건 안그러고 그냥 투스탭 쓰리스탭 계속 나아가기만 하다보면 또 동작 안되고 멎고. 이런 현상이 발생하기 때문에 특히나 MAUI 앱 개발은 test 브랜치 새로 만들어서 commit을 단계단계 하는 습관을 빠싹 들여놔야겠다..