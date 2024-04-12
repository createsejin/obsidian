솔직히 리눅스 shell에 비하면 정말로 압도적으로 불편하지만 못 쓸 정도는 아니다.
일단 주로 쓰는 것 중에 cd 할때에도 cmd에서 하려면 다른 디스크를 이동할때 다음과 같이 `/d` 옵션을 붙여야 이동이 가능하다.

`C:\Users\bae>cd /d D:\Projects\gta_cMecro\SQL`

또, 자주 쓰는 명령어 중에 mklink라는게 있는데, 하드링크 및 심볼릭 링크를 만들어주는 기능이다.
특히 데이터 베이스 파일에 대한 링크를 걸때 편리하다. 예를 들어서 다음과 같이 SQL 폴더에 있는 데이터 베이스를 하드링크를 걸어서 구현 프로그램의 실행파일 위치에 갖다주면 프로그램 내부 코드에서 이 DB를 아주 손쉽게 사용할 수 있게 된다. 이 부분에 있어서는 하드링크의 역할이 필수적이다.
```
cmake-build-debug>mklink /h mecro_data.db D:\Projects\gta_cMecro\SQL\mecro_data.db
```
사용 방법은 위와 같이 일단 하드링크를 생성할 위치로 간 뒤에, `mklink /h <link name> <source>` 이렇게 써주면 된다. `<source>`는 상대 경로를 사용할 수도 있다. 그러나 되도록이면 절대 경로로 해서 오류가 안나게 하는게 좋을 것이다. 

그리고 이 명령어는 반드시 powershell이 아닌 cmd에서 실행해야 작동한다.

https://blog.naver.com/PostView.nhn?blogId=777775959&logNo=220656513977
이 글을 참조하면 아주 좋다.

#Windows #cmd
