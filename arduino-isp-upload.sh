fileName=$1
avrdude -c arduino -p m328p -P /dev/cu.usbserial-1310 -b 19200 -U flash:w:${fileName}.hex