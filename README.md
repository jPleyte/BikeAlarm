# BikeAlarm
This project involves running a wire along the length of your bike lock. When the wire is cut an alarm goes off. An IR remote is used to turn the alarm on and off.

This project is still in the the development phase so I will first document how to build it on a breadboard and then follow up with instructions on soldering everything together on an ElectroCookie half breadboard that can be placed in to a water bottle and fitted on to your bike.

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
* male and female barrel connector for (dis)connecting device and lock


#### Initial Setup

*

## Production setup

## Where I left off
- 2021.6.14: Evertying is in order. Just need to add some reality


## To Do
- [ ] Bug: After enabling the alarm, and then restoring the wire: no lights are on. what is the state?
- [ ] Results are potentially random when input is unplugged (ex unplug d2 but hold it in your hand)
- [x] Disable alarm when disarmed
    - Instead of connecting input to vcc, raise and lower signal manually
- [x] bug: once the alarm goes on, it can't be turned off.
    - To fix this arlarming mneeds to be made in to a function
- [x] Improve battery performance by not performing on/off functions when nothing has changed.
    - eg. previousState != currentState
- [ ] Don't check the IR receiver too often, that will probably drain the battery
- [ ] Poewr the arduino with a battery rather than USB; but allow for both for debugging
- [x] Order a 2xAAA battery holder
- [x] Acquire a bikelock for testing and figuring out how to set it up
- [ ] Power source is currently a 9v battery. Need to change this to a 2xAAA battery and connect it to the alarm.
- [x] Connect remote control
- [ ] Tape this thing to an actual bike lock
- [ ] add a wifi mod so it will send an sms or email as part of the alarm
- [ ] Reduce power consumption by turning off LEDs; including ENABLE_LED_FEEDBACK

## Weaknesses
* using the Ultra TuF (TM) Door Alarm means that if you put a magnet next to the alarm you can prevent the alarm from sounding
  - the solution to this is to just use a piezo instead of a commercial alarm
* single digit arm/disarm code is week
* Alert wire can be cut and then reconnected to silence it.
  - Consider leaving the alarm on once it is triggered.
