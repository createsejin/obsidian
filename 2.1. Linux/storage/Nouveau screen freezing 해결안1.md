[이 글](https://bbs.archlinux.org/viewtopic.php?id=271872)에서 한가지 방법을 제안해놓긴 했는데 될지는 모르겠다. 
방법은 `/etc/profile` 마지막줄에 `export QSG_RENDER_LOOP=basic`를 추가하는것인데..
reboot 후 확인은 
`tr '\0' '\n' < /proc/$(pidof plasmashell)/environ`
명령어로 한다. 이 명령어를 실행한뒤 앞서 추가한 `QSG_RENDER_LOOP=basic`옵션이 보이면 추가는 성공한거다. 그러나 이게 정말로 이러한 화면 멈춤 현상을 해결해줄것인지는 여전히 의문이다. 
`