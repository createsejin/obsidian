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

