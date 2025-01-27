문제는 tmux에서 `set -g @plugin 'christoomey/vim-tmux-navigator'`를 사용하면 `Ctrl+{h, j, k, l}`에 키가 바인딩되어서 fzf-git.sh 의 기본 키바인딩 중 `Ctrl+G, Ctrl+H`, `Ctrl+G, Ctrl+L`이 안먹힌다는 것이다. 이문제는 이 [글](https://github.com/junegunn/fzf-git.sh/issues/16#issuecomment-1249657110)을 통해서 해결했다.
방법은 아래와 같다. 
```
# add ctrl_g_mode for fzf-git.sh
bind-key -n -T root C-g switch-client -T ctrl_g_mode
bind-key -T ctrl_g_mode C-B send-keys C-g C-B
bind-key -T ctrl_g_mode C-E send-keys C-g C-E
bind-key -T ctrl_g_mode C-F send-keys C-g C-F
bind-key -T ctrl_g_mode C-H send-keys C-g C-H
bind-key -T ctrl_g_mode C-R send-keys C-g C-R 
bind-key -T ctrl_g_mode C-S send-keys C-g C-S
bind-key -T ctrl_g_mode C-T send-keys C-g C-T
bind-key -T ctrl_g_mode C-L send-keys C-g C-L
bind-key -T ctrl_g_mode b send-keys C-g b 
bind-key -T ctrl_g_mode e send-keys C-g e
bind-key -T ctrl_g_mode f send-keys C-g f 
bind-key -T ctrl_g_mode h send-keys C-g h
bind-key -T ctrl_g_mode r send-keys C-g r
bind-key -T ctrl_g_mode s send-keys C-g s
bind-key -T ctrl_g_mode t send-keys C-g t       
bind-key -T ctrl_g_mode l send-keys C-g l       
```
이걸 `~/Documents/configs/.config/tmux/tmux.conf`에 추가하면 된다.

참고로 이 스크립트의 키바인딩은 다음과 같다. [git](https://github.com/junegunn/fzf-git.sh?tab=readme-ov-file#list-of-bindings)

- CTRL-G CTRL-F for **F**iles
- CTRL-G CTRL-B for **B**ranches
- CTRL-G CTRL-T for **T**ags
- CTRL-G CTRL-R for **R**emotes
- CTRL-G CTRL-H for commit **H**ashes
- CTRL-G CTRL-S for **S**tashes
- CTRL-G CTRL-L for ref**l**ogs
- CTRL-G CTRL-W for **W**orktrees
- CTRL-G CTRL-E for **E**ach ref (`git for-each-ref`)