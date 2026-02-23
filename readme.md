# programmer ATmega328P

Compile C code to hex with ```avr-gcc``` and ```avr-objcopy```
```
sh compile-hex.sh [filename exclude .c]
```
Upload code to ATmega328P with ```avrdude```
```
sh usbasp-upload.sh [filename exclude .hex]
```
Read fuse bit and save to file [hbit.hex, lbit.hex, ebit.h] with avrdude

```
sh usbasp-readFuse.sh
```