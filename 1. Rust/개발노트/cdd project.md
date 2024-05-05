매우매우 간단한 프로그램이다. 예를 들면 `cdd sc a`를 입력하면 `~/Documents/android/scripts` 로 이동하는 것. 문제는 rust에서 직접적으로 현재 shell의 working directory를 변경할 수는 없으니 어쩔 수 없이 script의 힘을 일부 빌려야 한다는 것이다. 

그러기 위해서 다음과 같이 `.zshrc`에 이 프로그램의 프론트엔드격인 함수 하나를 추가해야한다.
```
cdd() {
  result=$(cddr $1 $2 $3 $4)
  echo $result
  # . /home/bae/Projects/cdd/cdd.sh $1 $2 $3 $4
}
```
대략 생김새는 이렇다. 현재는 테스트 중이여서 저런식으로 해놨다. 
맨 아래부분의 `.`으로 시작하는 부분은 스크립트를 source해서 현재 shell을 sub_cmd에 맞는 directory로 이동시킨다. 우선은 result라는 부분이 중요한데, 일단은 여러가지 argument를 rust 실행파일인 cddr에 넘긴 뒤 그 출력에 따라 적절한 함수를 실행해주면 된다. 아마도 working directory를 바꾸는 일 말고는 출력하는 부분은 러스트에서 다룰 것이다. 그러므로 여기에는 딱 그 기능 하나만 넣으면 된다는 것이다.