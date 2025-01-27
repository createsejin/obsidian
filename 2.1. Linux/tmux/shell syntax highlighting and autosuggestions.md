[Fish](https://wiki.archlinux.org/title/Fish "Fish") provides very powerful shell syntax highlighting and autosuggestions. To use both in Zsh, you can install [zsh-syntax-highlighting](https://archlinux.org/packages/?name=zsh-syntax-highlighting), [zsh-autosuggestions](https://archlinux.org/packages/?name=zsh-autosuggestions), and finally [source](https://wiki.archlinux.org/title/Source "Source") one or both of the provided scripts from your zshrc:
```
~/.zshrc

source /usr/share/zsh/plugins/zsh-syntax-highlighting/zsh-syntax-highlighting.zsh
source /usr/share/zsh/plugins/zsh-autosuggestions/zsh-autosuggestions.zsh`
```