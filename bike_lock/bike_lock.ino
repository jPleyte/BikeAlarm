#include <IRremote.h>

/**
 * Bike alarm.
 * Run the alert wires along your bike alarm. When one is cut an alarm goes off. 
 * LED indicators are exclusive:
 *  green: device is on
 *  yellow: device is on and armed
 *  red: device is on, and alert is triggered. 
 * 
 * 
 *  
 */
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
bool isAlarmArmedPreviousState = false;

//int switchState = 0;

const bool IS_ARMED = false;

void setup() {
  Serial.begin(9600);  

  // Monitor the IR reciever for input
  IrReceiver.begin(IR_IN_PIN, ENABLE_LED_FEEDBACK);

  // Indicator LEDs: green: power, yellow: armed, red: alert
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED_MAIN, OUTPUT);

  // By default power is on, alert is off
  digitalWrite(LED_GREEN, HIGH);  
  digitalWrite(LED_YELLOW, LOW);  
  digitalWrite(LED_RED_MAIN, LOW);

  pinMode(TRIGGER_PIN_OUT, OUTPUT);
  digitalWrite(TRIGGER_PIN_OUT, HIGH);
//  pinMode(TRIGGER_PIN_IN, INPUT_PULLUP);
//  pinMode(TRIGGER_PIN_IN, INPUT_PULLDOWN); // doesn't exist 
//  pinMode(TRIGGER_PIN_IN, INPUT);
//   pinMode(TRIGGER_PIN_IN);
  pinMode(ALARM_ON_PIN, OUTPUT);  
  digitalWrite(ALARM_ON_PIN, LOW);  
  delay(1000);
  
  Serial.println("Setup complete");
}

void loop() {
  // Look for input from the IR remote
  if (IrReceiver.decode()) {
    int signal = IrReceiver.decodedIRData.command;
    if(signal == ENABLE_ALARM_IR_CODE) {
       enableAlarm();
    } else if(signal == DISABLE_ALARM_IR_CODE) {
       disableAlarm();
    } else {
      Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);      
    }
    
    delay(500);

    // Receive the next IR signal
    IrReceiver.resume(); 
  }

  if(isAlarmArmed == true && isAlarmArmedPreviousState == false) {
    digitalWrite(TRIGGER_PIN_OUT, HIGH);
    checkTriggerState();  
  } 

  // jDebug: consider putting a delay here.
}

/**
 * Turn the alarm on: trigger wires must be connected or alert is sounded 
 */
void enableAlarm() { 
  isAlarmArmedPreviousState = isAlarmArmed;
  isAlarmArmed = true;
  Serial.println("Alarm is enabled");
  digitalWrite(LED_GREEN, LOW);  
  digitalWrite(LED_YELLOW, HIGH); 
}

/**
 * Turn the alarm off: regarless of trigger wire connectivity, device goes neutral
 */
void disableAlarm() {
  isAlarmArmedPreviousState = isAlarmArmed;
  isAlarmArmed = false;
  Serial.println("Alarm is disabled");
  digitalWrite(ALARM_ON_PIN, LOW);  
  digitalWrite(LED_GREEN, HIGH);  
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_RED_MAIN, LOW);
}

/**
 * Assume alarm is armed, check the trigger wires to see if they are connected. 
 * Turn on alarm if they are not. 
 */
void checkTriggerState() {
  int switchState = digitalRead(TRIGGER_PIN_IN);

  // "If the pin isn’t connected to anything, digitalRead() can return either HIGH or LOW (and this can change randomly)."
  if(switchState == LOW) {
    soundTheAlarm();
  } else {
    Serial.println("Wire is intact");
    digitalWrite(LED_YELLOW, HIGH);
    digitalWrite(LED_RED_MAIN, LOW);
    digitalWrite(ALARM_ON_PIN, LOW);

    // Give the transistor time to react otherwise results are iffy
    delay(1000);
  }
}

void soundTheAlarm() { 
    Serial.println("Wire has been cut, sounding the alarm");
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_RED_MAIN, HIGH);

    // Send the signal to turn on the alarm
    digitalWrite(ALARM_ON_PIN, HIGH);    

    // Give the transistor time to react otherwise results are iffy
    delay(1000);  
}
