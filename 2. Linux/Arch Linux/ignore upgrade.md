[wiki](https://wiki.archlinux.org/title/Pacman#Skip_package_from_being_upgraded)
`/etc/pacman.conf` 에서 `IgnorePkg=linux linux-utils` 이런식으로 하면 된다.
Group을 제외시키려면 `IgnoreGroup=gnome` 이런식으로 한다.
나는 fcitx5에 문제가 있어서 이거 하나를 제외시켜놨다.