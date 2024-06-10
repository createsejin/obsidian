Ctrl + h, j, k, l 을 설정해두면 CLion을 사용하기가 매우매우 편리해진다. 

ideaVim plugin은 필수필수필수다. 무조건 설치해주자.

설치하면 오른쪽 하단 status bar에 Vim 표시가 초록색으로 뜬다. 그걸 눌러서 setting에 진입하자.

그러면 Ctrl+... 에 대한 설정들이 쭉 나오는데, 여기에서 Ctrl + h, j, k, l 얘네들을 모두 Vim으로 바꿔준다.

apply 후, 다시 오른쪽 하단 Vim 아이콘을 눌러서 `Open ~/.ideavimrc`를 누르면 ideaVim을 설정하는 설정파일이 나온다. 여기에 다음을 추가해주자.
```
" move panel
nnoremap <C-h> <C-w>h
nnoremap <C-j> <C-w>j
nnoremap <C-k> <C-w>k
nnoremap <C-l> <C-w>l
```
이렇게 해두면 Ctrl + h, j, k, l로 손쉽게 패널을 왔다갔다 할 수 있다. 무 조 건 이건 설정해야한다. 거의 가장 중요한 기능 중 하나이기 때문이다.