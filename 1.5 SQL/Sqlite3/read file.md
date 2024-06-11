`.read ddd.sql`을 이용하면 해당 sql문을 전부 실행해준다. 다만 마지막 줄은 직접 엔터를 눌러야 실행된다.

## 쉘 스크립트로 지정한 sql 실행하기
`.read mySQL.sql` 을 통해 내가 지정한 SQL문들을 실행할 수 있다. 다만 주의할 점은 해당 파일 내의 모든 SQL문이 전부 실행되기 때문에 적절히 주석처리 하거나 sql의 기능별로 sql을 나누는게 좋을 것이다.
```sqlite
sqlite> .read |script.sh -d
```
이런 식으로 입력하면 쉘 스크립트에 든 SQL문도 사용 가능할지도 모른다.
근데 문제는 얘가 쉘 스크립트를 직접 읽을 수 없다는 것이다.. 그래서 가능한 옵션은.. 
```bash
#!/bin/bash
# 쉘 스크립트에서 SQL문 생성
if [ "$1" = "option1" ]; then
    echo "SELECT * FROM table1;" > script.sql
elif [ "$1" = "option2" ]; then
    echo "SELECT * FROM table2;" > script.sql
else
    echo "SELECT * FROM table3;" > script.sql
fi
# SQLite에서 SQL 스크립트 실행
sqlite3 myDatabase.db < script.sql
```
쉘 스크립트를 그냥 이런식으로 작성하는 것이다.

## 진짜 방법
```bash
#!/bin/bash

# 쉘 스크립트에서 SQL문 생성
if [ "$1" = "option1" ]; then
    echo "SELECT * FROM table1;"
elif [ "$1" = "option2" ]; then
    echo "SELECT * FROM table2;"
else
    echo "SELECT * FROM table3;"
fi
```
쉘 스크립트를 이런식으로 작성한뒤,

```sqlite
sqlite> .read |script.sh option1
```
이런식으로 쓰면 된다! ㅋㅋㅋ 이거다. 언젠가 테스트 해보지.

#sqlite