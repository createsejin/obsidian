이 [글](https://ahnbk.dev/?p=316)을 보면 대략 감을 잡을 수 있다. 

일단은 `Win + R`을 눌러서 `ms-settings:optionalfeatures`을 입력하고 실행시킨다.
창 밑으로 내리면 맨 아래에 '기타 Windows 기능'이 있다. 들어가서 `Hyper-V`항목을 체크한 뒤 재부팅한다.

다시 실행창을 열어서 `virtmgmt.msc`를 통해 Hyper-V Manager에 들어간다.

상단 메뉴 -> 동작 -> 가상 스위치 관리자 
'새 가상 네트워크 스위치'를 선택하고 '외부' 선택, '가상 스위치 만들기'

이름을 적당히 짓는다(wsl2-external).
'연결 형식'에서 '외부 네트워크'에서 적당한 장치를 선택한다.
현재 내 메인컴은 WIFI에 연결되어있으므로 나는 `Inter(R) Wi-Fi 6E AX210 160MHz`를 선택했다.
현재 컴퓨터가 사용하는 네트워크 장치를 선택해야한다. 2025년 1월 기준으로 나는 유선랜을 쓰므로 유선랜 장치를 선택해서 적용했다.

적용 누르면 경고가 뜨는데 '예'를 누른다.

이제 Hyper-V Manager를 종료하고, 사용자 홈 디렉토리 (`C:\User\<user-name>\`)에 `.wslconfig` 파일을 생성하고 다음과 같이 입력한다.

```bash
[WSL2]
networkingMode = bridged
vmSwitch = wsl2-external
```

WSL을 완전히 종료한다.
```
wsl --shutdown
```

다시 ArchWSL을 실행하여 접속한다.
```
cd Arch
./Arch1.exe

ip addr
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
       valid_lft forever preferred_lft forever
2: eth0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc mq state UP group default qlen 1000
    link/ether 5e:bb:f6:9e:ee:fa brd ff:ff:ff:ff:ff:ff
    inet 192.168.45.219/24 brd 192.168.45.255 scope global eth0
       valid_lft forever preferred_lft forever
```
그러면 위와같이 외부망의 IP(192.168..)를 할당받아 사용되는 것을 볼 수 있다.

그러나 이 [글](https://ahnbk.dev/?p=342)에 따르면 위 사항을 적용하고 나서도 업로드 속도가 무차별로 저하되는 증상이 발생한다고 한다. 이것을 해결하기 위해서는 시작단추 우클릭 -> 장치 관리자 에서 '네트워크 어댑터' -> Hyper-V Virtual .. 우클릭 속성창을 띄운뒤
고급 탭 에서 Large Send Offload Version 2 (IPv4) ,Large Send Offload Version 2 (IPv6) 항목을 Enable에서 Disable로 바꿔주면 이 문제가 해결된다고 한다.

그런데 이 글 작성자 [블로그](https://ahnbk.dev/). 굉장히 알찬 정보가 많다. 둘러볼만한 정보가 꽤나 있는듯.

#Arch #linux 