/************************************************************************************
** Name       : Abbie Dyck                                                         **
** Date       : 03/26/19                                                           **
** Progam Name: LEDChaserWithTone.ino                                              **
** Desc       : This program makes the lights make a pattern, and changes speed    **
**              when a interrupt is triggered, and changes patterns when a         **
**              interrupt is triggered. It will also play a noise when each is     ** 
**              triggered.                                                         **
*************************************************************************************/
const int interruptPin0 = 2;                                                    //makes interruptPin0 as a constant
const int interruptPin1 = 3;                                                    //makes interruptPin1 as a constant
int changePattern       = 0;                                                    //makes changePattern 0
int counter             = 0;                                                    //creates a counter and sets it to 0
int slowDownSpeed       = 100;                                                  //this will slow down the delay by 100ms
int chaser[6][6]        = {{32, 16, 8, 32, 16, 8},                              //pattern 1 - chases from right to left
                           {8, 16, 32, 8, 16, 32},                              //pattern 2 - opposite of 1
                           {8, 16, 32, 16, 8, 16},                              //pattern 3 - weird pattern from left to right, but changes
                           {32, 16, 8, 16, 32, 16},                             //pattern 4 - opposite of 3
                           {32, 48, 56, 56, 48, 32},                            //pattern 5 - from right to left, lighting up
                           {8, 24, 56, 24, 8, 0}                                //pattern 6 - opposite of 5
                          };

void setup() {                
  pinMode(interruptPin0, INPUT_PULLUP);                                           //sets interruptPin0 as a INPUT_PULLUP
  pinMode(interruptPin1, INPUT_PULLUP);                                           //sets interruptPin1 as a INPUT_PULLUP
  pinMode(7, OUTPUT);                                                             //sets up pin 7 as a output for the speaker
  DDRB = B1111111;                                                                //sets up all of port B as a output
  attachInterrupt(digitalPinToInterrupt(interruptPin0), chaserSpeed, FALLING);    //attaches interruptPin0 to interrupt 1
  attachInterrupt(digitalPinToInterrupt(interruptPin1), chaserPattern, FALLING);  //attaches interruptPin1 to interrupt 2
}//end of setup()

void loop() {
  if (counter < 5) {                                                            //if loop to make the lights chase
    counter++;                                                                  //adds 1 to counter
  } else {
    counter = 0;                                                                //makes counter 0 if its exceeds 5
  }//end if()
  PORTB = chaser[changePattern] [counter] ;                                     //makes the pattren of the array change, and move thorugh the pattern
  delay(slowDownSpeed);                                                         //delays for the value of slowDownSpeed
}//end of loop()

/*********************************************************
**  Name    : buttonTone();                             **
**  Inputs  : pin for speaker                           **           
**            freqency for speaker                      **
**  Returns : void (nothing)                            **
**  Desc    : changes tone freqency for speaker         **
**********************************************************/
void buttonTone(int pin, int freq){
  tone(pin, freq, 1000);                                                        //sets up the tone() to be used for the speaker
}//end of buttonTone()

/**********************************************************
** INTERRUPTS BELOW                                      **
**********************************************************/

/*********************************************************
**  Name    : chaserSpeed();                            **
**  Inputs  : None                                      **
**  Returns : void (nothing)                            **
**  Desc    : Changed the speed of the pattern          **
**********************************************************/
void chaserSpeed() {
  static unsigned long last_interrupt_time = 0;                                 // creates a var that holds the LAST time the INT was pressed
  unsigned long interrupt_time = millis();                                      // CREATES A VAR THAT HOLDS THE CURRENT TIME IN MS
  if (interrupt_time - last_interrupt_time > 100) {
    slowDownSpeed = slowDownSpeed + 100;                                        //adds 100ms to slowDownSpeed
    buttonTone(7, 1000);                                                        //runs the buttonTone that makes a sound using the speaker
    if (slowDownSpeed > 2000) {                                                 //if slowDownSpeed is greater than 1s
      slowDownSpeed = 100;                                                      //set slowDownSpeed to 0
    } //end of if()
  }//end if()
  last_interrupt_time = interrupt_time;                                         // UPDATE THE LAST TIME THE INTERRUPT WAS PRESSED
}// end of chaserSpeed()

/*********************************************************
**  Name    : chaserPattern();                          **
**  Inputs  : None                                      **
**  Returns : void (nothing)                            **
**  Desc    : Changes the pattern for the caser         **
**********************************************************/
void chaserPattern() {
  static unsigned long last_interrupt_time = 0;                                 // creates a var that holds the LAST time the INT was pressed
  unsigned long interrupt_time = millis();                                      // CREATES A VAR THAT HOLDS THE CURRENT TIME IN MS
  if (interrupt_time - last_interrupt_time > 100) {
    buttonTone(7, 2000);                                                        //runs the buttonTone that makes a sound using the speaker
    if (changePattern < 5) {                                                    //if changePattern is less than 5
      changePattern++;                                                          //add 1
    } else {
      changePattern = 0;                                                        //Make changePattern 0 if it exceeds 5
    }//end if()
  }//end if()
  last_interrupt_time = interrupt_time;                                         // UPDATE THE LAST TIME THE INTERRUPT WAS PRESSED
}// end of chaserPattern()
