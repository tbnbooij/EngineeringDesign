 #include <Regexp.h>

#define COMM_BUFFER_SIZE 64

const char heartbeat = '_';
const boolean confirm_command = false;

// Setup - Everything that has to run once
void setup() {
  Serial1.begin(115200);
  Serial1.setTimeout(100);
  pinMode(13, OUTPUT);

  while(Serial1.available() > 0) {
    Serial1.read();
  }
}

// Loop - Everything that has to run continuously
void loop() {
  
  while (Serial1.available() > 0) {
    readMsg(Serial1.readString());
    if (confirm_command){
      sendHeartbeat();  
    }
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

      // Debug stuff
      switch(param)
      {
        case 0:
          break;
        case 1:
          break;
      }
      break;
  }
}

void sendHeartbeat(){
    Serial1.println(heartbeat);
    Serial1.flush();
}

// Read the serial buffer
void readMsg(String ser_buf) {
  ser_buf.trim();
  if (ser_buf.length() == 1
        && ser_buf[0] == heartbeat){
    sendHeartbeat();
    return;
  }
  
  char buf[COMM_BUFFER_SIZE];
  ser_buf.toCharArray(buf, COMM_BUFFER_SIZE);
 
  MatchState ms(buf);
  unsigned long count = ms.GlobalMatch ("#(%a)@(%d+)@(%d+)!", interpretMsg);
  
}

