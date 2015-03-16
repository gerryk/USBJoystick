/* USB Suncom SFS Conversion 
   for Teensy 3.1 MCU
   You must select Joystick from the "Tools > USB Type" menu

   Buttons are muxed into rows and columns
   SEL1, 2, 3 (columns) on Pins 17, 18, 19 - these need pull-downs
   Rows on pins 1, 2, 3, 4, 5, 6, 7, 8
   
*/
// 2-dimensional array of row pin numbers:
const int row[8] = { 1,2,3,4,5,6,7,8 };

// 2-dimensional array of column pin numbers:
const int col[3] = { 18,19,20 };

// setup() runs once on boot
void setup() {
  Serial.begin(9600);
  delay(2000);
  Serial.println("SFS Throttle Button analyser");
  delay(1000);
  for (int x = 0; x < 3; x++) {
    pinMode(col[x], INPUT);
  } 
  Serial.println("COL init");
  delay(1000);
  for (int x = 0; x < 8; x++) {
    pinMode(row[x], OUTPUT);  
  }
  Serial.println("ROW init");
}


// loop() runs for as long as power is applied
void loop() { 
  for (int x = 0; x < 3; x++) {
    for (int y = 0; y < 8; y++) {
     Serial.print("Button ");
     Serial.print(x);
     Serial.print("-");
     Serial.println(y);
     digitalWrite(row[y], HIGH);      
     delay(30);
     if (digitalRead(col[x]))  {
        Serial.println("Peww");
      }
     digitalWrite(row[y], LOW);      
    }
  }
}
