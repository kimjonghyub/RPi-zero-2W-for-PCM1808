#!/bin/bash
dtc -@ -I dts -O dtb -o $1.dtbo $1.dts || exit 1
sudo cp $1.dtbo /boot/overlays/
echo "dtoverlay=$1" | sudo tee -a /boot/config.txt
echo "Rebooting..."
sudo reboot
