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