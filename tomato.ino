#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"
#include "constants.h"

Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix();

mode_t mode = MODE_SETTING;
// initialziation of global variables
uint8_t minutes_set = 25;
unsigned long running_since_millis = 0;

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
}

// no can be 0 or 1 depending on the button pressed.
void buttonDown(uint8_t no) {
  switch (mode) {
    case MODE_SETTING:
      if (no == 0) {
        minutes_set+=5;
        if (minutes_set >= MAX_MINUTES)
          minutes_set = 5;
      }
      if (no == 1) {
        setMode(MODE_RUNNING);
      }
      break;
    case MODE_RUNNING:
      setMode(MODE_OFF);
      break;
    case MODE_ALARM:
      setMode(MODE_OVERTIME);
      break;
    case MODE_OVERTIME:
      setMode(MODE_OFF);
      break;
    case MODE_OFF:
      setMode(MODE_SETTING);
      break;
  }
}

// no can be 0 or 1 depending on the button pressed.
void buttonDownLong(uint8_t no) {
  switch (mode) {
    case MODE_SETTING:
      if (no == 0)
        minutes_set = 5;
    break;
    case MODE_RUNNING:
      break;
    case MODE_ALARM:
      break;
    case MODE_OVERTIME:
      break;
    case MODE_OFF:
      break;
  }
}

void setMode(mode_t to_mode) {
  mode = to_mode;
  switch (mode) {
    case MODE_SETTING:
      break;
    case MODE_RUNNING:
      running_since_millis = millis();
      break;
    case MODE_ALARM:
      break;
    case MODE_OVERTIME:
      break;
    case MODE_OFF:
      // clear display when chaning into OFF, so we do not need to do anything in the MODE_OFF state
      matrix.clear();
      matrix.writeDisplay();
      break;
  }
}

void doMode() {
  switch (mode) {
    case MODE_SETTING:
      doSetting();
    break;
    case MODE_RUNNING:
      doRunning();
      break;
    case MODE_ALARM:
      doAlarm();
      break;
    case MODE_OVERTIME:
      doOvertime();
      break;
    case MODE_OFF:
      doOff();
      break;
  }
}

void drawExpand(uint8_t minutes, uint8_t ones_color, uint8_t first_ring_color, uint8_t ring_color, uint8_t brightness) {
  matrix.setBrightness(brightness);
  matrix.clear();
  if (minutes >= ((8-ONES_WIDTH)*10 + 10)) {
    matrix.fillRect(0,0,8,8, ring_color);
    return;
  }
  uint8_t ones = minutes % 10;
  uint8_t tens = minutes / 10;

  // draw ones bitmap
  for (uint8_t j=0; j < ONES_HEIGHT; j++) {
    for (uint8_t i=0; i < ONES_WIDTH; i++) {
      if (ONE_BMPS[ones][j][i]) {
        matrix.drawPixel(i, 8-ONES_WIDTH+j, ones_color);
      }
    }
  }
  // draw 10 min rings
  for (uint8_t i=0; i < tens; i++) {
    uint8_t color = ring_color;
    if (i == 0)
      color = first_ring_color;
    matrix.drawLine(0, 8-ONES_HEIGHT-1-i, ONES_WIDTH+i, 8-ONES_HEIGHT-1-i, color); // horizontal line
    matrix.drawLine(ONES_WIDTH+i, 8-ONES_HEIGHT-1-i, ONES_WIDTH+i, 7, color); // vertical line
  }
  matrix.writeDisplay();
}  

void doSetting() {
  drawExpand(minutes_set, LED_YELLOW, LED_YELLOW, LED_YELLOW, LED_BRIGHT);
}

void doRunning() {
  uint8_t minutes_past = (millis() - running_since_millis) / MILLIS_TO_MINUTE_RATIO; // we ignore the overflow (approx. every 50 days)
  if (minutes_past >= minutes_set) {
    setMode(MODE_ALARM);
  }
  drawExpand(minutes_set - minutes_past, LED_GREEN, LED_YELLOW, LED_GREEN, LED_DARK);
}

void doAlarm() {
  unsigned long millis_over = -(millis() - running_since_millis);
  // will give a number between 0 and 15;
  float pulse = 0.5 + sin((millis_over % (ALARM_PULSE_DURATION * 1000)) / (ALARM_PULSE_DURATION * 1000.0) * 2.0 * PI) / 2.0; // pulses between 0.0 and 1.0 in ALARM_PULSE_DURATION seconds
  
  matrix.clear();
  
  matrix.setBrightness((uint8_t)(pulse * LED_BRIGHT));
  uint8_t box_size = min(8, 9 * pulse);
  matrix.fillRect(0,0, box_size, box_size, LED_RED);
  matrix.writeDisplay();
}

void doOvertime() {
  uint8_t minutes_past = (millis() - running_since_millis) / MILLIS_TO_MINUTE_RATIO; // we ignore the overflow (approx. every 50 days)
  drawExpand(minutes_past - minutes_set, LED_RED, LED_YELLOW, LED_RED, LED_BRIGHT);
}

void doOff() {
  // let's reduce energy consumption and not clear the display all the time (only done once when display state changes).
  // and now let's wait a bit.
  delay(500);
}

void setup() {
  matrix.begin(0x70);
  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);
}

void loop() {
  checkButtons();
  doMode();
  
  delay(50);
}
