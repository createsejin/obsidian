[Github Page](https://github.com/glzr-io/glazewm) Windows 환경에서 특정 키에 workspace를 할당 할 수 있으며, workspace 전환을 단축키로 쉽게 할 수 있다. 

간단히 `winget`을 이용해서 설치할 수 있다.
```
winget install GlazeWM
```

`glazewm` 명령어를 통해서 일단 최초 실행을 해야 기본 config file이 만들어진다. 
위치는 `C:\Users\creat\.glaze-wm`에 위치해있다.

앞 부분은 무난하다. 
```yaml
general:
  # Whether to automatically focus windows underneath the cursor.
  focus_follows_cursor: false

  # Whether to jump the cursor between windows focused by the WM.
  cursor_follows_focus: false

  # Whether to switch back and forth between the previously focused workspace
  # when focusing the current workspace.
  toggle_workspace_on_refocus: true

  # Whether to show floating windows as always on top.
  show_floating_on_top: false

  # Amount to move floating windows by (eg. when using `alt+<hjkl>` on a floating window)
  floating_window_move_amount: "5%"

  # Whether to center new floating windows.
  center_new_floating_windows: true

  # *Strongly* recommended to set to 'false'. Whether to globally enable/disable
  # window transition animations (on minimize, close, etc). Set to 'unchanged'
  # to make no setting changes.
  window_animations: "unchanged"

gaps:
  # Gap between adjacent windows.
  inner_gap: "0px"

  # Gap between windows and the screen edge.
  outer_gap: "0px"

# Highlight active/inactive windows with a colored border.
# ** Exclusive to Windows 11 due to API limitations.
focus_borders:
  active:
    enabled: true
    color: "#0000ff"

  inactive:
    enabled: false
    color: "#ff0000"

bar:
  height: "30px"
  position: "top"
  opacity: 1.0
  background: "#20242cc4"
  foreground: "#ffffff"
  font_family: "Segoe UI"
  font_size: "13px"
  padding: "4px 6px"
  offset_x: 0
  offset_y: 0
  border_radius: 0
  components_left:
    - type: "workspaces"
      focused_workspace_background: "#ffffff33"
      displayed_workspace_background: "#00000033"
      default_workspace_background: "transparent"
  components_center:
    - type: "window title"
  components_right:
    - type: "system tray"
    - type: "tiling direction"
      label_horizontal: "⮂"
      label_vertical: "⮁"
      background: "#ffffff33"
      margin: "0 4px"
      padding: "0 8px"
    - type: "binding mode"
      background: "#ffffff33"
      margin: "0 4px 0 0"
      padding: "0 8px"
    - type: "clock"
      # Documentation on formatting date/time string:
      # https://learn.microsoft.com/en-us/dotnet/standard/base-types/custom-date-and-time-format-strings
      time_formatting: "hh:mm tt  ddd MMM d"
```

workspace는 가장 중요한 영역이다. 
```yaml
workspaces:
  - name: "1"
    display_name: "Left"
    bind_to_monitor: 2
  - name: "2"
    display_name: "Main"
    bind_to_monitor: 1
  - name: "3"
    display_name: "Right"
    bind_to_monitor: 3
  - name: "4"
  - name: "5"
  - name: "6"
  - name: "7"
  - name: "8"
  - name: "9"
  - name: "0"
  - name: "t"
    display_name: "Terminal"
    bind_to_monitor: 3
  - name: "ob"
    display_name: "Obsidian"
    bind_to_monitor: 3
  - name: "vsc"
    bind_to_monitor: 1
    display_name: "Visual Studio Code"
  - name: "vs"
    bind_to_monitor: 1
    display_name: "Visual Studio 2022"
  - name: "chrome"
    display_name: "Chrome Web Browser"
    bind_to_monitor: 2
  - name: "file"
    display_name: "File Explorer"
    bind_to_monitor: 3
  - name: "every"
    display_name: "Everything"
    bind_to_monitor: 3
```
`- name:`을 통해 각 workspace의 기본 name을 정해줄 수 있고, `display_name`은 이 워크스페이스가 bar에 표시될 이름이다.
`bind_to_monitor`는 어떤 모니터에 이 workspace를 binding할건지  정한다. 만약 이 값이 없으면 현재 포커스된 workspace의 모니터에서 새 workspace가 만들어진다.

```yaml
binding_modes:
  - name: "resize"
    keybindings:
      # Resize focused window by a percentage or pixel amount.
      - command: "resize width -2%"
        bindings: ["H", "Left"]
      - command: "resize width +2%"
        bindings: ["L", "Right"]
      - command: "resize height +2%"
        bindings: ["K", "Up"]
      - command: "resize height -2%"
        bindings: ["J", "Down"]
      # Press enter/escape to return to default keybindings.
      - command: "binding mode none"
        bindings: ["Escape", "Enter"]

keybindings:
  # Shift focus in a given direction.
  - command: "focus left"
    bindings: ["Alt+H", "Alt+Left"]
  - command: "focus right"
    bindings: ["Alt+L", "Alt+Right"]
  - command: "focus up"
    bindings: ["Apps+K", "Alt+Up"]
  - command: "focus down"
    bindings: ["Apps+J", "Alt+Down"]
					
  # Move focused window in a given direction.
  - command: "move left"
    bindings: ["Apps+RShiftKey+H", "RMenu+RShiftKey+Left"]
  - command: "move right"
    bindings: ["Apps+RShiftKey+L", "RMenu+RShiftKey+Right"]
  - command: "move up"
    bindings: ["Apps+RShiftKey+K", "RMenu+RShiftKey+Up"]
  - command: "move down"
    bindings: ["Apps+RShiftKey+J", "RMenu+RShiftKey+Down"]
```
키보드는 이런식으로 바인딩하면 된다. 
  주의할점은 오른쪽 `RMenu` 키(오른쪽 `Alt`)를 사용할때에는 반드시 `HangulMode` 키 바인딩을 추가적으로 해줘야 입력기의 상태가 한글일때에도 정상적으로 동작한다.
겹치는 키가 있으면 기능이 작동하지 않으므로 키가 겹치지 않게끔 설정해주는게 중요하다.
또한 주의할점은 `RAlt + E`는 절대로 키바인딩에 포함하면 안된다. 만약 그 키바인딩을 사용하면 [[RAlt + E 누르면 Alt 고정되는 현상|Alt가 고정되는 문제]]가 생긴다.

설정한 KeyBind들은 [[GlazeWM KeyBinds|여기]]에서 확인하자.

```yaml
  # Launch CMD terminal (alternatively `exec wt` or `exec %ProgramFiles%/Git/git-bash.exe`
  # to start Windows Terminal and Git Bash respectively.
  - command: "exec wt"
    binding: "Apps+Enter"
  - command: "exec 'C:/Program Files/Microsoft Visual Studio/2022/Community/Common7/IDE/devenv'"
    binding: "OemPeriod+OemQuestion+V"
```
이걸로 특정 키에 어떤 프로그램을 실행시킬지 정할 수 있다. 

또한 Window rules라는게 있는데, 특정 윈도우가 띄워질때 어떤 동작을 실행할껀지 정해준다. 굉장히 중요한 기능 중 하나이다.
```yaml
window_rules:
  # Task Manager requires admin privileges to manage and should be ignored unless running
  # the WM as admin.
  - command: "ignore"
    match_process_name: "/Taskmgr|ScreenClippingHost/"

  # Launches system dialogs as floating by default (eg. File Explorer save/open dialog).
  - command: "set floating"
    match_class_name: "#32770"

  # Do not manage picture-in-picture windows for browsers. Note that the default is for
  # English; change `match_title` to the window's title if you use another language.
  - command: "ignore"
    match_title: "[Pp]icture.in.[Pp]icture"
    match_class_name: "Chrome_WidgetWin_1|MozillaDialogClass"
  - command: "ignore"
    match_process_name: "BandiView"
  - command: "ignore"
    match_process_name: "PowerToys.Peek.UI"
  - command: "set floating"
    match_process_name: "Everything"
  - command: "set floating"
    match_process_name: "KeePass"
  - command: "set floating"
    match_process_name: "Bandizip"
  - command: "move to workspace cave"
    match_title: "TheCave"
```
사용할 수 있는 command는 [여기](https://github.com/glzr-io/glazewm?tab=readme-ov-file#available-commands)에 있다.

  한가지 팁으로, Everything에서 `inspect.exe`를 찾아서 그걸 실행하면 커서를 움직여서 내가 찾고싶은 창의 title이라던가 process name, class name 같은걸 알아낼 수 있다.
이것은 windows sdk 툴킷에 포함되어있다.