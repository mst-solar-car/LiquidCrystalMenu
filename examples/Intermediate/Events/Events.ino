 /**
 * This example is one of the higher level intermediate examples.
 *
 * You should be comfortable with pointers and nested menus before you begin this
 * example.
 *
 * For information on pointers see:
 * https://www.arduino.cc/reference/en/language/structure/pointer-access-operators/reference/
 *
 * ---
 *
 * Somtimes you might want to know when a menu item is entered, or a menu item
 * is focused. The LiquidCrystalMenu library allows you to easily do this.
 *
 * Use the following method:
 *    menu.listen(MenuEvent, MenuID, callback);
 *
 * Where MenuEvent is:
 *    FocusEvent
 *    SelectEvent
 *
 * MenuID is the value returned from addMenu or addValue methods
 *
 * callback is a pointer to a function that will be executed when the event
 * happens.
 *
 * Your callback function should accept two parameters:
 *    1st: a MenuEvent type
 *    2nd: a value of type MenuItem
 *
 * MenuItem is a struct type that has two members:
 *    id: type MenuID (id of the menu item)
 * title: Type String (title of the menu item)
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
  MenuID option2 = navigation.addMenu("Option 2");

  // Add submenus
  MenuID option21 = navigation.addMenu(option2, "Option 2.1");
  MenuID option22 = navigation.addMenu(option2, "Option 2.2");

  // ==== Add Event Listeners ====
  // Subscribe to the Focus Event for menu option 1
  navigation.listen(FocusEvent, option1, &MenuOptionHighlighted);

  // Subscribe to the select and focus event for menu option 2
  navigation.listen(FocusEvent, option2, &MenuOptionHighlighted);
  navigation.listen(SelectEvent, option2, &EnteredSubmenu);

  // Subscribe to the focus events on the submenus
  navigation.listen(FocusEvent, option21, &MenuOptionHighlighted);
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