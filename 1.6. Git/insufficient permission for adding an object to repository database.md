`git commit`을 하려는데 다음과 같은 오류가 떴었다.
`error: insufficient permission for adding an object to repository database .git/objects`
`error: Error building trees`

`.git/objects`에 들어가보니 여러가지 object 파일들이 `root.root`로 권한이 배정되어있었다. 아마도 이전에 live_cd os에서 root 권한으로 여러가지 commit을 해서 그런것 같기도 하다.

해결 방법은 다음과 같다.
`sudo chown -R bae:bae .git/object`

이렇게 하면 다시 `.git/object/`에 있는 모든 파일이 재귀적으로 `bae.bae` 소유가 된다.
