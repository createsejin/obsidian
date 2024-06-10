이것 역시 무우조건 설치해야하는 플러그인 중 하나다. 
plugins -> Marketplace에서 IdeaVimExtension을 검색한다. vim으로 검색해도 나온다.

설치후, 오른쪽 아래 vim 아이콘을 눌러서 open ~/.ideavimrc를 통해 vim 설정파일에 들어간 후, 다음을 추가한다.
`set keep-english-in-normal-and-restore-in-insert`

아직은 안될거다. 이유는 windows 환경의 경우, en-US 키보드 레이아웃이 필요하다. 
`Win + I`를 눌러서 windows 제어판에 진입한다.
시간 및 언어 -> 언어 및 지역 에서 기본 설정 언어 옆 '언어 추가'를 통해 `English(United States)`를 추가해준다.

## 한글 입력기 바로가기 키 설정
그리고 또 한가지 할게 더 있다. 지금 이렇게만 하면 문제가 뭐냐, en-US와 kor 간의 전환을 해야하는데, `Win + Space`로 전환할 수 있긴 하다. 그러나 뭘로 전환됐는지 확실하지 않을때가 많다. 따라서 한글 입력으로 바로 전환할 수 있는 키를 설정하는게 좋다.

제어판에서 시간 및 언어 -> 입력 -> 고급 키보드 설정 -> 입력 언어 바로 가기 키 에서
한국어를 선택한 후, 키 시퀀스 변경을 누른다.
키 시퀀스 사용에 체크하고 왼쪽 Alt + Shift, 키 2를 선택해준다. 이건 자기가 원하는데로 선택해주면 된다. 이렇게 설정해두면 `Alt + Shift + 2`를 하면 한글 입력기로 바로 전환이 된다.

## 사용시 주의점
그리고 이제 실제로 clion에서 사용할때에는 몇 가지 주의점이 있다.
예를 들어서 clion과 obsidian을 왔다갔다 하면 clion에 커서가 올라가면 무조건 en-US로 키보드 레이아웃이 전환된다. 따라서 다시 obsidian으로 돌아올때에 다시 키보드를 전환시켜줘야한다.

또한, clion 내부에서 각 코드 줄을 편집할때, 입력된 위치 기준으로 input method가 restore된다. 
예를 들어 다음과 같은 코드가 있다면
```
    for (const auto &path : samples) { // 코멘트 입니다
      if (exists(path) && is_directory(path)) {
```
`// 코멘트 입니다` 처럼 comment를 한글로 입력한 지점에서는 한글로 restore된다. 근데 그 앞 줄, 즉, `for ..` 부분에서 insert mode로 들어가면 그때에는 en 모드로 된다는 것. 
이것은 clion을 종료하고 다시 열면 날아간다. 하지만 그럼에도 불구하고 이 플러그인은 반드시 필요하다. normal mode에서 en 키보드 mode를 유지시키는게 핵심 기능이기 때문.