.NET에서는 자동 구현 속성(Auto-Implemented Properties)을 사용하여 getter와 setter를 쉽게 구현할 수 있습니다. 이 방식은 일반적으로 권장되는 getter/setter 구현 방법입니다.

자동 구현 속성을 사용하면 다음과 같이 간단하게 구현할 수 있습니다:

```csharp
private ConcurrentQueue<string> _commandQueue;

public ConcurrentQueue<string> CommandQueue
{
    get { return _commandQueue; }
    set { _commandQueue = value; }
}
```

이렇게 구현하면 컴파일러가 자동으로 private 백킹 필드 `_commandQueue`와 getter/setter 메서드를 생성합니다. 이를 통해 외부에서는 `CommandQueue` 속성을 통해 `_commandQueue` 멤버 변수에 접근할 수 있습니다.

이 방식의 장점은 다음과 같습니다:

1. 간단하고 간결한 구문으로 getter/setter를 정의할 수 있습니다.
2. 필요에 따라 getter/setter 메서드의 동작을 커스터마이징할 수 있습니다.
3. 코드 가독성이 높아집니다.

대부분의 경우에는 이와 같은 자동 구현 속성을 사용하는 것이 가장 일반적인 getter/setter 구현 방법입니다. 필요에 따라 추가적인 로직이 필요한 경우에는 직접 getter/setter 메서드를 구현할 수도 있습니다. 

이런 자료를 참고했어요.
[1] 티스토리 - [C#] public 필드 vs 자동 구현 프로퍼티 비교 분석 - 장난감 연구소 (https://constructionsite.tistory.com/38)
[2] TISTORY - C# 프로퍼티(Property)란? (사용하는 이유 / Java get set) (https://jeongkyun-it.tistory.com/23)
[3] KLDP - get/set 메소드와 public 멤버변수 (https://kldp.org/node/89756)
[4] 네이버 블로그 - 자바(Java) Getter,Setter,ToString 메써드(Method) : 네이버 블로그 (https://m.blog.naver.com/pjok1122/221500925213) 

.Net에서 흔히 properties로 불려지는 아이들이 이런 애들이다. 저런식으로 getter와 setter를 이용해서 접근 가능한 멤버를 가리키는 명칭이라는 것.