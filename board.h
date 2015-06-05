#ifndef __BOARD_H__
#define __BOARD_H__

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6

#define GRID_WIDTH     30
#define GRID_HEIGHT    10

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      300

void setupLedBoard();
void setPixel(int x, int y, int r, int g, int b);
void setPixel(int x, int y, uint32_t color);
void render();
uint32_t createColor(uint8_t r, uint8_t g, uint8_t b);
uint32_t Wheel(uint8_t WheelPos);

#endif __BOARD_H__