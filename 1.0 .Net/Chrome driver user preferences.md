```
C:\Users\creat\AppData\Local\Google\Chrome\User Data\Default\Preferences
```
이 파일에서 User preferences 옵션들을 볼 수 있다.

일단 내가 현재 필요한 옵션들은
```
download.prompt_for_download = false
download.default_directory = "C:\\..."
```

이걸 
```csharp
var options = new ChromeOptions(); 
options.AddUserProfilePreference("download.default_directory", downloadDirectory); 
options.AddUserProfilePreference("download.prompt_for_download", false);
```
이런식으로 설정하고 저걸 driver 생성자에 넘기면 된다.