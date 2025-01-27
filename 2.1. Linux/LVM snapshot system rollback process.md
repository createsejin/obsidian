## before rollback
1. If `/boot` is located in seperated partition, you should back up /boot to root /boot backup directory(here I use `/boot_on_root`). Or you can use [pacman hook](https://wiki.archlinux.org/title/System_backup#Snapshots_and_/boot_partition). for automate backup /boot to root directory.
## rollback process
1. Boot Live CD arch linux
2. mount /boot on /mnt/boot
3. mount root on /mnt
4. rollback /mnt/boot_on_root
5. chroot /mnt
6. excute lvconvert and ready merge snapshot
7. reboot
