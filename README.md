# QR scanner Raspberry Pi
![output image]( https://qengineering.eu/images/QR.webp )
## QR and barcode scanner for the Raspberry Pi 3 and 4 (32 and 64 bit OS). <br/>
[![License](https://img.shields.io/badge/License-BSD%203--Clause-blue.svg)](https://opensource.org/licenses/BSD-3-Clause)<br/><br/>
Special made for a bare Raspberry Pi see : [Q-engineering computer vision](https://qengineering.eu/computer-vision-with-raspberry-pi-and-alternatives.html).


------------

## Benchmark.
| Operating system | FPS | CPU load |
| ------------- | :-----: | :-----: | 
| Bullseye 64-bit LCCV | 13.5 | 34% |
| Bullseye 64-bit | 12.0 | 46% |
| Bullseye 32-bit | 10.0 | 40% |
| Buster 64-bit | 8.7 | 34% |
| Buster 32-bit | 8.0 | 32% |

All versions work with GStreamer due to its very low latency.<br/>
There is also a Bullseye 64-bit version that works with our [LCCV](https://github.com/Qengineering/LCCV).<br/>
It outperforms GStreamer in terms of FPS and CPU load.

------------

## Dependencies.
To run the application, you have to:
- A raspberry Pi 4 with a 32 or 64-bit operating system. It may have a Buster (Debian 10) or Bullseye (Debian 11) operating system. <br/>
- ZBar installed.
- OpenCV installed. [Install OpenCV 4.5](https://qengineering.eu/install-opencv-4.5-on-raspberry-64-os.html) <br/>
- A working Raspicam.

------------

## Installing ZBar.
You have to install ZBar first. It is a perfect library for scanning QR and barcodes. Much better and faster than the comparable OpenCV module. 
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
Note that ZBar tries to work with /dev/video0, which the Bullseye operating system doesn't support (yet).<br/>
Since we're only using the decoding part of ZBar and not the ability to capture images, it won't affect our project.<br/>

### Scanning QR and/or barcodes
In the code you can configure the codes ZBar is trying to decode.
You can enable all possible codes by the single line
```
scanner.set_config(zbar::ZBAR_NONE, zbar::ZBAR_CFG_ENABLE, 1);
```
Or, if you want to scan a specific code, uncheck everything and then enable the one you want 
```
scanner.set_config(zbar::ZBAR_NONE, zbar::ZBAR_CFG_ENABLE, 0);
scanner.set_config(zbar::ZBAR_QRCODE, zbar::ZBAR_CFG_ENABLE, 1);
```
More info at [ZBar](http://zbar.sourceforge.net/api/zbar_8h.html#f7818ad6458f9f40362eecda97acdcb0).

------------

## Installing the app.

- Make sure you have OpenCV up and running on your system.<br/>
- Choose the folder with your operating system (Buster or BUllseye, 32 or 64 bit).<br/>
- Download the files.<br/>
- You can either build the app with Code::Blocks (`$ sudo apt-get install codeblocks`) or use CMake.<br/>
### Code::Blocks
Load the project file `QR.cbp` and run the app with F9.<br/>
For more info on how to work with the Code::Blocks IDE see our [tutorial](https://qengineering.eu/opencv-c-examples-on-raspberry-pi.html).<br/>
### CMake
```
mkdir build
cd build
cmake ..
make
```
![output image]( https://qengineering.eu/images/QRpi_CMake.png )<br/>
After the build you find the QRpi app in the buiild folder.<br/>
.<br/>
├── build<br/>
│   ├── CMakeCache.txt<br/>
│   ├── CMakeFiles<br/>
│   ├── cmake_install.cmake<br/>
│   ├── Makefile<br/>
│   └── **_QRpi_**<br/>
├── CMakeLists.txt<br/>
├── main.cpp<br/>
└── QRpi.cbp<br/><br/>

------------

## Final remarks.

- Keep the camera resolution at 1024x768 as we will crop the images to the required ZBar size of 720x720.
- The standard Raspicam is not the best choice when it comes to scanning small QR codes. With its fixed focus, the camera cannot zoom in very close. If you need to scan tiny QR codes, consider a variable focus camera like [ArduCam's 8Mp](https://www.uctronics.com/arducam-8-mp-sony-imx219-camera-module-with-m12-lens-ls40136-for-raspberry-pi.html). ![output image]( https://qengineering.eu/images/Arducam_M12.png )<br/><br/>

![output image]( https://qengineering.eu/images/QRsucces.png )

