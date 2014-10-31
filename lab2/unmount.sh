sudo umount /media/bootfs
sudo kpartx -d /dev/loop0
sudo losetup -d /dev/loop0
