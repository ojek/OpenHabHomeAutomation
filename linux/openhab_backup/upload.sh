#!/bin/bash
# OpenHab git push

cd /home/pi/git/OpenHabHomeAutomation 
rm -rf /home/pi/git/OpenHabHomeAutomation/openhab/etc/openhab2/*
cp -r /etc/openhab2/* /home/pi/git/OpenHabHomeAutomation/openhab/etc/openhab2/
git add --all
git commit -am 'Autobackup commit'
git push