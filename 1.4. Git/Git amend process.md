먼저 변경사항을 수정한 후, `git add .`으로 변경사항을 스태이징에 올린다. 
`gaa`로도 수행할 수 있다[^1]. 

그 다음에는 `git commit --amend --no-edit` 또는 `gcn!`으로 amend를 수행한다. 이렇게 하면 기존 commit msg를 수정하지 않는다. 

그리고 만약 이전 커밋을 원격 저장소에 push 했다면 push를 할때 강제 푸시(Force push)를 해야한다. 그렇지 않았다면 그냥 push를 해주면 된다.
강제 push는 다음과 같이 한다.
`git push origin main --force` 또는 `gpf!`


[^1]: oh-my-zsh의 git plugin을 사용할 경우에만 가능하다.