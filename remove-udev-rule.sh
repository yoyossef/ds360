#!/bin/sh
sudo rm -f /usr/lib/udev/rules.d/80-ds360.rules
sudo rm -f /usr/bin/ds360-stop.sh
sudo udevadm control --reload