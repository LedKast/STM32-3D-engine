/**
 * This Library was originally written by Olivier Van den Eede (4ilo) in 2016.
 * Some refactoring was done and SPI support was added by Aleksander Alekseev (afiskon) in 2018.
 *
 * https://github.com/afiskon/stm32-ssd1306
 */

#ifndef __SSD1306_H__
#define __SSD1306_H__


#define SSD1306_USE_I2C
#define STM32F1

#if defined(STM32F1)
#include "stm32f1xx_hal.h"
#elif defined(STM32F4)
#include "stm32f4xx_hal.h"
#else
#error "SSD1306 library was tested only on STM32F1 and STM32F4 MCU families. Please modify ssd1306.h if you know what you are doing. Also please send a pull request if it turns out the library works on other MCU's as well!"
#endif

#include "ssd1306_fonts.h"

/* vvv I2C config vvv */

#ifndef SSD1306_I2C_PORT
#define SSD1306_I2C_PORT		hi2c1
#endif

#ifndef SSD1306_I2C_ADDR
#define SSD1306_I2C_ADDR       0x78
#endif

/* ^^^ I2C config ^^^ */

/* vvv SPI config vvv */

#ifndef SSD1306_SPI_PORT
#define SSD1306_SPI_PORT        hspi2
#endif

#ifndef SSD1306_CS_Port
#define SSD1306_CS_Port         GPIOB
#endif
#ifndef SSD1306_CS_Pin
#define SSD1306_CS_Pin          GPIO_PIN_12
#endif

#ifndef SSD1306_DC_Port
#define SSD1306_DC_Port         GPIOB
#endif
#ifndef SSD1306_DC_Pin
#define SSD1306_DC_Pin          GPIO_PIN_14
#endif

#ifndef SSD1306_Reset_Port
#define SSD1306_Reset_Port      GPIOA
#endif
#ifndef SSD1306_Reset_Pin
#define SSD1306_Reset_Pin       GPIO_PIN_8
#endif

/* ^^^ SPI config ^^^ */

#if defined(SSD1306_USE_I2C)
extern I2C_HandleTypeDef SSD1306_I2C_PORT;
#elif defined(SSD1306_USE_SPI)
extern SPI_HandleTypeDef SSD1306_SPI_PORT;
#else
#error "You should define SSD1306_USE_SPI or SSD1306_USE_I2C macro!"
#endif

// SSD1306 OLED height in pixels
#ifndef SSD1306_HEIGHT
#define SSD1306_HEIGHT          64
#endif

// SSD1306 width in pixels
#ifndef SSD1306_WIDTH
#define SSD1306_WIDTH           128
#endif

// some LEDs don't display anything in first two columns
// #define SSD1306_WIDTH           130

// Enumeration for screen colors
typedef enum {
    Black = 0x00, // Black color, no pixel
    White = 0x01  // Pixel is set. Color depends on OLED
} SSD1306_COLOR;

// Struct to store transformations
typedef struct {
    uint16_t CurrentX;
    uint16_t CurrentY;
    uint8_t Inverted;
    uint8_t Initialized;
} SSD1306_t;

// Procedure definitions
void ssd1306_Init(void);
void ssd1306_Fill(SSD1306_COLOR color);
void ssd1306_UpdateScreen(void);
void ssd1306_DrawPixel(uint8_t x, uint8_t y, SSD1306_COLOR color);
char ssd1306_WriteChar(char ch, FontDef Font, SSD1306_COLOR color);
char ssd1306_WriteString(char* str, FontDef Font, SSD1306_COLOR color);
void ssd1306_SetCursor(uint8_t x, uint8_t y);

// extension
void ssd1306_DrawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, SSD1306_COLOR c);
/*
 * @param  x: Top left X start point. Valid input is 0 to SSD1306_WIDTH - 1
 * @param  y: Top left Y start point. Valid input is 0 to SSD1306_HEIGHT - 1
 * @param  w: Rectangle width in units of pixels
 * @param  h: Rectangle height in units of pixels
 */
void ssd1306_DrawRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, SSD1306_COLOR c);
void ssd1306_DrawFilledRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, SSD1306_COLOR c);
void ssd1306_DrawTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, SSD1306_COLOR color);
void ssd1306_DrawCircle(int16_t x0, int16_t y0, int16_t r, SSD1306_COLOR c);
void ssd1306_DrawFilledCircle(int16_t x0, int16_t y0, int16_t r, SSD1306_COLOR c);
/*
 * x, y - left top position
 * w, h - bitmap size
 * bitmap - unsigned char picture[]
 */
void ssd1306_DrawBitmap(uint8_t x, uint8_t y, uint8_t *bitmap, uint16_t w, uint16_t h, SSD1306_COLOR color);

// Low-level procedures
void ssd1306_Reset(void);
void ssd1306_WriteCommand(uint8_t byte);
void ssd1306_WriteData(uint8_t* buffer, size_t buff_size);

#endif // __SSD1306_H__
