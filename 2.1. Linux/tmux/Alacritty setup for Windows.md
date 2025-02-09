config option들은 공식문서인 [여기](https://alacritty.org/config-alacritty.html)에 잘 정리되어있다. 

기본적으로 설정 파일은 
```
C:\Users\creat\AppData\Roaming\alacritty
```
위치에 놓여있다. 우선 처음에는 이 설정 폴더가 만들어져있지 않기 때문에
```
cd C:\Users\creat\AppData\Roaming
```
으로 이동한 뒤 
```
mkdir alacritty
cd alacritty
code alacritty.toml
```

이제 입맛대로 config를 해주면 된다.

Alacritty는 기본적으로 vim mode를 지원하는데, `Ctrl+Shift+Space`로 진입할 수 있으며 진입시에는 vim keybinds를 사용할 수 있다.
기본적으로 복사는 `y`인데 복사 후 곧바로 꺼지는 방식이 아니고 vim mode를 종료하려면 다시 `Ctrl+Shift+Space`를 누르거나 `Ctrl+C`를 누르면 된다.
이것 역시 키를 바꿀 수 있으니 [config 문서](https://alacritty.org/config-alacritty.html)를 잘 참조하자.

아무래도 Alacritty의 목표는 심플하고 매우 빠른 터미널을 만들기를 지향하기 때문에 Tmux처럼 화면을 상하좌우로 분할하는 기능 구현이 프로젝트의 구현 목표를 벗어난다고 한다.
그런데 문제는 Msys2에서는 Tmux를 통해 화면을 분할할 경우 좀 느려지는 문제가 생긴다.

그래서 생각한 방법은 그냥 glazeWM을 통해 여러개의 Alacritty를 띄우고 창을 이동하는것이다. 이렇게 하더라도 설정만 제대로 하면 아무런 문제가 없다.
이렇게 하면 좋은게 Windows Terminal이랑 한 화면에서 여러개를 놓고 같이 쓸 수도 있다.