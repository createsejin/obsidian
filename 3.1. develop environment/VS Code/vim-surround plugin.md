[github](https://github.com/tpope/vim-surround)

vscode의 vim plugin에서는 `@ext:vscodevim.vim surround`를 settings에서 검색하는 것으로 Enable할 수 있다. vim plugin을 설치하면 기본적으로 설치되는 모양이다.

기본적으로 키바인딩은 `ys`, `cs`, `ds` 3가지다. 
`ys`는 감싸는걸 적용시키는 기능이고, `cs`는 감싼 걸 다른걸로 바꾸는것이고, `ds`는 감싼걸 지운다.

```
Hello World
```
이런 문장이 있다고 하자.

전체 문장 한 줄을 double quote에 넣으려면 `yss"`
```
"Hello World"
```

double quote를 single quote로 바꾸려면 `cs"'`
```
'Hello world'
```

single quote를 없애려면 `ds'`
```
Hello World
```

앞 단어만을 공백 없는 괄호에 넣으려면 `ysiw)`
```
(Hello) world
```

문장 전체를 공백 있는 중괄호에 넣으려면 `yss{`
```
{ (Hello) world }
```
그러니까 공백이 있는 괄호나 중괄호, 블록 괄호는 `(`, `{`, `[`
공백이 없는 괄호, 중괄호, 블록 괄호는 `)`, `}`, `]` 이다.

추가적으로 html 태그를 감싸는것도 가능한데, 예를들어서 `Hello World`가 있으면
앞 단어만을 `<p>`태그로 감싸려면 `ysiw<p>`
```
<p>Hello</p> world
```
그런데 문제는 이걸 다시 없애는 기능은 없다보다. 아마도 잘 안쓰이니 구현을 안한듯. 

한 문장 전체를 태그에 감싸는 기능도 있다. 우선 `V`로 전체 문장을 선택한 후, `S<p class="important">`
```
<p class="important">
<p>Hello</p> world
</p class="important">
```
이런식이다.


실전에서는 조오끔 팁이 필요한데,
예를 들어서 
```
Start-Process -FilePath $commander
```
이런식의 형태에서 마지막에 `$commander`를 double quote로 감싼다고 해보자.
이럴때에는 `ysiW`를 써야한다. 

또는, 예를들어서 위 문장에서 `-FilePath $commander` 부분만 감싸자고 하자. 
이럴때에는 이 부분을 비주얼 모드로 선택한 뒤, `S"`를 하면 된다.