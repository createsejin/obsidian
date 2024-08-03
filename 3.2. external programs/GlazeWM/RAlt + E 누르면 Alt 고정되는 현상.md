도대체 왜 그러는지 이유를 전혀 알 수 없지만 RAlt + E를 누르면 Alt가 고정되어버린다. 
푸는 방법은 win 버튼 클릭해서 검색창에서 한영키 바꾸고 글자를 쓰면 풀린다. 
LAlt + E를 눌렀을때에는 이런 현상이 없다. 도대체 왜 그러는건지는 모르겠다. 아마도 뭔가 GlazeWM 세팅때문일 수도 있고. 한번 [[GlazeWM KeyBinds|키]]를 싹 바꾼다음에 테스트를 해야할지도..
일단 다른키들은 테스트 해보면 문제가 없었다. 

범인은 여기 있었다..
```yaml
  - command: "focus workspace every"
    bindings: ["RMenu+E", "HangulMode+E"]
```
GlazeWM에서 이런식으로 binding을 설정할 경우 해당 키를 누르면 Alt가 고정된다. 이상한건 다른 RAlt + T 같은 애들은 정상적이라는것. RAlt + E 만 문제가 되는것 같다.
문제는 이것 뿐만이 아니라 `RAlt + E`를 포함하는 키바인딩이 있으면 또 그게 문제가 된다는 것이다. 정말 알송달송하다.. 

근데 꼭 그것도 아니었다. 내가 한가지 찾은 원인 중 하나는, 만약 예를들어서 오른쪽 모니터에서 Everything workspace를 띄웠는데 그 상태에서 Everything 프로그램을 실행하는 시도가 실패하면 Alt가 고정된다. 그리고 이 Everything workspace가 가장 오른쪽에 위치한 상태여야한다. 아마도 한글일때 프로그램 실행 시도가 실패되는것 같다. 

그냥 프로그램 실행키가 실패하거나, focus 전환이 실패하면 Alt가 고정되는 것 같다. 

해결방법은 그냥 focus workspace랑 exec 명령을 사용할때 Alt 키를 사용하지 않는것이다. 
나는 이걸 Tab이랑 Tab+Shift로 바꿔보았다. 아직까지는 괜찮은것 같다. 