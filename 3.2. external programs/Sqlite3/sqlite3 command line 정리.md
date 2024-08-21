처음에 데이터 베이스를 만드려면
```bash
bae@bae-H310M-E:~/Dropbox/Projects/CppStudy/Study/employee_manage$ sqlite3 test.db
SQLite version 3.37.2 2022-01-06 13:25:41
Enter ".help" for usage hints.
sqlite> create table table1(one text, two int);
sqlite> insert into table1 values('hello!', 10);
sqlite> insert into table1 values('goodbye', 20);
sqlite> select * from table1;
hello!|10
goodbye|20
sqlite> 
```
이런식으로 `sqlite3 test.db`로 파일에 접근해야한다.(아직 안 만들어짐)
이렇게 하면 sqlite3 CLI program이 실행되며, sqlite3 프롬프트인 `sqlite>`로 각종 데이터 베이스를 조작할 수 있게 된다. 반드시 처음에 `create table ..`을 해야 비로소 데이터 베이스 파일이 만들어진다.

출력옵션은 [[출력 옵션|이렇게]] 설정하면 될것 같다.

만약 그냥 들어왔다면 `.open [db]`로 db 파일을 열 수 있다.
근데 sqlite3는 좀 웃긴게 만약 파일이 존재하지 않으면 그 파일을 만들어버린다. 게다가 `.save [db]`도 있는데, 이건 만약 엉뚱한 파일 이름으로 적으면 만약 그 파일이 다른 파일로 존재했었다면 그 파일을 덮어써버린다.. 그러니 사용에 매우 주의할것..

기본적으로 `.schema table1`으로 테이블 구조를 볼 수 있다. 중요한 명령어이니 숙지할것. 그냥 `.schema`를 하면 데이터베이스의 전체 스키마를 보여준다.

^e073b1


#sqlite