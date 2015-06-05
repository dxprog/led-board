#include <avr/power.h>
#include <string.h>

#include "board.h"
#include "characters.h"
#include "characters_bitmap.h"

#define SPACE_WIDTH 4
#define CHAR_WIDTH  8

void drawCharacter(int character, int x, int y, int r, int g, int b) {
  for (int i = 0; i < 8; i++) {
    uint8_t row = CHARACTERS[character][i];
    for (int j = 0; j < 8; j++) {
      uint8_t offset = 7 - j;
      uint8_t pixel = (row >> offset) & 1;
      if (pixel > 0) {
        setPixel(x + j, y + i, r, g, b);
      } else {
        setPixel(x + j, y + i, 0, 0, 0);
      }
    }
  }
}

void drawNumber(int number, int r, int g, int b) {
  int right = GRID_WIDTH - 8;
  while (number > 0) {
    int digit = number % 10;
    drawCharacter(digit, right, 1, r, g, b);
    number = (int) number / 10;
    right -= 8;
  }
}

void drawString(char *string, int16_t xOffset, int16_t yOffset) {

  uint16_t width = 0;

  for (uint16_t i = 0, len = strlen(string); i < len; i++) {

    int16_t x = xOffset + width;
    uint8_t characterWidth = 0;

    if (string[i] == 32) {
      characterWidth = SPACE_WIDTH;
    } else if (string[i] > 32 && string[i]) {
      characterWidth = CHAR_WIDTH;
    }

    // Determine if the character is within the drawable field
    if (x + characterWidth > -1) {
      drawCharacter(string[i] - 32, x, yOffset, 80, 0, 0);
    }

    width += characterWidth;
    if (width > GRID_WIDTH) {
      break;
    }

  }

}