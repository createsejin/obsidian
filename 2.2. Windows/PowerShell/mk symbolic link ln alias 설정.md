기본적으로 `rpath`와 `path` [[absolute path, relative path Alias 설정하기|설정]]이 되어 있다고 가정한다.

`code $profile`로 profile을 연다.
```powershell
function mk_sym_link([string]$target_path, [string]$link_name) {
  New-Item -ItemType SymbolicLink -Path $link_name -Target $target_path
}
Set-Alias -Name ln -Value mk_sym_link
```

이제 작업을 해보자. 

예를들어서 `C:/Users/creat/mydoc/scripts/.scripts/cdd.sh` 를 `C:/Users/creat/Downloads`에 심볼릭 링크로 만드는걸 해보자.

위치 `C:/Users/creat/mydoc/scripts/.scripts`로 이동한다.
`path cdd.sh`를 통해 절대 경로 `C:/Users/creat/mydoc/scripts/.scripts/cdd.sh`를 얻는다.
```
> path cdd.sh

Path
----
C:\Users\creat\mydoc\scripts\.scripts\cdd.sh
```

관리자 powershell을 열고 `C:/Users/creat/Downloads`로 이동한다. 
`rpath` 명령어를 통해 앞서 얻은 target file의 상대 경로를 얻는다.
```
> rpath C:\Users\creat\mydoc\scripts\.scripts\cdd.sh
..\mydoc\scripts\.scripts\cdd.sh
```

얻은 상대 경로를 이용해서 `ln` 명령어로 링크를 만든다.
```
> ln ..\mydoc\scripts\.scripts\cdd.sh cdd
```
첫번째 인자가 얻은 상대 경로이고 두번째 인자가 link의 이름이다.

그런데 이것은 문제점이 있다. [[Start-Process 관리자 권한으로 실행하기|관리자 권한]]이 필요한 명령이기 때문이다. 
아예 관리자 권한으로 명령어를 실행하는 alias를 하나 만들어야할 것 같다.

결국 [[ln alias 관리자 권한으로 실행하기|이 방법]]으로 완전히 해결했다.
