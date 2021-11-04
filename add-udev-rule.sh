#!/bin/sh
sudo cp 80-ds360.rules /usr/lib/udev/rules.d/
sudo udevadm control --reload