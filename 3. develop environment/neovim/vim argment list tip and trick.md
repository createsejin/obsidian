기본적으로 argment는 global arg, local arg가 있다. global arg는 말 그대로 global이다.
처음에 아무런 설정 없이 `arge`나 `arga`로 argment를 추가하면 그것은 global argument에 추가된다.

그런데 이걸 `argl`을 쓰면 그 window는 현재 global의 argument를 복사해서 그 윈도우에 속하는 local argument list를 만든다. 이렇게 되면 local argument list는 global argument list와 독립적으로 분리된다.
그런데 이 상태에서 같은 화면에 화면을 가로나 세로로 분리해서 새로운 panel을 만들면 그 panel은 원래 panel, 즉 , 원래의 window의 local arguement를 동일하게 공유하게 된다. 
그리고 이러한 동작 방식은 tab을 현재 window로부터 새로 만들때에도 적용된다.
예를들어서 현재 window가 local arguement일때 새로운 tab을 만들면, 새로운 tab 역시 원래 window의 local arguement를 공유하게된다. 이때 새로운 tab에서 다시 `argg`를 쓰면 그 탭은 다시 global argument로 되돌아간다. 이 때 다시 `argl`을 쓰면 그 탭은 새로운 독립적인 local argument list가 만들어진다. 

즉, argument list는 기본적으로 global argument list로 다루어지며, 만약 global argument를 쓰는 window가 새로운 윈도우로 패널이 분리되거나 새로운 탭이 만들어지면 그 역시 동일한 global argument list를 가지게된다. 이와 동일한 원리로, 원래 window가 local argument list를 가졌다면, 이때에도 분리되거나 새로운 탭은 같은 local argument list를 가지게된다.

가장 이로운 시나리오는 먼저 global argument에 현재 workspace에서 다룰 모든 파일을 load하고, 각 탭 마다 윈도우에 `argl` 명령을 이용하여 local argument list를 독립적으로 할당해주고 탭을 만들때 마다 `argl` 명령어를 사용하여 탭 단위의 서로 다른 local argument list를 운용하는게 가장 이상적으로 보여진다.

또한 Obsession과 같은 자동 session 저장 plugin을 이용하면 현재 모든 tab들의 argument list를 항상 자동으로 저장해준다. 그리고 Obsession의 장점은 같은 세션을 여러 독립적인 vim instance들로 같이 사용해도 문제없이 저장된다는것. 그러나 주의할점은 항상 가장 마지막에 종료한 vim session의 상태가 마지막으로 기록된다는 것이다. 예를 들어서 같은 session 파일로 연 vim instance가 3개이고 1번 2번 3번이라고 할때 1번에서 여러 작업을 하고 2번에서 여러작업을 하고 3번에서 또 여러작업, 이때 서로 다 다른 작업을 했을때 1, 2, 3 으로 닫았을때 실제로 저장되는 세션은 마지막으로 닫은 3번 session이 저장된다.
그러므로 같은 workspace에서 여러 독립적 인스턴스의 vim을 운용하려면 서로 다른 session 파일을 만들어서 recording 해야한다는 것이다. 이렇게 하면 서로 다른 인스턴스들의 모든 세션이 자동으로 저장된다. Obsession plugin은 이것이 가능하다. 또한 Obsession의 최대 장점은 tmux 위에서 nvim을 사용할때 발휘되는데, tmux에서 세션을 저장하면 tmux 안에서 연 nvim의 세션까지 모두 자동으로 복원해준다는 것이다. 이것은 아주아주 강력한 기능이다.