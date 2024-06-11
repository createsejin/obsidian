상황은 여러가지가 있다. 예를 들어서 두 개의 장치를 생각해보자. 하나는 이 컴퓨터고 다른 하나는 안드로이드 폰이다. 그리고 이 안에는 같은 obsidian remote repository가 공유된다.

## 서로 같은 파일의 conflict
첫번째는 만약 서로 같은 파일을 서로 다른 장치에서 각각 제목만 똑같고 내용은 조금 다르게 추가한 경우다. 이럴 경우에는 auto-merging이 실패한다. 당연한 이유지만 같은 파일의 같은 줄에서 서로 다른 내용이 있을때 git은 이것을 사용자에게 수동으로 처리하지 않고서는 git이 이것을 합치는 방법은 없다. 

다음의 두 기기의 파일들을 생각해보자.
```
device: android
title: conflict test
content: foooooooo

device: subcom
title: confilct test
content: baaaaaaaar
```
앞서 말했듯이 파일 이름은 같고 서로 같은 줄에 서로 다른 내용을 가지고 있다. 그리고 한가지 가정을 더 추가하자 이 파일을 만들기 전에 각각의 장치들은 서로 동일한 commit 상태라고 가정해보자. 이 초기 커밋을 `001` 이라고 이름붙여보자. 그러면 각각의 두 장치들은 `001` commit 상태에서 각각 저 파일들을 만들었다고 치자. 그러면 새로운 change가 생긴것이므로 `git status`를 확인해보면 현재 modified된 파일을 보여준다.

이 상태에서 먼저 subcom에서 `git add .` 그리고 `git commit -m "002"` `git push`를 했다고 치자.
그러면 이제 remote는 `002` commit을 가르킨다.

이 상태에서 다시 android에서 `git add . && git commit -m "003" && git push`를 하면 에러가 난다. push 과정에서 서로 같은 이름의 두 장치의 파일들이 서로 conflict를 일으켰기 때문이다.

우리는 두 장치의 기본 `pull.rebase false`를 설정했다고 가정하자. 이 설정은
`git config pull.rebase false` 명령어를 통해 가능하다. 이것은 git conflict 상황에서 `rebase`가 아닌 `merge`를 사용하게 한다. 

그러면 git CLI는 먼저 `git pull`하라고 안내한다. `git pull`을 하자. 그러면 이제 remote로부터 repository가 업데이트 되면서 두 파일의 충돌을 해결하기 위한 편집기를 열게 된다. 그런데 android에서는 default로 설정된 vi 편집기가 없으므로 에러 메세지가 뜨고 명령은 종료된다. 이 파일을 obsidian에서 열어서 다음과 같이 수정했다고 치자.
```
device: android
title: conflict test
content: fooobar
```
그리고 다시 `git commit -m "merge 002 and 003"`를 해주자. 그러면 conflict는 merge되고 push가 가능해진다. 
`git push`

이렇게 하면 충돌이 났던 두 commit인 `001`과 `002`는 이제 병합된다. 

이제 다시 subcom으로 돌아와서 `git pull`을 하면 이것은 당연히 정상적으로 에러없이 작동한다.
그리고 `git log --graph`를 통해 log를 보면 
```
*   commit 12265a84048e1cd62c158b4059bcb58f5cf88ded (HEAD -> main, origin/main, origin/HEAD)
|\  Merge: 997869e b7f6726
| | Author: createjin <createsejin@gmail.com>
| | Date:   Thu Apr 18 18:20:14 2024 +0900
| |
| |     merge 002 and 003
| |
| * commit b7f6726b5dd9898acba71471aa719d5e8a6ea43a
| | Author: createsejin <createsejin@gmail.com>
| | Date:   Thu Apr 18 18:16:14 2024 +0900
| |
| |     002 -> subcom commit
| |
* | commit 997869eb6aa477c54f175957558cafd3095258de
|/  Author: createjin <createsejin@gmail.com>
|   Date:   Thu Apr 18 18:17:10 2024 +0900
|   Date:   Thu Apr 18 18:17:10 2024 +0900
|
|       003 -> android commit
|
*   commit 1a5f8911f66a4f60ebf645dc7154c9dae445cb48
|\  Merge: 8817e6c 1997b78
| | Author: createjin <createsejin@gmail.com>
| | Date:   Thu Apr 18 18:06:47 2024 +0900
| |
| |     001 -> base commit
```
이런식으로 뜬다. 결과는 예상한대로다.

## 서로 다른 파일의 conflict
만약 동일한 상황인데, 마찬가지로 같은 `001` base commit 상태에서 이번에는 다음과 같이 서로 다른 파일을 각각 서로 다른 장치에서 만들었다고 치자.
```
device: android
title: conflict test3
content: foooooooo

device: subcom
title: confilct test2
content: baaaaaaaar
```
이제는 서로의 파일 이름이 서로 다르다. 이런 경우에도 두 commit은 충돌한다. 그러나 이 경우에는 auto-merging이 성공한다. 
앞 상황과 마찬가지로 subcom에서 먼저 `002` commit을 통해 push를 했다고 치자.

그 상태에서 android도 마찬가지로 `003` commit을 push 하면 이번에도 충돌이 일어났다고 에러가 뜬다.

다시 `git pull`을 한다. 그리고 여기에서 중요한 차이점이 발생한다.
앞선 상황에서는 `git status`를 했을때 빨간 글씨로 Unmerged: 된 파일을 보여준다. 이번 상황에서는 그렇지 않다. 그러므로 우리는 수동으로 충돌난 파일을 수정할 필요가 없다.
이때에는 바로 `git commit -m "merge 002 and 003"`을 하고 `git push`를 하면 된다.
그러면 위와 같은 거의 동일한 그래프를 `git log --graph`를 통해 볼 수 있다.

## 정리
그러므로 두가지 상황이 있을 수 있다. 같은 파일의 같은 줄이 충돌이 난건가. 아니면 서로 다른 파일인데 commit에서 merge가 필요한 상황인가. 첫번째는 수동으로 직접 conflict를 해결해줘야한다. 두번째 상황은 commit과 동시에 auto-merging을 하면 된다.

과정은 요약하자면 이렇다.
파일 수정 -> `git add, git commit git push` -> conflict 발생 -> `git pull` -> 충돌 수정 -> `git commit, git push`

