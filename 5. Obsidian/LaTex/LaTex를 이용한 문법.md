만약 라텍스로 그래프까지 그릴 수 있다면 완벽하게 수학을 옵시디언에서 타자치며 할 수 있겠는데 ㅋㅋ 그럴 수 없을까. ㅋㅋ
```tikz
\begin{document}
  \begin{tikzpicture}[domain=0:4]
    \draw[very thin,color=gray] (-0.1,-1.1) grid (3.9,3.9);
    \draw[->] (-0.2,0) -- (4.2,0) node[right] {$x$};
    \draw[->] (0,-1.2) -- (0,4.2) node[above] {$f(x)$};
    \draw[color=red]    plot (\x,\x)             node[right] {$f(x) =x$};
    \draw[color=blue]   plot (\x,{sin(\x r)})    node[right] {$f(x) = \sin x$};
    \draw[color=orange] plot (\x,{0.05*exp(\x)}) node[right] {$f(x) = \frac{1}{20} \mathrm e^x$};
  \end{tikzpicture}
\end{document}
```
아니 이게 된다고??.. 미쳤따... 크아.. 이거만 가능하면 나 진짜 타자로 고수 수학 쌉가능?? 와.. 미친 ㅋㅋ
# [Obsidian TikZJax](https://github.com/artisticat1/obsidian-tikzjax/blob/main/README.md#obsidian-tikzjax)
여기 가면 할 수 있는 예들이 많다. 연습해보자. 언젠가는..
