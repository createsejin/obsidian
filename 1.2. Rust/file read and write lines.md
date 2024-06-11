## reader
먼저 file read에 사용되는 함수를 살펴보자.
```rust
  pub fn read_cdd_data(&mut self) -> io::Result<()> {
    let file = File::open(&self.path).expect("file not found \u{25A1}");
    let reader = io::BufReader::new(file);

    for line in reader.lines() {
      let line_str = line.unwrap();
      self.rows.push(line_str);
    }
    Ok(())
  }
```
먼저 body의 첫번째 줄에서 `File::open`에 들어가는 변수는 `self.path`의 type이 `&str`가 아닌 `String`이라면 반드시 `&self.path`로 들어가야한다. `String`은 Copy trait가 구현되어있지 않기 때문이다. 

file로부터 `BufReader`를 얻는다. 이때 `file`은 일종의 스트림이다.
그 후 `reader.lines()` 메소드를 이용해서 line을 iterating 할 수 있다. 주의할 점은 line을 읽을때 실패할 가능성도 있기 때문에 `.unwrap`과 같은 메소드를 이용해서 `Result`를 handling 해줘야 한다는 것이다.

## write_all
```rust
  pub fn rewrite_ordered_cdd_data(&self) {
    let mut file = File::create(&self.path).expect("can not create a file");
    
    self.rows.iter().for_each(|dto: &Dto| {
      let mut line_str = String::new();
      dto.get_args().iter().for_each(|arg| {
        let formatted_str = format!("{}|", arg);
        line_str.push_str(formatted_str.as_str());
      });
      line_str.push_str(dto.get_dir());
      
      file.write_all(line_str.as_bytes()).unwrap();
      file.write_all(b"\n").unwrap();
    });
  }
```
이번에는 `file` 스트림에서 `write_all` method를 이용해서 line을 wirte하는 예시를 보여주고 있다.
주의해야할 점은 입력해야할 데이터가 `String` 타입이라면 `as_bytes` method를 이용해서 이것을 byte 배열로 변환시켜서 입력해야한다는 것이다. 만약 literal로 입력할거면 
`file.write_all(b"hello world")`처럼 `b""` byte literal을 이용해야한다. 
또한, line을 입력한 후 끝에다가 `b"\n"`을 추가적으로 write 해줘야 한다는 것이다.