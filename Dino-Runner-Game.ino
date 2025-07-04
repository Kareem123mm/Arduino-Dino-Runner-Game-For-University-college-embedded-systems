#include <LiquidCrystal.h>

LiquidCrystal lcd(9, 8, 5, 4, 3, 2); //Fill out pin declarations according to board pins the LCD is connected to

// Game states
#define STATE_WELCOME 0
#define STATE_PLAYING 1
#define STATE_GAME_OVER 2
int gameState = STATE_WELCOME;

// Character definitions
byte DINO_PARADO_PARTE_1[8] = {B00000, B00000, B00010, B00010, B00011, B00011, B00001, B00001};
byte DINO_PARADO_PARTE_2[8] = {B00111, B00111, B00111, B00100, B11100, B11100, B11000, B01000};
byte DINO_PIE_DERE_PART_1[8] = {B00000, B00000, B00010, B00010, B00011, B00011, B00001, B00001};
byte DINO_PIE_DERE_PART_2[8] = {B00111, B00111, B00111, B00100, B11100, B11100, B11000, B00000};
byte DINO_PIE_IZQU_PART_1[8] = {B00000, B00000, B00010, B00010, B00011, B00011, B00001, B00000};
byte DINO_PIE_IZQU_PART_2[8] = {B00111, B00111, B00111, B00100, B11100, B11100, B11000, B01000};
byte DOS_RAMAS_PART_1[8] = {B00000, B00100, B00100, B10100, B10100, B11100, B00100, B00100};
byte DOS_RAMAS_PART_2[8] = {B00100, B00101, B00101, B10101, B11111, B00100, B00100, B00100};
// Improved bird graphics to make it more bird-like
byte BIRD_WING_UP[8] = {B00001, B00011, B00111, B01111, B11111, B00000, B00000, B00000};
byte BIRD_WING_DOWN[8] = {B00000, B00000, B00000, B01111, B11111, B00001, B00001, B00001};

//define variables
int dino_column1 = 1;
int dino_column2 = 2;
int dino_row = 1;
unsigned long timer = 0; 
int period = 100; 
int flag = 1;
int branch_row = 0;
int branch_column = 13;
int period2 = 100;
unsigned long timer2 = 0;
int a = 0;
int b = 1;
int c = 2;
int d = 0;
unsigned long timer3 = 0;
int period3 = 100;
int points = 0;
int points_hundreds = 0;
int random_number = 0;
int bird_column = 13;
int e = 0;
int bird_row = 1;
int current_signal = 0;
int previous_signal = 0;
int f = 13;
int acceleration = 1;
unsigned long timer4 = 0;
int period4 = 800;
int button = 11; 
int buzzer = 10;
int welcomeScrollPos = 0;
unsigned long welcomeTimer = 0;
unsigned long jumpStartTime = 0;
int maxJumpDuration = 1000; // Maximum jump duration in milliseconds (1 second)

void setup() {
  for (int i = 2; i <= 17; i++)  pinMode(i, OUTPUT);

  pinMode(button, INPUT);
  pinMode(buzzer, OUTPUT);

  lcd.begin(16, 2);
  lcd.createChar(0, DINO_PARADO_PARTE_1);
  lcd.createChar(1, DINO_PARADO_PARTE_2);
  lcd.createChar(2, DINO_PIE_DERE_PART_1);
  lcd.createChar(3, DINO_PIE_DERE_PART_2);
  lcd.createChar(4, DINO_PIE_IZQU_PART_1);
  lcd.createChar(5, DINO_PIE_IZQU_PART_2);
  lcd.createChar(6, DOS_RAMAS_PART_1);
  lcd.createChar(7, DOS_RAMAS_PART_2);
  
  // Show welcome screen
  showWelcomeScreen();
}

void showWelcomeScreen() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WELCOME TO DINO");
  lcd.setCursor(0, 1);
  lcd.print("PRESS BTN TO START");
  
  // Play welcome melody
  int welcomeNotes[] = {523, 659, 784, 1047}; // C5, E5, G5, C6
  for (int i = 0; i < 4; i++) {
    tone(buzzer, welcomeNotes[i], 150);
    delay(200);
  }
}

void loop() {
  // Game state machine
  switch(gameState) {
    case STATE_WELCOME:
      // Check for button press to start game
      if (digitalRead(button) == HIGH) {
        delay(200); // Button debounce
        lcd.clear();
        resetGame();
        gameState = STATE_PLAYING;
      }
      
      // Scroll welcome message every 300ms
      if (millis() > welcomeTimer + 300) {
        welcomeTimer = millis();
        lcd.scrollDisplayLeft();
      }
      break;
      
    case STATE_PLAYING:
      playGame();
      break;
      
    case STATE_GAME_OVER:
      // Game over screen already shown in the collision handler
      // Check for button press to return to welcome screen
      if (digitalRead(button) == HIGH) {
        delay(200); // Button debounce
        showWelcomeScreen();
        gameState = STATE_WELCOME;
      }
      break;
  }
}

void resetGame() {
  branch_column = 15;
  period2 = 100;
  points = 0;
  points_hundreds = 0;
}

void playGame() {
  if (millis() > timer + period) { 
    timer = millis();
    if (flag == 1) {
      flag = 2;
    }
    else if (flag == 2) {
      flag = 1;
    }
  }

  if (millis() > timer2 + period2) { 
    timer2 = millis();

    branch_column = branch_column - 1;
    if (branch_column < 0) {
      branch_column = 13;
      period2 = period2 - acceleration; 
      random_number = random(0, 3); 
    }

    f = branch_column + 1;
    lcd.setCursor(f, 1);         
    lcd.print(" ");

    f = branch_column + 1;
    lcd.setCursor(f, 0);          
    lcd.print(" ");

    lcd.setCursor(0, 1);          
    lcd.print(" ");

    lcd.setCursor(0, 0);
    lcd.print(" ");

    a = 1;
  }

  if (d == 0) {
    if (flag == 1) {
      lcd.setCursor(dino_column1, dino_row);
      lcd.write(byte(2));
      lcd.setCursor(dino_column2, dino_row);
      lcd.write(byte(3));
    }
    if (flag == 2) {
      lcd.setCursor(dino_column1, dino_row);
      lcd.write(byte(4));
      lcd.setCursor(dino_column2, dino_row);
      lcd.write(byte(5));
    }
  }

  if (a == 1) {
    if (random_number == 1) {
      branch_row = 1;
      lcd.createChar(6, DOS_RAMAS_PART_1);
      lcd.setCursor(branch_column, branch_row);
      lcd.write(byte(6));
    }
    else if (random_number == 2) {
      branch_row = 1;
      lcd.createChar(7, DOS_RAMAS_PART_2);
      lcd.setCursor(branch_column, branch_row);
      lcd.write(byte(7));
    }
    else {      // Bird obstacles with improved graphics
      bird_column = branch_column;
      bird_column = bird_column - 1;
      branch_row = 0;
      
      // Create and show improved bird graphics
      lcd.createChar(6, BIRD_WING_UP);
      lcd.setCursor(bird_column, branch_row);
      lcd.write(byte(6));

      lcd.createChar(7, BIRD_WING_DOWN);
      lcd.setCursor(branch_column, branch_row);
      lcd.write(byte(7));
    }
    a = 0;
  }
  
  //generamos condiciones al chocar
  if (digitalRead(button) == HIGH && (branch_column == 1 || branch_column == 2 || bird_column == 1 || bird_column == 2) && branch_row == 0 ) {
    handleGameOver();
  }

  if ((branch_column == b || branch_column == c) && branch_row == 1) { //condicion de la rama
    int note[] = {200, 150};
    for (int i = 0; i < 2; i++) {
      tone(buzzer, note[i], 250);
      delay(200);
    }
    handleGameOver();
  }

  if (digitalRead(button) == HIGH) {
    b = 50;  
    c = 50;

    if (d == 0) {
      lcd.setCursor(0, 1);  
      lcd.print("    ");
      jumpStartTime = millis(); // Record when jump started
    }
    d = 1;

    lcd.setCursor(dino_column1, 0);
    lcd.write(byte(2));
    lcd.setCursor(dino_column2, 0);
    lcd.write(byte(3));

    if (millis() > timer4 + period4) { //retardo para los puntos acumulados
      timer4 = millis();

      int note[] = {600};
      for (int i = 0; i < 1; i++) {
        tone(buzzer, note[i], 150);
        delay(20);
      }
    }
  }
  else {
    b = 1;  //que regrese a su valor de inicio
    c = 2;
    d = 0;
  }
  
  // Check if maximum jump duration has been exceeded
  if (d == 1 && (millis() - jumpStartTime) >= maxJumpDuration) {
    b = 1;  // Force dinosaur to come down
    c = 2;
    d = 0;
  }
  
  //creamos otro retardo para los puntos
  if (millis() > timer3 + period3) { //retardo para los puntos acumulados
    timer3 = millis();
    lcd.setCursor(14, 1);
    lcd.print(points);

    points = points + 1;

    if (points == 100) {
      int note[] = {800, 900};
      for (int i = 0; i < 2; i++) {
        tone(buzzer, note[i], 150);
        delay(150);
        points = 0;
        points_hundreds = points_hundreds + 1;
        if (points_hundreds == 100) {
          points_hundreds = 0;
        }
      }
    }

    lcd.setCursor(14, 1);
    lcd.print(points);
    lcd.setCursor(14, 0);
    lcd.print(points_hundreds);

    //detector de cambio de estado
    current_signal = digitalRead(button);
    if (current_signal != previous_signal)
    {
      lcd.setCursor(1, 0);
      lcd.print("  ");
    }
    previous_signal = current_signal;
  }
}

void handleGameOver() {
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("GAME OVER");
  lcd.setCursor(1, 1);
  lcd.print("PRESS TO RESTART");
  delay(2000);
  
  gameState = STATE_GAME_OVER;
  resetGame();
}
