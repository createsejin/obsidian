처음에 이 [Quick Start 가이드](https://spring.io/quickstart)를 보고 따라하려고 했다. https://start.spring.io/ 에서 spring boot 초기 파일을 받을 수 있었는데, 이걸 Windows 머신에서 받은뒤, WSL arch linux로 옮겨서 Windows상의 VSCode에서 띄워봤더니 Quick Start 가이드에서 새롭게 import 한 부분이 빨간줄이 쳐졌다. 그 원인은 Spring Web 디펜던시를 추가 선택을 안한 상태로 초기 파일을 받은 탓이었다.
다시 받고 다시 띄워봤다. 그런데도 뭔가 문제가 있었다. 알고보니 내 WSL에 `JAVA_HOME` 설정이 안되어있었다. 그래서 다음과 같이 `~/.zshrc`에 환경 변수 `JAVA_HOME`을 추가해주었다.
```bash
export JAVA_HOME=$(readlink -f /usr/bin/java | sed "s:bin/java::")
```

이건 그렇다 치는데, 갑자기 VSCode의 Java 인텔리센스가 아예 먹지 않는 현상이 나타났다. VSCode의 status bar에서 java: Ready라고 된 부분을 클릭하자 Open log 라는게 있어서 한번 봤다. 에러 내용은 다음과 같았다.
```
.../DemoApplication.java does not resolve to a ICompilationUnit
```
이 내용을 검색해봤다. 그러자 한 해결 방법으로 vscode의 java working directory 내용을 삭제하라는 의견이 있었다. 더 자세한 내용은 이 [페이지](https://github.com/redhat-developer/vscode-java/wiki/Troubleshooting#clean-the-workspace-directory)를 참고하면 되는데, 일단 Ctrl+Shift+P로 커맨드 팔레트를 열고 `Java: Clean the Java Language Server Workspace`를 검색해서 실행, 확인 프롬프트창에서 `Restart and delete`를 선택하여 실행한다.
이걸 해주자 다시 인텔리센스가 먹기 시작했다.

그리고 추가적으로 `JAVA_HOME` 외에 `gradle`을 `pacman`을 이용해서 WSL 리눅스에 설치해줬다.
그리고 Gradle 관련된 VSCode extension pack들을 설치해줬다. 또, Spring boot와 관련된 pack들 역시 설치해줬다.

여러가지 사소한 문제들 때문에 또 시간을 낭비해버렸다.