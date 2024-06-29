다음 명령어로 설치.
```powershell
winget install sharkdp.bat
```

```powershell
mkdir -p "$(bat --config-dir)/themes"
wget -P "$(bat --config-dir)/themes" https://github.com/catppuccin/bat/raw/main/themes/Catppuccin%20Mocha.tmTheme
```

wget이 없으면 그냥 해당 파일을 [git repo](https://github.com/catppuccin/bat)에서 직접 다운로드 해도 된다.

```powershell
bat cache --build
bat --list-themes
bat --config-file
C:\Users\creat\AppData\Roaming\bat\config

code C:\Users\creat\AppData\Roaming\bat\config
```

config file:
```
--theme="Catppuccin Mocha"
```
