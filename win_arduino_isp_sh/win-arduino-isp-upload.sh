fileName=$1
avrdude -c arduino -p m328p -P COM4 -b 19200 -U flash:w:../${fileName}.hex