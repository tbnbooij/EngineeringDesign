#include <Doors.h>
#include <Slope.h>
#include <Wheels.h>
#include <Regexp.h>

// PWM Pin definitions (pre-processor)
#define DOOR_L_PIN 1
#define DOOR_R_PIN 2
#define SLOPE_PIN 3
#define WHEEL_L1_PIN 4
#define WHEEL_L2_PIN 5
#define WHEEL_R1_PIN 6
#define WHEEL_R2_PIN 7
#define RECEIVE_DELAY 50

// State parameter definitions
#define LEFT_DOOR_IN 1
#define RIGHT_DOOR_IN 2
#define LEFT_DOOR_OUT 3
#define RIGHT_DOOR_OUT 4
#define BOTH_DOORS_IN 5
#define BOTH_DOORS_OUT 6


// Initialization of libraries
Doors doors(DOOR_L_PIN, DOOR_R_PIN);
Slope slope(SLOPE_PIN);
Wheels wheels(WHEEL_L1_PIN, WHEEL_L2_PIN, WHEEL_R1_PIN, WHEEL_R2_PIN);

// Update all actuators
void update() {
    doors.update();
    slope.update();
    wheels.update();
}

// Setup - Everything that has to run once
void setup() {
    Serial.begin(115200);
    Serial.setTimeout(RECEIVE_DELAY);
}

// Loop - Everything that has to run continuously
void loop() {
    if(Serial.available() > 0) {
        readMsg(Serial.readString());
    }

    update();
}

// Interpret a message in the serial buffer
void interpretMsg(const char * match, const unsigned int length, const MatchState & ms) {
    char cap [10]; 
    String header;
    int param;
    
    for (byte i = 0; i < ms.level; i++) {
        ms.GetCapture(cap, i);
        switch(i) {
          case 0:
            header = String(cap);
            break;
          case 1:
            param = String(cap).toInt();
            break;
        }
    }

    switch(header) {
      case "d":
      case "door":
        
        int doorStates[2] = {DOOR_STOP, DOOR_STOP};

        switch(param) {
            case LEFT_DOOR_IN:
                doorStates = {DOOR_IN, DOOR_STOP};
                break;
            case LEFT_DOOR_OUT:
                doorStates = {DOOR_OUT, DOOR_STOP};
                break;
            case RIGHT_DOOR_IN:
                doorStates = {DOOR_STOP, DOOR_IN};
                break;
            case RIGHT_DOOR_OUT:
                doorStates = {DOOR_STOP, DOOR_OUT};
                break;
            case BOTH_DOORS_IN:
                doorStates = {DOOR_IN, DOOR_IN};
                break;
            case BOTH_DOORS_OUT:
                doorStates = {DOOR_OUT, DOOR_OUT};
                break;
        }

        doors.leftState = doorStates[0];
        doors.rightState = doorStates[1];

        break;
      case "s":
      case "slope":
        if(param >= 0 && param <= 2) {
            slope.slopeState = param;
        }
        break;
      case "w":
      case "wheels":
        if(param >= 0 && param <= 2) {
            wheels.wheelsDir = param;
        }
        break;
    }
}

// Read the serial buffer
void readMsg(String ser_buf) {
    char buf[COMM_BUFFER_SIZE];
    ser_buf.toCharArray(buf, ser_buf.length() + 1);
    MatchState ms(buf);
    unsigned long count = ms.GlobalMatch ("#(%a+)@(%d+)!", interpretMsg);
}
