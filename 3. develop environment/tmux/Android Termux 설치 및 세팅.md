[기본 설치 참조 문서](https://toopyo.tistory.com/entry/Termux%EC%95%88%EB%93%9C%EB%A1%9C%EC%9D%B4%EB%93%9C-%ED%8F%B0%EC%97%90%EC%84%9C-%ED%84%B0%EB%AF%B8%EB%84%90-%EC%93%B0%EA%B8%B0) : 한국어 문서인데 Termux 설치 및 기본 세팅에 대해 설명하고 있다.
기본적으로 [F-Droid](https://f-droid.org/en/packages/com.termux/)에서 Termux apk file을 다운받아서 휴대폰에 저장한 후 실행하여 설치하면 된다. 또한 내가 이전에 쓴 [[Android termux를 이용한 git 사용하기|글]]에서는 처음에 Termux에서 저장 공간 접근 권한을 허용하는 방법을 설명해두고 있으니 참고하자.

[이글](https://practical.li/neovim/termux/)에서는 Termux에서 Neovim을 사용하는 방법을 간략하게 소개하고 있다.
나같은 경우는 `termux-chagne-repo`를 이용해서 우선 mirror site 지역을 Asia로 바꾸고 
`pkg upgrade -y`를 통해 패키지를 업그레이드 후 `pkg install tmux neovim git` 등을 설치해줬다.

또한 `cd`를 하면 home으로 가지는데, 여기에서 `mkdir -p .config/nvim`을 하고 `cd .config/nvim`, 
`git clone git@github.com:createsejin/nvimt.git .`을 통해 내 nvim 기본 설정을 불러와봤다. 아무래도 vim-plug가 설치되있지 않다보니 에러가 생겼었다. 

`sh -c 'curl -fLo "${XDG_DATA_HOME:-$HOME/.local/share}"/nvim/site/autoload/plug.vim --create-dirs https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim'`
이 명령이 필요해 보인다. [vim-plug](https://github.com/junegunn/vim-plug)

명령을 실행하고 다시 nvim을 실행한 뒤 `:PlugInstall`을 실행하니 plugin이 잘 설치됐다.

기존에 nvimt repository를 `~/.config/nvim`에 받아놔서 여기에 들어있는 `tmux.conf`를 다음 명령어들을 통해 link를 해주고 tmux source-file을 해주었다.
```
cd
mkdir -p .config/tmux
cd .config/tmux
ln -s -r ../nvim/tmux.conf tmux.conf
tmux source-file tmux.conf
```
또한 tmux plugin을 위해 tpm을 설치해주어야했다.
`git clone https://github.com/tmux-plugins/tpm ~/.tmux/plugins/tpm`
그 후 tmux 세션을 열어서 Ctrl+a, Shift+i를 통해 plugin들을 설치해줬다.

문제는 pkg에는 xsel이 없기 때문에 tmux에서 y키를 이용해서 클립보드에 붙여넣는건 안된다. 하지만 어차피 휴대폰이기 때문에 그냥 드래그해서 대충 copy를 누르면 되니까 신경 쓸것 없다. 또는 tmux copy-mode에서 clipboard에 붙여넣으려면 그냥 Enter키를 누르면 잘 된다.

또한 [이것](https://f-droid.org/ko/packages/com.termux.styling/)을 이용하면 놀랍게도 catppuccin mocha color theme를 선택할 수 있다. 또한 select font를 통해 source code pro font 역시 설정할 수 있었다. 우선 저 링크에서 termux-styling apk를 다운받아서 설치하고, termux에서 화면을 길게 누르면 뜨는 메뉴에서 more에 들어간 뒤 Style에서 이와 같이 설정할 수 있다.

oh-my-zsh를 다음 명령어를 통해 설치해줬다.
`sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"`
`chsh -s zsh`를 통해 기본 shell을 zsh로 설정해주었다.

zsh-syntax-highlighting과 zsh-autosuggestions을 설치해주었다.
방법은 oh-my-zsh plugin manager를 이용하는건데,
우선 두 개의 git repository를 다음 명령어를 통해 clone해 주어야한다.
```
git clone https://github.com/zsh-users/zsh-syntax-highlighting.git ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-syntax-highlighting

git clone https://github.com/zsh-users/zsh-autosuggestions ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-autosuggestions
```
그 뒤에 `~/.zshrc`에 다음과 같이 수정한다.
```
plugins=(git zsh-syntax-highlighting zsh-autosuggestions)
```
그 후 `source ~/.zshrc`를 통해 plugin을 설치해준다.

보안을 위해 gnupg를 설치해주었다.

[termux-api](https://f-droid.org/packages/com.termux.api/)를 설치해주었다.
apk 설치 후, termux에서도 `pkg install termux-api`를 설치해주어야한다.