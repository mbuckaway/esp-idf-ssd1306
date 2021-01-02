#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "ssd1306.h"
#include "font8x8_basic.h"

/*
 You have to set this config value with menuconfig
 CONFIG_INTERFACE

 for i2c
 CONFIG_MODEL
 CONFIG_SDA_GPIO
 CONFIG_SCL_GPIO
 CONFIG_RESET_GPIO

 for SPI
 CONFIG_CS_GPIO
 CONFIG_DC_GPIO
 CONFIG_RESET_GPIO
*/
static const char *tag = "SDD1306_EXAMPLE";

void app_main(void)
{
	SSD1306_t dev = {0};
	int center=0, top=0, bottom=0, max_lines=7;
	char lineChar[20] = {0};

    ESP_LOGI(tag, "[APP] Startup...");
    ESP_LOGI(tag, "[APP] Free memory: %d bytes", esp_get_free_heap_size());
    ESP_LOGI(tag, "[APP] IDF version: %s", esp_get_idf_version());

    esp_log_level_set("*", ESP_LOG_INFO);
    esp_log_level_set("SDD1306_EXAMPLE", ESP_LOG_DEBUG);
    esp_log_level_set("SDD1306", ESP_LOG_DEBUG);
    esp_log_level_set("SDD1306_I2C", ESP_LOG_DEBUG);
    esp_log_level_set("SDD1306_SPI", ESP_LOG_DEBUG);

	ssd1306_setup(&dev);

	while (1)
	{
		ESP_LOGI(tag, "Starting main loop");
		ssd1306_dump(&dev);
		ssd1306_clear_screen(&dev, false);
		ssd1306_contrast(&dev, 0xff);
		ESP_LOGI(tag, "Hello World");
#if CONFIG_SSD1306_128x64 || CONFIG_SPI_INTERFACE
		top = 2;
		center = 3;
		bottom = 8;
		ssd1306_display_text(&dev, 0, "SSD1306 128x64", false);
		ssd1306_display_text(&dev, 1, "ABCDEFGHIJKLMNOP", false);
		ssd1306_display_text(&dev, 2, "abcdefghijklmnop", false);
		ssd1306_display_text(&dev, 3, "Hello World!!", false);
		ssd1306_clear_line(&dev, 4, true);
		ssd1306_clear_line(&dev, 5, true);
		ssd1306_clear_line(&dev, 6, true);
		ssd1306_clear_line(&dev, 7, true);
		ssd1306_display_text(&dev, 4, "SSD1306 128x64", true);
		ssd1306_display_text(&dev, 5, "ABCDEFGHIJKLMNOP", true);
		ssd1306_display_text(&dev, 6, "abcdefghijklmnop", true);
		ssd1306_display_text(&dev, 7, "Hello World!!", true);
#endif // CONFIG_SSD1306_128x64

#if CONFIG_SSD1306_128x32
		top = 1;
		center = 1;
		bottom = 4;
		max_lines = 3;
		ssd1306_display_text(&dev, 0, "SSD1306 128x32", false);
		ssd1306_display_text(&dev, 1, "Hello World!!", false);
		ssd1306_clear_line(&dev, 2, true);
		ssd1306_clear_line(&dev, 3, true);
		ssd1306_display_text(&dev, 2, "SSD1306 128x32", true);
		ssd1306_display_text(&dev, 3, "Hello World!!", true);
#endif // CONFIG_SSD1306_128x32
		vTaskDelay(3000 / portTICK_PERIOD_MS);
    
		ESP_LOGI(tag, "Count down");
		// Display Count Down
		ssd1306_clear_screen(&dev, false);
		uint8_t image[24];
		memset(image, 0, sizeof(image));
		ssd1306_display_image(&dev, top, (6*8-1), image, sizeof(image));
		ssd1306_display_image(&dev, top+1, (6*8-1), image, sizeof(image));
		ssd1306_display_image(&dev, top+2, (6*8-1), image, sizeof(image));
		for(int font=0x39;font>0x30;font--) {
			memset(image, 0, sizeof(image));
			ssd1306_display_image(&dev, top+1, (7*8-1), image, 8);
			memcpy(image, font8x8_basic_tr[font], 8);
			ssd1306_display_image(&dev, top+1, (7*8-1), image, 8);
			vTaskDelay(1000 / portTICK_PERIOD_MS);
		}
		
		ESP_LOGI(tag, "Scroll Up");
		// Scroll Up
		ssd1306_clear_screen(&dev, false);
		ssd1306_contrast(&dev, 0xff);
		ssd1306_display_text(&dev, 0, "---Scroll  UP---", true);
		ssd1306_software_scroll(&dev, max_lines, 1);
		for (int line=0;line<bottom+10;line++) {
			lineChar[0] = 0x01;
			sprintf(&lineChar[1], " Line %02d", line);
			ssd1306_scroll_text(&dev, lineChar, false);
			vTaskDelay(500 / portTICK_PERIOD_MS);
		}
		vTaskDelay(3000 / portTICK_PERIOD_MS);
		
		ESP_LOGI(tag, "Scroll Down");
		// Scroll Down
		ssd1306_clear_screen(&dev, false);
		ssd1306_contrast(&dev, 0xff);
		ssd1306_display_text(&dev, 0, "--Scroll  DOWN--", true);
		ssd1306_software_scroll(&dev, 1, max_lines);
		for (int line=0;line<bottom+10;line++) {
			lineChar[0] = 0x02;
			sprintf(&lineChar[1], " Line %02d", line);
			ssd1306_scroll_text(&dev, lineChar, false);
			vTaskDelay(500 / portTICK_PERIOD_MS);
		}
		vTaskDelay(3000 / portTICK_PERIOD_MS);

		// Page Down
		ESP_LOGI(tag, "Page Down");
		ssd1306_clear_screen(&dev, false);
		ssd1306_contrast(&dev, 0xff);
		ssd1306_display_text(&dev, 0, "---Page  DOWN---", true);
		ssd1306_software_scroll(&dev, 1, max_lines);
		for (int line=0;line<bottom+10;line++) {
			if ( (line % max_lines) == 0) ssd1306_scroll_clear(&dev);
			lineChar[0] = 0x02;
			sprintf(&lineChar[1], " Line %02d", line);
			ssd1306_scroll_text(&dev, lineChar, false);
			vTaskDelay(500 / portTICK_PERIOD_MS);
		}
		vTaskDelay(3000 / portTICK_PERIOD_MS);

		ESP_LOGI(tag, "Horizontal Scroll");
		// Horizontal Scroll
		ssd1306_clear_screen(&dev, false);
		ssd1306_contrast(&dev, 0xff);
		ssd1306_display_text(&dev, center, "Horizontal", false);
		ssd1306_hardware_scroll(&dev, SCROLL_RIGHT);
		vTaskDelay(5000 / portTICK_PERIOD_MS);
		ssd1306_hardware_scroll(&dev, SCROLL_LEFT);
		vTaskDelay(5000 / portTICK_PERIOD_MS);
		ssd1306_hardware_scroll(&dev, SCROLL_STOP);
		
		ESP_LOGI(tag, "Vertical Scroll");
		// Vertical Scroll
		ssd1306_clear_screen(&dev, false);
		ssd1306_contrast(&dev, 0xff);
		ssd1306_display_text(&dev, center, "Vertical", false);
		ssd1306_hardware_scroll(&dev, SCROLL_DOWN);
		vTaskDelay(5000 / portTICK_PERIOD_MS);
		ssd1306_hardware_scroll(&dev, SCROLL_UP);
		vTaskDelay(5000 / portTICK_PERIOD_MS);
		ssd1306_hardware_scroll(&dev, SCROLL_STOP);
		
		ESP_LOGI(tag, "Invert");
		// Invert
		ssd1306_clear_screen(&dev, true);
		ssd1306_contrast(&dev, 0xff);
		ssd1306_display_text(&dev, center, "  Good Bye!!", true);
		vTaskDelay(5000 / portTICK_PERIOD_MS);


		ESP_LOGI(tag, "Fadeout");
		// Fade Out
		ssd1306_fadeout(&dev);
		vTaskDelay(5000 / portTICK_PERIOD_MS);
	}
}
