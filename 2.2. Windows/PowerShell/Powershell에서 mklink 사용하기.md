링크를 만들고자 하는 위치로 가서 다음 명령어를 실행한다.
```
cmd /c mklink /h <target_file_name> <source_file_path>
```
이 명령어는 원래 cmd 명령어다. cmd에서는 [[windows 환경에서의 cmd mklink|이것]]처럼 이 명령어를 바로 사용할 수 있다. 또한 batch script에서도 마찬가지다.

그런데 [[mk symbolic link ln alias 설정|여기]]에서 powershell에서 사용할 수 있는 간편한 alias를 통해 더 손쉽게 심볼릭 링크를 만들 수 있는 방법이 서술되어있다.