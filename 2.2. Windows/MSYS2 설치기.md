이 환경은 Windows에서 마치 리눅스처럼 pacman이나 zsh, tmux 등을 사용할 수 있게하며, 리눅스와 비슷한 폴더 구조를 가지고 있다. 
정확히는 Posix Emulator라고 한다. 이것이 있으면 WSL처럼 Windows 자체에서 편리한 터미널 쉘 환경을 구축할 수 있는것 같다. 무엇보다도 Arch Linux의 Pacman을 사용할 수 있다는게 너무나도 큰 장점인것 같다.
다만 리눅스와 동일한 환경은 아니다. 예를들어 `systemctl`같은 명령어는 존재하지 않는다. 하지만 이것을 이용하면 좀더 쉽게 Windows에서 C/C++ 개발 환경을 구축할 수 있을것 같다.
리눅스와 조금 커맨드가 다를 수 있기 때문에 `.zshrc`파일을 신중하게 테스트하면서 내 설정을 넣어야 할 것으로 보인다.

Windows Terminal에서 실행하게 하려면 [이 문서](https://www.msys2.org/docs/terminals/)의 지시를 따르면 된다. 
처음 설정하면 msys2가 갑자기 한국어 환경으로 바뀌는데 다음을 `~/.bash_profile`에 추가해주고 다시 쉘을 시작하면 영어로 설정할 수 있다.
```
export LC_ALL=en_US.UTF-8 
export LANG=en_US.UTF-8
```

[이 문서](https://www.msys2.org/docs/environments/)에 따르면 MSYS2의 환경은 여러가지가 존재하는데, gcc와 C Library를 ucrt로 사용하는 UCRT64 환경이 가장 안정적이고 널리 쓰이는 환경으로 보인다. 

[이 문서](https://www.msys2.org/docs/ides-editors/)의 마지막에서는 VSCode의 터미널에 MSYS2를 추가하는 방법이 나온다. VSC의 settings.json에 해당 terminal 설정을 붙여넣으면 된다.
또한 터미널을 열어서 + 버튼 옆 아래 화살표를 누른뒤, 'Select Default Profile'을 선택하면 VSC의 기본 터미널을 MSYS2로 설정할 수도 있다.

## gcc 설치 및 환경변수 설정
가장 중요한 gcc toolchain을 설치하기 위해서
```
pacman -S --needed base-devel mingw-w64-ucrt-x86_64-toolchain
```
이렇게 해주면 어떤 패키지들을 설치할거냐 묻는데, Enter(default)를 눌러 모든 패키지들을 설치해주자.
그리고 이것을 Windows의 다른 쉘에서도 사용할 수 있게 하려면 환경 변수에서 `C:\msys64\ucrt64\bin`를 추가해주자.
그러면 powershell에서도 gcc를 사용할 수 있게된다.

그리고 VSCode에서 커맨드 팔레트를 열고 `Select IntelliSense Configuration`을 실행하고 
`Use gcc.exe`를 설정해주면 된다. 위치는 `C\msys64\ucrt64\bin\` 이렇게 뜰 것이다.
## zsh 설정
이 [깃헙 페이지](https://gist.github.com/danieleagle/702f43184c4f1e5bf73021106fefc328)를 참고했다.
```
pacman -S zsh curl
sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"
```
을 통해 oh-my-zsh를 설치할 수 있다.

`C:\msys64\msys2_shell.cmd`를 열어서 
```
set "LOGINSHELL=zsh"
```
이렇게 바꿔준다.

## 그러나..
Windows Terminal에서는 너무 성능이 떨어진다. profile 로딩하는것도 너무 느리고 커서 플리커링 이슈도 있고, 특히 Tmux는 거의 쓸 수 없을 정도로 심각하게 느려터졌다. 
결국 그냥 gcc pacman으로 설치해주고 update나 해주고 이걸 windows 환경 변수에 등록해서 그냥 powershell 기반으로 쓰는게 훨씬 나아보인다.
쉘로서 쓰기에는 너무나도 열악한 성능 때문에.. 
아마도 Windows Terminal에서 사용할때에는 이렇다. 다른 쉘에서도 그런지는 테스트를 해봐야겠다.

[[Alacritty setup for Windows|이 글]]에서 Alacritty를 Windows에서 세팅해봤는데 생각보다 괜찮은것 같다. 일단 Tmux를 켜면 좀 느려지는데, 그냥 Msys만 켰을때에는 생각보다 괜찮다. 

## 심볼릭 링크 명령어 ln이 링크는 안만들고 deep copy를 하는 건에 대하여..
[이 페이지](https://www.msys2.org/docs/symlinks/)에 몇가지 이유가 나오는데 가장 큰 이유는 Windows가 이걸 관리자 권한에서만 만들수 있도록 했었다는데..
일단은 글 중간에 보면 `MSYS=winsymlinks:nativestrict` 이런식으로 환경변수를 정해주면 native windows symbolic link를 생성할 수는 있는것으로 보인다.
그러나 실제로 Msys에서 심링크를 만들어보면 역시나 permssion 때문에 실행할 수 없다고 한다.
[이 페이지](https://www.msys2.org/wiki/Sudo/)에서 한가지 실마리를 얻을 수 있었다. Windows에서도 Unix 계열의 `sudo`를 사용할 수 있도록 하는 기능을 Rust로 구현해놓은 것으로 보이며, [이 페이지](https://learn.microsoft.com/en-us/windows/sudo/)에서는 이것을 사용하는 방법을 안내하고 있다.
그런데 현재 Windows version 23H2 기준으로는 살짝 틀리다. 방법은 한국어 기준으로 제어판에 들어간뒤 시스템 -> 개발자용 -> 개발자 모드를 켜는 것이다. 
이렇게 하면 Windows에서도 심볼릭 링크를 만들때 관리자 권한을 요구하지 않는다.