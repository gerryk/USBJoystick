# USBJoystick
Teensy sketches to adapt an old Thrustmaster F22 to USB HID.

*f22-sfs* contains a sketch to convert both the F22 Joystick and a Suncom SFS Throttle for the full HOTAS experience.
The F22 buttons are read by 3 shift-registers which are polled by SPI and the bits mapped to button presses.
The SFS Throttle buttons are wired in a 3x8 diode matrix, which is read by 11 digital pins, with each of the 3 colums pulling LOW in turn, and each row being read in turn with a LOW signifying a button press.

*f22* is for the F22 Joystick only.

The rest are sketches I used to analyse the behaviour of the button interfaces before adding to the main sketches.
