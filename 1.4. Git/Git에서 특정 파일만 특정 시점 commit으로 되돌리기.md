먼저 git log를 이용해서 되돌리고 싶은 시점의 commit hash값을 얻는다. 이 값을 `<hash>`라고 하면,
다음과 같이 명령어를 쓴다. 만약 특정 시점의 commit 상태로 완전히 돌리려면 [[특정 commit으로 checkout 후 다시 master에 merge하기|이 글]]을 참고하자.
`git checkout <hash> -- <file>`
여기에서 `<file>`은 working directory의 root에서 file의 상대 경로를 써주면 된다.
보통은 [[상대 경로 찾기|이 명령어]]를 이용하면된다. 나는 alias로 `rpr`을 이용한다. 우선 파일의 절대 경로를 구한뒤, root로 가서 `rpr <file_path>`이런식으로 쓰면 된다.
그 후 적당히 파일을 원하는데로 수정하고 git status를 확인한뒤 git add, git commit을 하고 push하면 된다.

이 명령어는 특정 브랜치에서 특정 파일만 현재 브런치에 반영하고 싶을때에도 사용할 수 있다.

또한 특정 파일 하나만 [[git stash|stash]]해서 변경사항을 버리는 방법도 있다.
`git stash save -- myfile.txt mycode.py`
이런식으로 여러개의 파일을 동시에 포함시킬 수도 있다.

`git stash save -p` 
이걸 사용하면 어떤 파일을 선택할지 interactive mode로 묻는다.