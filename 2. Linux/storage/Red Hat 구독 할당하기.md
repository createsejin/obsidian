`subscription-manager list --available`를 실행하고 root 비밀번호를 입력하면 구독 가능한 목록이 나온다.
나는 개인 개발자용 red hat을 사용중이므로
`Subscription Name:   Red Hat Developer Subscription for Individuals`이걸 쓸거다.
이것의 Pool ID를 복사해준다.

```
sudo subscription-manager attach --pool=2c9472d88dad3cd0018dba39ee5e6e82
Ignoring the request to attach. Attaching subscriptions is disabled for organization "17700355" because Simple Content Access (SCA) is enabled.
```
근데 SCA가 활성화되어있으면 시스템에 구독을 attach할 필요는 없다고 한다.


