특정 웹사이트에 로그인하는것은 꽤나 까다로운 일이다. 로그인 페이지에 들어가면 얻는 각종 토큰 쿠키, 세션 값 등을 얻어내고 이것들을 request header에 담고, 필요한 request header들을 하나하나 세팅을 해주어야하기 때문이다. 
실제로 크롬에서 로그인을 해보고 개발자 툴의 Network 탭에서 어떤 헤더 정보가 오가는지, 어떤 쿠키가 오가는지, Payload에는 어떤 정보가 담겨서 전송되는지 등을 분석할 필요가 있다.

이를 위해서는 쿠키 컨테이너가 필요하고, 자동 리다이렉션을 허용하고 그외의 설정을 위해 `HttpClientHandler` 객체를 통해 `HttpClient` 객체를 생성해야한다.
```csharp
  private readonly HttpClientHandler _httpClientHandler = new()
  {
    UseCookies = true,
    UseDefaultCredentials = true,
    AllowAutoRedirect = true,
    CookieContainer = new(),
    UseProxy = true,
    /*
    HttpClientHandler @@down.login*/
  };
  private HttpClient _client => new(_httpClientHandler);
```
`HttpClient` 객체를 멤버 변수로 두고 이를 클래스 내부에서 필요한 곳에 재사용하면 매우 편리하다. 미리 필요한 사이트에 로그인해두면 인증 정보를 `_client` 멤버가 소유하기 때문이다.

우선 Login Method의 시작 부분에서는 먼저 로그인 페이지를 Get 요청해서 필요한 정보를 얻어야한다. 토큰, phpsession id 등을 얻을 수 있었다.
```csharp
  public async Task LoginRapidGatorAsync()
  {
    var login_page_response = await _client.GetAsync(_rapidLoginUrl);
    if (!login_page_response.IsSuccessStatusCode)
    {
      Console.WriteLine("No get login page response");
      return;
    }
```
이런식으로 `_client`를 통해 로그인 페이지의 요청을 받아두면 그 페이지에서 얻은 정보가 고스란히 `_client` 객체에 담기게 된다. 위 경우에는 `__token` 쿠키와 `PHPSESSID` 쿠키를 얻을 수 있었다.

때로 어떤 쿠키를 얻었는지 확인하기 위해 `response`로부터 얻은 쿠키들을 Key와 Value들로 나열할 수도 있다.
```csharp
    foreach (var cookie in _httpClientHandler.CookieContainer.GetAllCookies())
    {
      foreach (var (key, value) in cookie.ToDictionary())
      {
        Console.WriteLine($"{key}: {value}");
	  }
	  Console.WriteLine();
	}
```
이런식으로 처음에 멤버 변수로 선언한 `HttpClientHandler` 객체를 통해 `CookieContainer`에 접근해서 모든 쿠키 정보를 위와 같이 나열해서 출력할 수 있다.

이제 `LoginRapidGatorAsync` 메서드의 다음 부분을 살펴보자.
```csharp
    var (email, passwd) = fileUtils.AccountProvider(_myJson);
    var formValues = new Dictionary<string, string>
    {
      { "LoginForm[email]", email },
      { "LoginForm[password]", passwd },
      { "LoginForm[rememberMe]", "1" },
    };
    var content = new FormUrlEncodedContent(formValues);
    var request = new HttpRequestMessage(HttpMethod.Post, _rapidLoginUrl)
    {
      Content = content
    };
```
우선은 `fileUtils.AccountProvider(_myJson)` 메서드로부터 `email`과 `passwd`를 받아둔다. 이 메서드에 대한 구현은 여기서 생략한다. 대략 json 파일을 읽어서 앞 두 정보를 얻는 메서드라고 보면 된다. 
우선 로그인 페이지의 element를 분석해서 login form의 `name` 속성을 따서 저런식으로 입력을 해야한다. 3번째 항목처럼 추가적으로 입력 정보를 요구하는 경우가 있기 때문에 실제 크롬에서 로그인을 해보고 Network 탭의 Payload를 잘 분석해야한다.
이 로그인 form을 `FormUrlEncodedContent` 객체로 만들어서 `HttpRequestMessage` 객체에 담아서 `request` 객체를 만든다. 
이 객체의 생성자에는 첫번째, 요청 방식과 두번째, 요청 Url가 들어간다.

그 다음을 보자. 이번에는 헤더에 쿠키 값을 설정하는 부분이다.
```csharp
    object? phpsessid_cookie = null;
    object? token_cookie = null;
    foreach (var cookie in _httpClientHandler.CookieContainer.GetAllCookies())
    {
      foreach (var (key, value) in cookie.ToDictionary())
      {
        Console.WriteLine($"{key}: {value}");
        if (key.Equals("Name") && value.Equals("PHPSESSID"))
        {
          phpsessid_cookie = cookie;
        }
        else if (key.Equals("Name") && value.Equals("__token"))
        {
          token_cookie = cookie;
        }
      }
    }
    string phpsessid = phpsessid_cookie.ToDictionary().GetValueOrDefault("Value", string.Empty);
    string token = token_cookie.ToDictionary().GetValueOrDefault("Value", string.Empty);

    string cookie_str = string.Empty;
    if (phpsessid is not null && token is not null)
    {
      cookie_str = string.Format("lang=en; PHPSESSID={0}; __token={1}", phpsessid, token);
    }
    request.Headers.Add("Cookie", cookie_str);

```
처음에 쿠키 변수를 nullable로 선언하고 `_httpClientHandler` 객체의 `CookieContainer`를 순회하여 원하는 쿠키를 찾아서 앞서 선언한 변수에 저장한다. 그리고 아래에서는 그 쿠키에 담긴 값을 추출한다.
그리고 실제 로그인 과정에서 처럼 request header의 cookie 값과 동일한 방식으로 된 string을 `string.Format`을 이용해 생성해주고, 그 스트링을 `request.Headers`에 `Add` 해준다.

그 다음은 여러가지 필요할 것 같은 Header들을 적절히 세팅해주는 코드다.
```csharp
    request.Headers.UserAgent.ParseAdd("Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/127.0.0.0 Safari/537.36");
    request.Headers.Add("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7");
    request.Headers.Add("Accept-Encoding", "gzip, deflate, br, zstd");
    request.Headers.Add("Accept-Language", "en-US,en;q=0.9");
    request.Headers.Connection.ParseAdd("keep-alive");
    request.Headers.Add("Host", "rapidgator.net");
    request.Headers.Add("Referer", "https://rapidgator.net/");
    request.Headers.Add("Sec-Fetch-Dest", "document");
    request.Headers.Add("Sec-Fetch-Mode", "navigate");
    request.Headers.Add("Sec-Fetch-Site", "same-origin");
    request.Headers.Add("Sec-Fetch-User", "?1");
    request.Headers.Add("Upgrade-Insecure-Requests", "1");
    request.Headers.Add("sec-ch-ua", "\"Not)A;Brand\";v=\"99\", \"Google Chrome\";v=\"127\", \"Chromium\";v=\"127\"");
    request.Headers.Add("sec-ch-ua-mobile", "?0");
    request.Headers.Add("sec-ch-ua-platform", "\"Windows\"");
```
이 부분 역시 실제 크롬에서 로그인해서 어떤 정보가 request header에 담기는지 파악해서 그대로 옮겨서 적으면 된다.
보통은 그냥 `Add` 메서드를 쓰면 되지만, `request.Headers.UserAgent.ParseAdd` 처럼 직접 헤더의 해당 속성을 지정해서 올바른 값이 들어갔는지 검증할 수도 있다. 이 `ParseAdd` 메서드는 파싱에 실패할 경우 에러가 발생한다. 파싱 성공 여부를 bool로 반환하는 `TryParseAdd` 메서드도 존재한다. 그러나 나는 귀찮아서 그냥 `Add`를 썼다. 필요에 따라서 사용하자.

```csharp
    var login_response = await _client.SendAsync(request);

    var status_code = login_response.StatusCode.ToString();
    Console.WriteLine($"status_code = {status_code}");
    if (login_response.IsSuccessStatusCode)
    {
      var redirection_response = await _client.GetAsync(_rapidHomePage);
      redirection_response.EnsureSuccessStatusCode();

      string redirection_page_source = await redirection_response.Content.ReadAsStringAsync();
      IsLoginSuccess(redirection_page_source, email);
    }
    else if (login_response.StatusCode == HttpStatusCode.Found)
    {
      string result = await login_response.Content.ReadAsStringAsync();
      IsLoginSuccess(result, email);
      /*
      LoginRapidGatorAsync @@down.login*/
    }
```
이제 `request`를 `SendAsync` 메서드를 통해 요청을 보내고, `login_response`를 응답 받는다.
`StatusCode`에는 여러가지가 있는데, 보통은 `OK`가 나거나 `Found`인 경우가 있다. `Found`인 경우는 Redirect된 페이지를 반환한다. 
앞서 `_httpClientHandler`에서 `AllowAutoRedirect = true`로 설정했기 때문에 이 경우에는 자동으로 최종 응담이 Redirect된 페이지로 나오게 된다.

`OK`인 경우에는 Redirect가 되지 않는것 같다. 그래서 어쩔 수 없이 수동적으로 홈페이지에 접속해서 AngleSharp을 사용하는 메서드 `IsLoginSuccess`를 이용해서 html을 분석한 다음, 제대로 로그인이 됐는지를 검증한다.