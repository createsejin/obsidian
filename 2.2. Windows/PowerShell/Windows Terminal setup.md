[공식 Document](https://learn.microsoft.com/en-us/windows/terminal/)

우선 다음으로 `settings.json` file을 열자.
```
code %LOCALAPPDATA%\Packages\Microsoft.WindowsTerminal_8wekyb3d8bbwe\LocalState\settings.json
```

```json
    "actions": 
    [
        {
            "command": 
            {
                "action": "copy",
                "singleLine": false
            },
            "keys": "ctrl+shift+c"
        },
        {
            "command": "paste",
            "keys": "ctrl+shift+v"
        },
```

일단은 `nvim`을 위해서 `copy`와 `paste`의 키바인딩을 조금 바꿔줬다.