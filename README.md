# BikeAlarm
This project involves running a wire along the length of you bike lock. When the wire is cut an alarm goes off. An IR remote is used to turn the alarm on and off.

This project is still in the the development phase so I will document how to build this project on a breadboard and follow up with instructions on soldering everything together on an ElectroCookie half breadboard that can be placed in to a water bottle and fitted on to your bike.

## Breadboard setup

### Parts

* (A) 60 pin breadboard
* (B) Arduino mini
* (C) Green LED
* (D) Yellow LED
* (E) Red LED
* (F) IR Sensor (CHQ1838 Infrared (IR) Receiver)
* (G) IR Remote
* (H) Ultra TuF (TM) Door Alarm
* (I) Resistors
* Wires
* AA battery holder
*  male and female barrel connector for (dis)connecting device and lock


#### Initial Setup

*

## Production setup



Arduino mini.
D2 is connected to VCC.
When VCC goes from HIGH to LOW send HIGH on D4
D4 is connected to a transistor which, when sent HIGH, connects power to an alarm.

## History

* Basic setup
I have four breadboards set up.
The first holds the arduino

## Where I left off
The arduino is connected to several breadboards.
D2 is connected to vcc and D2
When you disconnect the green wire (D2) it sends a HIGH signal on D4 triggering the alarm
  - which is currently a red light

## To Do
- [ ] Disable alarm when disarmed
    - Instead of connecting input to vcc, raise and lower signal manually
- [ ] Don't check the IR receiver too often, that will probably drain the battery
- [ ] Poewr the arduino with a battery rather than USB; but allow for both for debugging
- [x] Order a 2xAAA battery holder
- [x] Acquire a bikelock for testing and figuring out how to set it up
- [ ] Power source is currently a 9v battery. Need to change this to a 2xAAA battery and connect it to the alarm.
- [x] Connect remote control
- [ ] Tape this thing to an actual bike lock
- [ ] add a wifi mod so it will send an sms or email as part of the alarm
- [ ] Reduce power consumption by turning off LEDs; including ENABLE_LED_FEEDBACK

## Materials



# BikeAlarm
Arduino
* USB In (for now)
  - 5v out
  - Grnd
  - D2
  - D4




## Weaknesses
* using the Ultra TuF (TM) Door Alarm means that if you put a magnet next to the alarm you can prevent the alarm from sounding
  - the solution to this is to just use a piezo instead of a commercial alarm
* single digit arm/disarm code is week
*
