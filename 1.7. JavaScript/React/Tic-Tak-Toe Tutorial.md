이 [가이드](https://react.dev/learn/tutorial-tic-tac-toe)를 따라 했다.
중간에 보면 node.js의 `npm`을 이용해서 로컬에서 리엑트 페이지를 띄우게 할 수 있는 방법이 있다.
일단 가이드 내 codepen을 'Fork'를 통해 브라우저 코드 에디터로 들어간뒤, 맨위 왼쪽 구석에 네모가 있다. 이걸 클릭하고 'Download Sandbox'를 누르면 zip 파일이 하나 다운로드 되는데, 이걸 project 폴더 적당한곳에 풀어준다. 

그리고 `npm install`을 해주면 디펜던시들을 설치해주는데, 문제는 에러가 뜰것이다. 
```bash
┌─[bae@Main]-[~/projects/react_study1/TicTakToe2]-[Thu Jan 23, 10:21]
└─[$]> npm install
npm error code ERESOLVE
npm error ERESOLVE unable to resolve dependency tree
npm error
npm error While resolving: react.dev@0.0.0
npm error Found: react@19.0.0-rc-3edc000d-20240926
npm error node_modules/react
npm error   react@"19.0.0-rc-3edc000d-20240926" from the root project
npm error
npm error Could not resolve dependency:
npm error peer react@">= 16" from react-scripts@5.0.1
npm error node_modules/react-scripts
npm error   react-scripts@"^5.0.0" from the root project
npm error
npm error Fix the upstream dependency conflict, or retry
npm error this command with --force or --legacy-peer-deps
npm error to accept an incorrect (and potentially broken) dependency resolution.
npm error
npm error
npm error For a full report see:
npm error /home/bae/.npm/_logs/2025-01-23T01_22_04_927Z-eresolve-report.txt
npm error A complete log of this run can be found in: /home/bae/.npm/_logs/2025-01-23T01_22_04_927Z-debug-0.log
```
뭐 이런 에러들이다. 해결 방법으로는 추가적인 커맨드인 `--force`나 `--legacy-peer-deps`를 사용하는 방법이 있다. 
나는 그냥 `--force`를 사용했다.
```
npm install --force
```
이렇게 해도 `npm warn deprecated` 등의 수많은 warning이 뜨지만 어쨌거나 다음 명령어가 먹힌다.
```
npm start
```
WSL의 경우 VScode에서 해당 프로젝트 폴더를 연 뒤에 VSCode 터미널에서 `npm start`를 해주면 Windows의 기본 웹 브라우저에 페이지를 띄워준다. 물론 이것은 VSCode의 WSL Extension 이 있어야할것이다.