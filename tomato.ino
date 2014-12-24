#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix();

// circuit constants
#define BUTTON1_PIN 6
#define BUTTON2_PIN 7

// user input constants
#define LONG_PRESS_MILLIS 1500
#define MAX_MINUTES 120 // (exclusive)

// drawing constants
#define MINUTES_TOP_OFFSET 1
#define MINUTES_PER_ROW 5
#define MAX_MINUTE_ROWS 6
#define MINUTES_IN_ROWS (MAX_MINUTE_ROWS*MINUTES_PER_ROW)

// modes
enum mode_t {
  MODE_SETTING,
  MODE_RUNNING,
  MODE_OFF
};

mode_t mode = MODE_SETTING;
// initialziation of global variables
uint8_t minutes_left = 20;

// button handling
uint8_t button_pins[2] = {BUTTON1_PIN, BUTTON2_PIN};
unsigned long button_down_millis[2] = {-1, -1};
boolean button_long_fired[2] = {false, false};

void checkButtons() {
  for (uint8_t i = 0; i < 2; i++) {
    if (digitalRead(button_pins[i]) == LOW) {
      if (button_down_millis[i] == -1) { // it was not pressed before
        button_down_millis[i] = millis();
        button_long_fired[i] = false;
        buttonDown(i);
      }
      if (!button_long_fired[i] && ((millis() - button_down_millis[i]) > LONG_PRESS_MILLIS)) {
        button_long_fired[i] = true;
        buttonDownLong(i);
      }
    } else {
      button_down_millis[i] = -1;
    }
  }
  
  return;
}

// no can be 0 or 1 depending on the button pressed.
void buttonDown(uint8_t no) {
  switch (mode) {
    case MODE_SETTING:
      if (no == 0) {
        minutes_left++;
        if (minutes_left > MAX_MINUTES)
          minutes_left = 1;
      }
      if (no == 1) {
        mode = MODE_RUNNING;
      }
      break;
    case MODE_RUNNING:
      // clear display when chaning into OFF, so we do not need to do anything in the MODE_OFF state
      matrix.clear();
      matrix.writeDisplay();
      mode = MODE_OFF;
      break;
    case MODE_OFF:
      mode = MODE_SETTING;
      break;
  }
}

// no can be 0 or 1 depending on the button pressed.
void buttonDownLong(uint8_t no) {
  switch (mode) {
    case MODE_SETTING:
      if (no == 0)
        minutes_left = 1;
    break;
    case MODE_RUNNING:
      break;
    case MODE_OFF:
      break;
  }
}

void draw() {
  switch (mode) {
    case MODE_SETTING:
      drawSetting();
    break;
    case MODE_RUNNING:
      drawRunning();
      break;
    case MODE_OFF:
      drawOff();
      break;
  }
}

void drawSetting() {
  matrix.clear();
  uint8_t minutes_in_rows = minutes_left % MINUTES_IN_ROWS;
  uint8_t period_blocks = minutes_left / MINUTES_IN_ROWS;
  if (minutes_in_rows == 0) { // make that full 30 min are displayed on the left and not on the right
    minutes_in_rows = MINUTES_IN_ROWS;
    period_blocks--;
  }
  
  // draw minutes on the left (minutes_in_rows)
  if (minutes_in_rows/MINUTES_PER_ROW > 0)
    matrix.fillRect(0, MINUTES_TOP_OFFSET, MINUTES_PER_ROW, minutes_in_rows/MINUTES_PER_ROW, LED_GREEN);
  // draw last row
  matrix.fillRect(0, MINUTES_TOP_OFFSET+minutes_in_rows/MINUTES_PER_ROW, minutes_left % MINUTES_PER_ROW, 1, LED_YELLOW);
  // draw periods dots (half hours)
  for (uint8_t i = 0; i < period_blocks; i++) {
    matrix.fillRect(6, i*3, 2, 2, LED_RED);
  }
  matrix.writeDisplay();
}

void drawRunning() {
  matrix.clear();
  matrix.fillRect(0, 0, 8, 8, LED_RED);
  
  // draw the display differently:
  // - set brightness to low
  // - maybe use all dots (64 minutes).
  // - if there are (more than 64 minutes, then make the last)
  
  matrix.writeDisplay();
}

void drawOff() {
  // let's reduce energy consumption:
  delay(500);
}

void setup() {
  matrix.begin(0x70);
  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);
}

void loop() {
  checkButtons();
  draw();
  
  delay(50);

//static const uint8_t PROGMEM smile_bmp[] =
//  { B00111100,
//    B01000010,
//    B10100101,
//    B10000001,
//    B10100101,
//    B10011001,
//    B01000010,
//    B00111100 };
//
//  matrix.blinkRate(2); // blinking on; set to 0 for full on
//  matrix.setBrightness(0); // between 0 and 15
//  matrix.fillRect(0,0, 5,4, LED_GREEN);
//  matrix.fillRect(0,4, 3,1, LED_GREEN);
//  
//  matrix.fillRect(6,0, 2,2, LED_GREEN);
//  matrix.fillRect(6,3, 2,2, LED_GREEN);

//  if (smiling) {
//    matrix.drawBitmap(0, 0, smile_bmp, 8, 8, color);
//  } else {
//    matrix.drawBitmap(0, 0, neutral_bmp, 8, 8, color);
//  }
  // TODO detection for just chaning once
//  if (digitalRead(BUTTON_1_PIN) == LOW) {
//    smiling = !smiling;
//  }
//  
//  if (digitalRead(BUTTON_2_PIN) == LOW) {
//    if (color == LED_GREEN) {
//      color = LED_RED;
//    } else {
//      color = LED_GREEN;
//    }
//  }
  
//  matrix.drawPixel(0, 0, LED_GREEN);
//  matrix.fillRect(0,6, 2,2, LED_GREEN);
//  matrix.drawRect(0,4, 2,2, LED_RED);
//  matrix.fillRect(0,6, 2,2, LED_GREEN);
}
