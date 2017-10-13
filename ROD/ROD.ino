#include <Doors.h>
#include <Slope.h>
#include <Wheels.h>
#include <Gimbal.h>
#include <Regexp.h>

// Pin definitions (pre-processor)
#define DOOR_L_PIN 1
#define DOOR_R_PIN 9
#define SLOPE_PIN 8
#define WHEEL_L_ENABLE 192
#define WHEEL_R_ENABLE 324
#define WHEEL_L1_PIN 5
#define WHEEL_L2_PIN 1
#define WHEEL_R1_PIN 3
#define WHEEL_R2_PIN 7
#define INTERNAL_LED_PIN 13
#define GIMBAL_X_PIN 10
#define GIMBAL_Y_PIN 11

// Constants
#define RECEIVE_DELAY 50
#define COMM_BUFFER_SIZE 64
#define UPDATE_DELAY 50

// State parameter definitions
#define LEFT_DOOR_IN 1
#define RIGHT_DOOR_IN 2
#define LEFT_DOOR_OUT 3
#define RIGHT_DOOR_OUT 4
#define LEFT_DOOR_STOP 5
#define RIGHT_DOOR_STOP 6
#define BOTH_DOORS_IN 7
#define BOTH_DOORS_OUT 8
#define BOTH_DOORS_STOP 9

// Initialization of libraries
Doors doors(DOOR_L_PIN, DOOR_R_PIN);
Slope slope(SLOPE_PIN);
Wheels wheels(WHEEL_L1_PIN, WHEEL_L2_PIN, WHEEL_R1_PIN, WHEEL_R2_PIN, WHEEL_L_ENABLE, WHEEL_R_ENABLE);
Gimbal gimbal(GIMBAL_X_PIN, GIMBAL_Y_PIN);

bool LED_ON = false;

// Update all actuators
void update() {
  doors.update();
  slope.update();
  gimbal.update();
}

// Setup - Everything that has to run once
void setup() {
  Serial.begin(115200);
  Serial.setTimeout(RECEIVE_DELAY);
  pinMode(INTERNAL_LED_PIN, OUTPUT);
}

// Loop - Everything that has to run continuously
void loop() {
  if (Serial.available() > 0) {
    readMsg(Serial.readString());
  }

  update();
  delay(UPDATE_DELAY);
}

// Interpret a message in the serial buffer
void interpretMsg(const char * match, const unsigned int length, const MatchState & ms) {
  Serial.println("I'm alive");
  char cap [10];
  char header;
  int param;
  int wSpeed;

  for (byte i = 0; i < ms.level; i++) {
    ms.GetCapture(cap, i);
    switch (i) {
      case 0:
        header = cap[0];
        break;
      case 1:
        param = (int) atol(cap);
        break;
      case 2:
        wSpeed = (int) atol(cap);
        break;
    }
  }

  switch (header) {
    case 'd':
      switch (param) {
        case LEFT_DOOR_IN:
          doors.leftState = DOOR_IN;
          break;
        case LEFT_DOOR_OUT:
          doors.leftState = DOOR_OUT; 
          break;
        case RIGHT_DOOR_IN:
          doors.rightState = DOOR_IN;
          break;
        case RIGHT_DOOR_OUT:
          doors.rightState = DOOR_IN;
          break;
        case LEFT_DOOR_STOP:
          doors.leftState = DOOR_STOP;
          break;
        case RIGHT_DOOR_STOP:
          doors.rightState = DOOR_STOP;
        case BOTH_DOORS_IN:
          doors.leftState = DOOR_IN;
          doors.rightState = DOOR_IN;
          break;
        case BOTH_DOORS_OUT:
          doors.leftState = DOOR_OUT;
          doors.rightState = DOOR_OUT;
          break;
        case BOTH_DOORS_STOP:
          doors.leftState = DOOR_STOP;
          doors.rightState = DOOR_STOP;
          break;
      }
      break;
    case 's':
      if (param >= 0 && param <= 2) {
        slope.slopeState = param;
      }
      break;
    case 'w':
      if (param >= 0 && param <= 100 && speed >= 0 && speed <= 100) {
        wheels.update(param, speed);
      }
      break;
    case 'l':
      digitalWrite(INTERNAL_LED_PIN, (LED_ON ? HIGH : LOW));
      LED_ON = !LED_ON;
      break;
    case 'g':
      if(param >= 0 && param <= 4) {
        gimbal.gimbalState = param;
      }
  }
}

// Read the serial buffer
void readMsg(String ser_buf) {
  char buf[COMM_BUFFER_SIZE];
  ser_buf.toCharArray(buf, ser_buf.length() + 1);
  MatchState ms(buf);
  unsigned long count = ms.GlobalMatch ("#(%a+)@(%d+)@(%d+)!", interpretMsg);
}

