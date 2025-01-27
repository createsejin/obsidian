우선은 당연히 [[shell syntax highlighting and autosuggestions|이것]]이 필요하고, [이 문서](https://wiki.archlinux.org/title/Zsh#Fish-like_syntax_highlighting_and_autosuggestions)에 설치 및 설정 방법이 자세히 나와있다. 

zsh가 기본 터미널로 설정되는게 좋다. 

가장 기본적인 사용 방법은 
```bash
┌─[bae@Main]-[~]-[Wed Jan 22, 09:42]
└─[$]> vim <tab>
./                       .histfile                .tmux/
../                      .local/                  .viminfo
.bash_history            .m2/                     .vscode-server/
.bash_logout             mydoc/                   .zcompdump
.bash_profile            .node_repl_history       .zcompdump-Main-5.9
.bashrc                  .npm/                    .zcompdump-Main-5.9.zwc
.cache/                  .nvm/                    .zsh_history
.config/                 .oh-my-zsh/              .zshrc@|
.dotnet/                 projects/                .zshrc.back
.gitconfig               .rnd                     .zshrc.zni
.gradle/                 .sts4/
```
이런식으로 처음에 `vim`을 입력하고, `tab`을 한번 누르면 suggestions 목록이 뜬다.

만약 `tab`을 한번 더 누르거나 처음부터 두번을 누르면 목록을 선택할 수 있는 선택 블록이 띄워진다.
```
┌─[bae@Main]-[~]-[Wed Jan 22, 09:42]
└─[$]> vim mydoc/
./                       .histfile                .tmux/
../                      .local/                  .viminfo
.bash_history            .m2/                     .vscode-server/
.bash_logout             mydoc/                   .zcompdump
.bash_profile            .node_repl_history       .zcompdump-Main-5.9
.bashrc                  .npm/                    .zcompdump-Main-5.9.zwc
.cache/                  .nvm/                    .zsh_history
.config/                 .oh-my-zsh/              .zshrc@
.dotnet/                 projects/                .zshrc.back
.gitconfig               .rnd                     .zshrc.zni
.gradle/                 .sts4/
```
이때 선택블록을 아래로 움직이는건 `Ctrl+n` 위로 움직이는건 `Ctrl+p` 오른쪽으로 이동은 `Ctrl+f` 왼쪽으로 이동은 `Ctrl+b`이다. 
물론 화살표키로도 움직일 수 있다.

또한 명령어를 입력하면 히스토리에 따라서 이전에 썻던 명령어를 보여준다. 이때 `Shift+right`를 하면 그 제안을 바로 입력해주며,
화살표키 위아래로 이전 히스토리를 탐색할 수도 있다.