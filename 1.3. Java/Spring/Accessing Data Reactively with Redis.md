[Guide](https://spring.io/guides/gs/spring-data-reactive-redis)
Redis는 키값 쌍의 데이터들을 메모리 상에 상주시켜주는 매우 빠른 데이터 베이스이다. 
예를들어서 우리가 어떤 게임을 만들었다고 하자. 게임에는 유저의 모든 데이터를 저장하는 거대한 분산 시스템을 지원하는 RDB가 사용되지만, 유저의 즉각적인 입력에 반응해 게임 내의 수많은 요소(데이터)들을 업데이트 해줘야한다. 이때 직접 RDB를 통해 모든 데이터를 조회하고 업데이트하면 성능상의 문제가 생길 가능성이 있다. 이럴때 Redis와 같은 key-value 쌍으로 이루어진 메모리 기반 데이터 베이스 Redis를 사용할 수 있다. Redis는 C언어로 컴파일된 성능적으로 매우 우수한 데이터 테이블이라고 볼 수 있다. 이를 통해 임시적으로 데이터 조회와 업데이트를 하고 추후에 본 서버의 RDB에 데이터를 기록하는 방식으로 application 로직을 구현한다면 사용자는 성능 저하 경험 없이 원활한 서비스를 누릴 수 있다. 

이 Spring 가이드에서는 'Spring Data Redis'와 'Project Reactor'를 이용해서 Redis 로컬 서버에 Access하여 Coffee Object의 데이터를 읽어오는 작업을 한다.

기본적으로 Spring boot에서는  [Spring Boot Docker Compose support](https://docs.spring.io/spring-boot/reference/features/dev-services.html#features.dev-services.docker-compose)를 지원하지만, 이를 통해 시도한 경우 외부 쉘에서 해당 서버 주소에 도달할 수 없는 문제가 생기곤 한다. 이것도 [[#특정 docker container와 동일한 네트워크에서 명령어 실행하기|해결 방법]]이 없는것은 아니지만 나는 그냥 project 루트에 존재하는 `compose.yaml` 파일을 이용한 `docker compse up` 명령어를 통해 직접 Redis 로컬 서버를 띄운뒤에 `./gradlew bootRun`을 통해 spring applicaiton을 실행하고 `curl` 명령어로 REST api를 통해 데이터를 요청했다. 

물론 처음에 `docker`를 그냥 실행시키면 에러가 날 수 있다. `docker.socket` 혹은 `docker.service` 가 os 상에서 돌아가는 상태여야한다.
이를 위해 Arch linux에서는 다음 명령어를 사용한다.
```
sudo systemctl start docker.socket
```

우리가 다룰 `Coffee`라는 `record` Object는 매우 단순하다.
```java
package com.example.demo;

public record Coffee(String id, String name) {}
```

다음은 Configuration Class이다.
```java
package com.example.demo;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.data.redis.connection.ReactiveRedisConnectionFactory;
import org.springframework.data.redis.core.ReactiveRedisOperations;
import org.springframework.data.redis.core.ReactiveRedisTemplate;
import org.springframework.data.redis.serializer.Jackson2JsonRedisSerializer;
import org.springframework.data.redis.serializer.RedisSerializationContext;
import org.springframework.data.redis.serializer.StringRedisSerializer;

@Configuration
public class CoffeeConfiguration {
  @Bean
  ReactiveRedisOperations<String, Coffee> redisOperations(ReactiveRedisConnectionFactory factory) {
    Jackson2JsonRedisSerializer<Coffee> serializer = new Jackson2JsonRedisSerializer<>(Coffee.class);

    RedisSerializationContext.RedisSerializationContextBuilder<String, Coffee> builder =
        RedisSerializationContext.newSerializationContext(new StringRedisSerializer());

    RedisSerializationContext<String, Coffee> context = builder.value(serializer).build();

    return new ReactiveRedisTemplate<>(factory, context);
  }
}
```

### 특정 docker container와 동일한 네트워크에서 명령어 실행하기
```
docker run --rm --network container:guide-redis -it alpine

apk add curl
curl http://localhost:8080/coffees
```