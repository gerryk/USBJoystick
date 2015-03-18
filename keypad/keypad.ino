#include <Keypad.h>

const byte numRows= 8; //number of rows on the keypad
const byte numCols= 3; //number of columns on the keypad

//keymap defines the key pressed according to the row and columns just as appears on the keypad
char keymap[numRows][numCols]=
{
{'A', 'B', 'C'},
{'D', 'E', 'F'},
{'G', 'H', 'I'},
{'J', 'K', 'L'},
{'M', 'N', 'O'},
{'P', 'Q', 'R'},
{'S', 'T', 'U'},
{'V', 'W', 'X'}
};

//Code that shows the the keypad connections to the arduino terminals
byte rowPins[numRows] = {0,1,2,3,4,5,6,7}; //Rows 0 to 3
byte colPins[numCols]= {18,19,20}; //Columns 0 to 3

//initializes an instance of the Keypad class
Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);

void setup()
{
Serial.begin(9600);
}

//If key is pressed, this key is stored in 'keypressed' variable
//If key is not equal to 'NO_KEY', then this key is printed out
//if count=17, then count is reset back to 0 (this means no key is pressed during the whole keypad scan process
void loop()
{
char keypressed = myKeypad.getKey();
if (keypressed != NO_KEY)
{
  Joystick.button((int)keypressed-63,1);
  Serial.print((int)keypressed);
}
}
