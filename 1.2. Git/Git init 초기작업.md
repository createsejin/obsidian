remote repository를 사전에 github.com에서 미리 만들어둔다.
```
git init
git remote add origin https://github.com/createsejin/<repo-name>
git pull origin main

git add .
git commit -m "comment..."

git push --set-upstream origin main
```
반드시 git pull을 먼저 해주는것이 중요하다.