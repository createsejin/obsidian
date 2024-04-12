[[2. Fedora workstation 설치 진행#pack009 script setup|간단한 셋업 정리]]

일단은 pack 파일들을 Dropbox 로컬 위치로 모두 옮겨주었다. 이렇게 한 이유는 그냥 그 자체로 바로바로 백업이 가능하도록 하는 것이었다. 구지 귀찮게 파일을 복사해서 백업할 필요가 전혀 없는것이다. 그래도 pack파일들은 너무나도 중요한 파일들이기 때문에 가끔씩은 구글드라이브나 네이버 N드라이브, 원드라이브에도 올려줘야한다. 

아무튼 오늘 정리할 내용은 pack009번에 대한 쉘스크립트 구현에 대한 내용이다.

먼저 pack009번의 위치는 다음과 같다.
```
/home/bae/Dropbox/Packs/Pack009_2023-10-22_001.hc
```
흠. 그런데 이제 pack010에 든 암호 데이터베이스를 그냥 드롭박스에 놓기로 하였다. 대신 암호를 매우매우 길게 해서 아주 안전한 암호를 사용하기로 하였다. 그래서 pack010은 사실상 무쓸모나 다름없게 되었다. 이렇게 한 이유는 호환성 때문이다. 또한 암호 데이터베이스의 경우 모바일에서도 자주 쓰기 때문에 백업을 바로바로 그때그때 적용하기 위해서였다. 또한 이렇게 하면 데이터베이스 변경과 백업이 동시에 이루어지는 장점을 가지게 된다. 
아무튼 이 이야기는 여기까지 하고 셀 스크립트로 다시 넘어가자.

일단 기본적으로 `home` 위치에 `scripts` 폴더를 만들어 주었다. 그리고 `/usr/local/bin`에 `pack009.sh`를 만들어 주었다.
```bash
cd /usr/local/bin
sudo touch pack009.sh
```
# 환경변수
`/usr/local/bin` 폴더에 있는 실행 파일이나 스크립트는 환경 변수로 등록되어 쉘의 어떤 위치에서도 모두 실행할 수 있는 장점을 가진다. 그래서 보통 실행파일로 된 프로그램을 여기에 넣어두면 어디서든 꺼내 쓸 수 있다.
```bash
sudo nano pack009.sh
```
다음은 pack009.sh의 내용이다.
```shell
#!/bin/bash
filepath=$(cat ~/Dropbox/scripts/pack009path.txt)
session_path="/mnt/pack009/session3.txt"

if [ "$1" = "-d" ]; then
        sudo veracrypt -d "$filepath"
elif [ "$1" = "-fd" ]; then
        sudo veracrypt -d -f "$filepath"
elif [ "$1" = "-w" ]; then
        sudo veracrypt -t -k "" --pim=0 --protect-hidden=no "$filepath" /mnt/pack009
elif [ "$1" = "-g" ]; then
        if [ -f "$session_path" ]; then
                cat "$session_path" | xargs echo -n | xclip -selection clipboard
                echo "copyed."
        else
                echo "can not found session file. Please mount pack009."
        fi
elif [ $# -eq 0 ]; then
        sudo veracrypt -t -m ro -k "" --pim=0 --protect-hidden=no "$filepath" /mnt/pack009
else
        echo "input correct option command."
fi
```
그리고 다음의 pack009path.txt 파일은 pack009의 위치를 마킹하면 된다.
```
/home/bae/Dropbox/Packs/Pack009_2023-10-28_001.hc
```
```bash
pack009.sh # 컨테이너를 read-only mode로 마운트 한다. 
pack009.sh -g # 마운트 후 keepass DB key값을 얻는다.
pack009.sh -d # unmount
pack009.sh -fd # force unmount
pack009.sh -w # writable mounting
```
