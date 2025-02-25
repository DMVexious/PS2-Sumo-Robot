#include <PS2X_lib.h> 
// Define motor connections with Arduino
#define INA1 3 // RF - 5 / I - 3
#define INA2 9 // RB - 6 / I - 9
#define INB1 5 // LB - 3 / I - 5
#define INB2 6 // LF - 9 / I - 6

// Define PS2 dongle connections with Arduino
#define PS2_DAT 11
#define PS2_CMD 12
#define PS2_SEL 10
#define PS2_CLK 13
#define pressure false
#define rumble false

PS2X gamepad9;
int error = 0;
byte type = 0;
byte vibration = 0;
int speed=0;
// Track current mode (Mode 1, Mode 2, Mode 3, etc.)
int mode = 1;  // Start with Mode 1
#define MAX_MODES 4  // Max number of modes (Mode 1, Mode 2, Mode 3, Mode 4)

bool lastSquareButtonState = false;
bool lastCircleButtonState = false;
bool lastCrossButtonState = false;
bool lastTriangleButtonState = false;

void setup() {
  pinMode(INA1, OUTPUT);
  pinMode(INA2, OUTPUT);
  pinMode(INB1, OUTPUT);
  pinMode(INB2, OUTPUT);
  Serial.begin(9600);
  delay(100);
  error = gamepad9.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressure, rumble);
  if (error == 0) {
    Serial.println("unknown controller");
  } else if (error == 1) {
    Serial.println("dual shock controller");
  } else if (error == 2) {
    Serial.println("guitar hero controller");
  } else if (error == 3) {
    Serial.println("wireless dual shock");
  }
  delay(3000);
}

// Functions for motor control
void forward() {
  digitalWrite(INA1, HIGH);
  digitalWrite(INA2, LOW);
  digitalWrite(INB1, LOW);
  digitalWrite(INB2, HIGH);
}

void left() {
  digitalWrite(INA1, HIGH);
  digitalWrite(INA2, LOW);
  digitalWrite(INB1, HIGH);
  digitalWrite(INB2, LOW);
}

void right() {
  digitalWrite(INA1, LOW);
  digitalWrite(INA2, HIGH);
  digitalWrite(INB1, LOW);
  digitalWrite(INB2, HIGH);
}

void back() {
  digitalWrite(INA1, LOW);
  digitalWrite(INA2, HIGH);
  digitalWrite(INB1, HIGH);
  digitalWrite(INB2, LOW);
}

void stopp() {
  digitalWrite(INA1, LOW);
  digitalWrite(INA2, LOW);
  digitalWrite(INB1, LOW);
  digitalWrite(INB2, LOW);
}

void loop() {
  gamepad9.read_gamepad(false,vibration);
  int lx = gamepad9.Analog(PSS_LX);
  int ly = gamepad9.Analog(PSS_LY);
  int rx = gamepad9.Analog(PSS_RX);
  int ry = gamepad9.Analog(PSS_RY);
  // Read button states for mode switching
  bool squareButtonState = gamepad9.ButtonPressed(PSB_SQUARE);
  bool circleButtonState = gamepad9.ButtonPressed(PSB_CIRCLE);
  bool crossButtonState = gamepad9.ButtonPressed(PSB_CROSS);
  bool triangleButtonState = gamepad9.ButtonPressed(PSB_TRIANGLE); // Added for Mode 1 switch
  

  if (gamepad9.Button(PSB_L1)){
    speed=200;
  }
  if (gamepad9.Button(PSB_L2)){
    speed-=50;
  }
   if (gamepad9.Button(PSB_R1)){
    speed=0;
  }
     if (gamepad9.Button(PSB_R2)){
    speed+=50;
  }
  

  
  // Switch to Mode 2 when Square button is pressed
  if (squareButtonState && !lastSquareButtonState) {
    mode = 2;  // Set mode to 2
    Serial.println("Switching to Mode 2");
    delay(200);  // Debounce delay
  }
  
  // Switch to Mode 3 when Circle button is pressed
  if (circleButtonState && !lastCircleButtonState) {
    mode = 3;  // Set mode to 3
    Serial.println("Switching to Mode 3");
    delay(200);  // Debounce delay
  }
  
  // Switch to Mode 4 when Cross button is pressed
  if (crossButtonState && !lastCrossButtonState) {
    mode = 4;  // Set mode to 4
    Serial.println("Switching to Mode 4");
    delay(200);  // Debounce delay
  }

  // Switch back to Mode 1 when Triangle button is pressed
  if (triangleButtonState && !lastTriangleButtonState) {
    mode = 1;  // Set mode to 1
    Serial.println("Switching to Mode 1");
    delay(200);  // Debounce delay
  }

  // Save the current button states for the next loop iteration
  lastSquareButtonState = squareButtonState;
  lastCircleButtonState = circleButtonState;
  lastCrossButtonState = crossButtonState;
  lastTriangleButtonState = triangleButtonState;

  // Print the current mode for debugging
  Serial.print("Current Mode: ");
  Serial.println(mode);
  
  // Mode 1: Joint motor control based on joystick
  // if (mode == 1) {
    
    if (ly < 128) {
    analogWrite(INA1, 255-speed);
    analogWrite(INA2, 0);
    analogWrite(INB1, 0);
    analogWrite(INB2, 255-speed);
    } else if (ly > 128) {
    analogWrite(INA1, 0);
    analogWrite(INA2, 255-speed);
    analogWrite(INB1, 255-speed);
    analogWrite(INB2, 0);
    } else if (rx > 128) {
    analogWrite(INA1, 0);
    analogWrite(INA2, 150);
    analogWrite(INB1, 0);
    analogWrite(INB2, 150);
    } else if (rx < 128) {
    analogWrite(INA1, 150);
    analogWrite(INA2, 0);
    analogWrite(INB1, 150);
    analogWrite(INB2, 0);
    } else {
      stopp();
    }
    
  // }

  // // Mode 2: Independent motor control for each motor
  // else if (mode == 2) {
  //   int ry = gamepad9.Analog(PSS_RY); // Right joystick Y for right motor control
  //   int ly = gamepad9.Analog(PSS_LY); // Left joystick Y for left motor control
    
  //   // Left motor control
  //   if (ly < 128) {
  //     digitalWrite(INB1, LOW);
  //     digitalWrite(INB2, HIGH); // Left motor forward
  //   } else if (ly > 128) {
  //     digitalWrite(INB1, HIGH);
  //     digitalWrite(INB2, LOW); // Left motor backward
  //   } else {
  //     digitalWrite(INB1, LOW);
  //     digitalWrite(INB2, LOW); // Stop Left motor
  //   }

  //   // Right motor control
  //   if (ry < 128) {
  //     digitalWrite(INA1, HIGH);
  //     digitalWrite(INA2, LOW); // Right motor forward
  //   } else if (ry > 128) {
  //     digitalWrite(INA1, LOW);
  //     digitalWrite(INA2, HIGH); // Right motor backward
  //   } else {
  //     digitalWrite(INA1, LOW);
  //     digitalWrite(INA2, LOW); // Stop Right motor
  //   }
  // }

  // // Mode 3: Custom behavior for Mode 3
  // else if (mode == 3) {
  //    int speed = map(ly, 128, 0, 128, 255);  // Speed should be proportional to LY
  //   if (ly < 128) {
  //     analogWrite(INA1, speed);
  //     digitalWrite(INA2, LOW);
  //     digitalWrite(INB1, LOW);
  //     analogWrite(INB2, speed);
  //   } else if (ly > 128) {
  //     digitalWrite(INA1, LOW);
  //     analogWrite(INA2, ly);
  //     analogWrite(INB1, ly);
  //     digitalWrite(INB2, LOW);
  //   } else if (rx > 128) {
  //     right();
  //   } else if (rx < 128) {
  //     left();
  //   } else {
  //     stopp();
  //   }

  // }

  // // Mode 4: Custom behavior for Mode 4
  // else if (mode == 4) {
  //   int speed = map(ly, 128, 0, 75, 255);  // Speed should be proportional to LY
  //  if (ly < 128) {
  //     digitalWrite(INB1, LOW);
  //     analogWrite(INB2, speed); // Left motor forward
  //   } else if (ly > 128) {
  //     analogWrite(INB1, ly);
  //     digitalWrite(INB2, LOW); // Left motor backward
  //   } else {
  //     digitalWrite(INB1, LOW);
  //     digitalWrite(INB2, LOW); // Stop Left motor
  //   }

  //   // Right motor control
  //   if (ry < 128) {
  //     analogWrite(INA1, speed);
  //     digitalWrite(INA2, LOW); // Right motor forward
  //   } else if (ry > 128) {
  //     digitalWrite(INA1, LOW);
  //     analogWrite(INA2, ly); // Right motor backward
  //   } else {
  //     digitalWrite(INA1, LOW);
  //     digitalWrite(INA2, LOW); // Stop Right motor
  //   }
  // }
}
