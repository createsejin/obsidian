기본적으로는 이 [부분](https://doc.rust-lang.org/beta/book/ch11-00-testing.html)을 review하면 좋다.

test를 작성할때에는 반드시 아래와 같이 `tests` 모듈을 사용해서 그 내부에 `#[test]` 어노테이션을 붙여야한다.
```
#[cfg(test)]
pub mod tests {
	#[test]
	fn _test001() {...}
}
```
보통은 이런식으로 따로 `tests` 처럼 모듈 단위로 만들어서 테스트를 하는게 좋다.
단순히 `#[test]`를 붙이는것으로도 test는 가능하다. 
## assert
`assert!(condition, msg)`: `condition`이 `true`여야만 이것을 통과하고, 실패하면 `msg`를 출력한다.
`assert_eq!(lhs, rhs, msg)`: `lhs`와 `rhs`가 서로 같아야만 통과한다. 실패시 msg를 출력한다.

## cargo test
`cargo test`
`cargo test _test001`: 특정 test만을 test한다.

`cargo test -- arg1 arg2`