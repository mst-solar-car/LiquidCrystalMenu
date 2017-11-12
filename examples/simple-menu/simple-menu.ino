#include <LiquidCrystalMenu.h>


/**
 * Changes these values to fit your LCD screen
 */
#define LCD_COLS  20
#define LCD_ROWS  4


LiquidCrystalMenu navigation(12, 11, 9, 5, 4, 3, 2);


void setup() {
  navigation.begin(LCD_COLS, LCD_ROWS);
}


void loop() {

}
