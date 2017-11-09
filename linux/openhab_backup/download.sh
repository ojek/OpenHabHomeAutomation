#!/bin/bash
# OpenHab git update

cd /home/pi/git/OpenHabHomeAutomation
git pull https://github.com/ojek/OpenHabHomeAutomation
rm -rf /etc/openhab2/*
cp -r /home/pi/git/OpenHabHomeAutomation/openhab/etc/openhab2/* /etc/openhab2/

#post download scripts begin
chmod a+x /etc/openhab2/scripts/rpiTemp.sh
#post download scripts end

if [ "$1" != 0 ] ; then
    sudo systemctl restart openhab2.service
fi