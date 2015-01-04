# CANtact

This repository contains the design files for CANtact, an open source CAN bus 
tool.

## Firmware

Firmware is located in the `fw/` folder. It contains the sources for this 
project, and all the driver sources for the STM32 microcontroller.

### Building

Firmware builds with GCC. Specifically, you will need gcc-arm-none-eabi, which 
is packaged for Windows, OS X, and Linux on 
[Launchpad](https://launchpad.net/gcc-arm-embedded/+download). Download for your 
system and add the `bin` folder to your PATH.

With that done, you should be able to compile using `make`.

### Flashing & Debugging

Debugging and flashing can be done with any STM32 Discovery board as a 
programmer. You can also use other tools that support SWD.

To use an STM32 Discovery, run [OpenOCD](http://openocd.sourceforge.net/) using
the stm32f0x.cfg file: `openocd -f fw/stm32f0x.cfg`.

With OpenOCD running, arm-none-eabi-gdb can be used to load code and debug.

## Hardware

The hardware design files are in the `hw/` folder. These files are editable with 
[KiCad](http://www.kicad-pcb.org/).
