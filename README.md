| Supported Targets | ESP32 | ESP32-C3 | ESP32-C6 | ESP32-H2 | ESP32-S2 | ESP32-S3

# Temperature Sensor Example

## Overview

This exemple create a LED driver to control the LED on an light bulb with temprature white variable. We drive it through a mosfet and a PWM signal.

Please note that in the exemple the mosfet inverse tension so 1 is off and 0 is on.

## How to use example

### Hardware Required

To run this example, you should have one ESP32, ESP32-S, ESP32-C or ESP32-H based development board as well. 

#### Pin Assignment:

In this example, we use the following pin assignment:
    5 -> Warm White
    6 -> Cold White

**Note:** There's no need to add an external pull-up resistors for SDA/SCL pin, because the driver will enable the internal pull-up resistors.

### Build and Flash

Enter `idf.py -p PORT flash monitor` to build, flash and monitor the project.

(To exit the serial monitor, type ``Ctrl-]``.)
