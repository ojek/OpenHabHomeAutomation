sleep 60
unclutter &
matchbox-window-manager &
iceweasel http://192.168.0.5:8080/habpanel/index.html#/view/SmartMirror?kiosk=on --display=:0 &
sleep 15s;
xte "key F11" -x:0