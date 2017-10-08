#!/bin/bash
# OpenHab git update

cd ~/git/OpenHabHomeAutomation 
git pull https://github.com/ojek/OpenHabHomeAutomation
rm -rf /etc/openhab2/*
cp -r ~/git/OpenHabHomeAutomation/openhab/etc/openhab2/* /etc/openhab2/
sudo systemctl restart openhab2.service