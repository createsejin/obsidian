일단 처음에는 `.cd`명령어를 이용해서 아카이브가 있는 디렉토리에 간 다음에 `.shell dir`을 이용해서 현재 디렉터리에 있는 아카이브 이름을 복사한뒤 `.open datas.sqlar`을 이용해서 sql archive를 연다. [[출력 옵션|출력옵션]]은 알아서 설정.

그 다음에 
```sqlite
sqlite> select * from sqlar;
name, mode, mtime, sz, data
test_db_000.db, 33206, 1706548399, 8192, "x��ױJ�@�$Th)� ��u�8�X%�P��4��@�As�� ur���Apqҧ��"
```
으로 현재 아카이브에 있는 데이터베이스들을 조회한다. 현재는 `test_db_000.db`가 타깃.

그 다음 `ATTACH DATABASE 'file::memory:?cache=shared' AS memdb;`으로 memory database를
attach 한다.
```sqlite
CREATE TABLE memdb.uncompressed AS  
SELECT name, mode, datetime(mtime,'unixepoch'), sqlar_uncompress(data,sz) as uncompressed_data  
FROM sqlar  
WHERE name='test_db_000.db';
```
그 다음에 sqlar 테이블에 있는 데이터를 꺼내오기 위해 `memdb`에 `uncompressd` 테이블을 새로 만든다. 그러면
```sqlite
sqlite> select * from memdb.uncompressed;
name, mode, "datetime(mtime,'unixepoch')", uncompressed_data
test_db_000.db, 33206, "2024-01-29 17:13:19", "SQLite format 3"
```
이런식으로 조회해보면 뜬다.

그러나 이 blob 데이터를 이용해서 데이터 베이스를 만드려면 결국 디스크에 파일 형태로 새로 db를 만들어서 진행해야하기 때문에.. 만약에 아카이브를 프로그램에서 다룰거면 
sqlite3.exe를 이용해서 
`.\sqlite3.exe -A -f datas.sqlar -x test_db_000.db` 이런식으로 쓰면 된다.
근데 아시다시피 프로그램에 shell 명령어를 직접 넣어버리는건 정말 신중해야함. 되도록이면
shell 코드를 짜는건 하지 말아야한다. 근데 만약 관리 프로그램을 만든다면 써야겠지만 말이다.