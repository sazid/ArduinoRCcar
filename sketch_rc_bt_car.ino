/*
Author: Mohammed Sazid Al Rashid
https://github.com/sazid/ArduinoRCcar
*/

#include <AFMotor.h>

AF_DCMotor m_rf(1); // right forward
AF_DCMotor m_lf(2); // left forward
AF_DCMotor m_rb(3); // right back
AF_DCMotor m_lb(4); // left back

char c, prev;
uint8_t speed = 255;
uint8_t turn_factor = 2;
String inString = "";    // string to hold input

void set_speed(uint8_t rf = speed, uint8_t lf = speed, uint8_t rb = speed, uint8_t lb = speed) {
  m_rf.setSpeed(rf);
  m_lf.setSpeed(lf);
  m_rb.setSpeed(rb);
  m_lb.setSpeed(lb);
}

void go_forward() {
  m_rf.run(FORWARD);
  m_lf.run(FORWARD);
  m_rb.run(FORWARD);
  m_lb.run(FORWARD);
  
  set_speed();
}

void go_back() {
  m_rf.run(BACKWARD);
  m_lf.run(BACKWARD);
  m_rb.run(BACKWARD);
  m_lb.run(BACKWARD);
  
  set_speed();
}

void go_right() {
  m_rf.run(BACKWARD);
  m_rb.run(BACKWARD);
  m_lf.run(FORWARD);
  m_lb.run(FORWARD);
  
  set_speed();
}

void go_left() {
  m_rf.run(FORWARD);
  m_rb.run(FORWARD);
  m_lf.run(BACKWARD);
  m_lb.run(BACKWARD);
  
  set_speed();
}

void go_left_forward() {
  m_rf.run(FORWARD);
  m_rb.run(FORWARD);
  m_lf.run(FORWARD);
  m_lb.run(FORWARD);
  
  set_speed(speed, speed/turn_factor, speed, speed/turn_factor);
}

void go_right_forward() {
  m_rf.run(FORWARD);
  m_rb.run(FORWARD);
  m_lf.run(FORWARD);
  m_lb.run(FORWARD);
  
  set_speed(speed/turn_factor, speed, speed/turn_factor, speed);
}

void go_left_backward() {
  m_rf.run(BACKWARD);
  m_rb.run(BACKWARD);
  m_lf.run(BACKWARD);
  m_lb.run(BACKWARD);
  
  set_speed(speed, speed/turn_factor, speed, speed/turn_factor);
}

void go_right_backward() {
  m_rf.run(BACKWARD);
  m_rb.run(BACKWARD);
  m_lf.run(BACKWARD);
  m_lb.run(BACKWARD);
  
  set_speed(speed/turn_factor, speed, speed/turn_factor, speed);
}

void stop_motors() {
  m_rf.run(RELEASE);
  m_lf.run(RELEASE);
  m_rb.run(RELEASE);
  m_lb.run(RELEASE);
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  while (Serial.available() > 0) {
    c = Serial.read();
    // Serial.print(c);
    
    if (isDigit(c)) {
      inString += (char)c;
    } else if (c == '\n') {
      if (inString.length() > 0) {
        if (prev == 'J') {
          speed = inString.toInt();
          set_speed();
        } else if (prev == 'K') {
          turn_factor = inString.toInt();
          set_speed();
        }
      }
      // clear the string for new input:
      inString = "";
    } else if (c == 'F') {
      go_forward();
    } else if (c == 'G') {
      go_back();
    } else if (c == 'S') {
      stop_motors();
    } else if (c == 'L') {
      go_left();
    } else if (c == 'R') {
      go_right();
    } else if (c == 'Q') {
      go_left_forward();
    } else if (c == 'E') {
      go_right_forward();
    } else if (c == 'Z') {
      go_left_backward();
    } else if (c == 'C') {
      go_right_backward();
    } else if (c == 'X') {
      // set full speed
      speed = 255;
      set_speed();
    } else if (c == 'Y') {
      // set partial speed
      speed = 180;
      set_speed();
    } else {
      prev = c;
    }
    
    // delay(10);
  }
}
