PowerShell의 `Remove-Item` 명령어는 파일, 폴더, 레지스트리 키, 변수, 별칭, 함수 등 다양한 항목을 삭제하는 데 사용됩니다¹. 

다음은 `Remove-Item`의 주요 매개변수입니다¹²:
- `-Path`: 삭제할 항목의 경로를 지정합니다.
- `-LiteralPath`: 항목의 정확한 경로를 지정합니다.
- `-Include`: 포함할 경로 요소를 지정합니다. 예: `*.txt`
- `-Exclude`: 제외할 경로 요소를 지정합니다. 예: `*.txt`
- `-Recurse`: 지정된 위치와 모든 하위 폴더의 항목을 삭제합니다.
- `-Force`: 읽기 전용 파일이나 숨겨진 항목을 삭제하는 데 사용됩니다.
- `-Confirm`: 삭제를 확인하도록 요청합니다.
- `-WhatIf`: 실제로 항목을 삭제하지 않고, 어떤 작업이 수행될 것인지 보여줍니다.

현재 폴더와 그 하위 폴더에 있는 모든 항목을 삭제하려면 `-Recurse` 매개변수를 사용해야 합니다. 다음은 그 예시입니다:

```powershell
Remove-Item .\* -Recurse
```

위의 명령어는 현재 디렉토리(`.\`)와 그 하위 디렉토리의 모든 파일과 폴더를 삭제합니다.

다른 예시들은 다음과 같습니다¹:

- 특정 확장자를 가진 모든 파일 삭제: `Remove-Item C:\Test\*.* -Include *.doc`
- 읽기 전용 파일 삭제: `Remove-Item -Path C:\Test\hidden-RO-file.txt -Force`
- 하위 폴더의 특정 확장자를 가진 파일 삭제: `Get-ChildItem * -Include *.csv -Recurse | Remove-Item`

이 명령어를 사용할 때는 주의가 필요합니다. `-Confirm` 또는 `-WhatIf` 매개변수를 사용하여 실제로 파일을 삭제하기 전에 확인하거나 예상 결과를 확인하는 것이 좋습니다².

