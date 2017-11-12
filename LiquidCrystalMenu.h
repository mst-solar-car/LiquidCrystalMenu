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

public:
  // Constructor
  LiquidCrystalMenu(int rs, int rw, int enable, int d4, int d5, int d6, int d7);

  // Start the library
  void begin(int cols, int rows);
};


#endif