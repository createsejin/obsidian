다 필요없고 
`git config --global credential.credentialStore cache`
이거 쓰면 끝난다. fugitive도 이걸 써야 제대로 동작한다. 
gpg는 나중에 [[Android에서 termux로 git ssh를 이용해서 인증하기|SSH]] 쓸거 아니면 그냥 쓰지 않는게 좋다. 제대로 동작하질 않는다.
## github-cli
그러나 이것보다 훨씬 좋은 방법이 있다.
그것은 바로 `github-cli`를 이용하는 방법이다.
pacman을 통해서 설치할 수 있었다.
설치 후 다음을 실행하자.
```
gh auth login
? What account do you want to log into? GitHub.com
? What is your preferred protocol for Git operations on this host? HTTPS
? Authenticate Git with your GitHub credentials? Yes
? How would you like to authenticate GitHub CLI? Login with a web browser
```
선택지는 위처럼 해주면 된다. 이렇게 해두고 repository의 url을 다음의 방법으로 해준다.
![[Android에서 termux로 git ssh를 이용해서 인증하기#^1]]
이 명령어를 그대로 사용하되 `https` 프로토콜 주소를 이용해서 레포지토리 remote url을 설정해준다.

이렇게 해주면 `git push`나 `git pull`등을 사용할때 인증을 알아서 자동으로 처리해준다. 매우 편리하다.

## Android
Termux에서는 
`pkg install gh`를 통해 github-CLI를 설치할 수 있다.
그 후 위와 동일한 방법으로 `gh auth login`을 진행해주면 된다.
terminal에 뜨는 인증번호 `ABCD-EFGH`를 통채로 복사해서 웹브라우저에 붙여넣으면 쉽게 인증할 수 있다. 그후 여기에 있는 모든 레포지토리를 전부 https 프로토콜로 set-url해주면 된다.