system backup 요소는 크게 3가지다. root 시스템 파일, boot 파일, home config 파일.
이 3가지를 모두 한꺼번에 백업을 하고 한꺼번에 복원을 해야 시스템이 올바르게 동작한다.

가장 쉬운 방법으로는 LVM snapshot을 이용하는 방법이 있다. 그러나 이 경우에는 boot를 백업 할 수 없으며(EFI partition, 즉 LVM이 아니다), home의 경우에는 통채로 백업을 해야해서 Documents나 Projects가 이전 버전으로 같이 복원되버리는 side effect가 발생하게 된다. 
따라서 snapshot을 이용하는 경우에는 우선 /boot 파일을 root 내부로 별도 백업 directory에 넣어서 같이 root snapshot을 찍어두는게 좋다. 이 경우에는 가능한 옵션으로는 home의 config 파일들을 같이 root에 넣어서 root snapshot을 찍으면 home 까지 백업이 가능하게 된다.
복원 프로세스는 [[LVM snapshot system rollback process|이 글]]을 참고하자.

다른 방법으로는 bsdtar와 pbzip2를 이용하는 방법이 있다. 