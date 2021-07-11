#include <IRremote.h>

const int IN_PIN = 2;
const int OUT_PIN = 4;
const int IR_IN_PIN = 10; 
const int LED_GREEN = 8;
const int LED_YELLOW = 7;

const int ENABLE_ALARM_IR_CODE = 66; // "7"
const int DISABLE_ALARM_IR_CODE = 94 // "3"



int switchState = 0;

const bool IS_ARMED = false;

void setup() {
  Serial.begin(9600);  

  // Monitor the IR reciever for input
  IrReceiver.begin(IR_IN_PIN, ENABLE_LED_FEEDBACK);

  // Indicator LEDs: green power, yellow armed
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  digitalWrite(LED_GREEN, HIGH);  
  digitalWrite(LED_YELLOW, LOW);  
  
  pinMode(IN_PIN, INPUT);
  pinMode(OUT_PIN, OUTPUT);  
  digitalWrite(OUT_PIN, LOW);  
  delay(1000);
  Serial.println("Setup complete");
}

void loop() {
  // Look for input from the IR remote
  if (IrReceiver.decode()) {
    int signal = IrReceiver.decodedIRData.command;
    if(signal == ENABLE_ALARM_IR_CODE) {
      Serial.println("Recieved on-code 66 ('7')");
      digitalWrite(LED_GREEN, LOW);  
      digitalWrite(LED_YELLOW, HIGH);  
    } else if(signal == DISABLE_ALARM_IR_CODE) {
      Serial.println("recieved off-code 94 ('3')");
      digitalWrite(LED_GREEN, HIGH);  
      digitalWrite(LED_YELLOW, LOW);  
    } else {
      Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);      
    }
    delay(500);
    IrReceiver.resume(); // Receive the next value
  }
    
  switchState = digitalRead(IN_PIN);
  
  if(switchState == LOW) {
    Serial.println("Wire has been cut");

    // Send the signal to ignite
    digitalWrite(OUT_PIN, HIGH);    

    // Give the transistor time to react otherwise results are iffy
    delay(1000);
  } else {
    Serial.println("Wire is intact");
    digitalWrite(OUT_PIN, LOW);

    // Give the transistor time to react otherwise results are iffy
    delay(1000);
  }
}
