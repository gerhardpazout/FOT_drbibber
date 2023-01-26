/**
 * Game idea:
 *
 * The game only supports 2 players - not more not less.
 * Player 1 starts first.
 * Whenever the current player finish the round they have to press the "end turn"-button,
 * that signalizes to the arduino that the current player wants to end their turn.
 * The game finished when all items are extracted or a player gets eliminated.
 * The player with the most items or the last surviving player wins.
 */

/**
 * What we need for the game idea:
 * -) player class inlcuding name, number of turns, number of fails, number of success
 * 
 */

/////////////////////////////////
//         Player class        //
/////////////////////////////////

// class Player
class Player {
  private:
    int id;
    int fails;

  public: 
    Player(int id) {
      this->id = id;
      this->fails = 0;
    }

    int getFails(){
      return this->fails;
    }

    void increaseFails(){
      this->fails++;
    }

    int getId(){
      return id;
    }

    void printStats() {
      Serial.print("Player ");
      Serial.print(id);
      Serial.print(": fails(");
      Serial.print(fails);
      Serial.print(")");
      Serial.println("");
    }
};

/////////////////////////////////
//      Gloabal Variables      //
/////////////////////////////////

Player player1 = Player(1);
Player player2 = Player(2);
Player currentPlayer = NULL;

//
const int MAX_FAILS = 3;
bool gameOver = false;

// pins
const int PIN_CIRCUIT = 6;
const int PIN_SWITCH_PLAYER_BUTTON = 7;
const int PIN_LED = 8;


/////////////////////////////////
//       Helper Functions      //
/////////////////////////////////

/**
 * initializes console to print stuff to.
 *
 * @return void
 */
void initConsole() {
  Serial.begin(9600);
}

/**
 * Returns true if the circuit is closed 
 * (circuit is closed when tweezers touch aluminum foil)
 *
 * @return bool - true if circuit is closed, false otherwise
 */
bool isCircuitClosed() {
  return (digitalRead(PIN_CIRCUIT) == HIGH)? true : false;
}

/**
 * Returns true if the 'switch player' button was pressed
 *
 * @return bool - true if switch player' button was pressed, false otherwise
 */
bool isSwitchButtonPressed() {
  return (digitalRead(PIN_SWITCH_PLAYER_BUTTON) == HIGH)? true : false;
}

/**
 * Turns the led on
 *
 * @return void
 */
void LedOn(){
  digitalWrite(PIN_LED, HIGH);  
}

/**
 * Turns the led off
 *
 * @return void
 */
void LedOff() {
  digitalWrite(PIN_LED, LOW);  
}

/**
 * Returns true if given player is eliminated, false otherwise.
 *
 * @return bool - true if given player is eliminated, false otherwise
 */
bool isPlayerEliminated(Player player) {
  return (player.getFails() >= MAX_FAILS)? true : false;
}

/**
 * Switches the current player to the next player (only if next player is not eliminated)
 *
 * @return true;
 */
void switchPlayer() {
  if (currentPlayer.getId() == 1 && !isPlayerEliminated(player2)) {
    currentPlayer = player2;
  }
  else if (currentPlayer.getId() == 2 && !isPlayerEliminated(player1)) {
    currentPlayer = player1;
  }
}

//////////////////////////////////////////
//       Arduino setup() & loop()       //
//////////////////////////////////////////

/**
 * Arduino setup function (run once)
 *
 * @return void
 */
void setup() {
  initConsole(); 
  Serial.println("Starting game initialization...");
  currentPlayer = player1; 
  Serial.println("Finished game initialization!");
  
  Serial.println("");
  Serial.print("Player ");
  Serial.print(currentPlayer.getId());
  Serial.print(" starts!");
  Serial.println("");
}

/**
 * Arduino loop function (run repeatedly)
 *
 * @return void
 */
void loop() {
  // get current player

  if(gameOver == false) {
    // check if circuit is closed
    if (isCircuitClosed()) 
    {
      // Turn LED on    
      LedOn();
      currentPlayer.increaseFails();
      if(isPlayerEliminated(currentPlayer)) {
        gameOver = true;
        Serial.println("");
        Serial.print("Player ");
        Serial.print(currentPlayer.getId());
        Serial.print(" eliminated!");
        Serial.println("");
      }
    } 
    else 
    {
      // Turn LED off
      LedOff(); 
    }

    // check if switch button was pressed
    if(isSwitchButtonPressed()) {
      switchPlayer();
    }
  }
  else {
    Serial.println("Game over!");
    delay(5000);
  }
}
