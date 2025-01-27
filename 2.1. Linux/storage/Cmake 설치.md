https://cmake.org/download/ 에 보면
|Linux x86_64|[cmake-3.28.3-linux-x86_64.sh](https://github.com/Kitware/CMake/releases/download/v3.28.3/cmake-3.28.3-linux-x86_64.sh)| 에서 .sh를 다운받는다.
`./cmake-3.28.3-linux-x86_64.sh /opt`
이걸 쉘에서 돌리면 `/opt`에 cmake가 설치된다.
이걸 환경 변수에 추가해주면 된다.

환경 변수는 `sudo nano ~/.bashrc`를 실행해서 맨 아랫줄로 가서(`Ctrl+Shift+-, Ctrl+v`) 
`export PATH="/opt/cmake-3.28.3-linux-x86_64/bin:$PATH"`
이런식으로 추가해주면 된다.
여기서 `$PATH`는 현재 환경 변수를 말하는것이고, `:`를 통해 각 PATH를 구분할 수 있다.

`cmake --version`을 실행해서 버전을 확인한다.