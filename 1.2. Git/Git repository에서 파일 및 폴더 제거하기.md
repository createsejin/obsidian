```git
PS D:\Projects\gta_cMecro> git rm -r --cached cmake-build-debug
PS D:\Projects\gta_cMecro> git rm -r --cached old_valt
PS D:\Projects\gta_cMecro> git add .
PS D:\Projects\gta_cMecro> git commit -m "24-02-06_004 remove files"
PS D:\Projects\gta_cMecro> git push origin master
```
이런식으로 `--cached`옵션을 사용하면 작업 디렉터리의 폴더들은 유지되면서 git 레포지토리에서만 제거된다. 또한 프로젝트 루트 디렉토리에 `.gitignore`파일에 다음과 같이 설정해두면 해당 폴더나 파일들은 git이 무시한다. `grmc -r <dir>`을 사용하면 더욱 쉽게 `git rm -r --cached`를 사용할 수 있다.
```
/cmake-build-debug/  
/cmake-build-release/  
/old_valt/
```