sudo tvservice -p && sudo chvt 2 && sudo chvt 7
DISPLAY=:0 chromium-browser -kiosk http://192.168.0.5:8080/habpanel/index.html#/view/SmartMirror?kiosk=on