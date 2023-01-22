# **Not maintained anymore**

I'm sure someone would find a more elegant way of doing this than simply wrapping xboxdrv, latest Proton + Steam Input work perfectly for me, add non-steam shortcut if it doesn't work (Steam Deck work seems to have improved controller support).

# Emulate Dualsense as a 360 controller on Linux

Initially wanted to implement Sony's PlayStation 5 controller support to `sc-controller` for broader config options but couldn't be bothered with all the python debugging right now.

Useful for games not recognizing the Dualsense for some reason, like RDR 2 or Dragon Quest XI or other non-steam games in my testing, emulating the controller as a 360 fixes the compatibility gap entirely so a Dualsense can be used as the ultimate controller.

The program is mainly based on xboxdrv's excellent ability to emulate a 360 controller.

## Pre-requirements


- Have a recent kernel (5.12+) that includes the latest official drivers (hid-playstation)
- Install xboxdrv (https://xboxdrv.gitlab.io)
- Basic dev tools like `g++` or `make`

## How to compile
```
git clone https://github.com/yoyossef/ds360.git
cd ds360
make
```
## Usage
#### Starting the process in terminal, press CTRL+C to stop
```
./ds360
```
#### Starting ds360.service manually, controller must be connected
```
systemctl start --user ds360.service
```
#### Automatically start ds360.service via udev rule when controller connects
```
./add-udev-rule.sh
```
## How to install
```
git clone https://github.com/yoyossef/ds360.git
cd ds360
make install
```

## How to uninstall

```
make uninstall
```

## Troubleshooting

The script should work fine if the Dualsense controller is connected through USB or via Bluetooth, but if you still get the "VID not found" error, please check your `/proc/bus/input/devices` file and see if your controller is there.

If it's not recheck if your kernel includes the `hid-playstation` driver and try to use `xboxdrv` manually with `dualsense.xboxdrv` config (edit the commented `evdev=...` line).


Hint: you can find the value to use for evdev with this command (thanks to /u/QushAes)
```sh
    for sysdevpath in $(find /sys/bus/usb/devices/usb*/ -name dev); do
    (
        syspath="${sysdevpath%/dev}"
        devname="$(udevadm info -q name -p $syspath)"
        [[ "$devname" == "bus/"* ]] && exit
        eval "$(udevadm info -q property --export -p $syspath)"
        [[ -z "$ID_SERIAL" ]] && exit
        echo "/dev/$devname - $ID_SERIAL"
    )
    done
```
