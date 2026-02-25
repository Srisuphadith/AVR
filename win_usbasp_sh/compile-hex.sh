fileName=$1
avr-gcc -mmcu=atmega328p -Os -o ../${fileName}.elf ../code/${fileName}.c
avr-objcopy -O ihex -R.eeprom ../${fileName}.elf ../${fileName}.hex