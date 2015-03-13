/* USB Thrustmaster F22 Conversion 
   for Teensy 3.1 MCU
   You must select Joystick from the "Tools > USB Type" menu

   Buttons are muxed into shift registers, use the SPI protocol to read them
   F22 Shift-reg are 3 x HCF4021BE
   Wiring from Handle to SPI as follows
   Brown:  +5v    
   Green:  GND
   Orange: SCLK (pin13)
   Red:    SS (pin10)
   Yellow: MISO (pin12)
*/

#include <SPI.h>
const int ss = 10;

unsigned int buttonInputs1;   // data read from SPI
unsigned int buttonInputs2;
unsigned int buttonInputs3;
unsigned int pitch, roll;

#define PINKY  !(buttonInputs1 & 0x80)    /* Pinky Switch */
#define TG1    !(buttonInputs1 & 0x40)    /* Trigger 1 */
#define TG2    !(buttonInputs1 & 0x20)    /* Trigger 2 */
#define S1     !(buttonInputs1 & 0x10)    /* Nose Wheel Steering */
#define PADDLE !(buttonInputs1 & 0x08)    /* Paddle Switch */
#define THUMB  !(buttonInputs1 & 0x04)    /* Pickle */

#define H1D  !(buttonInputs2 & 0x80)    /* HAT */
#define H1R  !(buttonInputs2 & 0x40)
#define H1U  !(buttonInputs2 & 0x20)
#define H1L  !(buttonInputs2 & 0x10)
#define H4U  !(buttonInputs2 & 0x08)    /* Castle */
#define H4L  !(buttonInputs2 & 0x04)
#define H4D  !(buttonInputs2 & 0x02)
#define H4R  !(buttonInputs2 & 0x01)

#define H3D  !(buttonInputs3 & 0x80)    /* Weap */
#define H3R  !(buttonInputs3 & 0x40)
#define H3U  !(buttonInputs3 & 0x20)
#define H3L  !(buttonInputs3 & 0x10)
#define H2D  !(buttonInputs3 & 0x08)    /* Target */
#define H2R  !(buttonInputs3 & 0x04)
#define H2U  !(buttonInputs3 & 0x02)
#define H2L  !(buttonInputs3 & 0x01)

// setup() runs once on boot
void setup() {
  Serial.begin(9600);
  Serial.println("USB Joystick analyser");
  // set the slaveSelectPin as an output:
  pinMode (ss, OUTPUT);
  // start the SPI library:
  SPI.begin();
  // configure the joystick to manual send mode.  This gives precise
  // control over when the computer receives updates, but it does
  // require you to manually call Joystick.send_now().
  Joystick.useManualSend(true);
}


// loop() runs for as long as power is applied
void loop() {
  // take the SS pin low to select the chip
  digitalWrite(ss,LOW);
  // send a value of 0 to read the SPI bytes
  buttonInputs1 = SPI.transfer(0x00);
  buttonInputs2 = SPI.transfer(0x00);
  buttonInputs3 = SPI.transfer(0x00);

  pitch = analogRead(0);
  roll = analogRead(1);
  // throttle = analogRead(3);
  Serial.println(buttonInputs1,BIN);
  Serial.println(buttonInputs2,BIN);
  Serial.println(buttonInputs3,BIN);
  // take the SS pin high to de-select the chip:
  digitalWrite(ss,HIGH); 
  if(TG1) Serial.println("Trigger 1");
  if(TG2) Serial.println("Trigger 2");
  if(PINKY) Serial.println("Pinky");
  if(THUMB) Serial.println("Thumb Fire");
  if(H1U) Serial.println("Hat 1 Up");
  if(H1D) Serial.println("Hat 1 Down");
  if(H1L) Serial.println("Hat 1 Left");
  if(H1R) Serial.println("Hat 1 Right");
  if(H2U) Serial.println("Hat 2 Up");
  if(H2D) Serial.println("Hat 2 Down");
  if(H2L) Serial.println("Hat 2 Left");
  if(H2R) Serial.println("Hat 2 Right");
  if(H3U) Serial.println("Hat 3 Up");
  if(H3D) Serial.println("Hat 3 Down");
  if(H3L) Serial.println("Hat 3 Left");
  if(H3R) Serial.println("Hat 3 Right");
  if(H4U) Serial.println("Hat 4 Up");
  if(H4D) Serial.println("Hat 4 Down");
  if(H4L) Serial.println("Hat 4 Left");
  if(H4R) Serial.println("Hat 4 Right");
/*
  Serial.print("Pitch ");
  Serial.print(pitch);
  Serial.print(" Roll ");
  Serial.println(roll);
*/
  // Determine Joystick Hat Position
  int angle = -1;

  if (H1U) {
    if (H1R) {
      angle = 45;
    } else if (H1L) {
      angle = 315;
    } else {
      angle = 0;
    }
  } else if (H1D) {
    if (H1R) {
      angle = 135;
    } else if (H1L) {
      angle = 225;
    } else {
      angle = 180;
    }
  } else if (H1R) {
    angle = 90;
  } else if (H1L) {
    angle = 270;
  }
 /* Serial.print("Hat ");
  Serial.println(angle); */
  Joystick.hat(angle);
  
  // Because setup configured the Joystick manual send,
  // the computer does not see any of the changes yet.
  // This send_now() transmits everything all at once.
  Joystick.send_now();
}
