#ifndef _PRST_DATA_H_
#define _PRST_DATA_H_

#include "prstlib/adc.h"
#include "prstlib/shtc3.h"

typedef struct {
  
  #ifdef CONFIG_BOARD_BPARASITE_LONG_NRF52840
  prst_adc_soil_moisture_t soil1;
  prst_adc_soil_moisture_t soil2;
  prst_adc_soil_moisture_t soil3;
  #else
  prst_adc_soil_moisture_t soil;
  #endif
  prst_adc_photo_sensor_t photo;
  prst_batt_t batt;
  prst_shtc3_read_t shtc3;
} prst_sensors_t;

int prst_sensors_read_all(prst_sensors_t *out);

#endif  // _PRST_DATA_H_
