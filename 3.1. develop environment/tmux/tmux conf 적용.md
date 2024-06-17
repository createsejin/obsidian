`tx source-file /home/bae/.config/tmux/tmux.conf`

이것을 매번 직접 치기 귀찮으니까 아예 tmux.conf에 기능키로 추가해버리면 아주 편하다.
```
bind r source-file /home/bae/.config/tmux/tmux.conf \; display ".tmux.conf reloaded."
```
이렇게 하면 `<leader>r` 하면 알아서 config를 reload 해준다.