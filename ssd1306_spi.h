
#ifndef SPI_SSD1306_H_
#define SPI_SSD1306_H_

#include "driver/spi_master.h"
#include "ssd1306.h"

#define SPI_Address 0xFF

void spi_master_init(SSD1306_t * dev, int16_t GPIO_MOSI, int16_t GPIO_SCLK, int16_t GPIO_CS, int16_t GPIO_DC, int16_t GPIO_RESET);
bool spi_master_write_byte(spi_device_handle_t SPIHandle, const uint8_t* Data, size_t DataLength );
bool spi_master_write_command(SSD1306_t * dev, uint8_t Command );
bool spi_master_write_data(SSD1306_t * dev, const uint8_t* Data, size_t DataLength );
void spi_init(SSD1306_t * dev, int width, int height);
void spi_display_text(SSD1306_t * dev, int page, char * text, int text_len, bool invert);
void spi_display_image(SSD1306_t * dev, int page, int seg, uint8_t * images, int width);
void spi_contrast(SSD1306_t * dev, int contrast);
void spi_hardware_scroll(SSD1306_t * dev, ssd1306_scroll_type_t scroll);

#endif