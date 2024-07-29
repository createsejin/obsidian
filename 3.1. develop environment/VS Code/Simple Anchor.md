[[Unique Anchor|이 글]]에 이어서 좀더 강력하고 보기 편한 방식이 하나 만들어졌다. 
```csharp
  private void DeleteButton_Clicked(object sender, EventArgs e)
  {
    if (File.Exists(_fileName)) File.Delete(_fileName);
    else if (File.Exists(_another_path)) File.Delete(_another_path);
    TextEditor.Text = string.Empty;
  }/* 
  NotePage                         @#*/
```
이런식으로 block comment를 이용해서 뒷 부분에 `@#` 패턴을 넣어서 VSCode에서 이 패턴을 찾게하는것이다.
이렇게 하면 굉장히 깔끔하게 Anchor Label을 search side bar에 표시할 수 있어서 가독성이 매우 향상된다.
다만 주의할점은 뒷부분이 너무 길어지면 뒷부분만 표시하는 경우가 있으므로
```
<!--
                              @#-->
```
이것을 M,N 레지스터에 등록한 후, vim의 `R`을 이용해서 Insert mode로 Label을 작성해주고, 필요에 따라 적절히 space 길이를 관리해주면 된다.

아니면 그냥 뒷 길이를 충분히 늘리고 정규 표현식으로 `\S.*@#` 이렇게 검색해주면 앞 Label이 짤리지 않고 뒷 길이에 관계없이 항상 표시된다. 
그러나 초록색으로 하이라이트 되기 때문에 조오금 불편해지기는 하다. 

이게 보니까 짧은 Label은 앞부분이 잘 짤리는데, 또 이게 충분히 Label이 길어지면 안짤리는 특성이 있는것 같다.

## 최종 결론안
그냥
```
    /*
    Main @#*/
```
이런식으로 하고 뒷부분 표시되는게 좀 불편하긴 하지만 대충 적응하면 이게 가장 편하고 심플하고 readable한 방법인 것 같다. 이런식으로 쓰면
```
//Main @#
#Func @#
```
이런식으로 single comment도 쉽게 적용이 가능하고, 뒷부분 길이를 조정할 필요가 없다.

powershell의 경우
```
<#
cave @#>
```
이런식으로 쓰면 comment block이 가능하다!

되도록이면 block comment를 쓰는게 가장 깔끔한 방법이다. 물론 뒷부분 @# 하이라이트 되는 지저분한 부분은 보기가 싫은게 사실이지만 적응하면 괜찮아질것으로 보인다.