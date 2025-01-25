Zebar가 새로운 버전으로 리뉴얼 되면서 세팅 파일이 조금 복잡해졌다. 일단 가장 큰 문제는 Font였다.

Windows 기준으로, 일단 사용자 폴더에 들어간다.
그리고 `<user>\.glzr\zebar\starter\styles.css` 파일을 열어준다.

```css
body {
  color: rgb(255 255 255 / 90%);
  font-family: 'SauceCodePro Nerd Font', ui-monospace, monospace;
  font-size: 12px;
  overflow: hidden;
}
```
주목할 부분은 이 부분이다. 여기에서 `font-family` 부분에 자신이 원하는 폰트를 넣으면 된다. 

보통은 Nerd 폰트를 추천한다. 여러가지 아이콘이 필요하기 때문이다.
https://www.nerdfonts.com/font-downloads 이곳에서 다운받을 수 있고, 설치 뒤 재부팅을 하고 이 사이트에 기재된 이름을 `font-family` 로 지정하면 된다.