이 [[Android에서 Rust 사용하기1|글]]에서는 조금 문제가 있었다. 아마도 Termux 내부에서 그냥 rust를 빌드하려는것 같은데. 조금 문제가 있다. 가장 큰 문제는 우선 Rust에서 공식으로 지원하는 티어 목록에서 `aarch64-linux-android`는 Tier2 without host tool 이라고 되어있다. host tool이 정확히 무엇을 뜻하는지는 나도 잘 모르지만, 아마도 `aarch64-linux-android` host상에서 직접 cargo를 이용해서 compile하는 작업 등을 지원하지 않는다는 것 같다. 따라서 Rust가 지원하는 host 환경에서 컴파일을 해야한다는 것이다. 

일단은 이 rust의 공식 [글](https://doc.rust-lang.org/rustc/platform-support/android.html)에서 간단한 정보를 확인할 수 있다. `aarch64-linux-android`시스템을 위한 rust 프로그램을 build하기 위해서는 Android NDK가 필요하다는 것이다. 이 글에서는 이 [링크](https://developer.android.com/ndk/downloads)를 통해 Android NDK를 다운로드 할 수 있다고 소개한다. 그래서 우선은 다운로드를 받고 압축을 풀어줬다.

그리고 삼성 tech blog에서 한가지 좋은 [글](https://techblog.samsung.com/blog/article/265)을 찾을 수 있어서 이걸 참고해봤다. 
글에서 소개하는 방법에 따르면 우선 `rustup`을 통해서 필요한 toolchain을 먼저 다운로드 해야한다는 것이다. 
`rustup target add aarch64-linux-android` 을 통해 설치할 수 있었다.

그 후에는 이것을 컴파일 하기 위한 컴파일러가 필요했다. 이 [글](https://www.reddit.com/r/rust/comments/ruafyd/how_can_i_build_hello_world_rust_for/)에 따르면 필요한 컴파일러는 `android-ndk-r26d/toolchains/llvm/prebuilt/linux-x86_64/bin`에서 `ls -Al | grep -i "clang"`을 통해 찾을 수 있었다. 
일단은 호환성 확인을 위해 내 휴대폰의 안드로이드 버전을 확인했다. 버전은 14 버전이었다. [여기](https://developer.android.com/tools/releases/platforms#14)에서 안드로이드 14버전은 API level 34를 사용하고 있음을 알 수 있다. 따라서 우리가 써야하는 컴파일러는 `aarch64-linux-android34-clang`인 것이다. 
일단 위에서 받은 NDK 폴더인 `android-ndk-r26d` 폴더를 `/opt`로 move해줬다. 그리고 아래의 export를 통해 bin을 PATH 환경 변수에 추가해줬다.
```
~/.zshrc :
--------------------------------------------
export PATH="/opt/android-ndk-r26d/toolchains/llvm/prebuilt/linux-x86_64/bin:$PATH"
```
`source ~/.zshrc`

다시 삼성 blog post에서 제안하듯이 이 컴파일러를 global cargo config file에 등록해야한다.
`~/.cargo/`로 가서 `touch config.toml`로 파일을 만든 뒤 연다.
```
config.toml :
-----------------------------------------------
[target.aarch64-linux-android]
linker = "aarch64-linux-android34-clang"
```
자신의 안드로이드 버전에 맞는 API level을 지정해서 적어야한다. 나는 `..-android34-`로 적어줬다.

그 후 `cd ~/Project`로 이동해서 test용으로 간단하게 `cargo new hello_android` 프로젝트를 만든뒤, 
```
cargo build --target=aarch64-linux-android
```
로 project를 build해준다. build가 완료되면 
`hello_android/target/aarch64-linux-android/debug`에 실행파일이 만들어진다. 

나는 편리한 개발과 배포를 위해서 github repository를 활용했다. 예를 들어서 현재 만든 Project를 github remote repository로 [[github-cli를 이용한 remote repository 만들기|만든]] 뒤 적절하게 실행파일을 옮기고 그것을 Android termux에서 git clone 하는 방법으로 간단히 실행파일을 옮기고 테스트할 수 있었다. 일단 `Hello, world!`를 출력하는데까지는 성공했다. 사실 여기까지 된거면 뭐 그 다음부터는 case by case이지만 아마도 외부 라이브러리도 가능하지 않을까 싶다. 