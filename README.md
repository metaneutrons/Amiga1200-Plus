![Scheme](https://mirrors.creativecommons.org/presskit/icons/cc.svg)
# Amiga 1200+

## About

This project is a re-implementation of the Amiga 1200 board started from the schematics.
I made some changes and enhancements to the original schematics.

## Features

* All Original AA chips are needed and can be put into the sockets. These include Lisa, Paula, Alice, The two CIA chips and the Keyboard controller.
* Gayle, Budgie and the DRAM have been removed and the functionality has been moved to a daughterboard. This board can also contain a CPU.
* Video output has been moved to a seperate output board. This board get all Lisa output signals and also all the typical Zorro signals. This means that an RTG card can be developed.
* The PCMCIA slot has been removed and in the free space a power switch, boot selector switch (DF0:/DF1:) and a uSD card slot have been added.
* A single supply universal power input has been added. (15V - 36V) From this the following voltages are created:
    * 5 Volts: main power rail 5 Amp capable
    * 12 Volts: 1 Amp capable
    * 3.3 Volts: 0.5 Amp capable (for daughter boards)
    * 1.2 Volts: 0.5 Amp capable (for daughter boards)
* two PC standard 3 Pin fan headers are added to the board.
* Terrible Fire compatible SPI port for network chip
* Extension board connector for mouse/joystick. (one is in development that has USB Mouse and two classic DB-9 connectors and autoswitches when fire button is pressed)

## License

This project is licensed by a Creative Commons license; You are welcome (and encouraged!) to extend, re-spin and otherwise use and modify the design as allowed by the license. - see  [Creative Commons](https://creativecommons.org/licenses/by-sa/4.0/) for details

