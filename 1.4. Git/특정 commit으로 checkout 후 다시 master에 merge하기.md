일단 git log를 통해서 특정 시점으로 돌아갈 commit의 hash값을 얻는다.
```
git log
git checkout <hash>
```
그러면 main branch와 detach된 상태로 그때 시점으로 돌아간다.

새로운 branch로 switch한다.
```
git switch -c temp001
```
작업을 한 후에 commit을 한다. 

master 브랜치로 이동한다.
```
git checkout master
```

새로 만들어진 `temp001` branch를 master에 merge한다.
```
git merge temp001
```

임시 branch를 삭제한다.
```
git branch -d temp001
```