#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Stepper.h>

const String CodePin = "1234#";
const int stepsPerRevolution = 200;
const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {4, 3, 2, A5};
byte colPins[COLS] = {5, 6, 7};
int n = 1;
String inPin = "";

Stepper myStepper(stepsPerRevolution, A0, A1, A2, A3);
Keypad customKeypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
void setup() {
    myStepper.setSpeed(60);
    customKeypad.addEventListener(keypadEvent);
    pinMode(A4, OUTPUT);
    noTone(A4);
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("ENTREE CODE");
}
void loop() {
    if (n <= 3) {
        char key = customKeypad.getKey();
    }
    else {
      tone(A4, 2500);
      lcd.setCursor(0, 0);
      lcd.print("SERRURE BLOQUEE");
    }
}
void keypadEvent(KeypadEvent key){
    if (customKeypad.getState() == PRESSED){
        inPin = inPin + key;
        if (key == '#') {
            if (inPin == CodePin) {
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("SERRURE OUVERTE");
                myStepper.step(3*stepsPerRevolution);
                delay(1000);
                // myStepper.step(-3*stepsPerRevolution);
                n = 1;
                noTone(A4);
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("ENTREE CODE");
            }
          else {
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("PIN INCORRECTE");
              lcd.setCursor(0, 1);
              lcd.print("ESSAI : ");
              lcd.setCursor(13, 1);
              lcd.print(3-n);
              n = n + 1;
              if (n == 4) {
                  lcd.clear();
              }
          }
          inPin = "";
      }
    }
  }
