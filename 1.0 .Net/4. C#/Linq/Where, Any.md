기본적으로 이 둘을 표현식의 bool 값에 따라 동작한다. 이것을 함께 합쳐 쓰는 경우가 한가지 있었다.
```csharp
	string[] img_dir_keywords = ["イラスト", "画像"];

    foreach (var dir in root_dirs)
    {
      var sub_dirs = Directory.EnumerateDirectories(dir, "*", SearchOption.AllDirectories)
        .Where(sub_dir => img_dir_keywords.Any(keyword => Path.GetFileName(sub_dir).Contains(keyword)));
```
이것을 한번 풀어서 보자. 우선 `root_dirs`에서 `dir`을 루핑하고 있다. 이 각각의 `dir`에 대해서 다시 그 `dir`의 directory들을 `Directory.EnumerateDirectories`을 통해 enumerate 하고 있다. 하위 폴더까지 모두 포함하는 옵션 `SearchOption.AllDirectories`를 사용하고 있다. 그리고 `.Where`이 사용되는데, 메인 표현식에서는 앞서 enumerate한 `sub_dirs` 배열에서 `sub_dir`에 대해서 `img_dir_keywords` 배열에 `.Any`를 사용하고 있다. `.Any`안에 든 표현식에서는 `Path.GetFileName`에서 그 인수로 `sub_dir`을 통해 file_name을 얻고 있다. 그 file_name에 `.Any`에서 캡쳐한 `img_dir_keywords`의 요소중 하나인 `keyword`가 그 중 하나라도 `.Contains`하면 이 식은 `true`가 되고, 다시 `.Any`에 하나라도 `true`가 전달되면 `sub_dir`을 캡쳐하고 있는 바깥 표현식이 다시 `true`가 될 것이다. 이러한 결과만을 쿼리한 결과, 즉, `img_dir_keywords` 배열의 `keyword`를 포함하는 `sub_dir`만 선택해서 쿼리를 반환하는 것이다. 

그러니까 여기서 `.Any`를 쓴 이유가 중요하다. 골자는 `img_dir_keywords` 배열 중 어느 하나라도 그것을 `Contains`한다면 `.Any`가 `true`로 된다는 것이다.

```csharp
    // 이미지 확장자 배열
    string[] img_extensions = ["*.jpg", "*.jpeg", "*.png"];
    string[] exclude = ["hentai", "www"];
    var img_files = img_extensions
      // img_extensions 배열에 담긴 ext가 포함된 모든 file들의 string들을 img_files에 담는다.
      .SelectMany(ext => Directory.EnumerateFiles(path, ext, SearchOption.AllDirectories))
      // 결과를 array로 만든 후, file 중에서 그 이름에 exclude 배열에 담긴 keyword 중 
      // 어느 하나라도 포함된다면 그것은 제외한다.
      .ToArray().Where(file => !exclude.Any(keyword => Path.GetFileName(file).Contains(keyword)));
```
이것은 [[Select와 SelectMany의 차이점|SelectMany]]와 Where, Any를 모두 사용한 쿼리다. 코멘트를 참조하자. 