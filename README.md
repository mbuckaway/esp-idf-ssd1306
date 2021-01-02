# SSD1306 Driver for ESP-IDF

This is a simple SSD1306 OLED display library based on the code from [nopnop2002's SSD1306 library](https://github.com/nopnop2002/esp-idf-ssd1306). There are lots of libraries available for this simple display, but all I wanted was to display text on the screen on a device as it boots up. I wanted something simple to display status information. This library does that.

This library supports:

- component for the ESP-IDF (just add to your project as a git submodule)
- I2C and SPI OLED displays 128x32 or 128x64. SPI displays are assumed to be 128x64.
- Using the included 8x8 font, it will display 4 lines of 16 chars on 128x32 displays, and 8 lines of 16 chars on 128x64 display
- Display images on the display
- Scrolling text based on a defined region (ie. a title line with 3 line of scrolling text)
- Hardware scrolling
- Clear, invert, and other misc functions

What it does not do:

- support anything other than the 8x8 font out of the box. It could/should be updated to use newer font formats that define the char size in the font data, however, it does what I need it to do.

The code has been updated from the original to clean up some of the methods, fix the example code, and "hide" the i2c and spi methods the user really shouldn't call directly. All user methods are documented in ssd1306.h.

The code was based on:
* [nopnop2002's SSD1306 library](https://github.com/nopnop2002/esp-idf-ssd1306)
* [yanbe's SDD1306 library](https://github.com/yanbe/ssd1306-esp-idf-i2c)   
* [8x8 font file from D. Hepper](https://github.com/dhepper/font8x8)  

## Installation for IDF project

Checkout the code as a submodule:

```
mkdir components
git submodule add https://github.com/mbuckaway/esp-idf-ssd1306
idf.py menuconfig
idf.py build
idf.py build
```

For the ESP32-S2 chip, the process is the same, except, you have to set the target first. This is nothing special about this code for the S2 chip, however.

## Config Variables

You have to set this config value with menuconfig.
- CONFIG_INTERFACE
- CONFIG_PANEL
- CONFIG_SDA_GPIO
- CONFIG_SCL_GPIO
- CONFIG_RESET_GPIO
- CONFIG_MOSI_GPIO
- CONFIG_SCLK_GPIO   
- CONFIG_CS_GPIO
- CONFIG_DC_GPIO


![config-main](images/config.png)

See the original repo is you want to see sample images for projects based on the driver.

## Building the example

The code is setup as a componment to be used in your application. To build the example, go into the example directory, and run the following:

```
cd example
idf.py menuconfig
idf.py build
idy.py flash
```

The example will build and be flashed into your device. The example was changed from the original to loop forever and provide logging on the serial console. Useful if you happen to incorrectly setup the GPIO pins.

The example is show running in the photo below.

![example-running](images/sample.jpg)


## Fonts

The basic 8x8 font is provided. The source of the font is from [Daniel Hepper's font8x8 repo](https://github.com/dhepper/font8x8). Other extended fonts are available for such things as European characters, box display, etc. Read font8x8_basic.h for details on how to transport the original font files to use with the SSD1306.

## Usage

The best way to figure out how to use component is to refer to example and the ssd1306.h. The API is straight forward.
