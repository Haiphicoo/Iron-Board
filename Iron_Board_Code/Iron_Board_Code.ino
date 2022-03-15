#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel strip(30, 0, NEO_GRB + NEO_KHZ800);

//Buttons
#include <Bounce2.h>
// INSTANTIATE A Bounce OBJECT
Bounce bounce = Bounce();


//Animation
int numGrid = 30;
int numFrames = 3;
int whichFrame = 0;

//state
int state = 0;

////timer variables
unsigned long timer = 0;
int timerInterval = 2000;
boolean isRed = true;

char index[30] {
  0, 1,
  2, 3, 4, 5,
  6, 7, 8, 9,
  10, 11, 12, 13,
  14, 15, 16, 17, 18, 19,
  20, 21, 22, 23,
  24, 25, 26, 27,
  28, 29
};

char colors [4] [3] {
  {255, 0, 0},   // red
  {200, 255, 0},  // yellow
  {139, 191, 251}, // blue
  {0, 0, 0}        // black
};

char frames[3][30] {
  {
    0, 0,
    0, 0, 0, 0,
    0, 4, 4, 0,
    0, 4, 4, 0,
    0, 4, 4, 4, 4, 0,
    4, 4, 4, 4,
    0, 4, 4, 0,
    0, 0
  },
  {
    0, 0,
    0, 0, 0, 0,
    0, 1, 1, 0,
    0, 1, 1, 0,
    0, 1, 1, 1, 1, 0,
    4, 4, 4, 4,
    0, 1, 1, 0,
    0, 0
  },
  {
    0, 0,
    0, 0, 0, 0,
    0, 1, 1, 0,
    0, 1, 1, 0,
    0, 1, 1, 1, 1, 0,
    2, 2, 2, 2,
    0, 1, 1, 0,
    0, 0
  }
};

void setup() {
  bounce.attach( 1, INPUT ); // USE EXTERNAL PULL-UP
  bounce.interval(50); // interval in ms
  strip.begin();
  strip.show();
}

void loop() {
  bounce.update();

  if ( bounce.rose() ) {
    state += 1;
  }

  if (state > 2) {
    state = 0;
  }

  switch (state) {
    case 0:
      // all NeoPixels off
      for (int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor (i, 0, 0, 0);
        strip.show();
      }
      break;

    case 1:
      //switch from silver to red

      if (millis() - timer >= timerInterval) {
        if (isRed == true) {
          for (int i = 0; i < strip.numPixels(); i++) {
            strip.setPixelColor (i, 128, 128, 128);
            strip.show();
            isRed = false;
          }
        }
        else if (isRed == false) {
          for (int i = 0; i < strip.numPixels(); i++) {
            strip.setPixelColor (i, 255, 0, 0);
            strip.show();
            isRed = true;
          }
        }
        // updating startTime
        timer = millis();
      }
      break;

    case 2:
      //animation

      //for (int j = 0; j < numFrames; j++) {
      if (millis() - timer >= timerInterval) {
        whichFrame++;
        if (whichFrame > 2) {
          whichFrame = 0;
        }
        for (int i = 0; i < numGrid; i++) {
          int whichLED = i;
          int whichIndex = index[whichLED];
          int whichColor = frames[whichFrame][whichLED];

          int r = colors[whichColor][0];
          int g = colors[whichColor][1];
          int b = colors[whichColor][2];

          strip.setPixelColor(whichIndex, r, g, b);
        }
        strip.show();
        // updating startTime
        timer = millis();
      }
      break;
  }
}
