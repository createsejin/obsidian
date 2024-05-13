우선 만들고자 하는 Project 최상단에 가서 `git init`을 이용해서 최초 local git repository를 만들어준다. 그후,
`gh repo create`를 하면 interactive question이 시작된다.
```
? What would you like to do? Push an existing local repository to GitHub
? Path to local repository .
? Repository name rust_android_001
? Description my rust programing test for android
? Visibility Private
✓ Created repository createsejin/rust_android_001 on GitHub
  https://github.com/createsejin/rust_android_001
? Add a remote? Yes
? What should the new remote be called? origin
✓ Added remote https://github.com/createsejin/rust_android_001.git
? Would you like to push commits from the current branch to "origin"? Yes
Enumerating objects: 9, done.
Counting objects: 100% (9/9), done.
Delta compression using up to 24 threads
Compressing objects: 100% (6/6), done.
Writing objects: 100% (9/9), 986.40 KiB | 10.84 MiB/s, done.
Total 9 (delta 0), reused 0 (delta 0), pack-reused 0 (from 0)
To https://github.com/createsejin/rust_android_001.git
 * [new branch]      HEAD -> main
branch 'main' set up to track 'origin/main'.
✓ Pushed commits to https://github.com/createsejin/rust_android_001.git
```
대략 이런 절차를 통해서 만들 수 있다. 대부분의 옵션은 Default값으로도 충분하나, 필요한 경우에 직접 입력해서 진행하면 된다. 이렇게 하면 홈페이지에서 하는것 보다 훨씬 간단하고 빠르게 Github remote repository를 만들 수 있게 된다.

또한, `gh repo list`를 통해 현재 로그인한 계정의 모든 github remote repository를 보여주기도 한다.