기본적으로 로컬 저장소는 [[branch 전환 및 병합]] 또는 [[특정 commit으로 checkout 후 다시 master에 merge하기]] 등의 방법이 있다.
`git branch -d <branch>`를 이용하는 방법인데, 문제는 원격 저장소에 push한 경우에는 이것으로 원격 저장소의 branch를 삭제할 수 없다. 

일단 원격 저장소와 로컬 저장소의 모든 브랜치를 조회하려면 `git branch -a`을 쓰면 된다.

또한 원격 저장소의 브런치를 제거하려면 다음 명령어를 쓴다.
```
git push origin -d <branch>
```
