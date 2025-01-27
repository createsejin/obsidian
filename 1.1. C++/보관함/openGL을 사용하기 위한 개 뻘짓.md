https://learnopengl.com/ 여기에서 openGL을 배우려고 지금까지 말도 안되는 분량의 개 뻘짓거리를 하고 말았다. 리눅스에서 이걸 하려고 한 것인데, glad에서 실패했다. 이 부분을 여기 사이트에서 처럼 그냥 VS 2022로 하니까 아무런 에러가 안뜨고 잘된다. 게다가 리눅스는 지금 용량 문제 때문에 사실상 모든걸 또 갈아엎고 다시 설치해야하는 위기에 처해졌다. 

처음에는 Rust에서 openGL과 CUDA를 진행하려 했으나.. 역시나 자료가 너어어어어무 없다. 그리고 어차피 openGL이든 CUDA든 unsafe한 메모리 관리를 직접 해주는 작업을 해줘야하기 때문에 Rust에서 쓴들 어차피 unsafe한 작업을 하기 때문에 C++랑 별 차이가 없다는 문제가 있다. 게다가 자료의 빈약함 정도가 너무나도 심했다. 그래서 어쩔 수 없이 Windows 환경 + C++을 사용하게 된것이다.

일단은 VS 2022에서 CUDA 프로젝트를 만들었다. 언젠가는 나도 반드시 쿠다를 쓸때가 올것이니. 왜냐면 대량의 데이처를 병렬 연산 스트림을 통해 처리할 것이기 때문이다. 그리고 learn openGL에서 말하는 것들을 해주었다. 우선 GLFW를 설치했다. 
https://www.glfw.org/download.html 여기에서 64-bit Windows binaries를 받아서 projects 폴더에 풀어주었다. 그리고 여기에서 lib-vc2022를 VS에서 project properties -> Configuration Properties -> VC++ Directories 에서 Library Directories에 추가해준다. include 폴더 역시 include Directories에서 추가해준다.

또한 다음은 glad라는걸 설치해야하는데, https://glad.dav1d.de/ 여기에서 gl 버전을 최신버전으로 선택하고 generate를 누르면 zip을 다운받을 수 있는데 이것 역시 projects 폴더에 적절히 풀어주고 여기의 include를 앞선 project properties의 VC++ Directories에서 include를 해준다. 

그리고 다음과 같이 include를 해줘서 컴파일을 해본다.
```cpp
#include <glad/glad.h>
#include <GLFW/glfw3.h>
```
