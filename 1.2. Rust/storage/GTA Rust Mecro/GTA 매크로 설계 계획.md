- 키 이벤트 매핑은 rdev를 이용한다.
- 이미지 인식 및 프로세싱은 [[OpenCV를 깔기 위한 여정..|opencv]]를 이용한다.
- 아두이노의 하드웨어 입력을 이용한다. 이를 위해 serial를 이용한다.
- 인터페이스는 CLI로 구성한다. GUI는 사용하지 않을 생각이다.
매크로는 대략적으로 위의 3가지 핵심적인 라이브러리만 있으면 구현이 가능할거다. 
일단은 키 매핑을 처리하는걸 해야하는데.. 해보자.