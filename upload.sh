fileName=$1
avrdude -c usbasp -p m328p -P /dev/ttyUSB0 -b 11250 -U flash:w:${fileName}.hex