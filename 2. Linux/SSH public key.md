다음의 방법으로 RSA key pair를 만들 수 있다.
![[Android에서 termux로 git ssh를 이용해서 인증하기#^2]]

그럼 `~/.ssh`에 두 개의 파일이 생긴다.
```
.rw-------  464 bae 19 Apr 22:02 󰌆 id_ed25519
.rw-r--r--  103 bae 19 Apr 22:02 󰷖 id_ed25519.pub
```
이 중에 `.pub`가 붙은것이 public key이다. 다른것은 private key이니 이 키는 절대로 외부에 노출되어서는 안된다.

다음의 명령어를 Client 단에서 실행한다.
`ssh-copy-id -i ~/.ssh/id_ed25519.pub -p 22 bsv@110.15.1.225`
여기에서 `-i` 옵션에 앞서 만든 public key를 특정할 수 있으며, `-p` 옵션은 port 번호를, 뒤는 접속할 서버의 username과 ip address를 적으면 된다. 좀더 자세한 사항은 [여기에](https://wiki.archlinux.org/title/SSH_keys#Copying_the_public_key_to_the_remote_server)
