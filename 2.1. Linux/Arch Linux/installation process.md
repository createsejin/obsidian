```bash
setfont ter-u18b.psf.gz
iwctl :
	station wlan0 scan
	station wlan0 get-networks
	station wlan0 connect SK_WiFiGIGAD61C_5G
	# input password
	exit
pacman-key --init
pacman-key --populate archlinux
pacman -Sy git curl neovim

# setting neovim
mkdir -p .config/nvim
cd .config/nvim
# clone my nvim config files for terminel environment
git clone https://github.com/createsejin/nvimt .
nvim :
:term
# vim-plug install
:e plug.txt
sh -c 'curl -fLo "${XDG_DATA_HOME:-$HOME/.local/share}"/nvim/site/autoload/plug.vim --create-dirs \
       https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim'
:qa
nvim :
:PlugInstall
:qa
nvim

# make lvm partition and format
lsblk # check disk status

cfdisk /dev/nvme0n1:
	first, select free space, enter, make 1G and select the type and select EFI System.
	next, make partition from remain free space, and select Linux filesystem Type
	and write changes and quit cfdisk.

# create pv, vg, lv
pvcreate /dev/nvme0n1p6
pvs

vgcreate Files /dev/nvme0n1p6
vgs

lvcreate -L 67G Files -n root
lvcreate -L 70G Files -n home
lvcreate -L 24G Files -n swap
lvs

# partition format
mkfs.fat -F 32 /dev/nvme0n1p5
mkfs.ext4 /dev/Files/root
mkfs.ext4 /dev/Files/home
mkswap /dev/Files/swap

# mount partitions
mount /dev/Files/root /mnt
mount --mkdir /dev/nvme0n1p5 /mnt/boot
mount --mkdir /dev/Files/home /mnt/home
swapon /dev/Files/swap

# set keyboard layout
loadkeys us

# set timezone
timedatectl set-timezone Asia/Seoul
timedatectl set-ntp true

# update fastest mirrorlist
reflector -c "South Korea" -a 12 --sort rate \
--save /etc/pacman.d/mirrorlist

# install essential packages
pacstrap -K /mnt base linux linux-firmware git neovim curl
pacstrap -K /mnt intel-ucode lvm2

# Generate an fstab file
genfstab -U /mnt >> /mnt/etc/fstab
cat /mnt/etc/fstab # check the file correctly generated

# exit nvim
:q

# arch-chroot to new system
arch-chroot /mnt

# install basic packges
pacman -Sy zsh reflector

# reflector for new system
reflector -c "South Korea" -a 12 --sort rate \
--save /etc/pacman.d/mirrorlist

# setting neovim for new system
cd
mkdir -p .config/nvim
cd .config/nvim
# clone my nvim config files for terminel environment
git clone https://github.com/createsejin/nvimt .
nvim :
:term
# vim-plug install
:e plug.txt
sh -c 'curl -fLo "${XDG_DATA_HOME:-$HOME/.local/share}"/nvim/site/autoload/plug.vim --create-dirs \
       https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim'
:qa
nvim :
:PlugInstall
:qa
nvim

# install additional packages
pacman -S alsa-utils pipewire bluez bluez-utils networkmanager network-manager-applet man-db bat texinfo unzip neofetch

# set time
ln -sf /usr/share/zoneinfo/Asia/Seoul /etc/localtime
hwclock --systohc

# Localization
:e /etc/locale.gen
en_US.UTF-8 UTF-8 # uncomment
ko_KR.UTF-8 UTF-8 # uncomment
:wq

locale-gen

:e /etc/locale.conf :
LANG=en_US.UTF-8
:wq

# enable networkmanager
systemctl enable NetworkManager
# enable bluetooth
systemctl enable bluetooth

# set hostname
:e /etc/hostname :
arch
:wq

# Adding lvm2 to mkinitcpio hooks
:e /etc/mkinitcpio.conf :
HOOKS=(base udev ... block lvm2 filesystems)

# initramfs
mkinitcpio -P

# root passwd config
passwd

# add user as wheel group
useradd -mG wheel bae
passwd bae
# install sudo package
pacman -S sudo
EDITOR=nvim visudo :
%wheel      ALL=(ALL:ALL) ALL # uncomment
:wq
usermod -aG video,input,audio bae

# Boot loader config
pacman -S grub efibootmgr os-prober dosfstools mtools ntfs-3g

# edit grub config
:e /etc/default/grub
GRUB_DISABLE_OS_PROBER=false # uncomment

# press Ctrl+Alt+F2 for switch to live CD os root session from new system root session
nvim :
:term
# mount windows boot manager partition
mkdir /mnt/windows-efi
lsblk
grub-mount /dev/nvme0n1p1 /mnt/windows-efi
# mount windows root partition
mkdir /mnt/windows
mount -t ntfs-3g -o ro,noexec,nodev,nosuid /dev/nvme0n1p3 /mnt/windows

# now to go back to the new system's root session,
# press Ctrl+Alt+F1
grub-install --target=x86_64-efi --efi-directory=/boot --bootloader-id=GRUB
grub-mkconfig -o /boot/grub/grub.cfg

# switch to live CD root (press Ctrl+Alt+F2)
# unmount windows partitions
cd /mnt
umount windows
umount windows-efi

#reboot
reboot

# login as user
bae ..

# network config
nmcli device wifi list
nmcli device wifi connect SK_WiFiGIGAD61C_5G password "password"
sudo systemctl start NetworkManager
sudo systemctl start bluetooth

# setting neovim for bae user
cd
mkdir -p .config/nvim
cd .config/nvim
# clone my nvim config files for terminel environment
git clone https://github.com/createsejin/nvimt .
nvim :
:term
# vim-plug install
:e plug.txt
sh -c 'curl -fLo "${XDG_DATA_HOME:-$HOME/.local/share}"/nvim/site/autoload/plug.vim --create-dirs \
       https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim'
:qa
nvim :
:PlugInstall
:qa
nvim

# set terminal font
sudo pacman -S terminus-font
:SudaRead /etc/vconsole.conf 
FONT=ter-u18b
FONT_MAP=8859-2
# reboot
reboot

# git clone mydoc to ~/Documents
cd
mkdir Documents
cd ~/Documents
git clone https://github.com/createsejin/mydoc .
```