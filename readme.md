# programmer ATmega328P
---
# dependency
- Windowns OS
    - Install ```avr-gcc```
        - link: https://github.com/ZakKemble/avr-gcc-build/releases/download/v15.2.0-1/avr-gcc-15.2.0-x64-windows.zip
        - Unzip file
        - move floder to drive C
        - add ```C:\avr-gcc-15.2.0-x64-windows\bin``` to environment path
        - Finish and restart CMD
    - Install ```avrdude```
        - link: https://github.com/avrdudes/avrdude/releases/download/v8.1/avrdude-v8.1-windows-mingw-x64.zip
        - Unzip file
        - move floder to drive C
        - add ```C:\avrdude-v8.1-windows-mingw-x64``` to environment path
        - Finish and restart CMD
- Mac OS 
    - Install ```brew``` package manage first
        - run in terminal ```/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"```
    - Install ```avr-gcc```
        - use brew ```brew tap osx-cross/avr \ brew install avr-gcc``` 
    - Install 
        - use brew ```brew install avrdude```

---

# Mac OS: ```cd mac_usbasp_sh``` to execute script
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

---

# Windows OS: ```cd win_usbasp_sh``` to execute script
Compile C code to hex with ```avr-gcc``` and ```avr-objcopy```
```
sh ompile-hex.sh [filename exclude .c]
```
Upload code to ATmega328P with ```avrdude```
```
sh win-usbasp-upload.sh [filename exclude .hex]
```
Read fuse bit and save to file [hbit.hex, lbit.hex, ebit.h] with avrdude

```
sh win-usbasp-readFuse.sh
```