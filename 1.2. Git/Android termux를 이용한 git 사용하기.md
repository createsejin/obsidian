https://f-droid.org/ko/packages/com.termux/ 에서 termux apk를 휴대폰에 다운받은뒤 설치한다.
각종 경고가 뜨는데 모두 무시하고 설치하면 된다.

그다음 termux를 띄우고 다음 명령어를 통해 패키지들을 업데이트 해준다.
중간 중간에 여러 question이 있는데 모두 y로 대답해주면 된다.
`pkg update && pkg upgrace`

그 다음에는 우리가 사용할 수 있는 저장공간을 접근 권한을 허용해야한다.
`termux-setup-storage`
알림이 뜨면 권한 허용을 해준다.

이제 `ls`를 하면 여러 폴더가 보이는데, 여기에서 `shared` 폴더에 들어가면 휴대폰 내부 로컬 저장소로 들어갈 수 있다.

다음 명령어를 통해 git을 설치할 수 있다.
`pkg install git`

그런데 git push를 하다보면 
`fatal: the remote end hung up unexpectly Everting up-to-date`에러가 뜰 수 있다.
이럴때에는 git 프로토콜의 버퍼 크기를 변경해주면 된다.
```
git config http.postBuffer 524288000 # 또는
git config ssh.postBuffer 524288000 # SSH 프로토콜 사용시
```
아직 git credential 부분이 안되어 있어서 조금 불편하긴 하지만 [[Android에서 termux로 git ssh를 이용해서 인증하기|방법]]은 있을 것 같다.
