필수 설치 Font : [JetBrain Mono](https://www.jetbrains.com/ko-kr/lp/mono/)

압축을 푼다.
`unzip JetBrainsMono-2.304.zip`

ttf 폴더로 들어간다.
`cd fonts/ttf`

모든 ttf를 시스템 폰트 디렉토리로 복사한다.
`sudo cp *.ttf /usr/share/fonts`

폰트 캐시를 업데이트 한다.
`sudo fc-cache -f -v`