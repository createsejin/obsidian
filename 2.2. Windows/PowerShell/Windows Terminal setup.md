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
                "singleLine": false,
                "dismissSelection": false
            },
            "keys": "ctrl+shift+c"
        },
        {
            "command": "paste",
            "keys": "ctrl+shift+v"
        },
```

일단은 `nvim`을 위해서 `copy`와 `paste`의 키바인딩을 조금 바꿔줬다.
`"dismissSelection": false`은 `copy` command로 copy할때 mark mode가 해제되는걸 방지한다. `Enter`키로 copy할 경우에는 mark mode가  해제된다.

```json
    {
      "command": {
        "action": "splitPane",
        "split": "auto",
        "splitMode": "duplicate"
      },
      "keys": "alt+shift+d"
    },
    {
      "command": {
        "action": "splitPane",
        "split": "right"
      },
      "keys": "alt+v"
    },
    {
      "command": {
        "action": "splitPane",
        "split": "down"
      },
      "keys": "alt+h"
    },
    {
      "command": "markMode",
      "keys": "ctrl+shift+m"
    },
    {
      "command": "closePane",
      "keys": "alt+q"
    },
    {
      "command": {
        "action": "moveFocus",
        "direction": "down"
      },
      "keys": "ctrl+j"
    },
    {
      "command": {
        "action": "moveFocus",
        "direction": "left"
      },
      "keys": "ctrl+h"
    },
    {
      "command": {
        "action": "moveFocus",
        "direction": "right"
      },
      "keys": "ctrl+l"
    },
    {
      "command": {
        "action": "moveFocus",
        "direction": "up"
      },
      "keys": "ctrl+k"
    },
    {
      "command": {
        "action": "swapPane",
        "direction": "down"
      },
      "keys": "alt+shift+j"
    },
    {
      "command": {
        "action": "swapPane",
        "direction": "left"
      },
      "keys": "alt+shift+h"
    },
    {
      "command": {
        "action": "swapPane",
        "direction": "right"
      },
      "keys": "alt+shift+l"
    },
    {
      "command": {
        "action": "swapPane",
        "direction": "up"
      },
      "keys": "alt+shift+k"
    },
    {
      "command": "togglePaneZoom",
      "keys": "f3"
    }
```
패널 관련 키들을 몇 가지 정해줬다. 
vertical 하게 패널을 만드려면 `alt + v`
horizontal 패널은 `alt + h`
포커스 이동은 vim처럼 `ctrl + [h,j,k,l]`
swap pane은 `alt + shift + [h,j,k,l]` 이다.
한 패널의 창을 최대로 키웠다가 다시 줄이는 zoom toggle 키는 `F3`이다.

참고로 Windows Terminal은 마우스로 패널 사이즈를 조정하는 기능이 없다. 
기본 세팅된 키는 `alt + shift + <arrow key>`이다.

놀라운점은 neovim에서 windows terminal의 다른 패널로 넘어가는게 가능하다는 것이다. 아마도 플러그인에서 이걸 지원하는건지 그건 모르겠다. 