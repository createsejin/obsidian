이 기능은 세미콜론을 구분자로 사용하는 code base 작업시에 반드시 필요한 기능이다. 
보통은 IdeaVim 또는 VSC vim emulator는 insert mode에서 `<C-e>` 기능을 제공하지 않는다. 따라서 `.vimrc`와 같은 설정파일에 이것을 명시적으로 config 해야한다.

우선 VSC vim emulator setting을 위해 VSC의 `settings.json` 파일에 다음을 추가해준다.
```json
    "vim.vimrc.enable": true,
    "vim.vimrc.path": "C:\\Users\\creat\\.ideavimrc",
```
당연히 위는 예시이므로 설정파일이 있는 path를 적으면 된다.
기본적으로 CLion같은 Jetbrains의 ideaVim 설정 파일을 기반으로 써주면 좋다. [[IdeaVim move panel setting#^6661b3|여기]]에 그 방법이 적혀있다.
```vim
" goto end of the line in insert mode
inoremap <C-E> <Esc>$a
```
이것을 추가해준다. 그러면 이제 insert mode에서 `Ctrl + E`를 누르면 줄 끝으로 이동하여 insert mode가 유지된다. 