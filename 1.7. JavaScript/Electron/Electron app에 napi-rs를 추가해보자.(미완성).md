napi-rs의 공식 홈페이지 [Getting started](https://napi.rs/docs/introduction/getting-started)와 이 [github page](https://github.com/dceddia/electron-napi-rs)를 참고했다.
우선 Electron app project를 만들어야 하므로 [[Building your First App|앞선 글]]을 참고하여 Electron 프로젝트를 만들어주자.

```
npm install -g @napi-rs/cli
npm install -g yarn
```
우선 `npm`을 이용하여 시스템에 이 두가지를 설치해야한다.

Electron project 위치에서 다음 명령어를 통해 napi-rs project를 만들어주자.
```
napi new
```
원래는 Electron project 위치에서 만들어도 되긴 하는데 몇가지 이상한 에러들이 발생해서 그냥 아예 다른 디렉토리에서 위 명령어로 따로 napi-rs project를 만든뒤 그걸 다시 electron project 폴더로 이동시켰다.
아예 다른 디렉토리에서는 아무런 문제없이 프로젝트가 잘 만들어진다. 아마도 `package.json` 이게 있으면 뭔가 안되나보다.
target을 설정할때에는 배포할 target만 골라서 해야하는데 일단은 그냥 해보자. 

[Getting started](https://napi.rs/docs/introduction/getting-started) 다음 글인 [A simple package](https://napi.rs/docs/introduction/simple-package)에서는 `cool` 이름으로 project를 만든다.
위에서 `napi new`를 통해 project를 생성했다면
```
cd cool
yarn install
yarn build
```
를 해주면
`cool` project 루트에 `index.js`가 생긴다.

기본적으로 만들어지는 기본 함수는 `sum`이다. 숫자 두 개를 넣으면 그 합을 반환하는 매우 간단한 함수가 들어있다. 이걸 테스트해보려면 
다음과 같이 `main.mjs`를 작성한다.
```js
import { sum } from './index.js'

console.log('From native', sum(40, 2))
```
그리고
```
node main.mjs
From native 42
```
이렇게 테스트 해볼 수 있다.

전체 프로젝트의 tree는 다음과 같다.
```
 .
├──  cool
│   ├──  build.rs
│   ├──  Cargo.lock
│   ├──  Cargo.toml
│   ├──  cool.win32-x64-msvc.node
│   ├──  index.d.ts
│   ├──  index.js
│   ├──  main.mjs
│   ├──  node_modules
│   ├──  npm
│   ├──  package.json
│   ├──  rustfmt.toml
│   ├──  src
│   ├──  target
│   └──  yarn.lock
├──  index.html
├──  main.js
├──  node_modules
├──  package-lock.json
├──  package.json
├──  preload.js
└──  renderer.js
```

이제 다시 Electron project 위치로 돌아와서 `package.json`에 다음과 같이 추가해준다.
```
  "dependencies": {
    "cool": "./cool"
  }
```

그리고 역시 Electron project에서
```
npm install
```