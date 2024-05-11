OpenSSH는 두 가지 component로 구성되어있다. 하나는 Client component, 다른 하나는 Server component다. 이름에서 알 수 있듯이 Client는 Server에 접속하기 위한 프로그램이고, Server는 Client의 연결을 리스닝하는 component다. 

우선 아래의 방법으로 서버 컴퓨터를 포트포워딩 해야한다.
![[IP 조회하기]]

22번 포트를 포트포워딩 해준다. 외부 포트와 내부 포트를 22로 정하고, 서버컴의 로컬 ip를 설정해주면 된다. 

그 후 다음 명령어를 통해 sshd service를 실행시켜줘야한다.
```
sudo systemctl enable sshd
sudo systemctl start sshd
sudo systemctl status sshd
```
마지막 명령어로 sshd의 service 상태를 볼 수 있다. 
Active: active(running) 이면 된다.

또한 다음의 명령어로 service를 중단시킬 수 있다.
```
sudo systemctl disable sshd
sudo systemctl stop sshd
```
서버가 준비 됐으면 이제 클라이언트(접속하려는 컴퓨터)에서 다음 명령어를 통해 접속 할 수 있다.
```
ssh bsv@120.12.2.225
```
여기에서 `bsv`는 접속하려는 서버의 user 이름이고, 그 뒤는 서버의 공인 아이피 주소다.
처음 접속하면 bsv의 passwd를 입력하라고 한다.

## Client config
매번 user name과 ip를 적는것은 귀찮다.
따라서 `~/.ssh/config` 파일에 다음과 같이 설정해보자.
```
Host bsv
  Hostname 110.15.1.225
  Port 22
  User bsv
```
이렇게 해두면 이제 이 서버에 접속할때 다음과 같이 심플하게 커맨드를 쓸 수 있다.
`ssh bsv`
