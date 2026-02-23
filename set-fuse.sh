avrdude -c usbasp -p m328p -P /dev/ttyUSB0 -U lfuse:w:0xFF:m
avrdude -c usbasp -p m328p -P /dev/ttyUSB0 -U hfuse:w:0xDE:m
avrdude -c usbasp -p m328p -P /dev/ttyUSB0 -U efuse:w:0x05:m