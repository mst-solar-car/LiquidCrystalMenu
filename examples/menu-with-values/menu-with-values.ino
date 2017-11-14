/**
 * This example is one of the more complex examples provided.
 *
 * You should be fully comfortable with creating multi-leveled menus before
 * moving onto this example.
 *
 * You will also want to have a knowledge, and understanding,
 * of pointers and how they function.
 *
 * For information on pointers see:
 * https://www.arduino.cc/reference/en/language/structure/pointer-access-operators/reference/
 *
 * ---
 * All values used for displaying on the LCD MUST be of type String
 *
 * You can provide a value in two ways:
 *
 * 1. Variable Pointer
 *  menu.addValue("Value Name", &stringVariable);
 *
 *  Where stringVariable is a variable of type String
 *  and menu is your LiquidCrystalMenu object
 *
 * 2. Pointer to a Function
 *  If the values that you want to display need type conversion, or some computation,
 *  then you can also provide a value using a pointer to a function that returns
 *  a String and accepts no parameters.
 *
 *  String myValue() { return "Sample Value"; }
 *  ...
 *  menu.addValue("Value Name", &myValue);
 */
#include <LiquidCrystalMenu.h>

/**
 * Changes these values to fit your LCD screen
 */
#define LCD_COLS 20
#define LCD_ROWS 4

#define LCD_RS  12
#define LCD_RW  11
#define LCD_EN  9
#define LCD_D4  5
#define LCD_D5  4
#define LCD_D6  3
#define LCD_D7  2


/**
 * Changes these values to line up with the digital pins your buttons are attached to
 */
#define UP_BTN      6
#define DOWN_BTN    7
#define SELECT_BTN  8
#define BACK_BTN    13


// Create our LCD Menu
LiquidCrystalMenu navigation(LCD_RS, LCD_RW, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);


String myValueFunction() {
  return "Value1";
}

String myValueVar;

void setup() {
  // Initialize the LCD menu with LCD display size
  navigation.begin(LCD_COLS, LCD_ROWS);

  myValueVar = "Value2";

  // Add our menus and values
  MenuID menu1 = navigation.addMenu("Menu 1");
  navigation.addValue(menu1, "Value Variable", &myValueVar); // Value on a submenu

  navigation.addValue("Value Function", &myValueFunction);


  // Configure our buttons as inputs
  pinMode(UP_BTN, INPUT);
  pinMode(DOWN_BTN, INPUT);
  pinMode(SELECT_BTN, INPUT);
  pinMode(BACK_BTN, INPUT);
}


void loop() {
  // Monitor button presses and perform action on the LCD Menu
  if (digitalRead(UP_BTN) == HIGH) {
    // Move up on the current menu
    navigation.up();
  }
  else if (digitalRead(DOWN_BTN) == HIGH) {
    // Move down on the current menu
    navigation.down();
  }
  else if (digitalRead(BACK_BTN) == HIGH) {
    // Move to the parent menu
    navigation.back();
  }
  else if (digitalRead(SELECT_BTN) == HIGH) {
    // Move to an inner child (sub) menu
    navigation.select();
  }
}
