// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

#include "board.h";
#include "characters.h";
#include "fireworks.h";

uint32_t tick = 0;

char *text = "1234";

void setup() {
  setupLedBoard();
  randomSeed(analogRead(0));
}

void loop() {

/*
  setPixel(x, y, 0, 0, 0);
  x += xVel;
  if (x >= GRID_WIDTH || x < 0) {
    x = x < 0 ? x : GRID_WIDTH - 1;
    xVel *= -1;
  }

  y += yVel;
  if (y >= GRID_HEIGHT || y < 0) {
    y = y < 0 ? y : GRID_HEIGHT - 1;
    yVel *= -1;
  }

  setPixel(x, y, 150, 0, 0);
*/

  tick++;
  // drawNumber(tick, 80, 0, 80);
  drawString(text, 0, 0);
  render();
}
