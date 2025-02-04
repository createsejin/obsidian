```
mkdir cxx-demo2
cd cxx-demo2
cargo init
```
기본 프로젝트를 만들어준다. 프로젝트 이름은 알아서.

그리고 `cargo.toml`파일을 다음과 같이 디펜던시들을 추가해준다.
```
[package]
name = "cxx-demo2"
version = "0.1.0"
edition = "2021"

# See more keys and their definitions at https://doc.rust-lang.org/cargo/reference/manifest.html

[dependencies]
cxx = "1.0"

[build-dependencies]
cxx-build = "1.0"
```
중요한 점은 다음과 같이 `include!`에서
```
#[cxx::bridge]
mod ffi {
  extern "Rust" {
    type MultiBuf;

    fn next_chunk(buf: &mut MultiBuf) -> &[u8];
  }

  unsafe extern "C++" {
    include!("/home/bae/Projects/cxx-demo2/include/blobstore.h");

    type BlobstoreClient;

    fn new_blobstore_client() -> UniquePtr<BlobstoreClient>;
    fn put(&self, parts: &mut MultiBuf) -> u64;
  }
}
```
저 헤더 파일 경로를 절대경로로 해주는게 가장 마음이 편해지는 솔루션이라는 것이다.