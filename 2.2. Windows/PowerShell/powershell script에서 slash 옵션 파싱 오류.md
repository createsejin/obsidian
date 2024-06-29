```
ParserError: C:\Users\creat\mydoc\scripts\.pwsh\pack.ps1:17
Line |
  17 |      $veracrypt /q /d M
     |                  ~
     | You must provide a value expression following the '/' operator.
```

veracrypt.exe의 파라미터의 경우 `/q` 처럼 slash 기반의 option indicator를 사용하고 있다. 이런 경우에 `.ps1`파일에 이런식으로 그냥 쓰게 되면 powershell은 이것을 나누기 연산자 `/`로 오인 파싱하여 파싱 에러를 내뱉게 된다. 

이것을 방지하려면 
```powershell
Start-Process -FilePath "$veracrypt" -Wait -NoNewWindow -ArgumentList "/q /d M"
```
이런식으로 해주면 된다. 