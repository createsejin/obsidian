`wt [options] [command] ; [command]`
보통은 이렇게 쓰인다.

```
wt -w 0 sp -[V|H] pwsh
wt -w 0 sp -V
wt -w 0 sp -H
```
현재 윈도우에서 창을 vertical로 분할하거나 horizon으로 분할한다.

```
wt -w 0 sp -V pwsh -c program.exe
```
현재 윈도우에서 창을 vertical로 분할하고 분할한 창에서 powershell로 `program.exe`를 실행하고 프로그램이 종료되면 창을 닫는다. 

```
wt -w 0 nt pwsh -c ls
```
현재 윈도우에서 새로운 탭을 생성하고 powershell로 `ls`명령을 실행하고 완료되면 창을 닫는다.

```
wt pwsh -c ls
```
새로운 윈도우에서 명령을 실행하고 완료시 창을 닫는다.