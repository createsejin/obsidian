rust의 cargo는 workspace라는 아주 이로운 기능이 존재한다. 이것은 말 그대로 workspace, 예를 들어서 라이브러리 프로젝트 2개와, 실행 바이너리 프로젝트 1개 또는 그 이상 등등등으로 구성이 가능하다. 이것은 rust [book](https://doc.rust-lang.org/beta/book/ch14-03-cargo-workspaces.html)에서 자세히 소개하고 있다.
우선 이러한 프로젝트들이 담길 가장 상위 폴더를 하나 만든다. 여기에서는 그 폴더 이름을 `study`라고 지었다.
```
mkdir study
cd study
touch Cargo.toml
```
그리고 최상위 `Cargo.toml`에 다음과 같이 적는다.
```
[workspace]
members = [ "study_lib", "study_bin" ]
resolver = "2"
```
여기에서 `members`는 각각의 독립된 workspace를 가르킨다. 
`resolver` 옵션은 2로 설정하면 된다.

그 후 다음 명령어를 통해 각각의 프로젝트를 만들어준다.
```
cargo new study_lib --lib
cargo new study_bin
```
그러면 다음과 같은 파일 구조를 이루게 된다.
```
study
├── Cargo.toml
├── study_bin
│   ├── Cargo.toml
│   └── src
│       └── main.rs
├── study_lib
│   ├── Cargo.toml
│   └── src
│       └── lib.rs
```
이제 실행 바이너리 프로젝트인 `study_bin`의 `Cargo.toml`에 가서 다음과 같이 Dependencies를 입력해줘야한다.
```
[package]
name = "study_bin"
version = "0.1.0"
edition = "2021"

# See more keys and their definitions at https://doc.rust-lang.org/cargo/reference/manifest.html

[dependencies]
study_lib = { path = "../study_lib" }
```
바로 옆자리의 `study_lib`의 상대 경로를 입력해주면 된다.

또한 여기에다가 외부 라이브러리를 적게되면 cargo에서 알아서 이 workspace에 속한 모든 프로젝트들이 동일한 버전의 그 라이브러리를 사용할 수 있게 한다. 만약 버전을 다르게 입력해도 알아서 compatible하게 버전을 정해준다. 이것은 한 라이브러리에서만 의존성을 입력한다고 다른 라이브러리에도 바로 적용되는건 아니다. 예를 들어서 바이너리 프로젝트에서 같은 라이브러리를 사용하고 싶다면, 그 프로젝트의 `Cargo.toml`파일에도 라이브러리 의존성을 적어줘야 사용이 가능하다.

또한 만약 여러개의 실행 바이너리 프로젝트가 있다면 다음 옵션을 통해 `cargo run`으로 어떤 프로젝트를 실행할건지 정할 수 있다.
```
cargo run -p study_bin
```
주의할점은 최상위 디렉토리에서 이 명령을 실행해야한다.
또한 이러한 `-p` 옵션은 `cargo test`에서도 동일한 context로 쓰인다. 예를 들면 다음과 같다.
```
cargo test -p study_lib
```