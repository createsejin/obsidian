Visual Studio 2022에서는 VSCode의 search 기능 처럼 file include, exclude 기능이 없다. 
대신 정규식 표현, Case Sense, Match whole word 기능은 존재한다. 따라서 exclude가 없기 때문에 나는 단가지 대안을 생각해냈다. 그것은 바로 `@@`뒤에 카테고리를 나타내는 sufix를 붙이자는 것이다. 예를 들면 다음과 같다.
```
/*
Downloader @@down.a*/
/*
Downloader @@down.b*/
```
이런식이다. 그럼 우리는 이제 원하는 카테고리만 지정해서 검색할 수 있다. 
예를들어 `@@down`을 검색하면 `down` 카테고리와 일치하는 애들만 검색할 수 있게된다. 
또한 그 뒤에는 또다른 추가적인 nested sufix를 붙여서 더 세분화할 수도 있다. 이렇게 하더라도 `@@down` 카테고리는 여전히 유지된다. 

이걸 [[file anchor|file anchor]]에 응용하면 내가 원하는 file 카테고리만 찾을 수도 있을것 같다. 
`file_name.wav.next.@@wav` 머 이런식?

그런데 실제 코드에서 응용할때에는 간단하게 `@@A`, `@@B` 이런식으로 문자 하나씩 붙이는 것도 좋은것 같다. 이렇게 하면 각 카테고리간 전환이 쉬워진다. 
또한 여러 카테고리를 혼합해서 

#anchor 
