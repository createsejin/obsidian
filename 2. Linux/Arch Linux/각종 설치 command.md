### setfont
```
setfont ter-u18b.psf.gz
```
### vim-plug
```
sh -c 'curl -fLo "${XDG_DATA_HOME:-$HOME/.local/share}"/nvim/site/autoload/plug.vim --create-dirs \
       https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim'
```
### grub
[참고 영상](https://youtu.be/4dKzYmhcGEU?si=UDM5P5LLl-O5477o)
```
# after arch linux installed
pacman -Sy grub efibootmgr dosfstools mtools

lsblk

grub-install --target=x86_64-efi --efi-directory=/boot --bootloader-id=GRUB

grub-mkconfig -o /boot/grub/grub.cfg

shutdown now

# after reboot
nvim /etc/default/grub
: 
GRUB_TIMEOUT=30
#uncomment follow line
GRUB_DISABLE_OS_PROBER=false

pacman -Sy os-prober
grub-mkconfig -o /boot/grub/grub.cfg
```
### networkmanager
nmcli device wifi connect SK-WiFiGIGAD61C_5G password ooo 
### git-credential-manager
```
curl -L https://aka.ms/gcm/linux-install-source.sh | sh
git-credential-manager configure
git config --global credential.credentialStore cache
```
### Rust
```
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
```
### Catppuccin for alacritty
```
curl -LO --output-dir ~/.config/alacritty https://github.com/catppuccin/alacritty/raw/main/catppuccin-mocha.toml

in ~/.config/alacritty/alacritty.toml:
# import must be placed first line!
import = [
  # uncomment the flavour you want below:
  # "~/.config/alacritty/catppuccin-latte.toml"
  # "~/.config/alacritty/catppuccin-frappe.toml"
  # "~/.config/alacritty/catppuccin-macchiato.toml"
  "~/.config/alacritty/catppuccin-mocha.toml"
]

[env]
TERM = "xterm-256color"
```

