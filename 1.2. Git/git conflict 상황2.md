```
~/.../shared/ob-git $ git add .                 ~/.../shared/ob-git $ git status
On branch main                                  Your branch is up to date with 'origin/main'.   
Changes to be committed:                          (use "git restore --staged <file>..." to unstage)
        new file:   "Test\354\236\205\353\213\210\353\213\244..md"                              
~/.../shared/ob-git $ git commit -m "test commit"                                               [main 5a9237e] test commit
 1 file changed, 1 insertion(+)                  create mode 100644 "Test\354\236\205\353\213\210\353\213\244..md"
~/.../shared/ob-git $ git push                  Enter passphrase for key '/data/data/com.termux/files/home/.ssh/id_ed25519':
To github.com:createsejin/obsidian.git           ! [rejected]        main -> main (fetch first) error: failed to push some refs to 'github.com:createsejin/obsidian.git'                        hint: Updates were rejected because the remote contains work that you do not
hint: have locally. This is usually caused by another repository pushing to                     hint: the same ref. If you want to integrate the remote changes, use                            hint: 'git pull' before pushing again.          hint: See the 'Note about fast-forwards' in 'git push --help' for details.                      ~/.../shared/ob-git $ git pull                  Enter passphrase for key '/data/data/com.termux/files/home/.ssh/id_ed25519':                    remote: Enumerating objects: 6, done.           remote: Counting objects: 100% (6/6), done.
remote: Compressing objects: 100% (2/2), done.  remote: Total 4 (delta 2), reused 4 (delta 2), pack-reused 0
Unpacking objects: 100% (4/4), 2.66 KiB | 21.00 KiB/s, done.                                    From github.com:createsejin/obsidian
   c61fa03..f1107c0  main       -> origin/main  hint: You have divergent branches and need to specify how to reconcile them.
hint: You can do so by running one of the following commands sometime before                    hint: your next pull:
hint:                                           hint:   git config pull.rebase false  # merge   hint:   git config pull.rebase true   # rebase
hint:   git config pull.ff only       # fast-forward only                                       hint:
hint: You can replace "git config" with "git config --global" to set a default                  hint: preference for all repositories. You can also pass --rebase, --no-rebase,                 hint: or --ff-only on the command line to override the configured default per
hint: invocation.                               fatal: Need to specify how to reconcile divergent branches.
~/.../shared/ob-git $ git config pull.rebase false                                              ~/.../shared/ob-git $ git pull
Enter passphrase for key '/data/data/com.termux/files/home/.ssh/id_ed25519':                    hint: Waiting for your editor to close the file... error: cannot run vi: No such file or directory
error: unable to start editor 'vi'              Not committing merge; use 'git commit' to complete the merge.
~/.../shared/ob-git $ git commit -m "try merge for test commit"                                 [main 405c7e0] try merge for test commit
~/.../shared/ob-git $ git push                  Enter passphrase for key '/data/data/com.termux/files/home/.ssh/id_ed25519':                    Enumerating objects: 7, done.
Counting objects: 100% (7/7), done.
Delta compression using up to 8 threads         Compressing objects: 100% (5/5), done.
Writing objects: 100% (5/5), 559 bytes | 32.00 KiB/s, done.
Total 5 (delta 2), reused 0 (delta 0), pack-reused 0 (from 0)
remote: Resolving deltas: 100% (2/2), completed with 1 local object.                            To github.com:createsejin/obsidian.git
   f1107c0..405c7e0  main -> main               ~/.../shared/ob-git $ git status
On branch main
Your branch is up to date with 'origin/main'.

nothing to commit, working tree clean           ~/.../shared/ob-git $ git log --graph
*   commit 405c7e08401821a8789317fcc4b1afa809fa89ae (HEAD -> main, origin/main, origin/HEAD)
|\  Merge: 5a9237e f1107c0
| | Author: createjin <createsejin@gmail.com>
| | Date:   Thu Apr 18 17:48:52 2024 +0900      | |
| |     try merge for test commit               | |
| * commit f1107c04fcf2d842d4025214304ba7bc1a9717c9
| | Author: createsejin <createsejin@gmail.com> | | Date:   Thu Apr 18 17:42:02 2024 +0900
| |                                             | |     2024-04-18-004
| |                                             * | commit 5a9237ec104beb56d9129329328261813aeb46a1
|/  Author: createjin <createsejin@gmail.com>   |   Date:   Thu Apr 18 17:45:24 2024 +0900
|                                               |       test commit
|
* commit c61fa0349c05870100c44f2da68a2057bd9c75ab                                               | Author: createsejin <createsejin@gmail.com>
~/.../shared/ob-git $
```