
[ch65279]//***********************************************************************************************//
//                                                                                               //
//  Name    : Matrix MIDI Keyboard                                                               //
//  Author  : Inky the Hooloovoo                                                                 //
//  Version : 1.1                                                                                //
//  Notes   : Code to use a 8 x 4 switch matrix keyboard as input for an Arduino board           //
//                                                                                               //
//***********************************************************************************************//

//=================================================================================================
                                                                                                 //
int HotPin[8] = {2,3,4,5,6,7,8,9}; //Hot (output) pins                                           //
int GndPin[4] = {10,11,12,13}; //Ground (input) pins                                             //
int OldKeyPress[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};           //
int NewKeyPress[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};           //
int KeyNum = 1; //Identifies the key being read                                                  //
int MidiNote = 60; //The MIDI note to be played (Middle C is 60)                                 //
                                                                                                 //
//=================================================================================================
void setup()                                                                                     //
{                                                                                                //
  Serial.begin(31250); //Start transmiting serial data for MIDI                                  //
  for (int i=0; i <= 3; i++)                                                                     //
  {                                                                                              //
    pinMode(HotPin[i], OUTPUT);   //Set pins 2 through 5 as output pins                          //
    pinMode(HotPin[i+4], OUTPUT); //Set pins 6 through 9 as output pins                          //
    pinMode(GndPin[i], INPUT);    //Set pins 10 through 13 as input pins                         //
  }                                                                                              //
}                                                                                                //
//=================================================================================================
void loop()                                                                                      //
{                                                                                                //
  for (int h=0; h <= 7; h++)                                                                     //
  {                                                                                              //
    digitalWrite(HotPin[h], HIGH);                                                               //
    {                                                                                            //
      for (int g=0; g <=3; g++)                                                                  //
      {                                                                                          //
        KeyNum = (g * 8) + h; //Sets KeyNum to a value from 0 to 31 (C1 is 04)                   //
        NewKeyPress[KeyNum] = digitalRead(GndPin[g]); //Find out if the key if pressed           //
        MidiNote = KeyNum + 56; //Makes C1 on the keyboard middle C                              //
        if (NewKeyPress[KeyNum] == 1 && OldKeyPress[KeyNum] == 0) //If key is pressed            //
        {                                                                                        //
          MidiMessage(0x90, MidiNote, 0x70); //note on, channel 1                                //
        }                                                                                        //
        else if (NewKeyPress[KeyNum] == 0 && OldKeyPress[KeyNum] == 1) //If key is released      //
        {                                                                                        //
          MidiMessage(0x80, MidiNote, 0x70); //note off, channel 1                               //
        }                                                                                        //
        OldKeyPress[KeyNum] = NewKeyPress[KeyNum] //Set state for next check                     //
      }                                                                                          //
    }                                                                                            //
  }                                                                                              //
}                                                                                                //
//=================================================================================================
void MidiMessage(char cmd, char data1, char data2)                                               //
{                                                                                                //
  Serial.print(cmd, BYTE);                                                                       //
  Serial.print(data1, BYTE);                                                                     //
  Serial.print(data2, BYTE);                                                                     //
}                                                                                                //
//=================================================================================================

