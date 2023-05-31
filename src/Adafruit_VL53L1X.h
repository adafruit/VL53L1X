/*!
 * @file Adafruit_VL53L1X.h

  This is a library for the Adafruit VL53L1X Sensor Breakout

  Designed specifically to work with the VL53L1X sensor from Adafruit
  ----> https://www.adafruit.com/products/3967

  These sensors use I2C to communicate, 2 pins are required to
  interface
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#ifndef ADAFRUIT_VL53L1X_H
#define ADAFRUIT_VL53L1X_H

#include "Wire.h"
#include "vl53l1x_class.h"

#define VL53L1X_I2C_ADDR 0x29 ///< Default sensor I2C address

/**************************************************************************/
/*!
    @brief  Class that stores state and functions for interacting with VL53L1X
   time-of-flight sensor chips
*/
/**************************************************************************/
class Adafruit_VL53L1X : public VL53L1X {
public:
  Adafruit_VL53L1X(uint8_t shutdown_pin = -1, uint8_t irq_pin = -1);

  bool begin(uint8_t i2c_addr = VL53L1X_I2C_ADDR, TwoWire *theWire = &Wire,
             bool debug = false);
  uint16_t sensorID(void);

  bool startRanging(void);
  bool stopRanging(void);
  bool setTimingBudget(uint16_t ms);
  uint16_t getTimingBudget(void);

  bool setInterMeasurement(uint16_t ms);
  uint16_t getInterMeasurement(void);
  bool setDistanceMode(uint16_t mode);

  bool dataReady(void);
  int16_t distance(void);

  bool clearInterrupt(void);
  bool setIntPolarity(bool polarity);
  bool getIntPolarity(void);

  /*
  boolean SetDistanceMode(VL53L1_DistanceModes mode);
  boolean SetMeasurementTimingBudgetMicroSeconds(uint32_t budget);
  boolean SetInterMeasurementPeriodMilliSeconds(uint32_t period);
  boolean StartMeasurement(void);
  boolean WaitMeasurementDataReady(void);
  boolean GetRangingMeasurementData(VL53L1_RangingMeasurementData_t *ranging);
  */

  VL53L1X_ERROR vl_status; /**< VL53L1X API Error Status */

private:
  int8_t _irq_pin, _shutdown_pin;
  /*
  VL53L1_Dev_t               MyDevice;
  VL53L1_Dev_t               *pMyDevice  = &MyDevice;
  //VL53L1X_Version_t                   Version;
  //VL53L1X_Version_t                   *pVersion   = &Version;
  VL53L1_DeviceInfo_t        DeviceInfo;
  */
};

#endif
