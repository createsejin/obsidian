[여기](https://trac.ffmpeg.org/wiki/Scaling)에 자세한 사용 방법이 나와있다.
```
ffmpeg -i 'input.jpg' -vf scale=300:-1 output.png
```
최대 품질로 출력하려면 output file을 비손실 압축 포맷인 png 형식으로 출력하는게 좋다.

```
ffmpeg -i "input.jpg" -vf "scale=w=300:h=216:force_original_aspect_ratio=decrease" "output.png"
```
이 명령어는 320x240 박스 크기에 자동으로 맞춰서 resize를 해준다. 예를들어 위아래로 긴 이미지는 높이를 240에 맞춰서 가로 크기를 알아서 맞춰주고, 너비가 넓은 이미지는 가로 320에 맞춰서 높이를 조절해준다. 이것은 썸네일을 만드는 명령어로 적합할 것이다.

```
ffmpeg -i "input.jpg" -vf "scale=w='min(300,iw)':h='min(216,ih)':force_original_aspect_ratio=decrease" "output.png"
```
이 명령어에는 `min` 함수와 `iw`, `ih`를 이용해서 이것보다 작은 사이즈의 이미지가 있는 경우 그 크기를 upscaling하지 않게끔 하고있다.