/**
 * This library is for easily creating, and traversing, multi-level menus
 * on an LCD screen. It allows for menus to go down serveral layers and
 * eventually end up at an observable, where values can be updated from the
 * loop().
 *
 * This was designed for use in a piece of hardware that would be plugged into
 * a CAN bus and be able to view live data.
 *
 * Written by Michael Rouse for the Missouri S&T Solar Car Team
 * MIT License
 */
#ifndef __LCD_MENU_H__
#define __LCD_MENU_H__

#if (ARDUINO >= 100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include <LiquidCrystal.h>


/**
 * Constants
 */
#define LCDMENU_ARRAY_INCREMENT   2
#define LCDMENU_ACTION_DEBOUNCE   350
#define LCDMENU_REFRESH_INTERVAL  750 // Number of milliseconds to allow for refreshing


// Type alias
typedef int MenuID;

/**
 * Doubly Linked List node that represents something on a menu
 */
struct MenuNode {
  String title;
  String (*valueFn)(void);
  String *value;

  MenuNode *parent;
  MenuNode *submenu;
  MenuNode *previous;
  MenuNode *next;
};


/**
 * Custom Glyphs
 */
#define MENU_ARROW_GLYPH (uint8_t)0


/**
 * Class for interacting and creating a menu system on an LCD
 */
class LiquidCrystalMenu {
private:
  // Pins for the LCD
  int pin_rs;
  int pin_rw;
  int pin_en;
  int pin_d4;
  int pin_d5;
  int pin_d6;
  int pin_d7;

  // LCD size and object
  int rows;
  int cols;
  LiquidCrystal* lcd;

  MenuNode *root; // Root menu
  MenuNode *menu; // Currently selected MenuNode

  void draw();

  // Finds an item with a memory address
  MenuNode* findNodeWithAddr(MenuNode *node, const MenuID &memAddr);

  // Adds to a menu
  void addNode(MenuNode *root, MenuNode *toAdd);

public:
  // Constructor
  LiquidCrystalMenu(int rs, int rw, int enable, int d4, int d5, int d6, int d7);

  // Destructor
  ~LiquidCrystalMenu();

  // Start the library
  void begin(const int cols, const int rows);

  // Shows a splash screen
  void splash(const String contents[], const int delayMs = 4000);

  // Add a new menu item (to the root menu)
  MenuID addMenu(const String title);

  // Add a new menu item to a specific menu
  MenuID addMenu(const MenuID &parent, const String title);

  // Add a value to the root menus
  void addValue(const String title, String (*callback)(void));
  void addValue(const String title, String *value);

  // Add a value to a specific menu
  void addValue(const MenuID &parent, const String title, String (*callback)(void), String *value = nullptr );
  void addValue(const MenuID &parent, const String title, String *value);

  // Refresh values currently displayed
  void refreshValues();

  // Move upwards in the current menu
  void up();

  // Move downwards in the current menu
  void down();

  // Select a menu option
  void select();

  // Back up the navigation tree
  void back();
};


// Helper functions
MenuNode* newMenuNode(const String &title, String (*fn)(void) = nullptr, String *val = nullptr);
void deleteMenuNode(MenuNode *node);
MenuNode* getLastNodeInList(MenuNode *list);


#endif