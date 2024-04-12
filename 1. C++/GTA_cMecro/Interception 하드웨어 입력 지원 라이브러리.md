https://github.com/oblitum/Interception
아마도 따로 드라이버를 설치해서 사용되는 라이브러리같다. 이걸 어떻게든 사용해서 만들면.. 잘하면 만들 수 있을지도 모른다..

https://www.microsoft.com/en-us/download/details.aspx?id=11800
일단 여기에서 WDK 7.1.0 버전을 다운받았다. 왜냐면 interception readme에서 나온 버전이기 때문. 이게 환경변수로 입력되어야 가능한것 같았다. 일단 설치해주자.

받아보니 왠 ISO 파일이다. 탑재를 한뒤 안에 있는 KitSetup.exe를 실행해서 설치를 시도했다. 뭘 설치해야할지 몰라서 그냥 모든 항목을 체크하고 전부 설치 체크했다. 아무래도 .Net frame work 3.5가 필요한것 같았다. 

기본적으로 드라이버라는 것은 하드웨어와 소프트웨어를 서로 연결해주는 일종의 인터페이스다. 아무튼 해보자. 이걸 만약 프로젝트에 사용하게 된다면 무려 아두이노 따위가 필요가 없게 된다. 이렇게 되면 잠재적으로 굉장히 가치가 있는 프로그램을 만들 수도 있을지 모른다.

일단 재부팅. 아무래도 [[서브컴 windows10 C++ 개발환경 세팅|서브컴의 C++ 개발 환경 세팅]]을 좀 해주었다.

이 라이브러리는 DLL 동적 라이브러리로, 실행 파일이 빌드되는 위치, 즉, 실행 파일 디렉토리에 .dll 파일과 .lib 파일이 있어야한다. 또한 헤더파일인 interception.h를 적절한 위치에 두면 이 라이브러리의 API를 사용할 수 있다. 아마도 WDK 같은건 필요 없어보인다. 어차피 그건 이 interception의 소스코드를 빌드할때나 사용되는 것 같았다. 무엇보다 중요한것은 관리자 권한으로 interception의 driver를 설치하는 일이다. 

아무래도 이 [사이트](https://www.oblita.com/interception.html)를 참고하는게 가장 득이 될것 같다. interception 공식 문서인것 같다.

링킹 에러가 있어서 cmake에 다음 줄을 추가해줬다.
```cmake
link_directories(${CMAKE_SOURCE_DIR}/external_lib/interception/x64)
target_link_libraries(gta_c2 gdiplus interception)
```

context를 만드는게 failed되서 관리자 권한으로 shell을 열고 다시 드라이버를 인스톨해봤다.
```
PS C:\Users\bae> cd "D:\Projects\Interception\command line installer"
PS D:\Projects\Interception\command line installer> .\install-interception.exe /install

Interception command line installation tool
Copyright (C) 2008-2018 Francisco Lopes da Silva

Interception successfully installed. You must reboot for it to take effect.
```
리부팅. 

이제 잘 된다. 아무래도 [이곳 블로그](https://catlab.tistory.com/12#article-3-3--3--%ED%95%98%EB%93%9C%EC%9B%A8%EC%96%B4-%EC%9E%85%EB%A0%A5)를 참조하면 더 정보를 얻을 수 있을듯. 그런데 여기는 파이썬이랑 오토핫키를 기준으로 이 interception을 다루고 있다. 근데 웃긴건 공식 readme에서는 드라이버 인스톨할때 아무런 입력값 없이 실행하라 했는데 그게 아니었다. 
`.\install-interception.exe /install` 이런식으로 입력값에 `/install`을 추가로 입력해야했던것. 그리고 이 드라이버가 성공적으로 설치됐는지 확인하기 위해 관리자 권한으로 터미널을 열고서 그곳에서 이 명령을 실행하면 직접 더블 클릭으로 실행하는것 보다 실행 결과를 알 수 있어서 좋다.

# 그러나 문제는..
이 라이브러리의 드라이버는 windows10까지만 지원하는것 같다. 아마도 windows11에서는 Trusted Computing 같은 보안 모듈 때문에 일반적인 드라이버는 아예 설치가 안되는것으로 보인다.. 이걸 해제해도 `system32/drivers`접근 권한을 얻을 수가 없어서 설치가 안됐다..