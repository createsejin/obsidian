Google의 gRPC라던가, Protobuf는 안타깝게도 Windows 환경에서 Clang과 같은 환경, 즉, Clion같은 Cmake 기반의 개발 환경에서는 컴파일이 보장되지 않는다. 이것 때문에 거의 이튿날을 삽질했다. 이 라이브러리를 제대로 Cpp 프로젝트에서 사용하고 빌드하려면 결국에는 Visual Studio 2022를 사용할 수 밖에 없다. 이것이 가장 확실한 방법이다. 

우선 기본적으로 VS 2022에서 C++ Console project를 만든다. 

그리고 vcpkg를 설치해야한다. 설치의 가장 좋은 방법은 자신의 home 폴더. 즉, 사용자 폴더에서 vcpkg git clone을 하는 것이다. 
나는 `C:/Users/creat/vcpkg`  여기에 설치했다.

설치 후에는 VS 2022의 설정에 들어가서 설정 검색에 `vcpkg`를 검색하면 설정항목이 나온다.
여기에서 `Enable automatic activation of vcpkg environments`에 체크하고, 그 및에 `Use custom path to vcpkg.exe`를 체크하고 `vcpkg.exe`가 들어있는 위치로 가서 해당 실행파일을 추가해주면 된다.

이렇게 해주고 터미널을 열어서 vcpkg 위치로 이동한 뒤, 
`vcpkg install protobuf`
`vcpkg install grpc`
를 해주고 의존성 라이브러리까지 전부 빌드될때까지 기다린다.

다 됐으면 이제 한가지 해야할일이 생겼다. 바로 `protoc.exe`  위치를 환경변수에 추가해야한다.
보통 vcpkg 내에서 그 위치는 
```
C:\Users\creat\vcpkg\installed\x64-windows\tools\protobuf
```
이 부분에 있다. 이것을 시스템 환경변수에 등록해줘야한다.  환경변수에 추가하는 방법은 이미 익숙한 방법이니 구지 여기서 적지는 않겠다.
등록을 하면 터미널을 새로 열고 `protoc --version`을 쳐서 버전이 제대로 나오면 성공이다.

또한, gRPC를 위한 `grpc_cpp_plugin.exe` 위치를 적어놔야한다. 나중에 cpp gRPC protoc 컴파일을 위한 플러그인 옵션 설정에 이 위치가 필요하다. 이 역시 다음의 위치에 존재한다.
```
C:\Users\creat\vcpkg\installed\x64-windows\tools\grpc\grpc_cpp_plugin.exe
```
이 위치를 git bash로 열어서 다음과 같이 git bash용 경로로 저장해주면 좋다.
```
/c/Users/creat/vcpkg/installed/x64-windows/tools/grpc/grpc_cpp_plugin.exe
```

이제 protobuf와 gRPC를 사용할 준비는 됐다.

다시 VS 2022로 돌아가서, `Ctrl+Backtick`을 눌러서 터미널을 띄운다. 되도록 터미널은 git bash를 띄우는게 좋다. powershell이 띄워졌다면, 터미널 상단 + 표시 옆에서 shell을 선택할 수 있다. 혹은 그 옆 톱니바퀴를 눌러서 git bash를 추가하고 그것을 default 터미널로 지정할 수 있다. 
아무튼 git bash를 열고, 프로젝트 소스가 있는 위치로 가서 `touch messenger.proto`를 통해 `.proto` 파일을 만들어준다.
다음과 같은 내용으로 만든다.
```
syntax = "proto3";

package messenger;

// gRPC 서비스 정의
service Messenger {
  rpc SendMessage(Message) returns (MessageResponse) {}
}

// 메시지 구조 정의
message Message {
  string text = 1;
}

// 메시지 응답 구조 정의
message MessageResponse {
  string response = 1;
}
```
각 항목의 자세한 사항은 공식 [문서](https://grpc.io/docs/languages/cpp/quickstart/)를 참조하자.
머 대충 말하자면, syntax는 어떤 proto 버전을 쓸것이냐고.. 보통은 최신버전인 proto3를 쓰면 된다. 이게 더 문법이 간결하기 때문.
package는 namespace가 된다. 서로 다른 protobuf끼리 이름 충돌을 방지하기 위함이다.
service Messenger는 service name이다.
`rpc SendMessage(Message) returns (MessageResponse) {}` 에서 SendMessage는 method 이름이다. 처음에 나오는 `Message`가 request 데이터이며, 두번째로 나오는 `MessageResponse`가 response 데이터를 가르킨다.
밑에서 그 두가지 데이터의 message 구조 정의를 할 수 있다.

자, 이제 이걸 cpp에 맞도록 `protoc`를 이용해서 컴파일해야한다. 터미널을 열고 `.proto` 파일이 있는 위치로 가서, 다음의 명령어로 두 번의 컴파일 과정을 거치자.
```
protoc -I=. --cpp_out=. messenger.proto
protoc -I=. --grpc_out=. --plugin=protoc-gen-grpc="/c/Users/creat/vcpkg/installed/x64-windows/tools/grpc/grpc_cpp_plugin.exe" messenger.proto
```
앞서 얘기했던 그 플러그인이 여기에 쓰이니 이 명령어를 프로젝트 어딘가에 잘 적어놓자. 나중에 또 쓰인다.

이제 실제 cpp 코드를 통해 서버와 클라이언트를 간단히 만들어보자. 위에서 만든 `.proto`파일에 담긴 메세지를 가지고 간단히 데이터를 교환하는 예제이다.

먼저 서버 코드다.
```cpp
#include <iostream>
#include <string>
#include <grpcpp/grpcpp.h>
#include "messenger.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using messenger::Messenger;
using messenger::Message;
using messenger::MessageResponse;

class MessengerServiceImpl final : public Messenger::Service {
  Status SendMessage(ServerContext* context, const Message* request,
    MessageResponse* response) override {
    std::string received_message = request->text();
    std::cout << "Received message: " << received_message << std::endl;

    // 메시지 처리 (간단한 예시)
    response->set_response("Message processed: " + received_message);
    return Status::OK;
  }
};

void RunServer() {
  std::string server_address("0.0.0.0:50051");
  MessengerServiceImpl service;

  ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;
  server->Wait();
}

int main()
{
  std::cout << "server start\n";
  RunServer();
  return 0;
}
```
당연하겠지만 생성된 `messenger.grpc.pb.h`파일을 프로젝트에 add에서 추가를 해야 사용할 수 있다. 파일을 컴파일만 하고 추가를 안하면 VS 2022에서 사용할 수가 없으니 주의하자.

이제 이것을 build하면 된다. 수많은 경고가 뜨겠지만 어쨌든 빌드는 성공할 것이다. 
추가적으로 project properties에서 C++20을 지정해서 빌드해도 좋다. C++20 feature를 사용할것이라면 말이다.

그 다음은 client다. 여기에서도 역시 `protoc`의 앞선 명령어를 통해 `.proto` 파일에 대한 컴파일이 필요하다. 컴파일된 파일이 모두 있다고 가정하고 다음의 client 코드를 작성해보자.

```cpp
#include <iostream>
#include <string>
#include <grpcpp/grpcpp.h>
#include "messenger.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using messenger::Messenger;
using messenger::Message;
using messenger::MessageResponse;

int main() {
    std::string addr = "localhost:50051"; // 서버 주소
    Messenger::Stub stub(grpc::CreateChannel(
        addr, grpc::InsecureChannelCredentials()));

    // 보낼 메시지 입력
    std::string message_text;
    std::cout << "Enter message to send: ";
    std::getline(std::cin, message_text);

    // gRPC 요청 생성 및 전송
    Message request;
    request.set_text(message_text);
    MessageResponse response;
    ClientContext context;

    Status status = stub.SendMessage(&context, request, &response);

    // 응답 처리
    if (status.ok()) {
        std::cout << "Server response: " << response.response() << std::endl;
    } else {
        std::cout << "RPC failed: " << status.error_code() << ": "
                  << status.error_message() << std::endl;
    }

    return 0;
}
```
역시 똑같이 빌드해주면 된다.

이제 서버를 먼저 실행해주자.
그리고 클라이언트를 실행해서 메세지 한개를 보내본다.
성공적으로 response를 받을 수 있을것이며, 서버 터미널로 가면 요청된 메세지가 찍힐것이다.