[이곳](https://github.com/yuk7/ArchWSL)에서 굉장한걸 발견했다. Arch linux를 windows WSL2에서 아주아주 쉽게 인스톨해주는 프로그램인데.
방법은 정말 쉽다. 그냥 Arch.zip 받은 뒤에 적당한 위치에 Arch.exe와 들어있는 파일을 배치하고 실행해주면 끝난다.
접속은 Arch.exe를 통해 접속한다. 혹은 이 실행파일이 있는 곳을 환경 변수에 등록하면 어디서든 `arch` 명령어를 치면 접속하게 만들 수도 있다.
만약 설치가 잘 안된다면 `win+R`을 눌러서 실행창에 `ms-settings:optionalfeatures`를 입력하면 윈11 기준으로 제어판이 뜨는데 맨 밑으로 내려가서 '기타 Windows 기능'에 들어가면 여러가지 추가 기능들이 있는데, 그 중에서 'Hyper-V'와 'Linux용 Windows 하위 시스템' 항목을 체크한뒤 재부팅 하면 이제 제대로 `Arch.exe`가 설치될 것이다.

또한 중요한 점이 있는데, Arch.exe로 설치하면 WSL에 Arch로 시스템이 등록된다. 이것은 `wsl -l -v`명령어를 통해 볼 수 있다. 시스템을 제거하려면 `wsl --unregister Arch`식으로 명령어를 치면 된다. 이것은 매우 위험한 명령어이다. 시스템 자체를 아예 없애버리기 때문이다. 따라서 주의가 필요하다. 
앞서 말했던바와 같이, Arch.exe를 다른 이름, 예를 들면 Arch1.exe로 복사한뒤 실행하면 Arch1이라는 이름의 새로운 Arch linux 시스템이 WSL에 등록된다. 이걸 이용해서 여러개의 Arch linux를 다룰 수 있다.

또한 Arch를 설치한 뒤, pacman을 이용하려면 여기 이 [가이드](https://wsldl-pg.github.io/ArchW-docs/How-to-Setup/#setup-after-install)를 따라서 pacman keyring setting을 해야한다.

그런데 문제가 발생했다. 인터넷 연결은 되는것 같은데 ip addr를 해보면 172.21.50.xx 대역의 아이피를 받아서 사용하고 있다는게 문제였다. 이렇게 할 경우 네트워크가 사용할 수 없을 정도로 매우매우 느려져서 pacman이 아예 진행이 안되는 문제가 있었다.
이것은 이 [글](https://ahnbk.dev/?p=316)에서 찾은 정보다. 이 글에 대한 구체적인 문제 해결 프로세스틑 이 [[ArchWSL 네트워크 문제|글]]에 내가 적어놓았다. 이 글을 통해 문제를 해결하자 pacman이 정상적으로 작동하였다.

#linux #Arch 