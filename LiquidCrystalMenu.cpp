#include "LiquidCrystalMenu.h"

// Create glyphs
byte menuArrow[8] = {0b00000,0b00100,0b00010,0b11111,0b00010,0b00100,0b00000,0b00000};


/**
 * Constructors
 */
LiquidCrystalMenu::LiquidCrystalMenu(
  const uint8_t &rs, const uint8_t &rw, const uint8_t &en, const uint8_t &d4,
  const uint8_t &d5, const uint8_t &d6, const uint8_t &d7
) {
  // Create the LCD instance
  this->lcd = new LiquidCrystal(rs, rw, en, d4, d5, d6, d7);
  this->init();
}

LiquidCrystalMenu::LiquidCrystalMenu(
  const uint8_t &rs, const uint8_t &en, const uint8_t &d4,
  const uint8_t &d5, const uint8_t &d6, const uint8_t &d7
) {
  this->lcd = new LiquidCrystal(rs, en, d4, d5, d6, d7);
  this->init();
}

LiquidCrystalMenu::LiquidCrystalMenu(
  const uint8_t &rs, const uint8_t &en, const uint8_t &d0,
  const uint8_t &d1, const uint8_t &d2, const uint8_t &d3,
  const uint8_t &d4, const uint8_t &d5, const uint8_t &d6,
  const uint8_t &d7
) {
  this->lcd = new LiquidCrystal(rs, en, d0, d1, d2, d3, d4, d5, d6, d7);
  this->init();
}

LiquidCrystalMenu::LiquidCrystalMenu(
  const uint8_t &rs, const uint8_t &rw, const uint8_t &en,
  const uint8_t &d0, const uint8_t &d1, const uint8_t &d2,
  const uint8_t &d3, const uint8_t &d4, const uint8_t &d5,
  const uint8_t &d6, const uint8_t &d7
) {
  this->lcd = new LiquidCrystal(rs, rw, en, d0, d1, d2, d3, d4, d5, d6, d7);
  this->init();
}


/**
 * Initializes the library (called by constructors)
 */
void LiquidCrystalMenu::init() {
  // Register Glyphs with the LCD
  this->lcd->createChar(MENU_ARROW_GLYPH, menuArrow);

  // Create root node
  this->root = newMenuNode("$", nullptr, nullptr);
  this->menu = this->root;
}


/**
 * Destructor
 */
LiquidCrystalMenu::~LiquidCrystalMenu() {
  delete this->lcd;
  this->lcd = nullptr;

  // Delete everything
  deleteMenuNode(this->root);
  this->root = nullptr;
  this->menu = nullptr;
}


/**
 * Initialize and begin the library
 */
void LiquidCrystalMenu::begin(const uint8_t &cols, const uint8_t &rows) {
  this->rows = rows;
  this->cols = cols;

  // Initialize and clear the LCD
  this->lcd->begin(cols, rows);
  this->lcd->clear();

  this->draw();
}


/**
 * Custom Splash Screen for the display
 */
void LiquidCrystalMenu::splash(const String contents[], const uint8_t &delayMs /*= 4000*/) {
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
 * A a menu to a specific menu
 */
MenuID LiquidCrystalMenu::addMenu(const MenuID &parent, const char *title) {
  // Find parent
  MenuNode *parentPtr = this->findNodeWithAddr(this->root, parent);

  // Create new node
  MenuNode *toAdd = newMenuNode(title, nullptr, nullptr);

  // Add the menu node
  this->addNode(parentPtr, toAdd);

  // Redraw
  this->draw();

  return (MenuID)toAdd;
}


/**
 * Add a menu to the root menu
 */
MenuID LiquidCrystalMenu::addMenu(const char *title) {
  return this->addMenu((MenuID)(this->root), title);
}


/**
 * Adds a value to the menu
 */
MenuID LiquidCrystalMenu::addValue(const MenuID &parent, const char *title, String (*callback)(void), String *value /*= nullptr*/) {
  // Find parent
  MenuNode *parentPtr = this->findNodeWithAddr(this->root, parent);

  // Create new node
  MenuNode *toAdd = newMenuNode(title, callback, value);

  // Add the node
  this->addNode(parentPtr, toAdd);

  this->draw();

  return (int)toAdd;
}


/**
 * Adds a value to a specific menu
 */
MenuID LiquidCrystalMenu::addValue(const MenuID &parent, const char *title, String *value) {
  return this->addValue(parent, title, nullptr, value);
}


/**
 * Add a value to the root
 */
MenuID LiquidCrystalMenu::addValue(const char *title, String (*callback)(void)) {
  return this->addValue((MenuID)(this->root), title, callback);
}


/**
 * Add a value to the root
 */
MenuID LiquidCrystalMenu::addValue(const char *title, String *value) {
  return this->addValue((MenuID)(this->root), title, value);
}


/**
 * Add an event listener to a node
 */
void LiquidCrystalMenu::listen(const MenuEvent &event, const MenuID &menu, void (*callback)(MenuEvent, MenuItem)) {
  // Attach a node
  MenuNode *node = this->findNodeWithAddr(this->root, menu);
  if (node == this->root) {
    return; // No...
  }

  this->attach(event, node, callback);
}


/**
 * Retrieves the value of a menu item (if it has one)
 */
String LiquidCrystalMenu::getValue(const MenuID &menu) {
  MenuNode *node = this->findNodeWithAddr(this->root, menu);
  if (node == this->root) {
    return "";
  }

  String *val = this->getValue(node->submenu);
  if (val == nullptr) {
    return "";
  }

  return *val;
}


/**
 * Refresh the value currently being displayed
 */
void LiquidCrystalMenu::refreshValues() {
  static unsigned long last_refresh = 0;

  if (millis() - last_refresh > LCDMENU_REFRESH_INTERVAL) {
    if (this->menu->valueFn != nullptr || this->menu->value != nullptr) {
      this->draw();
    }

    last_refresh = millis();
  }
}


/**
 * Renders the active menu
 */
void LiquidCrystalMenu::draw() {
  this->lcd->clear();
  this->lcd->setCursor(0, 0);

  // Just in case
  if (this->menu == nullptr) {
    this->menu = this->root;
  }

  // Show value if this is a value
  String *val = this->getValue(this->menu);
  if (val != nullptr) {
    // Give section a title
    this->lcd->print(this->menu->title);
    this->lcd->setCursor(0, 1);

    this->lcd->print(*val);
    return;
  }

  // Display the menu options
  MenuNode *ptr = this->menu;
  short row = 0;

  // Do not show the $ROOT element
  if (ptr == this->root) {
    ptr = ptr->next;

    // Force a change from the menu
    if (ptr != nullptr) {
      this->menu = ptr;
    }
  }

  while (ptr != nullptr && row < this->rows) {
    this->lcd->setCursor(0, row);

    if (row == 0) {
      this->lcd->write(MENU_ARROW_GLYPH);
    }

    this->lcd->print(ptr->title);
    ptr = ptr->next;
    row++;
  }
}


/**
 * Move Up
 */
void LiquidCrystalMenu::up() {
  // Change to the previous menu item if there is one
  if (this->menu->previous != nullptr) {
    this->menu = this->menu->previous;
    this->draw();

    // Dispatch focus event
    this->dispatch(FocusEvent, this->menu);
  }

  delay(LCDMENU_ACTION_DEBOUNCE);
}


/**
 * Move Down
 */
void LiquidCrystalMenu::down() {
  // Change to the next menu item if there is one
  if (this->menu->next != nullptr) {
    this->menu = this->menu->next;
    this->draw();

    // Dispatch focus event
    this->dispatch(FocusEvent, this->menu);
  }

  delay(LCDMENU_ACTION_DEBOUNCE);
}


/**
 * Move backwards up the navigation tree
 */
void LiquidCrystalMenu::back() {
  // Change to the parent menu if there is one
  if (this->menu->parent != nullptr) {
    this->menu = this->menu->parent;
    this->draw();

    // Dispatch the focus event to the new focused node
    this->dispatch(FocusEvent, this->menu);
  }

  delay(LCDMENU_ACTION_DEBOUNCE);
}


/**
 * Go into a submenu
 */
void LiquidCrystalMenu::select() {
  // If no submenu then don't do anything
  if (this->menu->submenu != nullptr) {
    this->menu = this->menu->submenu;
    this->draw();

    // Dispatch select event to the parent
    this->dispatch(SelectEvent, this->menu->parent);

    // Dispatch focus event to the new focused item
    this->dispatch(FocusEvent, this->menu);
  }

  delay(LCDMENU_ACTION_DEBOUNCE);
}


/**
 * Finds a menu node with a certain memory address
 */
MenuNode* LiquidCrystalMenu::findNodeWithAddr(MenuNode *node, const MenuID &memAddr) {
  MenuNode *tmp = nullptr;

  // Check the node that is about to be searched
  if ((MenuID)node == memAddr) {
    return node;
  }

  // Check the next item
  if (node->next != nullptr) {
    tmp = this->findNodeWithAddr(node->next, memAddr);
    if (tmp != nullptr) {
      return tmp;
    }
  }

  // Search submenus
  if (node->submenu != nullptr) {
    tmp = this->findNodeWithAddr(node->submenu, memAddr);
    if (tmp != nullptr) {
      return tmp;
    }
  }

  return this->root; // Not found
}


/**
 * Returns the value of a node (if it has one)
 */
String* LiquidCrystalMenu::getValue(MenuNode *node) {
  if (node == nullptr) {
    return nullptr;
  }

  if (node->valueFn != nullptr) {
    return new String((node->valueFn)());
  }
  else if (node->value != nullptr) {
    return node->value;
  }

  return nullptr;
}


/**
 * Attaches an event to a node
 */
void LiquidCrystalMenu::attach(const MenuEvent &event, MenuNode *node, void (*callback)(MenuEvent, MenuItem)) {
  switch (event) {
    case FocusEvent:
      node->focusEvent = callback;
      break;
    case SelectEvent:
      node->selectEvent = callback;
      break;
  }
}


/**
 * Dispatch an event to a menu item
 */
void LiquidCrystalMenu::dispatch(const MenuEvent &event, MenuNode *node) {
  void (*fn)(MenuEvent, MenuItem) = nullptr;

  MenuItem item = MenuItem { (int)node, String(node->title) };

  switch (event) {
    case FocusEvent:
      fn = node->focusEvent;
      break;
    case SelectEvent:
      fn = node->selectEvent;
      break;
  }

  // Trigger event
  if (fn != nullptr) {
    (fn)(event, item);
  }
}


/**
 * Generic add a node somewhere in the menu system
 */
void LiquidCrystalMenu::addNode(MenuNode *root, MenuNode *toAdd) {
  MenuNode *tmp = nullptr;

  toAdd->parent = root; // Give the new element a parent

  // Handle adding something to the root menu
  if (root == this->root) {
    tmp = getLastNodeInList(root);
    tmp->next = toAdd;
    toAdd->previous = tmp;
    return;
  }

  // Handle not adding to the root menu
  if (root->submenu == nullptr) {
    // First in submenu
    root->submenu = toAdd;
  }
  else {
    // Add at the end of the submenu
    tmp = getLastNodeInList(root->submenu);
    tmp->next = toAdd;
    toAdd->previous = tmp;
  }
}









/**
 * Helper function for creating a new MenuNode and initializing values
 */
MenuNode* newMenuNode(const char *title, String (*fn)(void), String *val) {
  MenuNode *node = new MenuNode;
  node->title = title;
  node->parent = nullptr;
  node->submenu = nullptr;
  node->previous = nullptr;
  node->next = nullptr;
  node->valueFn = nullptr;
  node->value = nullptr;

  node->focusEvent = nullptr;
  node->selectEvent = nullptr;

  if (fn != nullptr || val != nullptr) {
    MenuNode* subNode = node->submenu = newMenuNode(title, nullptr, nullptr);
    subNode->parent = node;
    subNode->valueFn = fn;
    subNode->value = val;
  }

  return node;
}


/**
 * Destructor for a menu node
 */
void deleteMenuNode(MenuNode *node) {
  if (node->next != nullptr) {
    deleteMenuNode(node->next);
    node->next = nullptr;
  }

  if (node->submenu != nullptr) {
    deleteMenuNode(node->submenu);
    node->submenu = nullptr;
  }

  delete node->title;
  node->title = nullptr;
  node->parent = nullptr;
  node->previous = nullptr;
  node->valueFn = nullptr;
  node->value = nullptr;

  node->focusEvent = nullptr;
  node->selectEvent = nullptr;
}


/**
 * Returns the last node in a list
 */
MenuNode* getLastNodeInList(MenuNode *list) {
  MenuNode *ptr = list;
  while (ptr->next != nullptr) {
    ptr = ptr->next;
  }

  return ptr;
}