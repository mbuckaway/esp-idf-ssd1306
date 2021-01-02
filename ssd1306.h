#ifndef MAIN_SSD1306_H_
#define MAIN_SSD1306_H_

#include "sdkconfig.h"
#include "driver/spi_master.h"

#define SCREEN_WIDTH_MAX 128
#if CONFIG_SSD1306_128x32
#define SCREEN_HEIGHT_MAX 32
#else
#define SCREEN_HEIGHT_MAX 64
#endif

#define SCREEN_MAX_PAGES 8

typedef enum {
	SCROLL_RIGHT = 1,
	SCROLL_LEFT = 2,
	SCROLL_DOWN = 3,
	SCROLL_UP = 4,
	SCROLL_STOP = 5
} ssd1306_scroll_type_t;

typedef struct {
	bool _valid;
	int _segLen; // 0-128
	uint8_t _segs[SCREEN_WIDTH_MAX];
} PAGE_t;

typedef struct {
	int _address;
	int _width;
	int _height;
	int _pages;
	int _dc;
	spi_device_handle_t _SPIHandle;
	bool _scEnable;
	int _scStart;
	int _scEnd;
	int	_scDirection;
	PAGE_t _page[SCREEN_MAX_PAGES];
} SSD1306_t;

/**
 * @brief Configures the ssd1306 driver based on configuration
 * @param SDD1306_t device descriptor which much be allocated before this call
 */
void ssd1306_setup(SSD1306_t *dev);

/**
 * @brief Prints a line of text to a specific line
 * @param dev SSD1306_t device reference
 * @param page Line to which to display the text (max 4 for 128x32 and max 8 for 128x64)
 * @param text null terminated text string to display (max 16 chars)
 * @param invert Display text inverted (black on white background)
 */
void ssd1306_display_text(SSD1306_t *dev, int page, char *text, bool invert);

/**
 * @brief Displays an image
 * @param dev SSD1306_t device reference
 * @param page Line to which to display the text (max 4 for 128x32 and max 8 for 128x64)
 * @param seg segment to use
 * @param images Int array of the data representing the image
 * @param width Width of the image
 */
void ssd1306_display_image(SSD1306_t *dev, int page, int seg, uint8_t *images, int width);

/**
 * @brief Clears the screen
 * @param dev SSD1306_t device reference
 * @param invert invert the screen if true (white)
 */
void ssd1306_clear_screen(SSD1306_t *dev, bool invert);

/**
 * @brief Clears a specific line (max 4 for 128x32 and max 8 for 128x64)
 * @param dev SSD1306_t device reference
 * @param invert invert the line if true (white)
 */
void ssd1306_clear_line(SSD1306_t *dev, int page, bool invert);

/**
 * @brief Sets the contract level
 * @param dev SSD1306_t device reference
 * @param contrast contract level (0=off, 0xFF=Max)
 */
void ssd1306_contrast(SSD1306_t *dev, int contrast);

/**
 * @brief Sets the scroll region used by the ssd1306_scroll_text function and scroll
 * direction. If start>end, then scroll up. Otherwise, if start<end scroll down.
 * @param dev SSD1306_t device reference
 * @param start start of the scroll region
 * @param end end of the scroll reqion
 */
void ssd1306_software_scroll(SSD1306_t *dev, int start, int end);

/**
 * @brief Displays text scrolling old text off the screen if needed. Function
 * uses the scroll region defined by ssd1306_software_scroll.
 * @param dev SSD1306_t device reference
 * @param text null terminated text string to display (max 16 chars)
 * @param invert Display text inverted (black on white background)
 */
void ssd1306_scroll_text(SSD1306_t *dev, char *text, bool invert);

/**
 * @brief Clears the scroll region setup by ssd1306_software_scroll
 * @param dev SSD1306_t device reference
 */
void ssd1306_scroll_clear(SSD1306_t *dev);

/**
 * @brief Scrolls the entire screen in the direction specified. Scrolling continues
 * until it is told to stop.
 * @param dev SSD1306_t device reference
 * @param scroll Defines the scroll direction or to stop scrolling
 */
void ssd1306_hardware_scroll(SSD1306_t *dev, ssd1306_scroll_type_t scroll);

/**
 * @brief Scrolls the entire screen in the direction specified. Scrolling continues
 * until it is told to stop.
 * @param buf Buffer data to invert bitmap
 * @param blen Length of the bitmap buffer
 */
void ssd1306_invert(uint8_t *buf, size_t blen);

/**
 * @brief Fades the entire screen to blank
 * @param dev SSD1306_t device reference
 */
void ssd1306_fadeout(SSD1306_t * dev);

/**
 * @brief Dumps some interesting items on the dev to the log
 * @param dev SSD1306_t device reference
 */
void ssd1306_dump(SSD1306_t *dev);

#endif /* MAIN_SSD1306_H_ */
