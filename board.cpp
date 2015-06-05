#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

#include "board.h"

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setupLedBoard() {
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  pixels.begin(); // This initializes the NeoPixel library.
  pixels.show();
}

void setPixel(int x, int y, uint32_t color) {
  // The pixel bust be in bounds to be rendered
  if (x >= 0 && x < GRID_WIDTH && y >= 0 && y < GRID_HEIGHT) {
    x = y & 1 == 1 ? (x - GRID_WIDTH - 1) * -1 : x;
    int index = ((y * GRID_WIDTH + x) - NUMPIXELS) * -1;
    pixels.setPixelColor(index, color);
  }
}

void setPixel(int x, int y, int r, int g, int b) {
  setPixel(x, y, createColor(r, g, b));
}

void render() {
  pixels.show();
}

uint32_t createColor(uint8_t r, uint8_t g, uint8_t b) {
  return pixels.Color(r, g, b);
}


// Taken from NeoPixel library
uint32_t Wheel(uint8_t WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}