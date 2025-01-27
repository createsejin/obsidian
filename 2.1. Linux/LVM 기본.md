[arch linux wiki](https://wiki.archlinux.org/title/LVM#Resizing_the_logical_volume_and_file_system_in_one_go)

view remain capacity of volume group
`sudo vgs`

create logical volume
`sudo lvcreate -L 10G MyVolGroup -n lv_vol`

after create lv, you must format the partition.
`sudo mkfs.ext4 /dev/MyVolGroup/lv_vol`