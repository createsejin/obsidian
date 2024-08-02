```
cargo test --package rar_unzipper --bin rar_unzipper -- unzipper::tests1::test1 --show-output
```
여기에서 `--package`와 crate의 이름이며, `--bin`은 아마도 이 crate의 특정 binary를 가리키는것 같다. 그 뒷 부분에 `--` 로 구역이 나뉘는데, 그 이후에 
`unzipper::tests1::test1` 이런식으로 특정 모듈의 특정 메서드를 특정해서 test할 수 있다. `--show-output`은 출력문을 출력하게 한다.