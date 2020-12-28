#include <LiquidCrystal.h>
#include <Keypad.h>

/*
* Initialize led
*/

int RED = 13;
int GREEN = 12;
int BLUE = 11;

/*
* Initialize lcd
*/

const int RS = 1, EN = 2, D4 = 4, D5 = 5, D6 = 6, D7 = 7;

LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

/*
* Initialize keypad
*/
const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {10, 9, 8, A0};
byte colPins[COLS] = {A1, A2, A3, A4};

Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

/*
* real-time systems group assignment (t1g1)
* made by andretai :D
*/

void setup()
{
  startScreen();
  //Serial.begin(9600);
  //pinMode(13, OUTPUT);
}

void loop()
{
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("PRESS A NUMBER..");
  delay(2000);
  lcd.clear();
  int ans = random(0, 9);
  for(int x=3; x>=0; x--){
    if(x == 0){
      winLose(0, ans);
      break;
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("CHANCES: ");
    lcd.print(x);
    char customKey = customKeypad.waitForKey();
    int input = int(customKey) - 48;
    lcd.setCursor(2, 1);
    lcd.print(input);
    lcd.print(" ");
    lcd.print(toggleLed(input, ans));
    delay(1000);
    if(input == ans && x>0){
      winLose(1, ans);
      break;
    }
  }
}

/*
* Welcome screen
*/
void startScreen(){
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("HELLO! WELCOME TO GUESS A DIGIT!");
  delay(1000);
  for(int x=0; x<24; x++){
    lcd.scrollDisplayLeft();
    delay(200);
  }
  delay(300);
  lcd.clear();
}

/*
* Toggle led and display hint
*/
String toggleLed(int urs, int ans){
  if(urs < ans){
    digitalWrite(RED, HIGH);
    delay(1000);
    digitalWrite(RED, LOW);
    return "(TOO LOW!)";
  }else if(urs == ans){
    digitalWrite(GREEN, HIGH);
    delay(1000);
    digitalWrite(GREEN, LOW);
    return "(NICE!)";
  }else if(urs > ans){
    digitalWrite(BLUE, HIGH);
    delay(1000);
    digitalWrite(BLUE, LOW);
    return "(TOO HIGH!)";
  }
}

/*
* Display final results
*/
void winLose(int won, int ans){
  lcd.clear();
  lcd.setCursor(0, 0);
  if(won == 0){
    lcd.print("WRONG!");
  }else{
    lcd.print("CORRECT!");
  }
  lcd.setCursor(6, 1);
  lcd.print("IT'S ");
  lcd.print(ans);
  if(won == 0){
    lcd.print("! :(");
  }else{
    lcd.print("! :)");
  }
  delay(3000);
}