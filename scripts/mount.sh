#fallocate -l 1M virtual_usb.img
#mkfs -t ext4 virtual_usb.img
if [ ! -d "/media/boscoand/virtual_usb" ]; then
  mkdir /media/boscoand/virtual_usb
  chmod 777 /media/boscoand/virtual_usb
fi

if [ ! -d "/media/boscoand/virtual_usb_2" ]; then
  mkdir /media/boscoand/virtual_usb_2
  chmod 777 /media/boscoand/virtual_usb2
fi

# if [ -d "/media/virtual_usb" ]; then
#   chmod 777 /media/virtual_usb
# fi

mount -t auto -o loop virtual_usb.img /media/boscoand/virtual_usb
mount -t auto -o loop virtual_usb_2.img /media/boscoand/virtual_usb_2
