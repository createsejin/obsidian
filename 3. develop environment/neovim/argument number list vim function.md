argument를 운용할때 다음과같은 vim 함수를 이용하면 매우 효과적으로 argument list를 운용할 수 있다.
```lua
vim.cmd([[
  function! Arg_number_list()
    let l:args = argv()
    let l:max_len = len(len(l:args))
    for l:i in range(len(l:args))
      let l:prefix = l:i == argidx() ? '> ' : ': '
      echo printf('%' . l:max_len . 'd%s%s', l:i + 1, l:prefix, l:args[l:i])
    endfor
  endfunction
]])
```
이것을 NvChad에서는 다음과 같이 키바인딩 할 수 있다.
```lua
M.my_general = {
  n = {
    ["<M-s>"] = { "<cmd> call Arg_number_list() <CR>" },
  }, ...
```
lua가 아닌 일반적인 vim에서는 다음과 같이 vim.cmd 부분을 제외하고 사용하면 된다.
```
function! Arg_number_list()
  let l:args = argv()
  let l:max_len = len(len(l:args))
  for l:i in range(len(l:args))
    let l:prefix = l:i == argidx() ? '> ' : ': '
    echo printf('%' . l:max_len . 'd%s%s', l:i + 1, l:prefix, l:args[l:i])
  endfor
endfunction

nnoremap <M-s> :call Arg_number_list()<CR>
```
이렇게 설정하면 다음처럼 argument list가 쉽게 사용할 수 있도록 표시된다.
```
1: tab1
2: lua/custom/plugins.lua
3: lua/custom/init.lua
4> lua/custom/mappings.lua
5: lua/core/mappings.lua
6: /home/bae/.config/nvimt/init.vim
```
## 유용한 argument key bindings
나같은 경우는 `g1, g2, g3, g4, ...` 등과 같이 g키에다가 숫자를 붙여서 argument list를 손쉽게 사용하고 있다. 또한 `:n`과 `:N`을 다음처럼 key mapping을 하면 좋다.
```
    ["<M-s>"] = { "<cmd> call Arg_number_list() <CR>" },
    ["<M-n>"] = { "<cmd> n <CR>" },
    ["2<M-n>"] = { "<cmd> 2n <CR>" },
    ["3<M-n>"] = { "<cmd> 3n <CR>" },
    ["<M-p>"] = { "<cmd> N <CR>" },
    ["2<M-p>"] = { "<cmd> 2N <CR>" },
    ["3<M-p>"] = { "<cmd> 3N <CR>" },
    ["g1"] = { "<cmd> argu1 <CR>" },
    ["g2"] = { "<cmd> argu2 <CR>" },
    ["g3"] = { "<cmd> argu3 <CR>" },
    ["g4"] = { "<cmd> argu4 <CR>" },
    ["g5"] = { "<cmd> argu5 <CR>" },
    ["g6"] = { "<cmd> argu6 <CR>" },
    ["g7"] = { "<cmd> argu7 <CR>" },
    ["g8"] = { "<cmd> argu8 <CR>" },
    ["g9"] = { "<cmd> argu9 <CR>" },
    ["g10"] = { "<cmd> argu10 <CR>" },
    ["g11"] = { "<cmd> argu11 <CR>" },
    ["g12"] = { "<cmd> argu12 <CR>" },
    ...
```
일반적인 init.vim 에서도 유사하다.
```
nnoremap <M-n> :n<CR>
nnoremap 2<M-n> :2n<CR>
nnoremap 3<M-n> :3n<CR>
nnoremap <M-p> :N<CR>
nnoremap 2<M-p> :2N<CR>
nnoremap 3<M-p> :3N<CR>

nnoremap g1 :argu1<CR>
nnoremap g2 :argu2<CR>
nnoremap g3 :argu3<CR>
nnoremap g4 :argu4<CR>
nnoremap g5 :argu5<CR>
nnoremap g6 :argu6<CR>
nnoremap g7 :argu7<CR>
nnoremap g8 :argu8<CR>
nnoremap g9 :argu9<CR>
nnoremap g10 :argu10<CR>
nnoremap g11 :argu11<CR>
nnoremap g12 :argu12<CR>
...
```
나 같은 경우는 넉넉하게 `g39`까지 해놨는데 이럴 경우에는 `g1, g2, g3`의 경우 그냥 사용하면 후속으로 입력해야하는 숫자 때문에 어쩔 수 없이 key waiting delay가 생기는데, 그냥 `g1j, g2j, g3j` 이런식으로 눌러주면 바로바로 argu 1, 2, 3번으로 이동할 수 있다.