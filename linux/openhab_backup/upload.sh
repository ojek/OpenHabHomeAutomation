#!/bin/bash
# OpenHab git push

cd ~/git/OpenHabHomeAutomation 
rm -rf ~/git/OpenHabHomeAutomation/openhab/etc/openhab2/*
cp -r /etc/openhab2/* ~/git/OpenHabHomeAutomation/openhab/etc/openhab2/
git add --all
git commit -am 'added openhab etc folder structure'
git push