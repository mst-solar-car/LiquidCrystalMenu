#include "LiquidCrystalMenu.h"


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
}


/**
 * Destructor
 */
LiquidCrystalMenu::~LiquidCrystalMenu() {
  delete this->lcd;
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
}
