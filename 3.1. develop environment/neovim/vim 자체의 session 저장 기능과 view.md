vim은 자체적으로 session 저장 기능을 가지고 있었다. 다만 이것을 매 변화마다 자동으로 저장하는 기능을 Obsession이라는 plugin이 했을뿐이다. 그리고 또 한가지 중요한 기능은 view라는 건데, 이것은 기본적으로 한 윈도우에 소속된다. 예를 들어서 그 윈도우에서 일어난 거의 여러가지 일들을 저장하는데, 대표적으로 그 윈도우에 속한 argument list를 저장한다. 또한 fold같은 것들을 저장한다. 하여간 folding을 다시 불러올때 `lo[adview]`를 쓰는 경우가 많은데, 주의할점은 현재의 argument list를 이 파일의 mkview의 argument list로 대체된다는 것이다. 이것을 session 단위로 키운데 `:mks[ession]`기능이다. 기본적으로는 현재 작업 디렉토리에 `Session.vim`파일로 저장된다. 다시 load하려면 `nvim -S`으로 시작할 수 있다. 만약 특정한 이름으로 저장하고 싶으면 `:mks specific_session.vim` 이렇게 하면 된다. 여기에서 Obsession plugin을 이용하면 세션을 자동으로 매번 업데이드를 해준다는 것이다. 
하지만 세션이 항상 완벽한 것은 [[vim argment list tip and trick#Obsession을 다시 load할때 주의할점|아니다]]. 또한 `:lo`를 이용할때에는 특히 주의해야한다. 현재 window의 argument list가 다른 값으로 대체될 가능성이 농후하기 때문이다. 어쩌면 `:mkview`와 `:lo`를 이용해서 window 단위의 argument list를 저장하고 불러오는데에 아주 편리하게 사용할 수 있을것 같다.
어차피 한 윈도우의 view를 불러온뒤 그 윈도우를 split하면 그 윈도우들은 그 한 세션동안 동일한 arguement list를 공유하기 때문이다. `:mkview file`을 이용하면 현재 working directory에 특정한 이름으로 현재 윈도우의 view를 파일로 저장하고 불러올 수 있다.
```
au BufWinLeave *.c mkview
au BufWinEnter *.c silent loadview
```
이런 명령으로 자동화할 수는 있지만 그다지 유용해보이지는 않는다.

여러가지를 종합해볼때, mkview는 꽤나 쓸만하지만 자동 저장은 사실상 어렵기 때문에 쉽지 않다. 게다가 아무런 argu 없이 `:mkview`만 하면 그 파일 이름 기준으로 view가 저장되는데 이것도 썩 그닥이다.

## 결론
그냥 Obsession을 이용해서 현재 세션을 자동 저장하는게 가장 편해보인다. 그렇지만 되도록이면 vim의 기본 세션 기능의 [[argument를 유지하면서 mkvie!, lo 사용하기#^1|수동 저장 방식]]을 이용하는것이 안전하다.
loadview를 남용하지만 않으면 Obsession에서도 안전하게 argument를 보존할 수 있을것으로 보인다. 어차피 폴딩은 그 view에 저장되는것이라 window 관리[^1]만 잘 해주면 될 것으로 보인다. 그러나 argument와 folding을 모두 보존하는 [[argument를 유지하면서 mkvie!, lo 사용하기|방법]]이 있다.
view는 이따금씩 window에 속한 local argument list를 저장해줄때 아주 유용하게 쓰일것 같다.

[^1]: session을 불러올때 두 개 이상의 윈도우가 있으면 Ctrl+w, o를 통해 한 윈도우만 남기고 다시 split하는 기법을 말한다. 그 이유는 [[vim argment list tip and trick#Obsession을 다시 load할때 주의할점|이렇다]].