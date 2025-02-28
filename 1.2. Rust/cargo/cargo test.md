기본적으로는 이 [부분](https://doc.rust-lang.org/beta/book/ch11-00-testing.html)을 review하면 좋다.

test를 작성할때에는 반드시 아래와 같이 `tests` 모듈을 사용해서 그 내부에 `#[test]` 어트리뷰션을 붙여야한다.
```
#[cfg(test)]
pub mod tests {
	#[test]
	fn _test001() {...}
}
```
보통은 이런식으로 따로 `tests` 처럼 모듈 단위로 만들어서 테스트를 하는게 좋다.
단순히 `#[test]`를 붙이는것으로도 test는 가능하다. 그러나 `#[cfg(test)]` 이것을 쓰는 이유는 `cargo build`를 할때 이 부분을 제외해서 build하기 때문에 필요하다.
## assert
`assert!(condition, msg)`: `condition`이 `true`여야만 이것을 통과하고, 실패하면 `msg`를 출력한다.
`assert_eq!(lhs, rhs, msg)`: `lhs`와 `rhs`가 서로 같아야만 통과한다. 실패시 msg를 출력한다.
`assert_ne!(lhs, rhs, msg)`: `lhs`와 `rhs`가 서로 달라야만 통과한다.

## cargo test
`cargo test`
`cargo test _test001`: 특정 test만을 test한다.

`cargo test -- --test-threads=1`: 멀티 스레드를 사용하지 않는다.
`cargo test -- --show-output`: `print!`들을 출력해준다.
## attribution
```
#[test]
#[should_panic]
fn _test002() {...}
```
이렇게 하면 test002는 반드시 panic을 일으켜야 테스트를 통과한다.
```
#[test]
#[ignore]
fn expensive_test() {
    // code that takes an hour to run
}
```
test에서 제외시킨다.
`cargo test -- --ignored`를 통해 제외된 test를 다시 test할 수 있다.
`cargo test -- --include-ignored` 이렇게 하면 제외된 test를 포함해서 모든 test를 진행한다.

## integration test
```
study_lib
├── Cargo.toml
├── src
│   ├── lib.rs
│   └── study15.rs
└── tests
    └── integration_test.rs
```
이런식으로 새로 `tests`라는 폴더를 만들고 그 안에 다시 `integration_test.rs`를 만든다. 아마도 내부 `.rs`모듈 파일은 다른 이름으로도 가능할거다.

이렇게 만들면 라이브러리 프로젝트에서 실제 바이너리 프로젝트와 거의 동일한 환경에서 라이브러리를 테스트 할 수 있다.

`integration_test.rs`는 다음과 같이 작성한다.
```
use study_lib::study15;

#[test]
fn test003() {
  study15::study004();
}
```
그 후 
`cargo test --test integration_test` 로 해당 테스트를 특정해서 테스트가 가능하다. 
물론 그냥 `cargo test`를 해도 자동으로 모든 테스트를 진행해준다. 
