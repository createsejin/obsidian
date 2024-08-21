
우선은 [릴리즈 페이지](https://github.com/open-telemetry/opentelemetry-collector-releases/releases)에서 windows용 otelcol을 다운받아야한다. 나는 `otelcol_0.107.0_windows_x64.msi` 이것을 다운받았다. 
다운받고 설치하면 보통 `C:\Program Files\OpenTelemetry Collector` 이 위치에 설치된다. 이 안에 `config.yaml`, `otelcol.exe` 파일이 있다. 

우선 터미널에서 이곳으로 들어가서 다음 명령어로 실행할 수 있다.
```
.\otelcol --config=config.yaml
```

```yaml
receivers:
  otlp:
    protocols:
      http:
        endpoint: localhost:4318
        
processors:
  batch:

exporters:
  otlp:
    endpoint: otelcol:4318

service:
  pipelines:
    traces:
      # receivers: [otlp, opencensus, jaeger, zipkin]
      receivers: [otlp]
      processors: [batch]
      exporters: [otlp]

    metrics:
      # receivers: [otlp, opencensus, prometheus]
      receivers: [otlp]
      processors: [batch]
      exporters: [otlp]

    logs:
      receivers: [otlp]
      processors: [batch]
      exporters: [otlp]
```
일단은 이런식으로 `config.yaml`을 작성할 수 있다. 여기에서는 `otlp`를 이용한다.

이걸 실행했을때 
```
Error: cannot start pipelines: listen tcp 127.0.0.1:4319: bind: An attempt was made to access a socket in a way forbidden by its access permissions.
2024/08/17 13:42:34 collector server run finished with error: cannot start pipelines: listen tcp 127.0.0.1:4319: bind: An attempt was made to access a socket in a way forbidden by its access permissions.
```
이런 에러가 발생할 수 있다.
이럴때에는 포트 번호를 하나씩 더 올려보자.

또한 
```
2024-08-17T13:43:14.555+0900    error   otelcol@v0.107.0/collector.go:315       Asynchronous error received, terminating process        {"error": "listen tcp :8888: bind: Only one usage of each socket address (protocol/network address/port) is normally permitted."}
```
이런 에러가 뜨면 
```
netstat -ano | findstr :8888
```
으로 이 포트에서 실행중인 프로세스의 pid를 알아낸 뒤, 
```
Stop-Process -Id 6160
```
이런식으로 프로세스를 종료시켜주자. 그리고 다시 시작시킨다.