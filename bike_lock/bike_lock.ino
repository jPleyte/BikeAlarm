#include <IRremote.h>

const int TRIGGER_PIN_OUT = 2; 
const int TRIGGER_PIN_IN = 3; 
//const int IN_PIN = 2;
const int ALARM_ON_PIN = 4;
const int IR_IN_PIN = 10; 
const int LED_GREEN = 8;
const int LED_YELLOW = 7;
const int LED_RED_MAIN = 6;

const int ENABLE_ALARM_IR_CODE = 66; // "7"
const int DISABLE_ALARM_IR_CODE = 94; // "3"

bool isAlarmArmed = false;
int switchState = 0;

const bool IS_ARMED = false;

void setup() {
  Serial.begin(9600);  

  // Monitor the IR reciever for input
  IrReceiver.begin(IR_IN_PIN, ENABLE_LED_FEEDBACK);

  // Indicator LEDs: green power, yellow armed
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED_MAIN, OUTPUT);
  
  digitalWrite(LED_GREEN, HIGH);  
  digitalWrite(LED_YELLOW, LOW);  
  digitalWrite(LED_RED_MAIN, LOW);

  pinMode(TRIGGER_PIN_OUT, OUTPUT);
//  pinMode(TRIGGER_PIN_IN, INPUT_PULLUP);
//  pinMode(TRIGGER_PIN_IN, INPUT_PULLDOWN); // doesn't exist 
//  pinMode(TRIGGER_PIN_IN, INPUT);
//   pinMode(TRIGGER_PIN_IN);
  pinMode(ALARM_ON_PIN, OUTPUT);  
  digitalWrite(TRIGGER_PIN_OUT, HIGH);
  digitalWrite(ALARM_ON_PIN, LOW);  
  delay(1000);
  Serial.println("Setup complete");
}

void loop() {
  // Look for input from the IR remote
  if (IrReceiver.decode()) {
    int signal = IrReceiver.decodedIRData.command;
    if(signal == ENABLE_ALARM_IR_CODE) {
      Serial.println("Turn alarm on");
      digitalWrite(LED_GREEN, LOW);  
      digitalWrite(LED_YELLOW, HIGH); 
      isAlarmArmed = true; 
    } else if(signal == DISABLE_ALARM_IR_CODE) {
      Serial.println("Turn alarm off");
      digitalWrite(LED_GREEN, HIGH);  
      digitalWrite(LED_YELLOW, LOW);  
      isAlarmArmed = false;
    } else {
      Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);      
    }
    
    delay(500);
    IrReceiver.resume(); // Receive the next value
  }

  // Don't check connectivity if alarm is off
  if(isAlarmArmed == false) {
    return;
  } else {
    digitalWrite(TRIGGER_PIN_OUT, HIGH);      
  }
  
  switchState = digitalRead(TRIGGER_PIN_IN);

  // "If the pin isn’t connected to anything, digitalRead() can return either HIGH or LOW (and this can change randomly)."
  if(switchState == LOW) {
    Serial.println("Wire has been cut");
    digitalWrite(LED_RED_MAIN, HIGH);
    
    // Send the signal to alert
    digitalWrite(ALARM_ON_PIN, HIGH);    

    // Give the transistor time to react otherwise results are iffy
    delay(1000);
  } else {
    Serial.println("Wire is intact");
    digitalWrite(LED_RED_MAIN, LOW);
    digitalWrite(ALARM_ON_PIN, LOW);

    // Give the transistor time to react otherwise results are iffy
    delay(1000);
  }
}
