# Emulate Dualsense as a 360 controller on Linux

Initially wanted to implement Sony's PlayStation 5 controller support to `sc-controller` for broader config options but couldn't be bothered with all the python debugging right now.

## Pre-requirements


- Have a recent kernel (5.12+) that includes the latest official drivers (hid-playstation)
- Install xboxdrv (https://xboxdrv.gitlab.io)

## Usage

```
xboxdrv -c /path/to/dualsense.xboxdrv       # Don't use `~` in the path or else it won't find the file
```