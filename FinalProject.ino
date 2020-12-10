/************************************************************************************
** Name       : Abbie Dyck                                                         **
** Date       : 04/01/19                                                           **
** Progam Name: FinalProject.ino                                                   **
** Desc       :                                                                    **
*************************************************************************************/
/*PLAYER 1 PINS AND VARS*/
const int player1GoToStartLED   = 3;            //sets pin 3 as player 1 go to start led
const int player1PlayLED        = 2;            //sets pin 2 as player 1 play led
const int player1WinnerLED      = 7;            //sets pin 7 as player 1 winner led

const int player1StartInput     = 8;            //sets pin 8 as player 1 start input
const int player1WireInput      = 9;            //sets pin 9 as player 1 wire input
const int player1EndInput       = 10;           //sets pin 10 as player 1 end input

int player1StartPos             = 0;            //sets player 1 start pos to 0
int player1HitWire              = 0;            //sets player 1 hit wire to 0
int player1EndPos               = 0;            //sets player 1 end pos to 0

/*PLAYER 2 PINS AND VARS*/
const int player2GoToStartLED   = 5;            //sets pin 5 as player 2 go to start led
const int player2PlayLED        = 6;            //sets pin 6 as player 2 play led
const int player2WinnerLED      = 4;            //sets pin 4 as player 2 winner led

const int player2StartInput     = 11;           //sets pin 11 as player 2 start input
const int player2WireInput      = 12;           //sets pin 12 as player 2 wire input
const int player2EndInput       = 13;           //sets pin 13 as player 2 end input

int player2StartPos             = 0;            //sets player 2 start pos to 0
int player2HitWire              = 0;            //sets player 2 hit wire to 0
int player2EndPos               = 0;            //sets player 2 end pos to 0

/*SPEAKER PIN*/
const int speakerPin            = 14;           //sets pin 14 as speaker

void setup() {
  pinMode(player1GoToStartLED, OUTPUT);         //sets player 1 go tostart LED as a output
  pinMode(player1PlayLED, OUTPUT);              //sets player 1 play LED as a output
  pinMode(player1WinnerLED, OUTPUT);            //sets player 1 winner LED as a output
  pinMode(player2GoToStartLED, OUTPUT);         //sets player 2 go to start LED as a output
  pinMode(player2PlayLED, OUTPUT);              //sets player 2 play LED as a output
  pinMode(player2WinnerLED, OUTPUT);            //sets player 2 winner LED as a output

  pinMode(player1WireInput,  INPUT_PULLUP);     //sets up player1WireInput as a input pullup
  pinMode(player1StartInput, INPUT_PULLUP);     //sets player1StartWire as a input pullup
  pinMode(player1EndInput,   INPUT_PULLUP);     //sets player1EndInput as a input pullup
  pinMode(player2WireInput,  INPUT_PULLUP);     //sets up player2WireInput as a input pullup
  pinMode(player2StartInput, INPUT_PULLUP);     //sets player2StartInput as a input pullup
  pinMode(player2EndInput,   INPUT_PULLUP);     //sets player2EndInput as a input pullup

  randomSeed(analogRead(0));                    //sets up the random seed function
  startGameSeq();                               //starts the startGameSeq function
}//end setup()

void loop() {
  //Player 1 if statements//
  if (digitalRead(player1StartInput) == LOW) {
    digitalWrite(player1PlayLED, HIGH);         //if player1StartInput is low, turn player1PlayLED to high
    digitalWrite(player1GoToStartLED, LOW);     //set player1GoToStartLed to low
    digitalWrite(player1WinnerLED, LOW);        //sets player1WinnerLED to low
    player1StartPos = 1;                        //sets player1StartPos = 1
    player1HitWire  = 0;                        //sets player1HitWire = 0
    player1EndPos   = 0;                        //sets player1EndPos = 0
  }//end if()
  if (digitalRead(player1WireInput) == LOW && player1HitWire == 0) {
    digitalWrite(player1PlayLED, LOW);          //if player1WireInput is low, turn player1PlayLED to low
    digitalWrite(player1GoToStartLED, HIGH);    //set player1GoToStartLed to high
    digitalWrite(player1WinnerLED, LOW);        //sets player1WinnerLED to low
    player1StartPos = 0;                        //sets player1StartPos = 0
    player1HitWire  = 1;                        //sets player1HitWire = 1
    player1EndPos   = 0;                        //sets player1EndPos = 0
  }//end if()
  if (digitalRead(player1EndInput) == LOW && player1StartPos == 1) {
    digitalWrite(player1PlayLED, LOW);          //if player1EndInput is low and player1StartPos is 1 (to prevent cheating), turn player1PlayLED to low
    digitalWrite(player1GoToStartLED, LOW);     //set player1GoToStartLed to low
    digitalWrite(player1WinnerLED, HIGH);       //sets player1WinnerLED to high
    player1StartPos = 0;                        //sets player1StartPos = 0
    player1HitWire  = 0;                        //sets player1HitWire = 0
    player1EndPos   = 1;                        //sets player1EndPos = 1
    winner(7, 4);                               //starts the player won or lost sequence
  }//end if()
  //Player 2 if statements//
  if (digitalRead(player2StartInput) == LOW) {
    digitalWrite(player2PlayLED, HIGH);         //if player2StartInput is low, turn player2PlayLED to high
    digitalWrite(player2GoToStartLED, LOW);     //set player2GoToStartLed to low
    digitalWrite(player2WinnerLED, LOW);        //sets player2WinnerLED to low
    player2StartPos = 1;                        //sets player2StartPos = 1
    player2HitWire  = 0;                        //sets player2HitWire = 0
    player2EndPos   = 0;                        //sets player2EndPos = 0
  }//end if()
  if (digitalRead(player2WireInput) == LOW && player2HitWire == 0) {
    digitalWrite(player2PlayLED, LOW);          //if player2WireInput is low, turn player2PlayLED to low
    digitalWrite(player2GoToStartLED, HIGH);    //set player2GoToStartLed to high
    digitalWrite(player2WinnerLED, LOW);        //sets player2WinnerLED to low
    player2StartPos = 0;                        //sets player2StartPos = 0
    player2HitWire  = 1;                        //sets player2HitWire = 1
    player2EndPos   = 0;                        //sets player2EndPos = 0
  }//end if()
  if (digitalRead(player2EndInput) == LOW && player2StartPos == 1) {
    digitalWrite(player2PlayLED, LOW);          //if player2EndInput is low and player2StartPos is 1 (to prevent cheating), turn player2PlayLED to low
    digitalWrite(player2GoToStartLED, LOW);     //set player2GoToStartLed to low
    digitalWrite(player2WinnerLED, HIGH);       //sets player2WinnerLED to high
    player2StartPos = 0;                        //sets player2StartPos = 0
    player2HitWire  = 0;                        //sets player2HitWire = 0
    player2EndPos   = 1;                        //sets player2EndPos = 1
    winner(4, 7);                               //starts the player won or lost sequence
  }//end if()
}//end loop()

/*********************************************************
** FUNCTIONS BELOW                                      **
**********************************************************/

/*********************************************************
**  Name    : startGameSeq();                           **
**  Inputs  : None                                      **
**  Returns : void (nothing)                            **
**  Desc    : Playes the starting sequence, by making   **
**            sure that both the players are at the     **
**            starting pos, and that noone is cheating. **
**********************************************************/
void startGameSeq() {
  do {
    if (digitalRead(player1StartInput) == LOW) {
      digitalWrite(player1PlayLED, LOW);          //if player1StartInput is low, turn off the player1PlayLED
    } else {
      digitalWrite(player1PlayLED, HIGH);         //else, keep player1PlayLED on
    }//end if()
    if (digitalRead(player2StartInput) == LOW) {
      digitalWrite(player2PlayLED, LOW);          //if player2StartInput is low, turn off the player2PlayLED
    } else {
      digitalWrite(player2PlayLED, HIGH);         //else, keep player2PlayLED on
    }//end if()
  }  while (digitalRead(player1StartInput) == HIGH || digitalRead(player2StartInput) == HIGH); //end do while()
  int delayNum = random(1, 6);                    //creates a random number between 1 and 5 and saves i to delayNum
  delay(delayNum);                                //delay for the random number amount
  Serial.println(delayNum);
  if (digitalRead(player1StartInput) == LOW && digitalRead(player2StartInput) == LOW) {
    tone(speakerPin, 1000, 100);                  //plays a tone
    delay(1000);                                  //delays for 1 second
    tone(speakerPin, 2000, 100);                  //plays a tone
    delay(1000);                                  //delays for 1 second
    tone(speakerPin, 3000, 100);                  //plays a tone
  }//end if()
}//end startGameSeq()

/*********************************************************
**  Name    : winner();                                 **
**  Inputs  : playerWhoWon and playerWhoLost            **
**  Returns : void (nothing)                            **
**  Desc    : Plays the winner sequence, by lighting up **
**            the players pin for who won, and blinks   **
**            the loosing players pin. It then plays a  **
**            noise, the rapidly blinks the pins to     **
**            attract players.                          **
**********************************************************/
void winner(int playerWhoWon, int playerWhoLost) {
  digitalWrite(playerWhoWon, HIGH);               //makes the player who wons LED HIGH
  tone(speakerPin, 5000, 100);                    //playes a winner tone
  for (int x = 0; x < 4 ; x++) {
    digitalWrite(playerWhoLost, HIGH);            //turns loosers LED on
    delay(1000);                                  //delays for 1 second
    digitalWrite(playerWhoLost, LOW);             //turns loosers LED off
    delay(1000);                                  //delays for 1 second
  }//end for()
  for (int x = 0; x > -1; x++) {
    int randomNum = random(1, 64);                //gets stuck in a endless loop blinking the lights on the game to attract players
    DDRB = randomNum;                             //blinks light in a random pattren (from random number above)
  }//end for()
}//end winner()
