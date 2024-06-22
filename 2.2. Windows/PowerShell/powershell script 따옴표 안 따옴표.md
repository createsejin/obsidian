```powershell
    Start-Process -FilePath "$bz" -Wait `
    -ArgumentList "x -aos -y -cp:65001 -target:name -consolemode:utf8 `"$archive`""
```
이런식으로 안 따옴표에는 앞에다가 백틱을 붙이면 된다.