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
lvs

# partition format
mkfs.fat -F 32 /dev/nvme0n1p5
mkfs.ext4 /dev/Files/root
mkfs.ext4 /dev/Files/home

# mount partitions
mount /dev/Files/root /mnt
mount --mkdir /dev/nvme0n1p5 /mnt/boot
mount --mkdir /dev/Files/home /mnt/home
```