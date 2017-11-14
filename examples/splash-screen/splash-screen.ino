/**
 * This splash screen example demonstartes how you can implement a splash screen
 * in your LCD Menu
 *
 * You should fully understand the simple-menu example before looking at this example.
 *
 * You should also be comfortable working with arrays:
 * https://www.arduino.cc/en/Tutorial/Arrays
 *
 *
 * ---
 * To create a splash screen you need to create an array of String objects.
 * This array should be the same number of rows as your LCD
 *
 * So if you have a LCD with 2 rows, your splash screen might look like this:
 *  String splashscreen[] = { "Row 1", "Row 2" };
 *  menu.splash(splashscreen);
 *
 * Or if you have an LCD with 3 rows:
 *  String splashscreen[] = { "Row 1", "Row 2", "Row3" };
 *  menu.splash(splashscreen);
 *
 * By default, the splash screen will be visible for 4 seconds, if yu want
 * to change this, then the splash() method takes a second argument.
 * That argument should be the amount of time (in milliseconds) that you want
 * the splash screen to be visible:
 *
 *  menu.splash(splashscreen, 5000);  // 5-second splash screen
 *  menu.splash(splaschreen, 1000);   // 1-second splash screen
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


// Add elements to this array to accomidate for larger screens
// This array needs to be the same size as LCD_ROWS
String splashscreen[] = {
  "My First",
  "Splash Screen"

// These next lines are just making sure that this array will be the same size
// as what is is in LCD_ROWS (up until 6 rows)
#if LCD_ROWS >= 3
  ,"Is"
#endif
#if LCD_ROWS >= 4
  ,"The Best!!"
#endif
#if LCD_ROWS >= 5
  ,"Five Rows? Wow"
#endif
#if LCD_ROWS >= 6
  ,"Unbelievable!"
#endif
};


void setup() {
  // Initialize the LCD menu with LCD display size
  navigation.begin(LCD_COLS, LCD_ROWS);

  // Show the splash screen (this can be done at any time)
  // But it is recomended to do it first
  navigation.splash(splashscreen);

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
