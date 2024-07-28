```csharp
public class ChromeDriverPool
{
  private readonly SemaphoreSlim _semaphore;
  private readonly ConcurrentBag<IWebDriver> _drivers;
  private readonly IMainMessenger _main_msger;
  public ChromeDriverPool(IMainMessenger main_msger, int maxPoolSize = 2)
  {
    _main_msger = main_msger;
    _semaphore = new(maxPoolSize, maxPoolSize);
    _drivers = [];
    var options = new ChromeOptions();
    options.AddArgument("--headless");
    for (int i = 0; i < maxPoolSize; i++)
    {
      _drivers.Add(new ChromeDriver(options));
    }
  }
  public async Task<IWebDriver> GetChromeDriverAsync([CallerMemberName] string callerName = "")
  {
    await _semaphore.WaitAsync();
    _main_msger.EnqueueAndPrint($"[{callerName}] GetChromeDriverAsync - Entered");

    IWebDriver? driver;
    while (!_drivers.TryTake(out driver))
    {
      await Task.Delay(100);
    }
    driver.SetActive(true);
    driver.Manage().Timeouts().ImplicitWait = TimeSpan.FromSeconds(8);
    Console.WriteLine($"[{callerName}] GetChromeDriverAsync - Exited (driver: {driver.GetHashCode()})");
    return driver;
  }

  public void ReturnChromeDriver(IWebDriver driver, [CallerMemberName] string callerName = "")
  {
    Console.WriteLine($"[{callerName}] ReturnChromeDriver - Entered (driver: {driver.GetHashCode()})");
    driver.SetActive(false); // 드라이버 비활성화
    _drivers.Add(driver); // 드라이버 풀에 반환
    _semaphore.Release(); // 세마포어 해제
    Console.WriteLine($"[{callerName}] ReturnChromeDriver - Exited");
  }
}

public class WebDriverActiveState
{
  public bool IsActive { get; set; }
}
public static class WebDriverExtensions
{
  private static ConditionalWeakTable<IWebDriver, WebDriverActiveState> _isActiveTable = [];
  public static bool IsActive(this IWebDriver driver)
  {
    return _isActiveTable.TryGetValue(driver, out var state) && state.IsActive;
  }
  public static void SetActive(this IWebDriver driver, bool value)
  {
    if (_isActiveTable.TryGetValue(driver, out var state))
    {
      state.IsActive = value;
    }
    else
    {
      _isActiveTable.Add(driver, new WebDriverActiveState { IsActive = value });
    }
  }
}
```