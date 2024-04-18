예를 들어서 obsidian을 여러 대의 컴퓨터에서 운용했을때, 나의 경우에는 서브컴에서 변경 사항이 발생하고, 휴대폰에서 마지막 변경사항을 push 했던 경우 서브컴에서 commit 없이 바로 git pull 을 하면 git은 다음과 같은 에러를 뱉는다.
```sh
PS C:\Users\bae\obsidian> git pull
remote: Enumerating objects: 65, done.
remote: Counting objects: 100% (65/65), done.
remote: Compressing objects: 100% (23/23), done.
remote: Total 44 (delta 30), reused 35 (delta 21), pack-reused 0
Unpacking objects: 100% (44/44), 1.09 MiB | 3.96 MiB/s, done.
From https://github.com/createsejin/obsidian
   6b9540f..90bf4b6  main       -> origin/main
error: Your local changes to the following files would be overwritten by merge:
        .obsidian/plugins/recent-files-obsidian/data.json
        .obsidian/workspace.json
Please commit your changes or stash them before you merge.
Aborting
Updating 6b9540f..90bf4b6
```
현재 local git에서 change가 발생했으니 이걸 commit 하거나 stash를 하라는 것이다.
commit은 현재 local의 변경사항을 remote에 쓰기 위해서 필요하며, stash는 현재의 변경 사항을 마지막 커밋 상태로 복원하고 remote에 push할 수 있는, 즉 현재 local의 변경사항을 일시적으로 버린다.

만약 현재 local의 변경사항을 commit하고 싶으면 `git add .`  `git commit -m ".."`을 하면 된다.
그 후 `git push`를 시도 해보자. 그러면 다음과 같은 메세지를 얻는다.
```sh
PS C:\Users\bae\obsidian> git add .
...
PS C:\Users\bae\obsidian> git commit -m "trying to add some stuffs"
[main 6d1ebdb] trying to add some stuffs
 create mode 100644 3. develop environment/tmux/shell syntax highlighting and autocompl.md
PS C:\Users\bae\obsidian> git push
To https://github.com/createsejin/obsidian
 ! [rejected]        main -> main (non-fast-forward)
error: failed to push some refs to 'https://github.com/createsejin/obsidian'
hint: Updates were rejected because the tip of your current branch is behind
hint: its remote counterpart. Integrate the remote changes (e.g.
hint: 'git pull ...') before pushing again.
hint: See the 'Note about fast-forwards' in 'git push --help' for details.
Auto-merging .obsidian/plugins/recent-files-obsidian/data.json
CONFLICT (content): Merge conflict in .obsidian/plugins/recent-files-obsidian/data.json
Auto-merging .obsidian/workspace.json
CONFLICT (content): Merge conflict in .obsidian/workspace.json
Automatic merge failed; fix conflicts and then commit the result.
```
대충 conflict, 즉 충돌이 발생했다는 것이다. 자세히 보면 충돌이 2개인데, 첫번째는  Auto-merging이 먹혔다. 두번째 파일은 Autom-merging이 실패했다고 한다. 그러면 우리가 할 일은 이 파일을 열어서 수동으로 diff view를 통해 conflict를 원하는 의도대로 직접 수정해야한다. 가장 좋은건 nvim diff view 또는 내부 fugitive 에서 `dv`를 이용해 3-way-diff-view로 해결하는것이다. 이렇게 conflict를 해결하고 나서 다시 git commit을 한다.
```sh
PS C:\Users\bae\obsidian\.obsidian> git commit --all -m "trying to merge"
warning: in the working copy of '.obsidian/workspace.json', LF will be replaced by CRLF the next time Git touches it
[main 73c340c] trying to merge

PS C:\Users\bae\obsidian\.obsidian> git push
Enumerating objects: 39, done.
Counting objects: 100% (35/35), done.
Delta compression using up to 12 threads
Compressing objects: 100% (19/19), done.
Writing objects: 100% (19/19), 2.69 KiB | 2.69 MiB/s, done.
Total 19 (delta 16), reused 0 (delta 0), pack-reused 0
remote: Resolving deltas: 100% (16/16), completed with 12 local objects.
To https://github.com/createsejin/obsidian
   90bf4b6..73c340c  main -> main
```
그러면 위와같이 push가 잘 된다.

아래와 같이 그래프가 그려진다.
```sh
PS C:\Users\bae\obsidian\.obsidian> git log -10 --graph
*   commit 73c3404b0d1fdc... (HEAD -> main, origin/main, origin/HEAD)
|\  Merge: 6d1ebdb 90bf4b6
| | Author: createsejin <createsejin@gmail.com>
| | Date:   Thu Apr 18 17:00:40 2024 +0900
| |
| |     trying to merge
| |
| * commit 90bf4b696691dea64773270ab0e33d8b661531eb
| |
| |
| * commit 272c1b12235ae73c905e2369b38773d536f1c6dd
| | Author: createjin <createsejin@gmail.com>
| | Date:   Thu Apr 18 05:14:31 2024 +0900
| |
| |     2024-04-18-002
| |
| * commit c17e4ecdb1a253d5d8456a0fc7bcf02e150e060e
| | Author: createjin <createsejin@gmail.com>
| | Date:   Thu Apr 18 14:00:06 2024 +0900
| |
| |     update plugins
| |
* | commit 6d1ebdb255526e4e8ef6093637f52d6676014967
|/  Author: createsejin <createsejin@gmail.com>
|   Date:   Thu Apr 18 16:57:31 2024 +0900
|
|       trying to add some stuffs
|
* commit 6b9540f16c55e57ac5e93c4f1ddea0360e8c315c
| Author: createsejin <createsejin@gmail.com>
| Date:   Wed Apr 17 17:16:09 2024 +0900
|
|     2024-04-17-001
|
```
만약 처음에 push를 시도하려고 할때에도 이런 문제는 비슷하게 발생한다.
그때에는 안내에 따라서 다시 pull을 해서 remote의 변경사항과 현재 local의 변경사항의 conflict를 적절히 해결한뒤 다시 commit, push하면 된다.

또한 git conflict가 처음에 발생하면 보통 git은 어떻게 merge를 처리할건지 묻는다.
3가지 중 하나를 고르면 된다.
```
git config pull.rebase false
git config pull.rebase true
git config pull.ff only
```
보통은 `rebase false` 즉 merge를 고르는게 좋다. 물론 rebase도 좋긴하지만 되도록이면 merge를 한 뒤에 브랜치를 제거하거나 아니면 rebase를 해도 좋다. 이 부분은 나도 아직 잘 모르는 부분이라 공부가 더 필요해보인다.
