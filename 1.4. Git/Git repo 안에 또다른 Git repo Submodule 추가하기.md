`Documents/configs`에 다른 config 폴더를 저장했는데 문제는 예를들어서
`Documents/configs/.oh-my-zsh/`같은 애들은 이미 git repository라는 것이다.
이럴 경우 그냥 경고를 무시하고 push할 경우 이러한 애들은 <span style="color:#c00000">내 git repo에 추가되지 않는다.</span>
그럴때에는 다음과 같이 하위 git repo 위치로 가서 
`git remote get-url origin`을 통해 url을 얻은 뒤, 다시 상위 git 디렉토리로 이동해서
`git submodule add <url> <path>`를 통해 submodule을 상위 git에 추가해야한다.

그런데 만약 경고를 무시하고 추가한경우 위 명령을 실행할때
`fatal: '<path>' already exists in the index`라는 에러가 뜰 수 있다.
이럴 경우에는 다음과 같이 git 추적을 삭제하고
`git rm -r --cached <path>`
다시 submodule 명령을 쓰면 된다.

## 그러나
이렇게 할 경우에 그 directory는 아예 다른 git repository로 분류되어서 <span style="color:#c00000">실제로는 내 git repo에 올려지지 않는다.</span> 따라서 이러한 경우에는 그냥 `.git` 자체를 삭제해버리고 일반 디렉토리로 취급하도록 하면 된다.