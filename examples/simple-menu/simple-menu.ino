#include <LiquidCrystalMenu.h>


/**
 * Changes these values to fit your LCD screen
 */
#define LCD_COLS  20
#define LCD_ROWS  4


#define UP_BTN 6
#define DOWN_BTN 7
#define SELECT_BTN 8
#define BACK_BTN 1

LiquidCrystalMenu navigation(12, 11, 9, 5, 4, 3, 2);


void setup() {
  navigation.begin(LCD_COLS, LCD_ROWS);
  navigation.AddMenu("Test");
  navigation.AddMenu("Test2");
  navigation.AddMenu("Test3");

  pinMode(UP_BTN, INPUT);
  pinMode(DOWN_BTN, INPUT);
  pinMode(SELECT_BTN, INPUT);
  pinMode(BACK_BTN, INPUT);
}


void loop() {
  if (digitalRead(UP_BTN) == HIGH) {
    navigation.Up();
  }
  else if (digitalRead(DOWN_BTN) == HIGH) {
    navigation.Down();
  }
  else if (digitalRead(BACK_BTN) == HIGH) {
    navigation.Back();
  }
  else if (digitalRead(SELECT_BTN) == HIGH) {
    navigation.Select();
  }
}
