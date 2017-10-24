#include <Regexp.h>

#define COMM_BUFFER_SIZE 64

// Setup - Everything that has to run once
void setup() {
  Serial.begin(115200);
  Serial.setTimeout(50);
  pinMode(13, OUTPUT);
}

// Loop - Everything that has to run continuously
void loop() {
  if (Serial.available() > 0) {
    Serial.println("RECEIVED MESSAGE");
    readMsg(Serial.readString());
  }
}

// Interpret a message in the serial buffer
void interpretMsg(const char * match, const unsigned int length, const MatchState & ms) {
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
    case 'l':
      digitalWrite(13, param);
      break;
  }
}

// Read the serial buffer
void readMsg(String ser_buf) {
  char buf[COMM_BUFFER_SIZE];
  ser_buf.toCharArray(buf, ser_buf.length() + 1);
  MatchState ms(buf);
  unsigned long count = ms.GlobalMatch ("#(%a)@(%d+)@(%d+)!", interpretMsg);
}

