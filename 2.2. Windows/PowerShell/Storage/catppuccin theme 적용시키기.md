[git repo](https://github.com/catppuccin/powershell)로 가자.
```
$env:PSModulePath
```
powershell에서 위 명령어를 치면 경로가 나온다. 아마도 `modules` 폴더가 없을것이니 만들어주자. 
나는 `C:/Users/creat/OneDrive/문서/PowerShell/Modules` 위치에 만들었다.
이 위치로 가서 `git clone https://github.com/catppuccin/powershell`를 해주자.
그리고 그 이름을 `Catppuccin`으로 바꾸자.

그리고 `code $PROFILE` 을 통해 파일을 열어서 다음을 추가해준다.
```
# Import the module
Import-Module Catppuccin

# Set a flavor for easy access
$Flavor = $Catppuccin['Mocha']
```

그런데 이것만으로는 안된다. 추가적으로 windows terminal에도 catppuccin을 적용시켜야 한다.

[git repo](https://github.com/catppuccin/windows-terminal)에 들어간다.

windows terminal에 들어가서 `Ctrl+,`을 눌러 settings에 들어간다.
왼쪽 아래에 'Json 파일 열기'로 json을 연다.
`settings.json` 파일에서 "schemas"를 찾는다.
git repo에서 `mocha.json`을 연다. 여기 내용을 schemas 테이블에 넣어준다.

다시 `settings.json` 파일에서 "themes"를 찾는다.
git repo에서 `mochaTheme.json`을 연다.
"themes" 테이블에 위 json 내용을 붙여넣는다.

파일을 저장하고 닫은 뒤, 다시 [[Windows Terminal setup|windows terminal]]에 들어간다.
settings -> 기본값 -> 모양 -> 색 구성표 -> Catppuccin Mocha를 선택해준다.
이 외에도 추가적으로 설정하고 싶은 쉘에 위와 똑같은 과정을 거친다.