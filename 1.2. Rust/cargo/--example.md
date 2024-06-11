Cargo book에서 [Package Layout](https://doc.rust-lang.org/beta/cargo/guide/project-layout.html#package-layout)을 보면 examples 라는게 있다. 이글에서 따온 구조를 보면 
```
.
├── Cargo.lock
├── Cargo.toml
├── src/
│   ├── lib.rs
│   ├── main.rs
│   └── bin/
│       ├── named-executable.rs
│       ├── another-executable.rs
│       └── multi-file-executable/
│           ├── main.rs
│           └── some_module.rs
├── benches/
│   ├── large-input.rs
│   └── multi-file-bench/
│       ├── main.rs
│       └── bench_module.rs
├── examples/
│   ├── simple.rs
│   └── multi-file-example/
│       ├── main.rs
│       └── ex_module.rs
└── tests/
    ├── some-integration-tests.rs
    └── multi-file-test/
        ├── main.rs
        └── test_module.rs
```
생김새는 이렇다. `tests`와 마찬가지로 project root에서 `examples`라는 directory로 존재할 수 있다.
여기에는 `simple.rs`와 같이 간단한 하나의 파일, 하나의 `main()`함수를 지닌 Rust code를 놓을 수 있다. 또한, `multi-file-example`과 같이 여러개의 모듈로 된 Rust code들을 놓을 수도 있다. 이들은 모두 `main()` function을 하나씩 가지는것으로 보인다. 그리고 다음과 같이 cargo command를 사용할 수 있다.
```
cargo run --example simple
```
또한, cargo workspace 환경에서는 다음과 같이 명령어를 쓸 수 있다.
```
cargo run -p my_binary --example simple
```
이런 좋은 기능을 왜 rust book에서 소개하지 않았는지 의문이다. 이걸 알았다면 좀더 쉽게 rust book 예제 코드를 사용할 수 있을텐데 말이다.. 