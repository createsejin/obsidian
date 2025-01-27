이 [가이드](https://docs.spring.io/spring-boot/reference/features/dev-services.html#features.dev-services.docker-compose)를 참고했으며, 아치 리눅스 위키의 이 [글](https://wiki.archlinux.org/title/Docker)을 참조했다.
우선 `docker`를 설치해준다.
```
sudo pacman -S docker
```

```
sudo systemctl start docker.socket
```
참고로 `docker.service`도 위의 `docker.socket` 대신 쓸 수는 있는데, 이것은 매번 리눅스가 부팅할때마다 service가 실행되기 때문에 부팅 속도 저하가 있다고 한다. 그러나 그냥 자동으로 실행되게 하려면 `docker.service`를 enable 해주면 될것 같다.

그리고 다음 명령어로 docker의 상태를 알 수 있는데,
```
docker info
```

만약 server 쪽에서 permission 오류가 난다면 다음 명령어를 입력해준다.
```
sudo chmod 666 /var/run/docker.sock
```
그리고 사용자를 다음 명령어를 통해 `docker` Group에 넣어주어야한다.
```
sudo usermod -aG docker bae
```

또한 `docker-compose` 패키지를 설치해주자.
```
sudo pacman -S docker-compose
```
