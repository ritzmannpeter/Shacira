#!/bin/sh

# boot directory
mkdir /mnt/strip/boot
cp -uv /boot/kernel /mnt/strip/boot/kernel
cp -ruv /boot/grub /mnt/strip/boot/grub

# root file system
cp -ruv /root /mnt/strip/root
cp -ruv /bin /mnt/strip/bin
cp -ruv /lib /mnt/strip/lib
cp -ruv /etc /mnt/strip/etc
cp -ruv /sbin /mnt/strip/sbin
cp -ruv /opt /mnt/strip/opt
cp -ruv /sys /mnt/strip/sys
cp -auv /var /mnt/strip/var

# removing smb developer links
unlink /mnt/strip/var/samba/public/root
unlink /mnt/strip/var/samba/public/prj

mkdir /mnt/strip/usr
cp -ruv /usr/bin /mnt/strip/usr/bin
cp -ruv /usr/lib /mnt/strip/usr/lib
cp -ruv /usr/i386-pc-linux-gnu /mnt/strip/usr/i386-pc-linux-gnu
cp -ruv /usr/i686-pc-linux-gnu /mnt/strip/usr/i686-pc-linux-gnu
cp -ruv /usr/include /mnt/strip/usr/include
cp -ruv /usr/libexec /mnt/strip/usr/libexec
cp -ruv /usr/sbin /mnt/strip/usr/sbin
cp -ruv /usr/local /mnt/strip/usr/local
cp -ruv /usr/share /mnt/strip/usr/share

# devices
cp -auv /dev /mnt/strip/dev

# mount point for proc file system 
mkdir /mnt/strip/mnt
mkdir /mnt/strip/proc
cp -ruv /home /mnt/strip/home

# X11 link
cd /mnt/strip/usr
ln -s ../usr X11R6

# strip locales
./striplocales.sh /mnt/strip/usr/lib/locale

# remove unused directories
rm -rf /usr/lib/perl5
rm -rf /usr/lib/python-2.4

# adapt fstab
cp -v /etc/fstab.stripped /mnt/strip/etc/fstab

# prepare qt3

# prepare tmp directory for ecl
#mkdir /mnt/strip/tmp
#mkdir /mnt/strip/tmp/ecl

# prepare Mosaic
mkdir /mnt/strip/Mosaic
cp -ruv /prj/MosaicTarget /mnt/strip/Mosaic

 

