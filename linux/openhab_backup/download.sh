#!/bin/bash
# OpenHab git update

cd /home/pi/git/OpenHabHomeAutomation 
git pull https://github.com/ojek/OpenHabHomeAutomation
rm -rf /etc/openhab2/*
cp -r /home/pi/git/OpenHabHomeAutomation/openhab/etc/openhab2/* /etc/openhab2/
./home/pi/git/OpenHabHomeAutomation/linux/openhab_backup/postDownloadScripts.sh
sudo systemctl restart openhab2.service