이 [영상](https://youtu.be/mmqDYw9C30I?si=c27Q7f7WPXLUNq7D)을 참고로 했다.
## fzf
`pacman`으로 설치할 수 있다. 설치 후 `.zshrc`파일에 다음을 추가한다.
`eval "$(fzf --zsh)"`
이렇게 하면 기본 키바인딩을 쓸 수 있다.

예를들어 다음과 같이 사용할수 있다.
`vim `을 친 뒤, `Ctrl+T`를 이용하면 된다.

또는 `vim **`을 친 뒤, `Tab`을 이용하면 된다.

`ssh **(Tab)`

`kill -9 **(Tab)`
특히 `kill`에서는 목록에서 `Tab`을 누르면 여러 목록을 동시에 선택할 수 있다. 또는 `Shift+Tab`을 누르면 deselect 할 수 있다.
이 기능은 여러 인수를 선택할 수 있는 `rm`, `mv` 같은 명령어에도 적용된다. 

그 외에도 `export`, `unalias` 같은 애들에도 **을 적용해서 편리하게 사용할 수 있다.

또한 `Ctrl+R`을 이용하면 command history를 보여준다. 또는 `vim` 처럼 명령어를 치고 이 기능을 이용하면 자동으로 history가 필터링된다.
## tldr
`tldr eza` 
man page와 비슷하지만 매우 심플하게 명령어를 어떻게 사용하는지 간단한 예시로 알려준다.
나는 이걸 `tl`로 alias 설정을 해놓았다.

