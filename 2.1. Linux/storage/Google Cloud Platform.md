

나는 rclone을 이용해서 구글 드라이브를 로컬 마운트 포인트에 마운트 했다.

우선 `/mnt/gdrive`처럼 미리 마운트 포인트를 만들어준다.
이곳은 `sudo mkdir gdrive`로 만들어야한다.

다음 명령어로 rclone을 설치했다.
```bash
curl -O https://downloads.rclone.org/rclone-current-linux-amd64.zip
unzip rclone-current-linux-amd64.zip
cd rclone-*-linux-amd64
sudo cp rclone /usr/bin/
sudo chown root:root /usr/bin/rclone # rclone 바이너리 소유권 변경
sudo chmod 755 /usr/bin/rclone # 실행 권한 변경
# rclone 메뉴얼 페이지 설치
sudo mkdir -p /usr/local/share/man/man1
sudo cp rclone.1 /usr/local/share/man/man1/
sudo mandb
```
그 다음에 `rclone config`를 실행해서 대화 상자대로 진행하면 된다. 
참고로 google cloud platform의 project client ID가 필요하다. 이 부분은 rclone에 제시된 [문서](https://rclone.org/drive/#making-your-own-client-id)를 참조하면 좋다. 여기에 제시된 대로 Project를 만들고 설정을 해주면 된다.
https://console.cloud.google.com/welcome?project=ardent-bridge-414707
여기에서 APIs & Services -> Credentials -> OAuth 2.0 Client IDs

config 진행 중에 이걸 custom 설정하면 꽤나 복잡하므로 일반적인 사용을 위해서는 그냥 default 설정으로 모두 설정하겠다고 해버리면 된다. 그 후에도 각각 대화 상자를 따라가면 된다.

그 이후에는 시스템이 시작될 때마다 이 rclone을 자동으로 로컬 마운팅 해주는걸 systemd라는걸 이용해서 설정해줘야한다.

우선 다음 명령어로 디렉토리 이동하자
`cd /etc/systemd/system`

그런다음 새로운 service 파일을 만든다.
`sudo touch rclone.service`

그리고 다음과 같이 내용을 작성한다.
```
[Unit]
Description=Rclone Service
Wants=network-online.target
After=network-online.target

[Service]
ExecStart=/usr/bin/rclone mount gdrive: /mnt/gdrive
Restart=on-abort
User=bae
Group=bae

[Install]
WantedBy=default.target
```
여기에서 rclone이 설치된 부분과 미리 설정해둔 rclone config name과 마운트할 포인트 위치,
그리고 유저 이름과 Group을 유의해서 넣어준다.
참고로 유저이름은 `whoami`명령어를 통해, group은 `groups bae`를 통해 알 수 있다.
group의 경우 `bae : bae wheel`이런식으로 뜰텐데, 그냥 가장 앞에 있는 `bae`를 넣어주면 된다.

그리고 
```
sudo systemctl daemon-reload
sudo systemctl enable rclone.service
```
를 통해 서비스를 등록한다.

문제가 발생하면
`systemctl status rclone.service`로 상태를 알 수 있다.




