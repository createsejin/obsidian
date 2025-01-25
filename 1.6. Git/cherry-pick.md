예를들어서 master 브랜치에서 test01 브런치의 어떤 커밋의 변경사항만을 가져오고 싶은 경우가 있다. 
A 파일의 어떤 부분, B 파일의 어떤 부분이 변경사항으로 기록된 commit이 있다면 그것만 master로 가져오는 방법은
cherry-pick을 이용하는 것이다.

```
git cherry-pick <commit_hash>
```
이런식으로 이용한다. 

이것은 특정 파일을 특정 커밋 시점으로 되돌리는 `git checkout test01 -- A_file_name` [[Git에서 특정 파일만 특정 시점 commit으로 되돌리기|명령어]]와는 조금 다르다. 
이 `checkout .. -- ..` 명령어는 특정 파일을 특정 커밋 시점으로 되돌리는 기능이고, cherry-pick은 특정 커밋의 변경사항만을 현재 브런치에 적용시킨다.