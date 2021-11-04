#!/bin/sh
sudo rm /usr/lib/udev/rules.d/80-ds360.rules
sudo udevadm control --reload