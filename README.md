# QR scanner Raspberry Pi
![output image]( https://qengineering.eu/images/QR.webp )
## QR and barcode scanner for the Raspberry Pi 3 and 4 (32 and 64 bit OS). <br/>
[![License](https://img.shields.io/badge/License-BSD%203--Clause-blue.svg)](https://opensource.org/licenses/BSD-3-Clause)<br/><br/>
Special made for a bare Raspberry Pi see : [Q-engineering computer vision](https://qengineering.eu/computer-vision-with-raspberry-pi-and-alternatives.html).

------------

## Dependencies.
To run the application, you have to:
- A raspberry Pi 4 with a 32 or 64-bit operating system. It may have a Buster (Debian 10) or Bullseye (Debian 11) operating system. <br/>
- ZBar installed.
- OpenCV installed. [Install OpenCV 4.5](https://qengineering.eu/install-opencv-4.5-on-raspberry-64-os.html) <br/>
- Code::Blocks installed. (```$ sudo apt-get install codeblocks```)
- A working Raspicam.

------------

## Installing ZBar.
You have to install ZBar first. It is a perfect library for scanning QR and barcodes. Much better and faster than the comparable OpenCV module.. 
```
$ sudo apt install autopoint build-essential libv4l-dev libtool
$ git clone -b 0.23.92 https://github.com/mchehab/zbar.git
$ cd zbar
$ autoreconf -vfi
$ ./configure
```
![output image]( https://qengineering.eu/images/QR_build.webp )
```
$ make -j4
$ sudo make install
$ sudo ldconfig
```
Note that ZBar tries to work with /dev/video0, which the Bullseye OS doesn't support (yet). Since we're only using the decoding part of ZBar and not the ability to capture images, it won't affect our project.<br/>
At **Bullseye** you can choose between [LCCV](https://github.com/Qengineering/Libcamera-OpenCV-RPi-Bullseye-64OS) or [GStreamer](https://github.com/Qengineering/Libcamera-OpenCV-RPi-Bullseye-64OS). Whatever you like best.<br/>
The **Buster** operating system uses the relatively simple OpenCV video capture module. You could also use [GStreamer](https://github.com/Qengineering/GStreamer-1.18.4-RPi_64-bits)

### Scanning QR and/or barcodes
In the code you can configure the codes ZBar is trying to decode.
At the beginning of main.cpp you see two lines.
```
scanner.set_config(zbar::ZBAR_NONE, zbar::ZBAR_CFG_ENABLE, 0);
scanner.set_config(zbar::ZBAR_QRCODE, zbar::ZBAR_CFG_ENABLE, 1);
```
The first line `(zbar::ZBAR_NONE, zbar::ZBAR_CFG_ENABLE, 0)` disable all types of code.<br/>
The second line `(zbar::ZBAR_QRCODE, zbar::ZBAR_CFG_ENABLE, 1)` enables only QR codes.<br/>
By removing the first line, all known Barcode types will detected also. More info at [ZBar](http://zbar.sourceforge.net/api/zbar_8h.html#f7818ad6458f9f40362eecda97acdcb0).

------------

## Installing the app.

