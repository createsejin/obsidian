우선 `npm`, `npx`가 필요하므로 node.js를 설치해주자. WSL Arch Linux에 설치해주었다.
그리고 Next.js에서 권장하는 `pnpm` 패키지 매니저를 `npm`을 통해 설치해야한다.
```
sudo npm install -g pnpm
```

`pnpm`이 설치됐으면 이제 Next.js 프로젝트를 생성해야한다.
```
npx create-next-app@latest
```
프로젝트 루트로 들어가서 다음 명령어를 통해 프로젝트에 필요한 의존성 패키지들을 설치해주자.
```
pnpm i
```
다음의 명령어로 개발 서버를 start할 수 있다.
```
pnpm dev
```

보통은 다음과 같이 두 가지 경로로 서버에 접근할 수 있다.
```
   - Local:        http://localhost:3000
   - Network:      http://192.168.50.98:3000
```
