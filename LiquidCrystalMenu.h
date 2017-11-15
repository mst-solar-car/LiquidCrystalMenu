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
#ifndef LCDMENU_ARRAY_INCREMENT
  #define LCDMENU_ARRAY_INCREMENT   2
#endif
#ifndef LCDMENU_ACTION_DEBOUNCE
  #define LCDMENU_ACTION_DEBOUNCE   350
#endif
#ifndef LCDMENU_REFRESH_INTERVAL
  #define LCDMENU_REFRESH_INTERVAL  750 // Number of milliseconds to allow for refreshing
#endif


// Type alias
typedef int MenuID;

/**
 * Doubly Linked List node that represents something on a menu
 */
struct MenuNode {
  char *title;
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
  // LCD size and object
  uint8_t rows;
  uint8_t cols;
  LiquidCrystal* lcd;

  MenuNode *root; // Root menu
  MenuNode *menu; // Currently selected MenuNode

  // Draw on the
  void draw();

  // Finds an item with a memory address
  MenuNode* findNodeWithAddr(MenuNode *node, const MenuID &memAddr);

  // Adds to a menu
  void addNode(MenuNode *root, MenuNode *toAdd);

public:
  // Constructor
  LiquidCrystalMenu(const uint8_t &rs, const uint8_t &rw, const uint8_t &en,
                    const uint8_t &d4, const uint8_t &d5, const uint8_t &d6,
                    const uint8_t &d7
                  );

  // Destructor
  ~LiquidCrystalMenu();

  // Start the library
  void begin(const uint8_t &cols, const uint8_t &rows);

  // Shows a splash screen
  void splash(const String contents[], const uint8_t &delayMs = 4000);

  // Add a new menu item (to the root menu)
  MenuID addMenu(const char *title);

  // Add a new menu item to a specific menu
  MenuID addMenu(const MenuID &parent, const char *title);

  // Add a value to the root menus
  void addValue(const char *title, String (*callback)(void));
  void addValue(const char *title, String *value);

  // Add a value to a specific menu
  void addValue(const MenuID &parent, const char *title, String (*callback)(void), String *value = nullptr );
  void addValue(const MenuID &parent, const char *title, String *value);

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
MenuNode* newMenuNode(const char *title, String (*fn)(void) = nullptr, String *val = nullptr);
void deleteMenuNode(MenuNode *node);
MenuNode* getLastNodeInList(MenuNode *list);


#endif