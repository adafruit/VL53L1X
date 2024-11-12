# Adafruit VL53L1X Library [![Build Status](https://github.com/adafruit/Adafruit_VL53L1X/workflows/Arduino%20Library%20CI/badge.svg)](https://github.com/adafruit/Adafruit_VL53L1X/actions) [![Documentation](https://github.com/adafruit/ci-arduino/blob/master/assets/doxygen_badge.svg)](http://adafruit.github.io/Adafruit_VL53L1X/html/index.html)

<img src="https://cdn-shop.adafruit.com/970x728/3967-00.jpg" height="300"/>

This is a library for the Adafruit VL53L1X time-of-flight breakout:
  * https://www.adafruit.com/products/3967

Check out the links above for our tutorials and wiring diagrams. This chip uses I2C to communicate

Adafruit invests time and resources providing this open source code, please support Adafruit and open-source hardware by purchasing products from Adafruit!

Written by Limor Fried/Ladyada for Adafruit Industries.
Uses ST's VL53L1X underlying api implementation
BSD license, all text above must be included in any redistribution

## API

This sensor uses I2C to communicate. And I2C instance is required to access to the sensor.

The API provides simple distance measure, single swipe gesture detection,
directional (left/right) swipe gesture detection and single tap gesture detection.


## Note

The maximum detection distance is influenced by the color of the target and
the indoor or outdoor situation due to absence or presence of external
infrared.
The detection range can be comprise between ~40cm and ~400cm. (see chapter 5 of
the VL53L1X datasheet).
The library should work also with standard Arduino boards. In this case you just
need to adjust the code in the sketch in order to use the correct Wire instance and
the correct pin number for XSHUT and GPIO1 pins.

## Documentation

You can find the source files at
https://github.com/stm32duino/VL53L1X

The VL53L1X datasheet is available at
https://www.st.com/content/st_com/en/products/imaging-and-photonics-solutions/proximity-sensors/vl53l1x.html
