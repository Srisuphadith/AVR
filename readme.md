# programmer ATmega328P

compile C code to hex with avr-gcc and avr-objcopy
```
sh avr-hex.sh [filename]
```
upload code to ATmega328P with avrdude
```
sh avr-upload.sh [filename]
```
Read fuse bit and save to file [hbit.hex, lbit.hex, ebit.h] with avrdude

```
sh avr-rfuse.sh
```