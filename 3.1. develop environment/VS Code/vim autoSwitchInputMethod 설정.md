기능은 [[IdeaVimExtension - keep english in normal mode|IdeaVimExtension]]과 거의 동일하다. 이 [글](https://nor-s.github.io/posts/2021/12/28/02/01/vscode-vim-ime/)을 참고하면 좋다.

이 github [page](https://github.com/daipeihust/im-select)에서 windows용 `im-select.exe`를 다운받는다.

적당한 폴더로 옮긴다. 나는 `C:/tools/im-select.exe`에다가 놓았다.

다음 설정을 VSCode settings.json에 넣는다.
```json
    "vim.autoSwitchInputMethod.enable": true,
    "vim.autoSwitchInputMethod.defaultIM": "1033",
    "vim.autoSwitchInputMethod.obtainIMCmd": "C:\\tools\\im-select.exe",
    "vim.autoSwitchInputMethod.switchIMCmd": "C:\\tools\\im-select.exe {im}",
```
주의할점은 예를들어서 옵시디언에서 이렇게 한글을 치고 vscode로 바로 가면 그때에는 이게 적용되지 않는다. IdeaVim은 CLion으로 돌아갈때 영문키로 스위칭을 해주는데 VSC vim은 그렇지 않다. 따라서 다른 창에서 VSC로 진입하기 전에 영문키로 전환하고 진입하는걸 추천한다.

또한 한글 키보드 바로가기 기능을 [[IdeaVimExtension - keep english in normal mode#한글 입력기 바로가기 키 설정|이 글]]을 통해 설정할 것을 추천한다. 