/**
 * Game idea:
 *
 * The game only supports 2 players - not more not less.
 * Player 1 starts first.
 * Whenever the current player finish the round they have to press the "end turn"-button,
 * that signalizes to the arduino that the current player wants to end their turn.
 * After every turn the player statistic will be computed. 
 */

/**
 * What we need for the game idea:
 * -) player class inlcuding name, number of turns, number of fails, number of success
 * 
 */


// class Player
class Player {
  private:
    int id;
    int tries;
    int fails;
    int success;

  public: 
    Player(int id) {
      this->id = id;
      this->tries = 0;
      this->fails = 0;
      this->success = 0;
    }

    int getTries(){
      return this->tries;
    }

    void increaseTries(){
      this->tries++;
    }

    int getFails(){
      return this->fails;
    }

    void increaseFails(){
      this->fails++;
    }

    int getSuccess(){
      return this->success;
    }
    void increaseSuccess(){
      this->success++;
    }

    int getName(){
      return id;
    }

    void printStats() {
      float successRate = 0;
      float failureRate = 0;
      if(tries > 0) {
        successRate = float(success) / float(tries);
        failureRate = float(fails) / float(tries);
      }

      Serial.print("Player ");
      Serial.print(id);
      Serial.print(": tries(");
      Serial.print(tries);
      Serial.print(") success(");
      Serial.print(successRate);
      Serial.print(") failure(");
      Serial.print(failureRate);
      Serial.print(")");
      Serial.println("");
    }
};

// Gloabal Variables
Player player1 = Player(1);
Player player2 = Player(2);



/**
 * initializes console to print stuff to.
 */
void initConsole() {
  Serial.begin(9600);
}

void setup() {
  // put your setup code here, to run once:
  initConsole();
  player1.printStats();
  player1.increaseTries();
  player1.increaseTries();
  player1.increaseTries();
  player1.increaseTries();
  player1.increaseTries();
  player1.increaseTries();
  player1.increaseTries();
  player1.increaseTries();
  player1.increaseTries();
  player1.increaseTries();
  player1.increaseSuccess();
  player1.increaseSuccess();
  player1.increaseSuccess();
  player1.increaseFails();
  player1.increaseFails();
  player1.increaseFails();
  player1.increaseFails();
  player1.increaseFails();
  player1.increaseFails();
  player1.increaseFails();
  player1.printStats();

  /*
  Serial.print("tries player 1: ");
  Serial.print(player1.getTries());
  Serial.println("");  
  */
}

void loop() {
  // put your main code here, to run repeatedly:

}
