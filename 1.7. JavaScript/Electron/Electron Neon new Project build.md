기본적으로는 [이 포스트](https://medium.com/nerd-for-tech/how-to-use-rust-inside-your-electron-application-using-neon-bindings-64bd83fec316)를 참고했지만 포스트가 조금 오래됐기 때문에 [[Electron with Neon IPC|Electron의 IPC]]를 기본적으로 알고 있어야한다.
일단 당연히 Rust, Node.js가 설치되어야한다. 
또, `npm`을 이용해서
```
npm install -g yarn
```
`yarn`을 설치해주자. `yarn`은 `npm`같은 Javascript package manager라고 한다. [yarn](https://yarnpkg.com/)

## Neon part
다음 명령어를 통해 새로운 Neon Project를 만들 수 있다.
```
npm init neon neon-electron
```

`cargo.toml`을 다음과 같이 수정해준다.
```toml
[package]
name = "neon-electron"
version = "0.1.0"
license = "ISC"
edition = "2021"
exclude = ["index.node"]

[lib]
crate-type = ["cdylib"]

# See more keys and their definitions at https://doc.rust-lang.org/cargo/reference/manifest.html

[dependencies.neon]
version = "1"
default-features = false
features = ["napi-6"]

[dependencies]
num_cpus = "1"
```
튜토리얼에서는 현재 시스템의 CPU의 코어 개수를 출력하는걸 예제로 하고 있기 때문에 `num_cpus`라는 crate가 사용되었다.
그리고
```
yarn
```
을 해주면 dependencies를 자동으로 설치해준다.

다음으로 `src/lib.rs`를 다음과 같이 수정한다.
```rust
use neon::prelude::*;

fn get_num_cpus(mut cx: FunctionContext) -> JsResult<JsNumber> {
  Ok(cx.number(num_cpus::get() as f64))
}

#[neon::main]
fn main(mut cx: ModuleContext) -> NeonResult<()> {
    cx.export_function("get", get_num_cpus)?;
    Ok(())
}
```
Neon에서는 저 `cx`라는게 거의 무조건 필수적으로 들어간다고 보면 된다. 조금 짜증나긴 하지만 어쩔 수 없다.
위 예시에서는 `num_cpus::get()` 함수를 통해 CPU 개수를 얻고 있으며, 이것을 `f64`로 캐스팅해줘야한다. 그래야 Javascript number type으로 변환할 수 있단다.
Return type은 `JsResult<JsNumber>` 이다.

`main` 함수는 `#[neon::main]` macro를 달고, 역시 `cx: ModuleContext`가 매개변수로 사용되며, `NeonResult<()>`를 리턴 타입으로 한다. `cx.export_function`을 통해 `get_num_cpus` 함수를 `"get"`이라는 이름으로 매핑할 수 있다.
이 이름은 [[Electron with Neon IPC|이 글]]에서  `main.js`에서 `const nativeModule = require('../index.node')`을 통해 import되어 `ipcMain.handle('getCpus', () => nativeModule.get())`에서 `.get()` 이것에 사용되는 이름이라고 보면 된다. 자세한건 앞에 제시한 링크의 글에서 확인하자.

```
yarn add -D cargo-cp-artifact
yarn add -D electron
```
이 두가지 dependencies가 필요하다.

그리고 `package.json`에서 `"script"` 부분에서 `"build"`를 수정하고 `"dev"`와 `"install"` 명령어를 설정해준다.
```json
  "scripts": {
    ...
    "build": "cargo-cp-artifact -nc index.node -- cargo build --message-format=json-render-diagnostics",
    "dev": "electron ./src/main.js",
    "install": "npm run build"
  },
```

이제 다음 명령어를 통해 Neon Project를 빌드해보자.
```
npm run build -- --release
```
그러면 Project root에 `index.node`라는 파일이 생긴다. 이것이 electron의 `main.js`에 import 해야하는 핵심적인 파일이다.

## Electron part
이제 `src/main.rs`를 만들어보자. 이것은 Electron의 [Building your First App](https://www.electronjs.org/docs/latest/tutorial/tutorial-first-app)과 거의 같다.
```js
// Modules to control application life and create native browser window
const { app, BrowserWindow, ipcMain } = require('electron')
const path = require('path')
const nativeModule = require('../index.node')

function createWindow () {
  // Create the browser window.
  const mainWindow = new BrowserWindow({
    width: 800,
    height: 600,
    webPreferences: {
      preload: path.join(__dirname, 'preload.js'),
      nodeIntegration: false,
      contextIsolation: true
    }
  })

  // and load the index.html of the app.
  mainWindow.loadFile('index.html')

  // Open the DevTools.
  // mainWindow.webContents.openDevTools()
}

// This method will be called when Electron has finished
// initialization and is ready to create browser windows.
// Some APIs can only be used after this event occurs.
app.whenReady().then(() => {
  ipcMain.handle('getCpus', () => nativeModule.get())
  createWindow()

  app.on('activate', function () {
    // On macOS it's common to re-create a window in the app when the
    // dock icon is clicked and there are no other windows open.
    if (BrowserWindow.getAllWindows().length === 0) createWindow()
  })
})

// Quit when all windows are closed, except on macOS. There, it's common
// for applications and their menu bar to stay active until the user quits
// explicitly with Cmd + Q.
app.on('window-all-closed', function () {
  if (process.platform !== 'darwin') app.quit()
})

// In this file you can include the rest of your app's specific main process
// code. You can also put them in separate files and require them here.
```

이 코드에서 중요한 부분을 뜯어보자.
```js
const { app, BrowserWindow, ipcMain } = require('electron')
```
여기에서 `ipcMain`은 `main.js`에서 IPC message handler를 만들어준다. 해당 코드는 밑 부분에서 확인할 수 있다.

```js
const nativeModule = require('../index.node')
```
이 부분은 Neon의 생성 파일인 `index.node`를 `nativeModule`이라는 변수명으로 불러온다. `src/main.js` 파일 기준이니 project root에 있는 `index.node`의 위치는 상대 경로로 `../index.node`가 된다.
주의할 점은 다음 코드에서 설명할 Electron의 특성인 `preload.js`나 `rendered.js`에서는 직접적으로 `require`을 통한 외부의 `index.node`같은 파일에 접근할 수 없다는 것이다.

이와 같은 특성은 다음의 코드에서 설정된다.
```js
function createWindow () {
  // Create the browser window.
  const mainWindow = new BrowserWindow({
    width: 800,
    height: 600,
    webPreferences: {
      preload: path.join(__dirname, 'preload.js'),
      nodeIntegration: false,
      contextIsolation: true
    }
  })
  ...
```
여기서 `nodeIntegration:`을 `false`로 설정하면 `preload.js`와 `rendered.js`는 제약적인 기능만을 갖게된다. 이는 [[Electron with Neon IPC|이 글]]에서 설명하듯이 보안적인 문제가 있으므로 반드시 이렇게 설정해주자.