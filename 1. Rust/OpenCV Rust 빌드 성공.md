결국에는 해냈다. [이곳](https://github.com/twistedfall/opencv-rust)의 도움을 빌렸다. 일단 chocolatey를 먼저 설치해야한다. 그리고 문서의 도움말과 같이 llvm과 opencv를 깔아야했다.
`choco install llvm opencv`
뭐 여기까지는 쉽다.
그리고 Cargo.toml에 `opencv = "0.88.1"`를 추가.
아직이다. 아직 Cargo.toml를 업데이트 하면 안된다. 환경 변수 작업이 필요하기 때문

이 [링크](https://github.com/twistedfall/opencv-rust/issues/118#issuecomment-619608278)에 따르면 3가지의 opencv 환경 변수가 필요했다.
```
OPENCV_INCLUDE_PATHS = "C:\tools\opencv\build\include"
OPENCV_LINK_LIBS = "opencv_world481"
OPENCV_LINK_PATHS = "C:\tools\opencv\build\x64\vc16\lib"
```
tools에 설치된 애들은 choco에 의해 설치된 애들이다. 

또한 위 링크의 아랫글을 더 보면 `opencv_worldxxx.dll`을 빌드 타겟 .exe가 위치한 폴더에 넣어줘야한다고 한다. 나의 경우는 `C:\tools\opencv\build\x64\vc16\bin\opencv_world481.dll` 이 파일이었다. 이것을 `project_root/target/debug/`에 넣어주면 된다.

또한 환경변수에 `VCPKGRS_DYNAMIC = 1` 를 추가해줬는데, 이건 뭐 모르겠다. 아무튼 이 작업 전에 vcpkg도 clion에서 열어서 llvm이랑 opencv를 깔아주긴 했다.. 근데 이게 꼭 필요한건지는 아직 모르겠다. 아마도 그냥 choco 방법으로 하는거랑 독립적인 다른 소스/방법인듯? 모르겠다. 