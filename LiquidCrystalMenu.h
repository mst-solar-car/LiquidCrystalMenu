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


/**
 * Struct that represents an item on a menu
 */
struct MenuItem {
  String title;
  MenuItem *parent;
  MenuItem *submenus; // Array of submenus
  int num_submenus;  // Number of submenus
  int submenus_size; // Maximum size of the submenus array
  int selected_item; // Index of the item currently selected
};


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

  MenuItem root_menu;
  MenuItem *active_menu;

  void Draw();

public:
  // Constructor
  LiquidCrystalMenu(int rs, int rw, int enable, int d4, int d5, int d6, int d7);

  // Destructor
  ~LiquidCrystalMenu();

  // Start the library
  void begin(const int cols, const int rows);

  // Shows a splash screen
  void splashScreen(const String contents[], const int delayMs = 4000);

  // Add a new menu item (to the active menu)
  MenuItem AddMenu(const String title);

  // Add a new menu item to a specific menu
  MenuItem AddMenu(const MenuItem &parent, const String title);

  // Move upwards in the current menu
  void Up();

  // Move downwards in the current menu
  void Down();

  // Select a menu option
  void Select();

  // Back up the navigation tree
  void Back();
};


#endif