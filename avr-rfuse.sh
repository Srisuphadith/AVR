avrdude -c usbasp -p m328p -U hfuse:r:hbit.hex:h
avrdude -c usbasp -p m328p -U lfuse:r:lbit.hex:h
avrdude -c usbasp -p m328p -U efuse:r:ebit.hex:h