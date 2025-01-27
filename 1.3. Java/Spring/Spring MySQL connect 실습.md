[Tutorial](https://spring.io/guides/gs/accessing-data-mysql)
이걸 하기 전에 docker를 설치해야한다. 설치 방법 및 기본 세팅은 이 [[Docker 설치|글]]에서 다루고 있다. 반드시 시작 전에 
```
sudo systemctl start docker.socket
```
이 명령어로 docker service를 시작해주자.

Tutorial에 나온대로 디펜던시를 체크하고 spring initializr로 project를 만든뒤
java 코드 역시 Tutorial에 나온데로 그대로 짜면 된다.

코드를 모두 작성한뒤 처음에 실행하면 `mydatabase`가 없다며 오류를 낼 것이다.
그럴때에는 우선 아래와 같이 project 루트에서 `compose.yaml` 파일을 수정하자.
```yaml
services:
  mysql:
    container_name: 'guide-mysql'
    image: 'mysql:latest'
    environment:
      - 'MYSQL_DATABASE=mydatabase'
      - 'MYSQL_PASSWORD=secret'
      - 'MYSQL_ROOT_PASSWORD=verysecret'
      - 'MYSQL_USER=myuser'
    ports:
      - '3306:3306'
```
`accessingdatamysql/src/main/resources/application.properties` 에 있는 이 파일도 다음과 같이 수정하면 좋다.
```
spring.application.name=accessingdatamysql
spring.jpa.hibernate.ddl-auto=update
spring.datasource.url=jdbc:mysql://localhost:3306/mydatabase
spring.datasource.username=myuser
spring.datasource.password=secret
spring.datasource.driver-class-name=com.mysql.cj.jdbc.Driver
spring.jpa.show-sql: true
```
그리고 다음의 명령어를 project root에서 사용해준다.
```
docker compose up
```
이걸 해주면 처음에는 docker가 `mysql:latest` image를 다운받아 container가 실행되면서 `mydatabase`가 만들어질 것이다.
직접 이 docker에 접속하려면 다른 쉘에서 다음의 명령어를 사용하자. 
```
docker exec -it guide-mysql bash
```
여기서 `guide-mysql`는 처음에 `compose.yaml`에서 `container_name`에 지정한 이름이다.
현재 실행되고 있는 docker를 확인하려면 다음 명령어를 사용하자.
```
docker ps -a

CONTAINER ID   IMAGE          COMMAND                  CREATED         STATUS         PORTS                               NAMES
d976e5b13dfa   mysql:latest   "docker-entrypoint.s…"   2 minutes ago   Up 2 minutes   0.0.0.0:3306->3306/tcp, 33060/tcp   guide-mysql
```
그러면 이런식으로 마지막에 container의 name이 뜬다.

`docker exec` 명령어를 통해 docker shell에 접속했다면 다음의 명령어로 `mysql`에 접속할 수 있다.
```
mysql -u root -p
```
여기에서 비밀번호는 처음 `compose.yaml`에 설정해둔 `MYSQL_ROOT_PASSWORD=verysecret` 즉, `verysecret`을 입력해주면 된다.
그러면 `mysql>` 프롬프트가 뜰것이다.  여기에 다음의 명령어를 통해 현재 `mysql`의 데이터베이스들을 확인할 수 있다.
```
mysql> show databases;

+--------------------+
| Database           |
+--------------------+
| information_schema |
| mydatabase         |
| mysql              |
| performance_schema |
| sys                |
+--------------------+
```
이런식으로 `mydatabase`가 나오면 이제 위 Tutorial에서 만든 프로그램의 `curl` 요청이 성공적으로 작동할 것이다.

참고로 Tutorial에 따르면 `curl` 요청은 다음과 같이 할 수 있다.
```
curl http://localhost:8080/demo/add -d name=First -d email=someemail@someemailprovider.com
curl http://localhost:8080/demo/all
```

마지막으로 Tutorial에서 Security를 위해 다음을 진행할 것을 권장한다.
```
mysql> revoke all on mydatabase.* from 'myuser'@'%';
```
여기에서 `myuser`는 앞서 `compose.yaml`에서 설정한 `- 'MYSQL_USER=myuser'`이다.
이렇게 하면 이제 spring application은 이 db에 대해 아무런 작업을 하지 못하므로 다음 명령어를 통해 일부 권한을 다시 돌려줘야한다.
```
mysql> grant select, insert, delete, update on mydatabase.* to 'myuser'@'%';
```