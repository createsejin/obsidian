VSCode에는 현재 workspace 기준으로 모든 파일의 내용을 정규 표현식으로 검색하고, 특정 파일을 exclude하거나 include하는 강력한 기능이 존재한다. 
[[단축키 정리|단축키]]는 `ctrl+shift+F`이다. 검색창에서는 3가지 옵션을 선택할 수 있는데, 첫번째는 대소문자를 구분하는 유무, 두번째는 찾는 단어가 온전한 한 단어를 찾을건지의 유무, 세번째는 정규표현식을 사용할건지의 유무이다. 그 바로 밑에 ...을 누르면 file을 이름 기준으로 include 또는 exclude를 할 수 있다. 여기에는 와일드 카드와 같은 패턴 표현식이 사용될 수 있으며 콤마로 구분한다. 여기에서 한가지 팁은 예를들어서 `NUnitTest,Operator,SharedLib,Commander` 이런식의 file include가 설정됐다고 했을때, 간단하게 파일 이름 앞에 `-`을 붙여서 그 파일을 간단히 제외하고 나중에 다시 include하려면 `-`를 제거하기만 하면 되기 때문에 `NUnitTest,Operator,SharedLib,-Commander` 이런식으로 `Commander`를 include에서 간단히 제외시킬 수 있게된다. 

이 기능을 더 강력하게 만들어주는 한가지 방식이 있는데, 그것은 `@#` 마커이다. 나는 이것을 사용한다. 그 어떤 코드베이스에서도 이것을 코멘트와 함께 사용할 수 있으며 기본적으로는 아래와 같이 사용한다.
```
//@#Pointer001

#@#Script001

/*
@#Pointer002 			*/

<!--
@#AppShell.X                   -->
```
이런식으로 single line 또는 block comment로 깔끔하게 만들어줄 수 있다. 또한
```
/*
@# 			*/
<!--
@#                 -->
```
이런식의 block comment들을 미리 vim 레지스터 M, N에 저장해두었다가 쓰면 매우 편리하다.

나는 이것을 다른 이름으로 'anchor'라고도 부르는데, 이렇게 만들어주면 파일이 수정되어서 줄이 바뀌더라도 이 anchor는 그대로 그 위치를 유지한다.

또한 나는 이러한 anchor를 현재 작성중인 코드 바로 밑에 두고 사용하는데, 이렇게 하면 내가 일일히 위치를 코드를 수정할때마다 매번 수정할 필요가 없게된다.
예를 들어서 다음과 같이 사용하는것이다.
```csharp
  private void DeleteButton_Clicked(object sender, EventArgs e)
  {
    if (File.Exists(_fileName)) File.Delete(_fileName);
    else if (File.Exists(_another_path)) File.Delete(_another_path);
    TextEditor.Text = string.Empty;
    /* 
    @#NotePage.cs                    */
  }
```

block comment를 사용하는 이유는 single comment에서는 `//@#`이런식으로 써야해서 앞부분이 길어지기 때문에 사용하는 것인데, 문제는 위 코드처럼 불필요한 공간이 생긴다.
따라서 visual mode로 block comment 부분만 M, N 레지스터에 붙여서 필요한 위치의 코드 바로 그 다음에 쓰면 다음과 같이 깔끔하게 사용할 수 있다.
```csharp
  private void DeleteButton_Clicked(object sender, EventArgs e)
  {
    if (File.Exists(_fileName)) File.Delete(_fileName);
    else if (File.Exists(_another_path)) File.Delete(_another_path);
    TextEditor.Text = string.Empty;/* 
    @#Pointer003                    */
  }
```
block comment의 뒷부분을 저렇게 띄워놓는것도 VSCode의 search side bar에서 좀더 깔끔하게 키워드를 보이기 위함이다. 

또한 만약 특정 Anchor를 제외하고 싶으면 `@#`를 `@-#` 이런식으로 바꾸면 된다.
만약 제외한 Anchor까지 모두 보고 싶으면 정규 표현식으로 `@#|@-#`를 검색해주면 된다.