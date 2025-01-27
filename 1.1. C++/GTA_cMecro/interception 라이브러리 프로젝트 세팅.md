일단 앞서 기본적인 사항은 [[Interception 하드웨어 입력 지원 라이브러리|여기]]에 적어두었다. 기본적으로 windows10/11 SDK 가 필요하다. 이것은 Visual Studio를 설치하면 된다.

일단 [공식 github release](https://github.com/oblitum/Interception/releases)에서 interception.zip을 받고 적당한 곳에 압축을 해제한다. 나는 일단 Projects 폴더에 풀어주었다.

이제 가장 먼저 할 일은 'command line installer'에 들어가서 탐색기의 주소를 복사 한 뒤, 관리자 권한으로 터미널을 열어서 
```
cd "D:\Projects\Interception\command line installer"
install-interception.exe /install
```
이걸 통해 성공적으로 드라이버가 설치됐음을 확인하고 리부팅한다.

그 다음에 프로젝트를 IDE로 열어서 `interception/library` 폴더를 복사 한뒤 프로젝트의 적절한 디렉토리에 넣어준다. 나는 조금 폴더 이름들을 수정해서 
`project_root/external_lib/interception/x64` 뭐 이런식으로 넣어주었다.

그 다음에는 CmakeLists.txt를 만져줘야하는데, 가장 먼저 `project_root/external_lib/interception/interception.h` 헤더 파일을 `add_executable` 리스트에 추가하는 것이다. 실제로 추가할 때에는 아래와 같이 한다.
```cmake
add_executable(gta_c2 main.cpp
        test/test000_capture.cpp
		...
        external_lib/interception/interception.h
        ...
        test/test002_interception.cpp
        test/test002_interception.h
)
```
그리고 아래와 같이 cmake를 설정해준다.
```cmake
link_directories(${CMAKE_SOURCE_DIR}/external_lib/interception/x64)
target_link_libraries(project_name interception)
```
이제 헤더파일을 추가하고 사용하면 된다.