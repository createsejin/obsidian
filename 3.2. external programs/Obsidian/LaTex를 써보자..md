$1 \leq x \rightarrow x^2+2x-1 = 0$ 
$$
\begin{aligned}
x^2&+x\times-3+6=0 \\
x^2&-3x+6=0
\end{aligned}
$$
수학을 이해하는데 있어서 매우매우 도움이 되는 도구 중 하나이다. 아마도 왠만한 수학적 심볼, 수식은 전부 될껄?
전부 된다. 안되는게 없다. 게다가 이제는 Latex가 기본적으로 옵시디언에서 직접 지원이 된다.
여기에다가 그래프같은것들은 GeoGebra에서 긁어올 수 있다.
[LaTex 수식 작성법 정리](https://velog.io/@jhjangjh/LaTex-%EC%88%98%EC%8B%9D-%EC%9E%91%EC%84%B1%EB%B2%95-%EC%A0%95%EB%A6%AC)
[Wiki LaTex 문법](https://ko.wikipedia.org/wiki/%EC%9C%84%ED%82%A4%EB%B0%B1%EA%B3%BC:TeX_%EB%AC%B8%EB%B2%95)
<iframe scrolling="no" title="중2-p.253 사각형 넓이 등분하기" src="https://www.geogebra.org/material/iframe/id/wcmzxkkv/width/2752/height/966/border/888888/sfsb/true/smb/false/stb/false/stbh/false/ai/false/asb/false/sri/false/rc/false/ld/false/sdz/false/ctl/false" width="2752px" height="966px" style="border:0px;"> </iframe>
뭐 이런식이다. 놀랍게도 가능하다. 물론 기능은 조금 제한적이기는 하다. 
그러나 이런식으로 그래프를 불러올수도 있고. 너므나도 좋지 않은가. 

## 한가지 팁: 수식 왼쪽 정렬하기
다음과 같이 한다.
```
\begin{flalign*}
3x + y =&\ 1+2 \\ 
3x+2y =&\ 2+3 
&&
\end{flalign*}
```
여기에서 `&` 하나는 정렬 기준이 되는 기호 오른쪽에 쓰고, `\ `는 띄어쓰기이며, `\\`는 줄바꿈이다.
왼쪽 정렬을 하려면 반드시 줄바꿈 끝에 `&&`를 써야한다.
$$
\begin{flalign*}
3x + y =&\ 1+2 \\ 
3x+2y =&\ 2+3 &&
\end{flalign*}
$$
따라서 다음의 템플릿을 메모앱에 저장해두고 사용해야겠다.
```
$$
\begin{flalign*}

&&
\end{flalign*}
$$
```

이 외에도 수식을 편하게 쓰려면 수식의 기본 구조가 미리 정의된 템플릿을 하나씩 만들어서 쓰는게 좋아보인다.