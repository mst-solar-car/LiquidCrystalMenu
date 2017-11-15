# Liquid Crystal Menu
This is an Arduino library for easily creating a menus for LCD screens.

At the heart of this library, it is just a wrapper around the LiquidCrystal library.

&nbsp;

# Before You Begin
Before you get started with this library, you should be familiar with the Arduino [LiquidCrystal](https://www.arduino.cc/en/Reference/LiquidCrystal) library, and how to use it.

See [this tutorial](https://www.arduino.cc/en/Tutorial/HelloWorld?from=Tutorial.LiquidCrystal) for the basics of using an LCD with your Arduino.

&nbsp;

# Installation
For installation of this library please follow [this tutorial](https://www.arduino.cc/en/Guide/Libraries) (go to the "Importing a .zip library" section).

Get the zip folder from the tags page or by cloning this repository and creating the zip folder yourself.

&nbsp;

# Examples
Looking at, running, and modifying the examples provided by this library, is probably
the best way to learn how to use it.

There are examples that cover everything you need to know to get starting with
creating your own menus.

Example | Level | Description |
--------|:-------:|-------------|
[Simple Menu](examples/Beginner/SimpleMenu/SimpleMenu.ino) | Beginner | Create a basic menu |
[Splash Screen](examples/Beginner/SplashScreen/SplashScreen.ino) | Beginner | Shows how to create a splash screen |
[Nested Menus](examples/Intermediate/NestedMenus/NestedMenus.ino) | Intermediate | Creates menus inside of other menus |
[Values](examples/Advanced/Values/Values.ino) | Advanced | Creates values that get displayed on the LCD |
[Changing Values](examples/Advanced/ChangingValues/ChangingValues.ino) | Advanced | Shows how to modify values that are displayed on the screen |

&nbsp;

# Usage
This section will cover the basics of the API, but for working examples please refer to the [examples](examples/).

You must include the library before you can use it:
```c
#include <LiquidCrystalMenu.h>
```

&nbsp;

## Creating an Instance
Next, you'll need to create the `LiquidCrystalMenu` object, to do this,you need to connect the following pins from your LCD to your Arduino.

```c
LiquidCrystalMenu myMenu(RS, RW, EN, D4, D5, D6, D7);
```

This library also accepts any of the constructors provided by the [LiquidCrystal library](https://www.arduino.cc/en/Reference/LiquidCrystalConstructor).


Next, inside your `setup()` function you'll want to perform the following:

```c
// cols should be the number of columns your LCD has
// rows should be the number of rows your LCD has
myMenu.begin(cols, rows);
```
This will initialize the library so it can accurataly display stuff on your LCD.

&nbsp;


## Splash Screens
For some projects it could be desirable to have a splash screen displayed on boot. This is easily done using the `splash(String[], uint8_t)`.

Parameter | Type | Description | Default |
----------|------|------------| ---------|
1 | String[] | Array of the contents to display for the splash screen | N/A |
2 | uint8_t | Amount of time (in milliseconds) to display the splash screen | 4000 |

> **Note:** the array of contents_to_display should be the same number of rows as your
LCD, even if some of them are just empty strings.

```c
// This snipped is assuming that the LCD is 2 rows.
// The example Beginner/SplashScreen can handle LCDs up to 6 rows
// (if those even exist).
String mySplashScreen[] = {
  "Row 1",
  "Row 2"
};

// Display splash screen for 3 seconds
myMenu.splash(mySplashScreen, 3000);
```

It is recomended that you have your splash screen displayed before adding anything
to your menu.

&nbsp;

## Adding Menus
To add menus at a root level, use the `addMenu(char*)` method (inside your `setup()` function).

Parameter | Type | Description | Default |
----------|------|-------------|---------|
1 | char* | Name of the menu | N/A |



```c
myMenu.addMenu("Option 1");
myMenu.addMenu("Option 2");
```

This will result in the following menu structure:
```
- Option 1
- Option 2
```

&nbsp;

## Nested Menus
To add nested menus, save the return value of `addMenu()`, and pass that to the `addMenu(MenuID, char*)` method.

Parameter | Type | Description | Default |
----------|------|-------------|---------|
1 | MenuID | Value returned from `addMenu()` | N/A |
2 | char* | Name of the nested menu | N/A |



```c
MenuID option1 = myMenu.addMenu("Option 1");
myMenu.addMenu(option1, "Option 1.1");
myMenu.addMenu("Option 2");
```

This will give the following menu structure:
```
- Option 1
    - Option 1.1

- Option 2
```

&nbsp;

## Displaying Values
Since you are using a menu system with an Arduino you are probably wanting to
use it to show data. This is also easily done with this Library, using one of the
following methods:

1. `addValue(MenuID, char*, String *fn(void))`
2. `addValue(MenuID, char*, String*)`

Parameter | Type | Description | Default |
----------|------|-------------|---------|
1 | MenuID | Value returned from `addMenu()` (this value will be shown as a submenu of this menu) | N/A |
2 | char* | Name of the value | N/A |
3.1 | String *fn(void) | Pointer to a function that returns a String (to retrieve the value) | N/A |
3.2 | String* | Pointer to a string that holds the value | N/A |


```c
String myValueFunction() {
  return "Sample Value";
}

MenuID dataMenu = myMenu.addMenu("Data");
myMenu.addValue(dataMenu, "Sample", &myValueFunction);

myMenu.addMenu("Not Data");
```

or

```c
String myValue = "Sample Value";

MenuID dataMenu = myMenu.addMenu("Data");
myMenu.addValue(dataMenu, "Sample", &myValue);

myMenu.addMenu("Not Data");
```

Both of these will create the following menu structure:
```
- Data
    - Sample
        - When inside this menu the data value will be shown

- Not Data
```

&nbsp;

## Changing Displayed Values
Since the values you pass to the library are pointers, you can change the value they
represent and it will be reflected on the screen.

To do this, all you need to do is add the `refreshValues()` method to your `loop()` function.
This will allow for the screen to show the new value automatically.

&nbsp;

## Constants
The following table lists the constants (`#define`) that are used by this library.

You can override these by doing `#define CONSTNAT_NAME value` before the `#include <LiquidCrystalMenu.h>` in your sketch.

Constant | Description | Default |
---------|-------------|---------|
`LCDMENU_ACTION_DEBOUNCE` | Amount of time (in milliseconds) to delay at the end of the movement methods(`up()`, `down()`, `select()`, `back()`) | 350 |
`LCDMENU_REFRESH_INTERVAL` | Number of milliseconds used as a throttle for the `refreshValues()` method. The higher the interval the more milliseconds must pass before the library updates the value on the screen. | 750 |




