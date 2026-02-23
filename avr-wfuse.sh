avrdude -c usbasp -p m328p -U lfuse:w:0xFF:m
avrdude -c usbasp -p m328p -U hfuse:w:0xDE:m
avrdude -c usbasp -p m328p -U efuse:w:0x05:m