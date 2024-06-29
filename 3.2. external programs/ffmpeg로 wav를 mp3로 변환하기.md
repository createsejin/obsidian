```powershell
ffmpeg -i "$input" -b:a 192k -q:a 2 -ar 44100 -ac 2 -acodec libmp3lame `
-vn -map_metadata 0 -id3v2_version 3 "$output"
```

1. `-i "$input"`: 입력 파일 지정
2. `-b:a 192k`: 오디오 비트레이트를 192kbps로 설정
3. `-q:a 2`: 오디오 품질 설정 (2는 중간 품질)
4. `-ar 44100`: 샘플링 레이트를 44.1kHz로 설정
5. `-ac 2`: 2채널 (스테레오) 오디오로 설정
6. `-acodec libmp3lame`: MP3 인코더로 LAME 라이브러리 사용
7. `-vn`: 비디오 스트림 제외
8. `-map_metadata 0`: 메타데이터 복사
9. `-id3v2_version 3`: ID3v2.3 태그 사용
10. `"$output"`: 출력 파일 지정