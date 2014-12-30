// circuit constants
#define BUTTON1_PIN 6
#define BUTTON2_PIN 7

// user input constants
#define LONG_PRESS_MILLIS 1500
#define MAX_MINUTES 60 // (exclusive)

#define ALARM_PULSE_DURATION 3

// drawing constants
#define MINUTES_TOP_OFFSET 1
#define MINUTES_PER_ROW 5
#define MAX_MINUTE_ROWS 6
#define MINUTES_IN_ROWS (MAX_MINUTE_ROWS*MINUTES_PER_ROW)

#define ONES_WIDTH 3
#define ONES_HEIGHT 3

#define LED_BRIGHT 15 // between 0 and 15
#define LED_DARK 0

static const bool ONE_BMPS[][ONES_HEIGHT][ONES_WIDTH] = { 
    { {0,0,0}, // 0
      {0,0,0},
      {0,0,0} },
    { {0,0,0}, // 1
      {0,1,0},
      {0,0,0} },
    { {1,0,0}, // 2
      {0,0,0},
      {0,0,1} },
    { {0,0,1}, // 3
      {0,1,0},
      {1,0,0} },
    { {0,1,0}, // 4
      {1,0,1},
      {0,1,0} },
    { {0,1,0}, // 5
      {1,1,1},
      {0,1,0} },
    { {1,0,1}, // 6
      {1,0,1},
      {1,0,1} },
    { {1,0,1}, // 7
      {0,1,1},
      {1,1,1} },
    { {1,1,1}, // 8
      {1,0,1},
      {1,1,1} },
    { {1,1,1}, // 9
      {1,1,1},
      {1,1,1} }
  };

// mode type
enum mode_t {
  MODE_SETTING,
  MODE_RUNNING,
  MODE_ALARM,
  MODE_OVERTIME,
  MODE_OFF
};

#define PI 3.14159265
#define MILLIS_TO_MINUTE_RATIO 600