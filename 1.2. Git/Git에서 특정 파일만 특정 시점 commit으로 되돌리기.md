먼저 git log를 이용해서 되돌리고 싶은 시점의 commit hash값을 얻는다. 이 값을 `<hash>`라고 하면,
다음과 같이 명령어를 쓴다.
`git checkout <hash> -- <file>`
여기에서 `<file>`은 working directory의 root에서 file의 상대 경로를 써주면 된다.
보통은 [[상대 경로 찾기|이 명령어]]를 이용하면된다. 나는 alias로 `rpr`을 이용한다. 우선 파일의 절대 경로를 구한뒤, root로 가서 `rpr <file_path>`이런식으로 쓰면 된다.
그 후 적당히 파일을 원하는데로 수정하고 git commit을 하고 push하면 된다.