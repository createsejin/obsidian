마지막 100줄만 보기:
`journalctl -u sshd -n 100`

실시간으로 로그 following 하기
`journalctl -fu sshd`

특정 시간 범위의 로그 보기
`journalctl -u ssh --since "2024-05-11 10:00:00`
여기서 `--since`를 사용하면 그 이후의 로그를 볼 수 있고, `--until` 옵션을 사용하면 그 이전을 볼 수 있다.
