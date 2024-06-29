`code $profile`
```
# 콘솔 입출력 인코딩 UTF-8로 변경
[Console]::InputEncoding = [Console]::OutputEncoding = [System.Text.Encoding]::UTF8
# 기본 인코딩 UTF-8로 설정
$PSDefaultParameterValues['*:Encoding'] = 'utf8'
```
