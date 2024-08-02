```
cargo run -p rar_unzipper -- arg1 arg2 "arg ddd sss" 'dddddddd ddd ' "aaa 'fff'"
Unzipper start
target\debug\rar_unzipper.exe|arg1|arg2|arg ddd sss|dddddddd ddd |aaa 'fff'|
```
이런식이다. 앞에 `-p` 옵션은 만약 현재 디렉토리가 [[cargo workspace|workspace]] 형식으로 되어있으면 어떤 package를 선택할 것인지 정하는 옵션이다. 
argument list는 `--` seperator 뒤에다가 저런식으로 넘기면 된다.

Rust argument list는 첫번째 자리에 자신의 실행 파일 이름을 포함한다. 따라서 1번 index부터 실제 argument가 된다.
이것은 .Net과는 조금 다른 방식이며, 원래 이 방식이 전통적인 argument list indexing 방식이다.