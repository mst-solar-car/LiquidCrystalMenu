/**
 * This is the most basic example of how to use the LiquidCrystalMenu
 * library.
 *
 * You should probably be comfortable working with buttons:
 * https://www.arduino.cc/en/Tutorial/Button
 *
 * ---
 * Create a menu is really simple once you create your LiquidCrystalMenu object
 *
 * To add a menu all you need is the following:
 *  menu.addMenu("Name of Menu");
 *
 * Where menu is your LiquidCrystalMenu object
 *
 * To navigate your menu you can use the following methods:
 *  menu.up();      // This will move up in your menu
 *
 *  menu.down();    // This will move down in your menu
 *
 *
 * ---
 * The example below creates this menu system:
 * - Menu 1
 * - Menu 2
 * - Menu 3
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


void setup() {
  // Initialize the LCD menu with LCD display size
  navigation.begin(LCD_COLS, LCD_ROWS);

  // Add our menus at a root level
  navigation.addMenu("Menu 1");
  navigation.addMenu("Menu 2");
  navigation.addMenu("Menu 3");

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
