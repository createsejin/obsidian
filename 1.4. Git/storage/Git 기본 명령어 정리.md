`git pull <url>` 또는 `git pull origin master`
remote 레포지토리에서 프로젝트를 가져온다. 이것은 처음 작업을 시작할때 무조건 해줘야함. 이걸 안하고 하면 confilc되서 작업한걸 레포지토리에 push할 수 없다.
여기에서 `master`는 브랜치라는 것이다.

`git add .`
현재 변경 사항을 스태이징 영역에 추가한다. 
반대로 unstaging은 `git reset`으로 할 수 있다.

`git commit -m "comments"`
현재 변경 사항이 담긴 스태이징을 commit한다.

`git push origin master`
커밋된 변경사항을 remote repository에 push 한다. 이렇게 하면 실제 remote repository가 변경된다.

## CLion 내장 기능을 이용한 Git 작업
위 명령어들을 쓰는것도 좋지만 기본적으로 CLion에 내장된 update project, commit, push를 사용하면 좀 더 쉽게 git 작업을 할 수 있다. 단축키를 활용하면 한번에 가능하다.

작업을 시작할때에는 `Ctrl+T`로 update project를 해주고(Git pull), Commit은 `Ctrl+K`이며,
push는 `ctrl+shift+K`이다.
