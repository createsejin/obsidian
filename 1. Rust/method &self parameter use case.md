`self.path`가 `String` type이라고 할때,
```rust
  pub fn rewrite_ordered_cdd_data(&self) {
    let mut file = File::create(self.path).expect("can not create a file");
    ...
```
이런 method 하나를 생각해보자. 여기에서 무엇이 잘못됐을까?

Rust-analayzer는 다음의 에러 메세지를 뱉는다.
```
Diagnostics:
1. cannot move out of `self.path` which is behind a shared reference
   move occurs because `self.path` has type `String`, which does not implement the `Copy` trait [E0507]
```
이것은 무엇을 의미할까? 아마도 `self.path` 이렇게 전달하면 우리는 `String` 그 자체를 값으로 `File::create` method에 전달하는 것이다. 이렇게 되면 Rust는 `String`을 `create` method의 구조체로 move한다. 이렇게 되면 기존 String은 더이상 vaild 하지 않다. 이와 같은 문제로 인해서 `File::create`같은 method는 `clone` trait가 구현되지 않은 변수에 대한 값 전달, move out을 허용하지 않는것으로 보인다. 따라서 `&self.path`로 전달하는것이 옳다. 

또한 다음의 경우도 생각해보자.
```rust
  pub fn get_dir(&self) -> &str {
    &self.dir
  }
```
여기에서도 동일하게 `self.dir`은 `String` type이라고 해보자. 이 메소드는 단순하게 현재 struct의 멤버인 `dir`의 참조를 반환하는 함수다. 따라서 이 메소드의 마지막 표현식은 `&self.dir`이 되는 것이다. 만약 `self.dir`을 반환하면 에러가 발생한다. 그것은 `&str` type이 아닌, `String` type이기 때문이다.

그러니까 결론적으로 이러한 메소드의 `&self` parameter에 대한 method body의 정확하고 구체적인 사용 방법과 그 의미를 알아야한다는 것이다. 특히 body 안에서의 `&self` 및 `self`의 정확한 차이점을 알아야한다. `self`를 쓰는 순간부터 우리는 이미 parameter의 자신 참조, 즉, `&self`를 이용하는 것이다. 이러한 `&self` parameter를 통해 우리는 그 구조체 자신의 참조를 통해 자신의 멤버 또는 메소드에 접근할 수 있다. 그러나 메소드 body 안에서의 `self` 사용은 조금 의미가 다르다. 

`self.dir`이 `String` type이었다. 이것에 주목해야한다. 그리고 `&self.dir`은 그 `String` type에 대한 참조를 뜻한다. 즉, 여기에서는 일반적인 변수앞에 `&`가 붙을때 그것은 그 변수에 대한 참조를 뜻한다. 이러한 원리가 여기에 적용된다. 

다음의 메소드를 살펴보자. 이번에는 `&mut self`가 method parameter로 사용됐다.
```rust
  pub fn read_cdd_data(&mut self) -> io::Result<()> {
    let file = File::open(&self.path).expect("file not found \u{25A1}");
    let reader = io::BufReader::new(file);

    for line in reader.lines() {
      //...
      self.rows.push(dto);
    }
    self.rows.sort();
    Ok(())
  }
```
여기에서 `self.rows.push(dto)`를 하기 위해서 우리는 `&mut self`를 이용한 것이다. 그렇다면 여기에서는 `&self.rows.push(dto)`를 써야하는것인가? 아니면 전자를 쓰는게 옳은가? 사실은 그것은 조금 애매한 문제이긴 하다. 그러나 크게 상관은 없다. 따라서 전자를 쓰는게 더욱 깔끔하고 readable하다. 메소드 body에서 `&self`를 쓰느냐, `self`를 쓰느냐는 사실 마지막 표현식으로 리턴할 값을 명확히 결정할때, 그때에는 확실하게 구분해서 쓰는것이 맞다. 그러니 이런식으로 그냥 body 안에서 `self`를 통해 무언가를 작업할때에는 그것을 구지 구분할 필요가 없다. `self`든 `&self`든 어차피 동일한 개체를 가르키기 때문이다.