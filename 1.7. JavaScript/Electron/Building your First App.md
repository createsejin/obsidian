[문서](https://www.electronjs.org/docs/latest/tutorial/tutorial-first-app)

Project directory를 만들고 그곳으로 이동,
```
npm init
npm install electron --save-dev
```
나는 그냥 `type`을 `commonjs`로 했다.
`main`을 뭘로 할거냐 물어보는데 `index.js` 대신 `main.js`로 입력해주자. 이것 이외에는 그냥 default값으로 넘기면 된다.

`package.json`에서 `"scripts"` 섹션에 다음과 같이 `"start": ...`를 추가해준다.
```json
  "scripts": {
    "start": "electron .",
    "test": "echo \"Error: no test specified\" && exit 1"
  },
```

`.gitignore`를 작성해야하는데, [이곳](https://github.com/github/gitignore/blob/main/Node.gitignore)에서 그대로 복사해서 붙여넣으면 된다.

튜토리얼 대로 `main.js`를 만들고 `index.html` 페이지를 만들고 다음 명령어를 통해 실행한다.
```
npm run start
```

또한 VSCode에서 디버깅을 할 수 있는데, 가이드에 나온대로 `.vscode/launch.json`을 만들어야 하는데, VSCode에서 왼쪽 툴바에서 디버그 툴을 눌러주고 'create a launch.json file'을 눌러주고 다음 내용을 복사 붙여넣기 해준다.
```json
{
  "version": "0.2.0",
  "compounds": [
    {
      "name": "Main + renderer",
      "configurations": ["Main", "Renderer"],
      "stopAll": true
    }
  ],
  "configurations": [
    {
      "name": "Renderer",
      "port": 9222,
      "request": "attach",
      "type": "chrome",
      "webRoot": "${workspaceFolder}"
    },
    {
      "name": "Main",
      "type": "node",
      "request": "launch",
      "cwd": "${workspaceFolder}",
      "runtimeExecutable": "${workspaceFolder}/node_modules/.bin/electron",
      "windows": {
        "runtimeExecutable": "${workspaceFolder}/node_modules/.bin/electron.cmd"
      },
      "args": [".", "--remote-debugging-port=9222"],
      "outputCapture": "std",
      "console": "integratedTerminal"
    }
  ]
}
```

이렇게 하면 디버깅도 잘 먹힌다. 참고로 이렇게 설정해두면 `Main`과 `Renderer` 따로 디버깅 하거나 같이 디버깅하는게 가능한 것으로 보인다.