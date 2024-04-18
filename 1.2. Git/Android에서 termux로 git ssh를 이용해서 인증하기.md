기본적으로 [이곳](https://docs.github.com/en/authentication/connecting-to-github-with-ssh)을 참조하면 된다. 
처음에 termux를 설치하고 git을 설치한뒤 git clone을 하고 또 다른 git 작업을 할때 다음과 같은 에러가 뜰 수 있다.
`fatal: detected dubious ownership in repository at '/storage/emulated/0/ob-git' ...`
이럴 경우에는 다음 명령어를 사용해서 현재 directory를 신뢰할 수 있는 work directory로 만들어야한다.
`git config --global --add safe.directory/storage/emulated/0/ob-git`

또한 다음 명령어를 이용하여 자신이 누구인지를 git에게 알려줘야한다.
`git config --global user.email "createsejin@gmail.com"`
`git config --global user.name "createjin"`

또한 이전에 git clone을 할때 https 프로토콜을 이용해서 clone을 했다면 다음 명령어를 통해 https 프로토콜 대신 SSH 프로토콜을 이용하게 할 수 있다.
`git remote set-url origin git@github.com/createsejin/obsidian.git`
다음 명령어로 현재 등록된 remote repository가 어떤 프로토콜을 사용하는지 알 수 있다.
`git remote -v`

이제 여기부터는 SSH key를 만들어야한다.
다음 명령어로 만들 수 있다.
`ssh-keygen -t ed25519 -C "createsejin@gmail.com"`
몇가지를 물어보는데, 먼저 어떤 file에 key를 save할건지 묻는다. 그냥 Enter를 입력하면 defualt로 설정된 file에 key가 새겨지므로 Enter를 눌러 진행한다.
그러면 다음으로 passphrase를 입력하라고 한다. 기억할 수 있는 같은 password를 두 번 같게 입력하면 된다. 이 비밀번호는 나중에 이 key를 사용할때 매번 묻는 password가 된다.

다음으로 이 키를 github.com에 upload해야한다.
`cd ~/.ssh`
`ls`
`cat id_ed25519.pub`
이때 나오는 내용을 클립보드에 붙여넣어서 적당히 알아서 desktop으로 옮겨준다. 
desktop에서는 이 내용을 가지고 [여기](https://docs.github.com/en/authentication/connecting-to-github-with-ssh/adding-a-new-ssh-key-to-your-github-account)를 참고해서 github.com에서 이 키를 추가해주면 된다.
나는 안드로이드에서 만들었기 때문에 이름을 android로 title을 지었다.

이제 SSH가 잘 동작하는지 다음 command를 이용해 TEST하면 된다.
`ssh -T git@github.com`
passphrase를 입력하고 successfully 메세지를 받으면 된거다.

이제 휴대폰에서도 termux와 git을 이용해서 손쉽게 obsidian과 같은 중요한 repository를 관리할 수 있으며 접근 할 수 있다. git을 이용한 방법은 무료이며 아주 빠르고 정확하다. 다만 git에 대한 몇 가지 지식은 필요하다. 그러나 git을 이용하므로서 발생되는 수많은 이점들이 이들을 무시하게 만든다.

