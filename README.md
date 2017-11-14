# Liquid Crystal Menu
This is an Arduino library for easily creating a menus for LCD screens.

At the heart of this library, it is just a wrapper around the LiquidCrystal library.


# Installation
This section is being written


# Examples
Looking at, running, and modifying the examples provided by this library, is probably
the best way to learn how to use it.

There are examples that cover everything you need to know to get starting with
creating your own menus.


# Usage
This section will cover the basics of the API, but for working examples please refer to the examples.

## Include
To begin using this library you need to include the library.
```c
#include <LiquidCrystalMenu.h>
```

## Creating Object
Next, you'll need to create the `LiquidCrystalMenu` object, to do this,you need to connect the following pins from your LCD to your Arduino.

Pin |
----|
RS |
RW |
EN (Enable) |
D4 |
D5 |
D6 |
D7

Once you have those pins connected you can call the constructor
```c
LiquidCrystalMenu myMenuObject(RS, RW, EN, D4, D5, D6, D7);
```

## Adding Menus
To add menus at a root level, use the `addMenu(string)` method (inside your `setup()` function).

```c
myMenuObject.addMenu("Option 1");
myMenuObject.addMenu("Option 2");
```

This will result in the following menu structure:
```
- Option 1
- Option 2
```

## Nested Menus
To add nested menus, save the return value of `addMenu(string)`, and pass that to the `addMenu(MenuID, string)` method.

```c
MenuID option1 = myMenuObject.addMenu("Option 1");
myMenuObject.addMenu(option1, "Option 1.1");
myMenuObject.addMenu("Option 2");
```

This will give the following menu structure:
```
- Option 1
    - Option 1.1

- Option 2
```





