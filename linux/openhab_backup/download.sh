#!/bin/bash
# OpenHab git update

cd /home/pi/git/OpenHabHomeAutomation
git pull https://github.com/ojek/OpenHabHomeAutomation
rm -rf /etc/openhab2/*
rm -rf /usr/share/openhab2/addons/*
cp -r /home/pi/git/OpenHabHomeAutomation/openhab/etc/openhab2/* /etc/openhab2/
cp -r /home/pi/git/OpenHabHomeAutomation/openhab/usr/share/openhab2/addons/* /usr/share/openhab2/addons/

#post download scripts begin
chmod a+x /etc/openhab2/scripts/rpiTemp.sh
chmod a+x /etc/openhab2/scripts/screen_on.sh
chmod a+x /etc/openhab2/scripts/screen_off.sh
sudo chown -hR openhab:openhab /etc/openhab2
#post download scripts end 

if [ "$1" != 0 ] ; then
    sudo systemctl restart openhab2.service
fi