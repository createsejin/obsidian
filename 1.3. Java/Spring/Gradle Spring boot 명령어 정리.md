[https://start.spring.io/](https://start.spring.io/) 에서 Start Project를 Gradle로 받거나, VSCode에 Spring boot Extension pack을 깔면 커맨드 팔레트에서 `Spring initializr: Create a Gradle Project`를 선택하여 Start Project를 만들 수 있다.

프로젝트 루트에서 다음의 명령어로 Gradle Project를 실행할 수 있다.
```
gradle bootRun
```
그러면 웹 브라우저에서 `http://localhost:8080` 으로 이동하면 구현한 페이지를 볼 수 있다. [[Spring Boot Quick Start 뻘짓|Quick Start]] 가이드에서는 `http://localhost:8080/hello` 로 이동하면 `Hello World!` 메세지를 볼 수 있다.

가끔 튜토리얼에서 Maven Project 서버를 기동시키라고 하는데, 그때에는 다음 명령어를 사용하면 된다.
```
./mvnw spring-boot:run
```

또한  Gradle Project를 Excutable Jar 파일로 만들 수 있는데, 다음 명령어를 사용한다.
```
gradle bootJar
```

이렇게 하면 `<project_root>/build/libs/<project>-0.0.1-SNAPSHOT.jar` 파일이 만들어지고 이를 다음의 명령어로 `java`를 통해 실행할 수 있다.
```
java -jar build/libs/<project>-0.0.1-SNAPSHOT.jar
```
그러면 위에서 `bootRun`을 한것과 동일하게 서버가 동작한다.