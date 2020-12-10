/************************************************************************************
** Name       : Abbie Dyck                                                         **
** Date       : 04/01/19                                                           **
** Progam Name: JaseyBox.ino                                                       **
** Desc       :                                                                    **
*************************************************************************************/

const int contGameIntPin    = 2;                                                    //makes interruptPin0 as a constant
const int restartGameIntPin = 3;                                                    //makes interruptPin1 as a constant

const int LED1              = 9;                                                    //makes pin 9 player 1 LED
const int LED2              = 10;                                                   //makes pin 10 player 2 LED
const int LED3              = 11;                                                   //makes pin 11 player 3 LED
                          
const int player1Button     = 4;                                                    //makes pin 4 player 1 button
const int player2Button     = 5;                                                    //makes pin 4 player 2 button
const int player3Button     = 6;                                                    //makes pin 4 player 3 button

int player1Stopped          = 0;                                                    //makes player 1 stopped == 0
int player2Stopped          = 0;                                                    //makes player 2 stopped == 0
int player3Stopped          = 0;                                                    //makes player 3 stopped == 0

int continueGame            = 0;                                                    //makes continue game == 0
int restartGame             = 0;                                                    //makes restart game == 0

void setup() {
  pinMode(contGameIntPin, INPUT_PULLUP);                                            //sets interruptPin0 as a INPUT_PULLUP
  pinMode(restartGameIntPin, INPUT_PULLUP);                                         //sets interruptPin1 as a INPUT_PULLUP

  pinMode(7, OUTPUT);                                                               //sets up pin 7 as a output for the speaker

  DDRB = B1111111;                                                                  //sets up all of port B as a output

  pinMode(player1Button, INPUT_PULLUP);                                             //makes player1Button a input pullup
  pinMode(player2Button, INPUT_PULLUP);                                             //makes player2Button a input pullup
  pinMode(player3Button, INPUT_PULLUP);                                             //makes player3Button a input pullup

  attachInterrupt(digitalPinToInterrupt(contGameIntPin), contGame, FALLING);        //attaches interruptPin0 to interrupt 1
  attachInterrupt(digitalPinToInterrupt(restartGameIntPin), resetGame, FALLING);    //attaches interruptPin1 to interrupt 2

}//end of setup()

void loop() {
  if (digitalRead(player1Button) == LOW && player1Stopped == 0) {
    buttonPressed(1);                                                               //runs the buttonPressed with 1 as a param
  }//end if()
  if (digitalRead(player2Button) == LOW && player2Stopped == 0) {
    buttonPressed(2);                                                               //runs the buttonPressed with 2 as a param
  }//end if()
  if (digitalRead(player3Button) == LOW && player3Stopped == 0) {
    buttonPressed(3);                                                               //runs the buttonPressed with 3 as a param
  }//end if()
  if (restartGame == 1) {
    blinkLights();                                                                  //runs the blink lights function
    restartGame = 0;                                                                //makes restart game == 0
  }//end if()
}//end of loop()

/*********************************************************
** FUNCTIONS BELOW                                      **
**********************************************************/

/*********************************************************
**  Name    : blinkLights();                            **
**  Inputs  : None                                      **
**  Returns : void (nothing)                            **
**  Desc    : Blinks all 3 lights 3 time to show new    **
**            question/start of game.                   **
**********************************************************/
void blinkLights() {
  for (int x = 0; x < 3; x++) {
    digitalWrite(LED1,HIGH);                                                        //makes LED1 High
    digitalWrite(LED2,HIGH);                                                        //makes LED2 High
    digitalWrite(LED3,HIGH);                                                        //makes LED3 High
    delay(100);                                                                     //delay
    digitalWrite(LED1,LOW);                                                         //makes LED1 Low
    digitalWrite(LED2,LOW);                                                         //makes LED2 Low
    digitalWrite(LED3,LOW);                                                         //makes LED3 Low
    delay(100);                                                                     //delay
  }//end for()
}//end blinkLights()

/*********************************************************
**  Name    : buttonPressed();                          **
**  Inputs  : playerNum                                 **
**  Returns : void (nothing)                            **
**  Desc    : Inputs player number to call fade up and  **
**            down function                             **
**********************************************************/
void buttonPressed(int playerNumb) {
  if (playerNumb == 1) {
    player1Stopped = 1;                                                             //makes player1Stopped == 1
  }//end if()
  if (playerNumb == 2) {
    player2Stopped = 1;                                                             //makes player2Stopped == 1
  }//end if()
  if (playerNumb == 3) {
    player3Stopped = 1;                                                             //makes player3Stopped == 1
  }//end if()
  if (continueGame == 1) {
    continueGame = 0;                                                               //makes continue game == 0
  }//end if()
  if (restartGame == 1) {
    restartGame = 0;                                                                //makes restart game == 0
  }//end if()
  while (continueGame == 0 && restartGame == 0) {
    buttonTone(7, 3521);                                                            //runs the buttonTone that makes a sound using the speaker ///////MIGHT NEED TO CHANGE FREQ
    fadeUpAndDown(playerNumb);                                                      //fades up and down witht eh player who got the question wrong
  }//end while()
  buttonTone(7, 70);                                                                //runs the buttonTone that makes a sound using the speaker ///////MIGHT NEED TO CHANGE FREQ
  analogWrite(playerNumb + 8, 50);                                                  //makes the one who got the question wrongs led fade
}//end buttonPressed()

/*********************************************************
**  Name    : fadeUpAndDown();                          **
**  Inputs  : playerNum                                 **
**  Returns : void (nothing)                            **
**  Desc    : Fades the playes light up and down        **
**********************************************************/
void fadeUpAndDown(int playerNum) {
  for (int i = 0 ; i < 255 ; i += 5) {
    analogWrite(playerNum + 8, i);                                                  //fades up
    delay(5);                                                                       //delay
  }//end for()
  for (int i = 255 ; i >= 0 ; i -= 5) {
    analogWrite(playerNum + 8, i);                                                  //fades down
    delay (5);                                                                      //delay
  }//end if()
}//end fadeUpandDown()

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


/*********************************************************
** INTERRUPTS BELOW                                     **
**********************************************************/

/*********************************************************
**  Name    : constGame();                              **
**  Inputs  : None                                      **
**  Returns : void (nothing)                            **
**  Desc    : Continues the Jasey Box game.             **
**********************************************************/
void contGame() {
  static unsigned long last_interrupt_time = 0;                                     // creates a var that holds the LAST time the INT was pressed
  unsigned long interrupt_time = millis();                                          // CREATES A VAR THAT HOLDS THE CURRENT TIME IN MS
  if (interrupt_time - last_interrupt_time > 100) {
    
    buttonTone(7, 177);                                                             //runs the buttonTone that makes a sound using the speaker ///////MIGHT NEED TO CHANGE FREQ
    continueGame = 1;                                                               //makes continue game == 1

  }//end if()
  last_interrupt_time = interrupt_time;                                             // UPDATE THE LAST TIME THE INTERRUPT WAS PRESSED
}// end of contGame()

/*********************************************************
**  Name    : resetGame();                              **
**  Inputs  : None                                      **
**  Returns : void (nothing)                            **
**  Desc    : Resets the Jasey Box Game.                **
**********************************************************/
void resetGame() {
  static unsigned long last_interrupt_time = 0;                                     // creates a var that holds the LAST time the INT was pressed
  unsigned long interrupt_time = millis();                                          // CREATES A VAR THAT HOLDS THE CURRENT TIME IN MS
  if (interrupt_time - last_interrupt_time > 100) {
    
    buttonTone(7, 478);                                                             //runs the buttonTone that makes a sound using the speaker ///////MIGHT NEED TO CHANGE FREQ
    restartGame = 1;                                                                //makes restart game == 1
    player1Stopped  = 0;                                                            //player1Stopped == 0
    player2Stopped  = 0;                                                            //player2Stopped == 0
    player3Stopped  = 0;                                                            //player3Stopped == 0

  }//end if()
  last_interrupt_time = interrupt_time;                                             // UPDATE THE LAST TIME THE INTERRUPT WAS PRESSED
}// end of resetGame()
