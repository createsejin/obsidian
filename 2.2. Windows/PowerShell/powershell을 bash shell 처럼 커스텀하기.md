powershell을 띄워서 `$profile`을 쳐보면 현재 이 powershell의 profile의 path가 나온다. 나는 이 파일을 mydoc에 넣어서 original path에 [[ln alias 관리자 권한으로 실행하기|심볼릭 링크]]로 만들어서 사용중이다.

어쨌거나, 나는 편한 명령어 alias들을 사용하기 위해 [이렇게](https://github.com/createsejin/mydoc/blob/main/win_configs/pwsh_profile/Microsoft.PowerShell_profile.ps1) profile에서 alias들을 손봤다.

우선, [[catppuccin theme 적용시키기|catppuccin theme]]을 기본적으로 적용시켜줬다. 

[[eza 설치 및 configure|eza]] 라던가 [[zoxide 설치 및 configure|zoxide]], [[bat 설치 및 테마 설정|bat]]을 config 하는 script도 있다.
eza를 이용해서 `ls`와 `l` 명령어를 지정했으며, `tree <level>` 명령어도 지정했다.
zoxside로 `cd` 명령어를 지정했다.
|
또한 절대 경로와 상대 경로를 출력해주는 [[absolute path, relative path Alias 설정하기|기능]]으로 `path`와 `rpath`를 지정했다.
[[ln alias 관리자 권한으로 실행하기|심볼릭 링크]]를 만드는 명령어도 지정했다. `ln <target path> <link name>` 식으로 사용한다.

`touch` alias로 간단히 빈 파일을 만들게 했다.
나머지 `mkdir`, `cp`, `rm`, `mv` 명령어들은 기본적으로 powershell에서 alias로 등록되어있고, bash shell에서와 거의 동일하게 사용할 수 있었다.

또한 `vim`, `vimt`를 지정해서 neovim을 더욱 간편하게 실행시킬 수 있도록 했다.

`ban <archive> [<target_dir>]`을 통해 [[반디집 bz command line tool|반디집 커맨드라인 툴]]로 각종 압축파일을 해제할 수 있게 했다. 여기에서 `<target_dir>`은 optional한 argument다. 이게 없으면 archive 이름 폴더를 만든 후 그 폴더에 압축 해제하도록 하였다.

또한 `which`를 통해 현재 커맨드의 실행파일 위치를 출력하는 기능을 더했다.

`ex`를 통해 현재 쉘에서 windows file explorer를 실행하도록 하였다.

`cl`을 통해 현재 쉘을 `clear`해준다.

`so`로 현재 쉘의 powershell profile을 source 해준다.

`sudo <commands>`를 통해 특정 명령어를 새로운 powershell 터미널에서 [[Start-Process 관리자 권한으로 실행하기|관리자 권한]]으로 실행한다.

[[zsh git plugin 정리|zsh git plugin 기능]]을 몇 가지 설정했다. 필요한게 있으면 [여기](https://github.com/ohmyzsh/ohmyzsh/blob/master/plugins/git/git.plugin.zsh)에서 가져다 쓰자.

powershell에서도 zsh처럼 auto suggestions 기능이 있다. [이 문서](https://learn.microsoft.com/en-us/powershell/scripting/learn/shell/using-keyhandlers?view=powershell-7.4)에서 사용되는 `Get-PSReadLineKeyHandler`를 이용해서 `MenuComplete` Function에 키바인딩을 하는것이다. 기본적으로는 `Ctrl+Space`로 설정되어있다. 
또한 `dotnet` CLI 같은 경우에는 [이 문서](https://learn.microsoft.com/en-us/dotnet/core/tools/enable-tab-autocomplete)에서 powershell에 tab completion을 설정하는 방법을 안내하고 있다.