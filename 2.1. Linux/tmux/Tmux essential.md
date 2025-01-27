`<prefix>:swap-window -s 2 -t 1`
`<prefix>:new` create new session
`<prefix>s` view sessions
`<prefix>w` view windows
`<prefix>q` select pane by number
`<prefix>&` kill window
`<prefix>c` new window
`<prefix>1~9` 해당 window로 스위칭
`<prefix>z`  Zoom and maximaize window
`<prefix>!` turn a pane to new window
`<prefix>{` or `<prefix>}` panes swap
`<prefix>d` detach tmux

## 명령어
`tmux ls` 현재 tmux 세션이 어떻게 구성되어있는지 출력한다.
`tmux attach-session -t 0` 세션 `0`에 attach 한다.
`tmux kill-session -t 0` 세션 `0`를 kill 한다.
`tmux kill-server` 모든 tmux 세션을 kill 한다.
`tmux -new -s <session name>` 특정 세션 이름으로 세션을 새로 시작한다.

[참고 영상](https://www.youtube.com/watch?v=DzNmUNvnB04&ab_channel=DreamsofCode) [참고 블로그](https://gptjs409.github.io/infra/2019/07/29/tmux.html)