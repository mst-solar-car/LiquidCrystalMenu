#include "LiquidCrystalMenu.h"


// Add a new item to the active menu item
void addToSubmenu(MenuItem* active, MenuItem item) {
  if (active->num_submenus >= active->submenus_size) {
    // Increase array size
    MenuItem *newArr = new MenuItem[active->submenus_size + LCDMENU_ARRAY_INCREMENT];

    for (int i = 0; i < active->num_submenus; i++) {
      newArr[i] = active->submenus[i];
    }

    delete [] active->submenus;
    active->submenus = newArr;
    newArr = NULL;
  }

  // Add the new menu item
  active->submenus[active->num_submenus] = item;
  active->num_submenus++;
}


/**
 * Basic constructor
 */
LiquidCrystalMenu::LiquidCrystalMenu(int rs, int rw, int enable, int d4, int d5, int d6, int d7) {
  this->pin_rs = rs;
  this->pin_rw = rw;
  this->pin_en = enable;
  this->pin_d4 = d4;
  this->pin_d5 = d5;
  this->pin_d6 = d6;
  this->pin_d7 = d7;

  this->lcd = new LiquidCrystal(rs, rw, enable, d4, d5, d6, d7);

  this->root_menu = (MenuItem) {
    "$ROOT",
    new MenuItem[LCDMENU_ARRAY_INCREMENT],
    0, // No submenus
    LCDMENU_ARRAY_INCREMENT,
    0
  };

  this->active_menu = &(this->root_menu);
}


// Recursively clean up menu items
void recursiveDelete(MenuItem &item) {
  for (int i = 0; i < item.num_submenus; i++) {
    recursiveDelete(item.submenus[i]);
  }

  delete [] item.submenus;
}


/**
 * Destructor
 */
LiquidCrystalMenu::~LiquidCrystalMenu() {
  delete this->lcd;

  recursiveDelete(this->root_menu);

  this->active_menu = NULL;
}


/**
 * Initialize and begin the library
 */
void LiquidCrystalMenu::begin(int cols, int rows) {
  this->rows = rows;
  this->cols = cols;

  // Initialize and clear the LCD
  this->lcd->begin(cols, rows);
  this->lcd->clear();

  this->Draw();
}


/**
 * Custom Splash Screen for the display
 */
void LiquidCrystalMenu::splashScreen(const String contents[], const int delayMs) {
  this->lcd->clear();

  // Display number of rows
  for (int i = 0; i < this->rows; i++) {
    this->lcd->setCursor(0, i);
    this->lcd->print(contents[i]);
  }

  // Delay and then clear again
  delay(delayMs);
  this->lcd->clear();
}


/**
 * Add a menu to the active menu
 */
MenuItem LiquidCrystalMenu::AddMenu(String title) {
  MenuItem item = (MenuItem) {
    title,
    new MenuItem[LCDMENU_ARRAY_INCREMENT],
    0, // No submenus
    LCDMENU_ARRAY_INCREMENT,
    0
  };

  addToSubmenu(this->active_menu, item);

  this->Draw();

  return item;
}


/**
 * Renders the active menu
 */
void LiquidCrystalMenu::Draw() {
  this->lcd->clear();
  this->lcd->setCursor(0, 0);

  MenuItem *menu = this->active_menu; // Alias

  // Show if the menu is empty
  if (menu->num_submenus == 0) {
    this->lcd->print("Empty");
    return;
  }

  // Show the menu items
  for (int i = menu->selected_item; i < (menu->selected_item + this->rows); i++) {
    // If there are less menu items than rows, do not loop around
    if (i > menu->num_submenus && i < this->rows) {
      this->lcd->print("BYE");
      break;
    }

    // Position cursor on appropriate row
    this->lcd->setCursor(0, (i - menu->selected_item) % this->rows);

    // Display the title of the menu item
    if (i == menu->selected_item) {
      this->lcd->print("> " + menu->submenus[i % this->rows].title);
    }
    else {
      this->lcd->print(menu->submenus[i % this->rows].title);
    }
  }

}