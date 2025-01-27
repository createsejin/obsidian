이 [글](https://dev.to/guilhermerochas/how-to-compile-rust-command-line-tools-for-termux-6gf)을 참고했다. 또한 이 [글](https://github.com/rust-lang/rustup/issues/2872#issuecomment-1158238378) 역시 참고할만 하다.
우선 여기 공식 홈페이지 [다운로드 페이지](https://developer.android.com/studio?_gl=1*1qondko*_up*MQ..*_ga*MTE1Mjc4NjE5OS4xNzE1NDY3ODgy*_ga_6HH9YJMN9M*MTcxNTQ2Nzg4MS4xLjAuMTcxNTQ2Nzg4MS4wLjAuMA..&gclid=CjwKCAjwrvyxBhAbEiwAEg_KgoWLE9G7JD12v2bUMj0UTNk6s3Ky5ezTLDuIv3nO1xg-aQFiPK5OZBoCFXYQAvD_BwE&gclsrc=aw.ds)에서 Command line tool only의 Linux 버전을 Android에 다운로드 했다. 
Android에는 termux가 세팅되어있다. home으로 이동해서 
`mkdir Android`
`cd Android`

그 후 다운로드된 곳으로 이동한다.
`cd ~/storage/shared/Download`
`mv commandlinetools-linux-11076708_latest.zip ~/Android`

다시 아까 그 directory로 이동
`cd ~/Android`
압축을 풀어준다.
`unzip commandlinetools-linux-11076708_latest.zip`

`~/Android`안에 폴더를 하나 더 만들어준다.
`mkdir sdk`
그 후 풀어진 압축 파일들이 담긴 폴더를 아래와 같이 옮겨준다.
`mv cmdline-tools ./sdk/tools`

그 후 
`cd sdk/tools/bin`
`yes | ./sdkmanager --licenses`

문제는 현재 내 Termux 환경에 Java가 없어서 위 명령어를 못하고 있다. 아마도 sdkmanager가 Java를 요구하는 것 같았다. 

이 방법대로는 되지 않는다. 대신 이 [[aarch64-linux-android rust build|방법]]을 참고하자.



