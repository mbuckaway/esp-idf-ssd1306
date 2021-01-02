#ifndef I2C_SSD1306_H_
#define I2C_SSD1306_H_

#include "ssd1306.h"

#define SSD1306_I2C_ADDRESS 0x3C

void i2c_master_init(int16_t sda, int16_t scl, int16_t reset);
void i2c_init(SSD1306_t * dev, int width, int height, int I2CAddress);
void i2c_display_text(SSD1306_t * dev, int page, char * text, int text_len, bool invert);
void i2c_display_image(SSD1306_t * dev, int page, int seg, uint8_t * images, int width);
void i2c_contrast(SSD1306_t * dev, int contrast);
void i2c_hardware_scroll(SSD1306_t * dev, ssd1306_scroll_type_t scroll);

#endif