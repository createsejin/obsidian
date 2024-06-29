```powershell
Start-Process -FilePath "manage-bde" -Wait -ArgumentList "-lock Q:" -Verb RunAs
```
이런식으로 해주면 된다. 다만 여기서 주의할점은 `-NoNewWindow` 옵션을 사용해서는 안된다. 만약 현재 쉘이 일반 권한이라면 이 옵션을 사용할 경우 에러가 발생한다. 
끝 옵션인 `-Verb RunAs`가 이 process를 관리자 권한으로 실행하게 해준다.
그러나 이렇게 할 경우 쉘에서 실행하는게 아닌 그냥 `manage-bde` 프로그램 자체를 실행하게 된다.

만약 powershell과 windows terminal 위에서 실행하게 하려면 [[wt 명령어 기본|wt 명령어]]를 사용해서 다음과 같이 해줄 수 있다.
```powershell
Start-Process -FilePath "wt" -Wait -ArgumentList "pwsh -c manage-bde -lock Q:" -Verb RunAs
```
`wt`는 windows terminal의 실행파일이고, `pwsh`은 powershell을 쉘로 실행하게 한다. `-c` 뒤에는 실행할 커맨드를 지정해줄 수 있다. 

`Start-Process`에 대한 자세한 사항은 이 [문서](https://learn.microsoft.com/en-us/powershell/module/microsoft.powershell.management/start-process?view=powershell-7.4)를 참고해보자.
`manage-bde`는 이 [문서](https://learn.microsoft.com/en-us/windows-server/administration/windows-commands/manage-bde-unlock)를 참고하자.