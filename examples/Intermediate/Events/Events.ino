 /**
 * This example is the most complex one.
 *
 * You should absolutely be comfortable with the Values example, and all the
 * other examples.
 *
 * You will also want a knowledge, and understanding, of pointers.
 *
 * For information on pointers see:
 * https://www.arduino.cc/reference/en/language/structure/pointer-access-operators/reference/
 *
 * Also, make sure you have looked at and understand the menu-with-values example.
 *
 * ---
 * Since you provide your LiquidCrystalMenu object a pointer when setting values,
 * that means you can change the value of whatever it points to and it will
 * reflect on the LCD screen.
 *
 * To automatically update the LCD screen with new variable values all you need
 * to do is add the following line to your loop() function:
 *
 *  menu.refreshValues();
 *
 * Where menu is your LiquidCrystalMenu object.
 *
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


/**
 * This function will execute when you highlight a menu option
 */
void MenuOptionHighlighted(MenuEvent event, MenuItem menuItem) {
  Serial.println("Item " + menuItem.title + " selected");
}


/**
 * This function will execute whenever you navigate into a menu
 */
void EnteredSubmenu(MenuEvent event, MenuItem menuItem) {
  Serial.println("Entered submenu " + menuItem.title);
}


/**
 * The setup function only happens once
 */
void setup() {
  Serial.begin(9600);

  // Initialize the LCD menu with LCD display size
  navigation.begin(LCD_COLS, LCD_ROWS);

  // Create menu structure
  MenuID option1 = navigation.addMenu("Option 1");
  navigation.listen(FocusEvent, option1, &MenuOptionHighlighted);

  MenuID option2 = navigation.addMenu("Option 2");
  navigation.listen(FocusEvent, option2, &MenuOptionHighlighted);
  navigation.listen(SelectEvent, option2, &EnteredSubmenu);

  MenuID option21 = navigation.addMenu(option2, "Option 2.1");
  navigation.listen(FocusEvent, option21, &MenuOptionHighlighted);

  MenuID option22 = navigation.addMenu(option2, "Option 2.2");
  navigation.listen(FocusEvent, option22, &MenuOptionHighlighted);


  // Configure our buttons as inputs
  pinMode(UP_BTN, INPUT);
  pinMode(DOWN_BTN, INPUT);
  pinMode(SELECT_BTN, INPUT);
  pinMode(BACK_BTN, INPUT);
}


/**
 * The loop function will keep repeating
 */
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