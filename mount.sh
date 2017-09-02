#fallocate -l 1M virtual_usb.img
#mkfs -t ext4 virtual_usb.img
if [ ! -d "/media/virtual_usb" ]; then
  mkdir /media/virtual_usb
  chmod 777 /media/virtual_usb
fi

if [ ! -d "/media/virtual_usb_2" ]; then
  mkdir /media/virtual_usb_2
  chmod 777 /media/virtual_usb_2
fi

# if [ -d "/media/virtual_usb" ]; then
#   chmod 777 /media/virtual_usb
# fi

mount -t auto -o loop virtual_usb.img /media/virtual_usb #mount LABEL=mydisk -o noatime,nodev,nosuid
# -w, --rw, --read-write --target directory --label label mount /tmp/disk.img /mnt -t vfat -o loop=/dev/loop3


mount -t auto -o loop virtual_usb_2.img /media/virtual_usb_2
