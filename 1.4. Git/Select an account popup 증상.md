자꾸 계정 중 하나를 선택하라는 popup message 창이 뜨는 증상이다.

중복되는 자격 증명이 두 개 이상일때 뜨는 것 같다. 자세한건 [여기](https://velog.io/@ssm0725/GitHub-%EC%82%AC%EC%9A%A9-%EC%A4%91-Select-an-account-%EC%B0%BD%EC%9D%B4-%EB%9C%A8%EB%8A%94-%EA%B2%BD%EC%9A%B0)참조.
```powershell
cmd /c cmdkey /list:git*
```
이걸 조회하면 git 관련 자격 증명 리스트를 볼 수 있다.

[[windows god mode|갓 모드 폴더]]에서 검색창에 '자격 증명'을 친다. 'Windows 자격 증명'으로 들어간다.
중복되는 필요없는 자격 증명을 지워준다.