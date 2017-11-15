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
#ifndef LCDMENU_ACTION_DEBOUNCE
  #define LCDMENU_ACTION_DEBOUNCE   350
#endif
#ifndef LCDMENU_REFRESH_INTERVAL
  #define LCDMENU_REFRESH_INTERVAL  750 // Number of milliseconds to allow for refreshing
#endif

/**
 * Enum for events
 */
enum MenuEvent {
  FocusEvent,    // When a menu item gains focus
  SelectEvent   // When a menu value is selected
};

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

  void (*focusEvent)(void);
  void (*selectEvent)(void);
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

  // Initialize (constructor)
  void init();

  // Retrieves the value of a node
  String* getValue(MenuNode *node);

  // Attach an event listener
  void attach(const MenuEvent &event, MenuNode *node, void (*callback)(void));

  // Dispatch an event callback to a node
  void dispatch(const MenuEvent &event, MenuNode *node);


public:
  // Constructors
  LiquidCrystalMenu(const uint8_t &rs, const uint8_t &rw, const uint8_t &en,
                    const uint8_t &d4, const uint8_t &d5, const uint8_t &d6,
                    const uint8_t &d7
                  );
  LiquidCrystalMenu(const uint8_t &rs, const uint8_t &en, const uint8_t &d4,
                    const uint8_t &d5, const uint8_t &d6, const uint8_t &d7
                  );
  LiquidCrystalMenu(const uint8_t &rs, const uint8_t &en, const uint8_t &d0,
                    const uint8_t &d1, const uint8_t &d2, const uint8_t &d3,
                    const uint8_t &d4, const uint8_t &d5, const uint8_t &d6,
                    const uint8_t &d7
                  );
  LiquidCrystalMenu(const uint8_t &rs, const uint8_t &rw, const uint8_t &en,
                    const uint8_t &d0, const uint8_t &d1, const uint8_t &d2,
                    const uint8_t &d3, const uint8_t &d4, const uint8_t &d5,
                    const uint8_t &d6, const uint8_t &d7
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
  MenuID addValue(const char *title, String (*callback)(void));
  MenuID addValue(const char *title, String *value);

  // Add a value to a specific menu
  MenuID addValue(const MenuID &parent, const char *title, String (*callback)(void), String *value = nullptr );
  MenuID addValue(const MenuID &parent, const char *title, String *value);

  // Attach an event to a menu item
  void listen(const MenuEvent &event, const MenuID &menu, void (*callback)(void));

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