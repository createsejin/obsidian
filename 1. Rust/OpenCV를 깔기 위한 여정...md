처음에 Cargo.toml에 `opencv = "0.88.1"`을 했지만 build fail을 일으켰다. 아마도 이 라이브러리는 C 기반 라이브러리이기 때문에 vcpkg에 선행적으로 설치되어야만 하는 것이었다..
어쨌거나 예전에 썼던 clion의 vcpkg를 VCPKG_ROOT로 설정하는게 필요했다.

windows 시스템에서 코딩을 하는 작업은 이러한 환경이 말썽을 일으키기 때문에 매우 힘든 것이다..

일단은 다음을 통해 대충 환경 변수를 추가해줬다.
windows의 환경 변수는 시작버튼을 오른쪽 클릭 -> 시스템 -> 고급 시스템 설정 -> 고급 -> 환경 변수 에서 시스템 변수 탭에서 '새로 만들기'를 통해 할 수 있었다.

다음 세 가지를 추가해줬다.
```
PKG_CONFIG_PATH = C:\tools\opencv\build\x64\vc16\bin
OpenCV_DIR = C:\tools\opencv\build
VCPKG_ROOT = C:\Users\creat\.vcpkg-clion\vcpkg
```
opencv를 설치하기 위해 기존에 chocolateyTools도 [설치](https://chocolatey.org/install)해줬었다.

어차피 cmake는 이미 추가해뒀으니 잘 될거고.. 

아, 그전에 저 위에 있는 pkg_config 어쩌구도 설치해줬었는데.. 아마 choco로 설치한것 같다. 얘는 잘 동작하는데.. 문제는 llvm이랑 opencv를 vcpkg에 빌드하는게 안되고있다.. 미처버리겠다.. 시불 .. 

그러나 결국 [[OpenCV Rust 빌드 성공|해결]]했다.