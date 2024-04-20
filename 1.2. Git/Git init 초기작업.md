remote repository를 사전에 github.com에서 미리 만들어둔다.
```
git init
git remote add origin https://github.com/createsejin/<repo-name>

git pull origin main

git add .
git commit -m "comment..."

git push --set-upstream origin main
```
만약 아직 아무런 commit을 만들지 않았다면 pull은 생략해도 된다.
다만 이미 commit이 존재하는 repository에 push하려면 반드시 pull을 해야한다.

## Github 공식 가이드
```
echo "# nvimt" >> README.md
git init
git add README.md
git commit -m "first commit"
git branch -M main
git remote add origin https://github.com/createsejin/nvimt.git
git push -u origin main
```
or push an existing repository from the command line
```
git remote add origin https://github.com/createsejin/nvimt.git
git branch -M main
git push -u origin main
```

만약 현재 디렉토리가 안전한 디렉토리로 지정되지 않아서 다음과 같은 오류가 뜨면
[[Android에서 termux로 git ssh를 이용해서 인증하기#^gitsafedir|이곳]]을 참조하자.