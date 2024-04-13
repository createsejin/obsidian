## Wayland session
일단 Wayland에서는 아주 쉽게 arch wiki에 있는 내용을 tmux.conf에 붙여넣으면 된다.
참고로 tmux.conf는 `~/.config/tmux/tmux.conf`에 있다.
물론 그 전에 반드시 [wl-clipboard](https://archlinux.org/packages/?name=wl-clipboard)를 설치해줘야한다.
```
bind-key -T copy-mode-vi y send-keys -X copy-pipe-and-cancel "wl-copy && wl-paste -n | wl-copy -p"
bind-key p run "wl-paste -n | tmux load-buffer - ; tmux paste-buffer"
```
## Xorg session
Xorg display server session에서는 조금 삽질을 많이 했는데, 기본적으로 위에 소개한 tmux-yank 플러그인을 설치하고, `xsel`을 설치한 뒤, 다음과 같이 tmux-yank 기본 설정을 override 해주면 된다.
```
set -g @override_copy_command 'xsel -i -b'
```
## 공통 설정
공교롭게도 tmux-yank에는 p 키바인딩 기능이 없는것으로 보인다.
이를 설정하려면 다음을 `tmux.conf`에 추가하면 된다.
```
unbind p
bind-key p run "xsel -o | tmux load-buffer - ; tmux paste-buffer"
```
이렇게 하면 문제는 `<leader>p`에 대한 기능: prev window 기능이 unbind 되기 때문에 이 기능을 다시 다른 키로 설정해주어야한다. 나는 o 키에 다음과 같이 설정했다.
```
bind-key o previous-window
```
## 그외 참고 할만한 페이지
[여기](https://madforfamily.com/post/%EB%82%B4%EA%B0%80-%EB%A6%AC%EB%88%85%EC%8A%A4%EB%A5%BC-%EC%8D%A8%EC%95%BC%EB%A7%8C-%ED%95%98%EB%8A%94-%EC%9D%B4%EC%9C%A0-3-tmux.html)에 가면 어떤 똑똑한분이 아주 자세하게 tmux config 한걸 볼 수 있다. 여기에서 나중에 찾아다가 추가적으로 config를 해보자.
