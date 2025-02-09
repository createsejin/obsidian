역시나 오늘도 삽질을 했다. 역시나 Electron의 `main.js`와 `preload.js`의 정확한 차이점과 한계를 분명히 알아야했다. 요약하자면 `main.js`는 Electron application의 Entry Point로써 역할을 하게 되고, 이곳에서는 모든 node.js의 기능들이 허용된다. 그러나 `preload.js`나 `rendered.js` 처럼 사용자 화면을 구성하는 스크립트는 `main.js`에서 `BrowserWindow`의 properties를 config할 때 `webPreferences`의 `nodeIntegration` 옵션을 `false`로 할 경우, User side의 두 script는 상당히 제약적인 node.js 기능에만 접근할 수 있게 된다. node.js의 모든 기능들이 User side의 script에서 허용될 경우 심각한 시스템 악성 코드가 실행 될 수 있기 때문에 이것을 방지하는 차원에서 이렇게 한 것으로 보인다.
즉, `preload.js`에서 `const nativeModule = require('../index.node')`와 같이 직접적으로 `require`을 통해 Neon의 `index.node`에 접근 할 수 없게된다.

따라서 사용자 페이지에서 `main.js`의 어떤 기능을 호출하기 위해 `contextBridge`라는 것을 사용해야한다. Electron에서는 이것을 IPC(Internal-process Communication)이라고 부르고 있으며, `main.js`에서는 
```js
const { app, BrowserWindow, ipcMain } = require('electron')
const path = require('path')
const nativeModule = require('../index.node')

app.whenReady().then(() => {
  ipcMain.handle('getCpus', () => nativeModule.get())
  createWindow()
  ...
```
이런식으로 `ipcMain.handle`을 통해 위 예시에서는 `getCpus`라는 메세지가 오면 Neon의 Rust native 함수인 `nativeModule.get()`을 호출하는 handler를 설정할 수 있다.
이것을 다음과 같이 `preload.js`에서 IPC messaging을 통해 `main.js`에서 설정한 함수(Neon을 이용한 rust 함수)를 호출할 수 있도록 노출시킨다.
```js
const { contextBridge, ipcRenderer } = require('electron')

contextBridge.exposeInMainWorld('native', {
  get: () => ipcRenderer.invoke('getCpus')
})
```
이런식으로 설정해두면 이제 `rendered.js`에서는 다음과 같이 
```js
window.addEventListener('DOMContentLoaded', () => {
  ...
  func()
})

const func = async () => {
  const numberOfCPUs = await window.native.get()
  const numberOfCPUsElement = document.getElementById('number-of-cpus')
  numberOfCPUsElement.innerText = numberOfCPUs
}
```
`await window.native.get()`을 통해 호출하는데, 여기에서 `get()`은 `preload.js`의 `contextBridge.exposeInMainWorld` 에서 미리 정해둔 `get:` 이것이며, `.native`는 역시 `contextBridge.exposeInMainWorld`에서 첫번째 매개변수로 넘겨지는 `apikey`를 가리킨다. 이렇게 호출되면 `contextBridge.exposeInMainWorld`에서 `get:`에 지정한 `getCpus` 메세지를 `main.js`에서 정해둔 규약인 `ipcMain.handle('getCpus' `에 따라 
`ipcMain.handle('getCpus', () => nativeModule.get())` 의 함수 `nativeModule.get()`을 호출하는 것이다.
이렇게 설명만 해서는 사실 나도 나중에 이걸 읽으면 알아 들을 수가 없기 때문에 `apikey`라던가 `message`는 어떤게 오가는가, 어떤 함수가 호출되는가 등을 중점적으로 스스로 점검할 필요가 있다.
