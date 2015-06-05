#include <avr/power.h>
#include <Adafruit_NeoPixel.h>

#include "board.h"
#include "fireworks.h"

#define MAX_PARTICLES 20

struct Particle {
    int8_t x;
    int8_t y;
    int8_t xVel;
    int8_t yVel;
    uint32_t color;
    uint8_t counter;
    uint8_t stage;
    bool alive;
} particles[MAX_PARTICLES];

#define FRAME_DELAY 10

const int8_t X_VELOCITIES[] = { -2, 0, 2, -1, 1, -2, 0, 2 };
const int8_t Y_VELOCITIES[] = { -1, -2, -1, 0, 0, 1, 2, 1 };

uint32_t nextFirework;

void createExploder() {
    int particle = 0;
    uint32_t color = createColor(30 + random(70), 80 + random(70), 40 + random(70));
    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (!particles[i].alive) {
            particles[i].x = random(3, 27);
            particles[i].y = random(1, 6);
            particles[i].xVel = X_VELOCITIES[particle];
            particles[i].yVel = Y_VELOCITIES[particle];
            particles[i].stage = 13;
            particles[i].counter = 1;
            particles[i].alive = true;
            particles[i].color = color;
            particle++;
        }
        if (particle > 7) {
            break;
        }
    }
}

void fireworksFrame(uint32_t ticks) {

    if (ticks > nextFirework) {
        createExploder();
        nextFirework = ticks + 40 + random(40);
    }

    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (particles[i].alive) {
            particles[i].counter--;
            if (particles[i].counter <= 0) {
                setPixel(particles[i].x, particles[i].y, 0, 0, 0);
                particles[i].x += particles[i].xVel;
                particles[i].y += particles[i].yVel;
                setPixel(particles[i].x, particles[i].y, particles[i].color);
                particles[i].counter = FRAME_DELAY;
                particles[i].stage--;

                if (particles[i].stage == 10) {
                    particles[i].xVel = 0;
                    particles[i].yVel = 1;
                }
            }
            particles[i].alive = particles[i].stage > 0;
        }
    }

}