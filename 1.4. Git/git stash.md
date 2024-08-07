다른 [[branch 전환 및 병합|브랜치로 전환]]을 해서 작업을 하는데 또다른 브랜치에서 이슈가 생겼다. 그런데 현재 브랜치에서 commit을 하기는 애매하고, 변경사항을 어찌 처리할지가 애매하다. 그럴때 쓸 수 있는게 바로 `git stash` 명령어이다. 이것은 현재 변경사항을 stash list에 저장하고 변경사항을 없애준다. 

`git stash list`를 사용하면 stash list에 저장된 데이터를 확인할 수 있는데,

`git stash apply`를 사용하면 가장 최근의 stash 변경 사항을 적용해준다.

`git stash list`를 치면
```
stash@{0}: WIP on http001: 6016090 HttpClient Login attempt is failed.
stash@{1}: WIP on master: 23f5369 anchor reform
```
이런식으로 나오는데, 
가장 최근이 아닌 stash를 pop할 수도 있다. `git stash pop stash@{1}` 이렇게 하면 된다.