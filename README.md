![Scheme](https://mirrors.creativecommons.org/presskit/icons/cc.svg)
# Amiga 1200+

## About

This project is a re-implementation of the Amiga 1200 board started from the schematics.
I made some changes and enhancements to the original schematics.

## Features

* All Original AA chips are needed and can be put into the sockets. These include Lisa, Paula, Alice, The two CIA chips and the Keyboard controller.
* The CPU is removed, you need some accellerator board to run this board.
* The DRAM has been removed and the functionality has been moved to a daughterboard.
* Video output has been moved to a seperate output board. This board get all Lisa output signals and also all the typical Zorro signals. This means that an RTG card can be developed.
* The PCMCIA slot has been removed and in the free space a Compact Flash socket has been added.
* A 110V-240V AC-DC powersupply has been added, so no more power brick. This generates these voltages:
    * 5 Volts: main power rail 5 Amp capable
    * 12 Volts: 0.8 Amp capable
* two PC standard 3 Pin fan headers are added to the board.
* A non-volatile digipot has been added in the audio path, this allows you to set the stereo separation.
* Extension board connector for Mouse/Joystick/Network/FlashFloppy. (one is in development that has USB Mouse and two classic DB-9 connectors and autoswitches when fire button is pressed + ethernet)

## License

This project is licensed by a Creative Commons license; You are welcome (and encouraged!) to extend, re-spin and otherwise use and modify the design as allowed by the license. - see  [Creative Commons](https://creativecommons.org/licenses/by-sa/4.0/) for details

