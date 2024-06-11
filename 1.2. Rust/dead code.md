rust에서 dead code로 분류되는 경우는 여러가지다. 
우선 메인 함수로부터 시작되는 줄기에 함수가 포함된다면 dead code로 분류되지 않는다.
그러나 여기에 포함되지 않거나 사용되지 않았다면 dead code로 분류된다.

또한 lib project에서는 주로 tests 모듈에 포함되지 않은 함수들 혹은 구조체를 dead code로 분류한다. lib.rs안의 tests module과 같은 곳에 test 용도로 함수를 올리면 dead code로 분류되지 않는다.
그리고 만약 lib.rs 외부의 다른 모듈파일, 예를 들면 그 옆 모듈이 `study15.rs`라면 여기에 포함되는 함수들 역시 lib.rs의 tests 모듈에 직접적으로 포함되면 dead code로 분류된다. 이게 무슨 말이냐. 예를 들어서 lib.rs 안에 존재하는 어떤 함수를 `in_lib`라는 함수라고 하자. 이 함수 안에 `study15.rs` 모듈의 함수를 호출한다. 따라서 다음과 같다.
```
fn in_lib() {
  study15::study001();
}
```
그리고 다음과 같이 `in_lib()`함수를 tests 모듈에 넣는다.
```
#[cfg(test)]
mod tests {
  use super::*;

  #[test]
  fn test001() {
    in_lib();
  }
}
```
이런식으로 `lib.rs`안에 있는 함수를 통해 거쳐서 들어가는 `study15::study001()`함수는 dead code로 분류되지 않는다. 그러나 다음과 같이,
```
#[cfg(test)]
mod tests {
  use super::*;

  #[test]
  fn test001() {
    study15::study001();
  }
}
```
이런식으로 `lib.rs`안에 있는 함수를 통해 거치지 않고 바로 외부 모듈을 저렇게 갖다가 쓰면 dead code로 분류된다.

이러한 원리는 [[cargo test#integration test|integration test]]에서도 동일한 context로 사용된다. 즉, `integration_test.rs` 안에 있는 함수를 거쳐서 그 안의 test 함수에 호출되면 외부 모듈의 함수는 dead_code로 분류되지 않는다.
