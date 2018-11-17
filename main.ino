#include <Joystick.h>

int only_on_press_joystick_buttons[] = {13, 14, 15, 16};
int pins[] =           {22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41};
int joystick_buttons[] = {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32};
int curr[30];
int prev[30];

int PIN_COUNT = 20;
int ONLY_ON_PRESS_COUNT = 4;

int i, j;
int print_count;
int loop_count;

#define MESSAGE_SIZE 100
char message[MESSAGE_SIZE];

bool is_only_on_press;


void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the pushbutton's pin an input:
  pinMode(22, INPUT); // Eject Button
  pinMode(23, INPUT); // Big Red - Left
  pinMode(24, INPUT); // Big Red - Right
  pinMode(25, INPUT); // Big Blue
  pinMode(26, INPUT); // Switch - Bottom - Far Right
  pinMode(27, INPUT);
  pinMode(28, INPUT); // Switch - Bottom - Center Right
  pinMode(29, INPUT); 
  pinMode(30, INPUT); // Switch - Bottom - Center Left
  pinMode(31, INPUT);
  pinMode(32, INPUT); // Switch - Bottom - Far Left
  pinMode(33, INPUT);
  pinMode(34, INPUT); // Switch - Top - Far Right
  pinMode(35, INPUT);
  pinMode(36, INPUT); // Switch - Top - Center Right 
  pinMode(37, INPUT);
  pinMode(38, INPUT); // Switch - Top - Center Left
  pinMode(39, INPUT);
  pinMode(40, INPUT); // Switch - Top - Far Left
  pinMode(41, INPUT);

  for (i = 0; i < PIN_COUNT; i++){
    int pin = pins[i];
    prev[i] = digitalRead(pin);
  }

  Joystick.begin(true);
  loop_count = 0;
}

// the loop routine runs over and over again forever:
void loop() {
  loop_count++;
  for (i = 0; i < PIN_COUNT; i++){
    curr[i] = digitalRead(pins[i]);
    if (curr[i] != prev[i]) {
      is_only_on_press = false;
      for (j = 0; j < ONLY_ON_PRESS_COUNT; j++) {
        if (joystick_buttons[i] == only_on_press_joystick_buttons[j]) {
          is_only_on_press = true;
          break;
        }
      }
      if (! is_only_on_press || (is_only_on_press && prev[i] == LOW)) {
        Joystick.pressButton(joystick_buttons[i]);
        delay(50);
        Joystick.releaseButton(joystick_buttons[i]);
        
        sprintf(message, "Joy%d pressed", joystick_buttons[i]);
        Serial.println(message);
        memset(message, 0, MESSAGE_SIZE);
      }
    }
    prev[i] = curr[i];
  }

  if (loop_count > 50) {
    print_count = 0;
    for(i = 0; i < PIN_COUNT; i++) {
      int pin_state = curr[i];
      Serial.print(pin_state);
      print_count++;
      if (print_count >= 4) {
        Serial.print("|");
        print_count = 0;
      }
    }
    Serial.println("");
    
    loop_count = 0;
  }

  delay(10);        // delay in between reads for stability
}                                                                                 
