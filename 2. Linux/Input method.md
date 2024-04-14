무조건 fcitx가 제일 좋다. 호환성이 가장 좋으며 Xorg 던 Wayland건 Qt건 뭐던 다 잘 동작한다. 
[fcitx5-hangul](https://archlinux.org/packages/?name=fcitx5-hangul)을 설치하면 한글 입력이 지원된다. 물론 fcitx5 기본 패키지를 설치해야한다.
그리고 다음을 `~/.xinitrc` 파일에 추가해주면 된다.
```
export GTK_IM_MODULE='fcitx'
export QT_IM_MODULE='fcitx'
export XMODIFIERS='@im=fcitx'
```
그리고 재부팅후, KDE의 경우 system settings에서 Keyboard -> Virtual Keyboard -> Fcitx5 Wayland Launcher.. 를 선택해주면 된다.