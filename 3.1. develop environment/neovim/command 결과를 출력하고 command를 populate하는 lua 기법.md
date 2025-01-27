예를 들어서 나의 vim session file들이 있는 directory가 `~/se`이라고 하자.
그러면 나는 vim의 external command 기능을 이용해서
`!ls --ignore=storage ~/se`를 통해 vim의 command line에 이 결과를 띄울 수 있다.
그 직후에 내가 원하는 것은 바로 `so ~/se/`나 `mks! ~/se/`를 command line에 populate 하는 것이다. 이것은 일반적인 vim script로는 꽤나 까다로운 작업이다. 
그러나 lua라면 가능하다. 
예를 들어서 `so ~/se/`를 띄우는 작업은 아래와 같은 lua function으로 설계가 가능하다.
```lua
function Source_session()
  vim.cmd('!ls --ignore=storage ~/se')
  vim.fn.setreg('r', 'so ~/se/')
  vim.api.nvim_feedkeys(':', 'n', true)
  vim.api.nvim_feedkeys(vim.api.nvim_replace_termcodes('<C-r>r', true, true, true), 'n', true)
end
```
다소 복잡할 수 있지만 간단히 정리하자면, 첫번째는 단순히 저 `ls`명령을 실행하여 결과를 command line에 띄운다. 그 후, `so ~/se/`를 레지스터 `r`에 저장한다. 그 후 `vim.api.nvim_feedkeys`를 이용해서 우선 `:`키를 입력하게 한다. 그 직후 그 아래의 구문을 실행해서 `<C-r>r`을 차례대로 누르게 만든다. 이렇게 하면 레지스터 `r`에 있는 내용을 command line에 자동으로 띄워주게된다. 
구지 이렇게까지 하는 이유가 있냐 싶은데, 만약 `vim.fn.input`기능을 이용하면 실제로는 command가 제대로 실행되지 않는다. 따라서 이 방법이 현재로써는 잘 동작하는 방법 중 하나다.

이것에 대한 자세한 설명은 MS copilot이 설명해주었는데 내용은 다음과 같다.

> 1. `vim.api.nvim_feedkeys`: 이 함수는 Neovim에 키 입력을 전달하는 역할을 합니다. 이 함수는 세 개의 인자를 받습니다.
    - 첫 번째 인자는 전달할 키 입력입니다.
    - 두 번째 인자는 입력 모드를 지정합니다. 여기서는 `'n'`이 사용되어, 키 입력이 일반 모드에서처럼 동작하도록 설정되었습니다.
    - 세 번째 인자는 키 입력이 매크로 녹화에 기록되는지 여부를 지정합니다. 여기서는 `true`가 사용되어, 키 입력이 매크로 녹화에 기록되지 않도록 설정되었습니다.

> 2. `vim.api.nvim_replace_termcodes('<C-r>r', true, true, true)`: 이 함수는 특수 키 코드를 실제 키 입력으로 변환하는 역할을 합니다. 이 함수는 네 개의 인자를 받습니다.
    - 첫 번째 인자는 변환할 키 코드입니다. 여기서는 `'<C-r>r'`이 사용되어, `Ctrl+r`와 `r` 키 입력을 나타냅니다.
    - 두 번째 인자는 `<...>` 형식의 키 코드를 변환할지 여부를 지정합니다. 여기서는 `true`가 사용되어, `<...>` 형식의 키 코드가 변환되도록 설정되었습니다.
    - 세 번째 인자는 특수 문자를 변환할지 여부를 지정합니다. 여기서는 `true`가 사용되어, 특수 문자가 변환되도록 설정되었습니다.
    - 네 번째 인자는 키 코드를 변환할 때 터미널 모드를 고려할지 여부를 지정합니다. 여기서는 `true`가 사용되어, 터미널 모드가 고려되도록 설정되었습니다.

> 따라서, `vim.api.nvim_feedkeys(vim.api.nvim_replace_termcodes('<C-r>r', true, true, true), 'n', true)` 코드는 `Ctrl+r`와 `r` 키 입력을 Neovim에 전달하는 역할을 합니다. 이 키 입력은 레지스터 `r`의 내용을 명령 줄에 붙여넣습니다.

또한 마지막으로 이것을 키바인딩에 적용하려면 다음과 같이 `custom/mapping.lua`파일에 넣으면 된다.
```
M.my_general = {
	n = {
		["<leader>ms"] = { "<cmd> lua Source_session() <CR>", "populate ':so ~/se/'" },
	}
}
```
이러한 기법은 여타 다른 기능에도 적용할 수 있으며, 특정 명령어를 실행하기 전에 어떤 인자를 넣어야할지 먼저 그 목록을 알아야할때 유용하게 사용할 수 있을 것으로 기대된다.
