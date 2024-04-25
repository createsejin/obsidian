무조건 fcitx가 제일 좋다. 호환성이 가장 좋으며 Xorg 던 Wayland건 Qt건 뭐던 다 잘 동작한다. 
[fcitx5-hangul](https://archlinux.org/packages/?name=fcitx5-hangul)을 설치하면 한글 입력이 지원된다. 물론 fcitx5 기본 패키지 `fcitx5-im`을 설치해야한다.
그리고 다음을 `~/.xinitrc` 파일에 추가해주면 된다.
```
export GTK_IM_MODULE='fcitx'
export QT_IM_MODULE='fcitx'
export XMODIFIERS='@im=fcitx'
```
그리고 재부팅후, KDE의 경우 system settings에서 Keyboard -> Virtual Keyboard -> Fcitx5 Wayland Launcher.. 를 선택해주면 된다.

## 순수 Wayland, hyprland에서 설정하기
우선 `fcitx5-im`, `fcitx5-hangle`을 설치한다. launcher에서 fcitx5 Configuration을 실행한다.
Input method의 오른쪽 창에서 아랫부분으로 스크롤을 내리면 'korean' 섹션에 'hangle'이 보일 것이다. 이걸 추가한다. `Hangle`과 `Keyboard - English(US)` 두 개가 있으면 된다. 그리고 Global Options 탭으로 이동해서 Trigger Input Method에서 나머지 키 바인딩을 지우고 하나를 선택한 뒤, 자신이 원하는 키로 설정한다. 나는 Right Alt키로 설정했다. 