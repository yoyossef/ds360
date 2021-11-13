#!/bin/sh
sudo cp 80-ds360.rules /usr/lib/udev/rules.d/
sudo cp ds360-stop.sh /usr/bin/
sudo chmod 555 /usr/bin/ds360-stop.sh
sudo udevadm control --reload