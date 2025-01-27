놀랍게도 개인 개발자에게는 Red Hat Hat Enterprise Linux가 무료로 제공된다. 정말로 다행이 아닐 수 없다. 나같은 백수 개발자에게는 정말정말 엄청난 옵션인듯. ㅋㅋ 어쨌거나 오랜 삽질 끝에 초기 설정을 대충 끝냈다. 엔비디아 드라이버를 설치해주었고, FireFox에도 로그인해서 동기화 해주고, 특히 rclone을 이용해서 google cloud platform을 통해 client id를 이용해서 로컬 마운트 포인트에 구글 드라이브를 마운트하는데에 성공했다. 또한 systemd를 이용해서 자동으로 시스템 시작시에 rclone을 이용해서 마운트하는걸 자동으로 실행되게 했다. 또한 Obsidian을 AppImage로 설치해서 icon을 다운받아서 .desktop 파일을 만들어서 도크바에 표시되도록 하였다. 

이제부터는 LLVM, Clang, libc++, LLDB, Ninja, Clion 등등이 설치되어야한다. RustRover도 써볼까 고민중.. 근데 두 개 쓰면.. ㅋㅋ 그냥 VSCode도 고려해보자..

### 2024-02-19-001 환경 변수 추가

![[리눅스 환경 변수 추가하기]]

