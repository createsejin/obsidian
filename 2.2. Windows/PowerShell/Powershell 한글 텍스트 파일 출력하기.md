```
Get-Content -Encoding UTF8 "파일명.txt"
```
이 명령어를 사용하자.
```
Get-Content -Encoding UTF8 "파일명.txt" | Select-Object -Skip 10 -First 20
```
이런식으로 하면 처음에 10번째 줄까지 건너뛴 후 그 이후에 20번째 줄까지만 출력한다.
SQLite의 limit offset과 비슷하다.

그런데 이건 그냥 [[bat 설치 및 테마 설정|bat]] 쓰면 되잖아.