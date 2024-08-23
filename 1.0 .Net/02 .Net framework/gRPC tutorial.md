[문서](https://learn.microsoft.com/en-us/aspnet/core/tutorials/grpc/grpc-start?view=aspnetcore-8.0&tabs=visual-studio-code)
```
dotnet new grpc -o GrpcGreeter 
code -r GrpcGreeter

cd GrpcGreeter
dotnet dev-certs https --trust
```
일단 시작은 이렇다. 마지막 명령어로 Trust the HTTPS development certificate를 해주면 된다. 윈도우즈 기준으로, 경고 메세지가 뜨면 예를 누르면 된다.

