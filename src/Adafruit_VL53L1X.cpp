/*!
 * @file Adafruit_VL53L1X.cpp
 *
 * @mainpage Adafruit VL53L1X time-of-flight sensor
 *
 * @section intro_sec Introduction
 *
 * This is the documentation for Adafruit's VL53L1X driver for the
 * Arduino platform.  It is designed specifically to work with the
 * Adafruit VL53L1X breakout: https://www.adafruit.com/product/3967
 *
 * These sensors use I2C to communicate, 2 pins (SCL+SDA) are required
 * to interface with the breakout.
 *
 * Adafruit invests time and resources providing this open source code,
 * please support Adafruit and open-source hardware by purchasing
 * products from Adafruit!
 *
 * @section dependencies Dependencies
 *
 *
 * @section author Author
 *
 * Written by Limor Fried/Ladyada for Adafruit Industries.
 *
 * @section license License
 *
 * BSD license, all text here must be included in any redistribution.
 *
 */

#include "Adafruit_VL53L1X.h"

/**************************************************************************/
/*!
    @brief  Create a new VL53L1X instance
    @param  shutdown_pin Optional specify pin attached to shutdown
    @param irq_pin Optional specify pin attached to interrupt
*/
/**************************************************************************/
Adafruit_VL53L1X::Adafruit_VL53L1X(uint8_t shutdown_pin, uint8_t irq_pin)
    : VL53L1X(NULL, irq_pin) {
  _shutdown_pin = shutdown_pin;
  _irq_pin = irq_pin;
}

/**************************************************************************/
/*!
    @brief  Setups the I2C interface and hardware
    @param  i2c_addr Optional I2C address the sensor can be found on. Default is
   0x29
    @param  theWire Optional The Wire bus object to use.
    @param  debug Optional debug flag. If true, debug information will print out
   via Serial.print during setup. Defaults to false.
    @returns  True if device is set up, false on any failure
*/
/**************************************************************************/
bool Adafruit_VL53L1X::begin(uint8_t i2c_addr, TwoWire *theWire, bool debug) {
  if (_shutdown_pin != -1) {
    pinMode(_shutdown_pin, OUTPUT);
    digitalWrite(_shutdown_pin, HIGH);
    digitalWrite(_shutdown_pin, LOW);
    delay(5);
    digitalWrite(_shutdown_pin, HIGH);
  }
  delay(5);

  theWire->begin();

  MyDevice.I2cHandle = theWire;
  dev_i2c = theWire;

  vl_status = InitSensor(i2c_addr * 2);
  if (vl_status != VL53L1X_ERROR_NONE) {
    return false;
  }

  if (sensorID() != 0xEACC) {
    return false;
  }

  /*
  Status = VL53L1_software_reset(pMyDevice);
  if (Status != VL53L1_ERROR_NONE) return false;

  // from Nucleo main.c
  Status = VL53L1_WaitDeviceBooted(pMyDevice);
  if (Status != VL53L1_ERROR_NONE) return false;

  if (debug)
    Serial.println("DataInit");
  Status = VL53L1_DataInit(pMyDevice);         // Data initialization
  if (Status != VL53L1_ERROR_NONE) return false;

  if (debug)
    Serial.println("StaticInit");
  Status = VL53L1_StaticInit(pMyDevice);
  if (Status != VL53L1_ERROR_NONE) return false;

  Status = VL53L1_GetDeviceInfo(pMyDevice, &DeviceInfo );
  if (Status != VL53L1_ERROR_NONE) return false;
  if (debug) {
    Serial.println( F( "VL53L1X Info:" ) );
    Serial.print( F( "Device Name: ")  ); Serial.print( DeviceInfo.Name );
    Serial.print( F( ", Type: " ) ); Serial.print( DeviceInfo.Type );
    Serial.print( F( ", ID: " ) ); Serial.println( DeviceInfo.ProductId );

    Serial.print( F( "Rev Major: " ) ); Serial.print(
  DeviceInfo.ProductRevisionMajor ); Serial.print( F( ", Minor: " ) );
  Serial.println( DeviceInfo.ProductRevisionMinor );
  }

  if (! SetDistanceMode(VL53L1_DISTANCEMODE_LONG)) return false;
  if (! SetMeasurementTimingBudgetMicroSeconds(50000)) return false;
  if (! SetInterMeasurementPeriodMilliSeconds(50)) return false;

  */
  return true;
}

/**************************************************************************/
/*!
    @brief  Get the sensor ID.
    @returns The sensor ID.
*/
/**************************************************************************/
uint16_t Adafruit_VL53L1X::sensorID(void) {
  uint16_t sensorID = 0;
  vl_status = VL53L1X_GetSensorId(&sensorID);
  return sensorID;
}

/**************************************************************************/
/*!
    @brief  Get the distance.
    @returns The distance.
*/
/**************************************************************************/
int16_t Adafruit_VL53L1X::distance(void) {
  uint16_t distance;
  uint8_t rangeStatus;

  vl_status = VL53L1X_GetRangeStatus(&rangeStatus);
  if ((vl_status != VL53L1X_ERROR_NONE) || (rangeStatus != 0x0)) {
    return -1;
  }

  vl_status = VL53L1X_GetDistance(&distance);
  if (vl_status != VL53L1X_ERROR_NONE) {
    return -1;
  }
  return (int16_t)distance;
}

/**************************************************************************/
/*!
    @brief  Clear the interrupt.
    @returns True if successful, otherwise false.
*/
/**************************************************************************/
bool Adafruit_VL53L1X::clearInterrupt(void) {
  vl_status = VL53L1X_ClearInterrupt();
  return (vl_status == VL53L1X_ERROR_NONE);
}

/**************************************************************************/
/*!
    @brief  Set the interrupt polarity.
    @param polarity The polarity to set as a boolean.
    @returns True if successful, otherwise false.
*/
/**************************************************************************/
bool Adafruit_VL53L1X::setIntPolarity(bool polarity) {
  vl_status = VL53L1X_SetInterruptPolarity(polarity);
  return (vl_status == VL53L1X_ERROR_NONE);
}

/**************************************************************************/
/*!
    @brief  Get the interrupt polarity.
    @returns Polarity as a boolean.
*/
/**************************************************************************/
bool Adafruit_VL53L1X::getIntPolarity(void) {
  uint8_t x = 0;
  vl_status = VL53L1X_GetInterruptPolarity(&x);
  return (bool)x;
}

/**************************************************************************/
/*!
    @brief  Start ranging operations.
    @returns True if successful, otherwise false.
*/
/**************************************************************************/
bool Adafruit_VL53L1X::startRanging(void) {
  vl_status = VL53L1X_StartRanging();
  return (vl_status == VL53L1X_ERROR_NONE);
}

/**************************************************************************/
/*!
    @brief  Stop ranging operations.
    @returns True if successful, otherwise false.
*/
/**************************************************************************/
bool Adafruit_VL53L1X::stopRanging(void) {
  vl_status = VL53L1X_StopRanging();
  return (vl_status == VL53L1X_ERROR_NONE);
}

/**************************************************************************/
/*!
    @brief  Check status of new data.
    @returns True if new data available, otherwise false.
*/
/**************************************************************************/
bool Adafruit_VL53L1X::dataReady(void) {
  uint8_t x = 0;
  vl_status = VL53L1X_CheckForDataReady(&x);
  return (bool)x;
}

/**************************************************************************/
/*!
    @brief  Set the timing budget.
    @param ms Timing budget in milliseconds.
    @returns True if successful, otherwise false.
*/
/**************************************************************************/
bool Adafruit_VL53L1X::setTimingBudget(uint16_t ms) {
  vl_status = VL53L1X_SetTimingBudgetInMs(ms);
  return (vl_status == VL53L1X_ERROR_NONE);
}

/**************************************************************************/
/*!
    @brief  Get the timing budget.
    @returns Timing budget in milliseconds.
*/
/**************************************************************************/
uint16_t Adafruit_VL53L1X::getTimingBudget(void) {
  uint16_t ms = 0;

  vl_status = VL53L1X_GetTimingBudgetInMs(&ms);
  if (vl_status == VL53L1X_ERROR_NONE) {
    return ms;
  }
  return 0;
}

/**************************************************************************/
/*!
    @brief  Set the inter measurement time.
    @param ms Inter measurement time in milliseconds.
    @returns True if successful, otherwise false.
*/
/**************************************************************************/
bool Adafruit_VL53L1X::setInterMeasurement(uint16_t ms){
  vl_status = VL53L1X_SetInterMeasurementInMs(ms);
  return (vl_status == VL53L1X_ERROR_NONE);
}

/**************************************************************************/
/*!
    @brief  Get the inter measurement time.
    @returns inter measurement time in milliseconds.
*/
/**************************************************************************/
uint16_t Adafruit_VL53L1X::getInterMeasurement(){
  uint16_t ms = 0;

  vl_status = VL53L1X_GetInterMeasurementInMs(&ms);
  if (vl_status == VL53L1X_ERROR_NONE) {
    return ms;
  }
  return 0;
}

/**************************************************************************/
/*!
    @brief  Set distance mode.
    @param mode Operation mode
                1 = short
                2 = medium
                X = long
    @returns True if successful, otherwise false.
*/
/**************************************************************************/
bool Adafruit_VL53L1X::setDistanceMode(uint16_t mode) {
  vl_status = VL53L1X_SetDistanceMode(mode);
  return (vl_status == VL53L1X_ERROR_NONE);
}

/*
}

boolean
Adafruit_VL53L1X::GetRangingMeasurementData(VL53L1_RangingMeasurementData_t
*ranging) { Status = VL53L1_GetRangingMeasurementData(pMyDevice, ranging);
  return (Status == VL53L1_ERROR_NONE);
}
*/
