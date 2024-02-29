#include "prstlib/sensors.h"

#include <zephyr/logging/log.h>

#include "prstlib/adc.h"
#include "prstlib/led.h"
#include "prstlib/macros.h"

LOG_MODULE_REGISTER(sensors, CONFIG_PRSTLIB_LOG_LEVEL);

int prst_sensors_read_all(prst_sensors_t *sensors) {
  RET_IF_ERR(prst_adc_batt_read(&sensors->batt));
  #ifdef CONFIG_BOARD_BPARASITE_LONG_NRF52840
  RET_IF_ERR(prst_adc_soil_read(sensors->batt.adc_read.voltage, &sensors->soil1,&sensors->soil2,&sensors->soil3));
  #else
  RET_IF_ERR(prst_adc_soil_read(sensors->batt.adc_read.voltage, &sensors->soil));
  #endif
  
  RET_IF_ERR(prst_adc_photo_read(sensors->batt.adc_read.voltage, &sensors->photo));
  RET_IF_ERR(prst_shtc3_read(&sensors->shtc3))
  RET_IF_ERR(prst_tmp117_read(&sensors->tmp117))

  LOG_DBG("Batt: %d mV (%.2f%%)", sensors->batt.adc_read.millivolts,
          100 * sensors->batt.percentage);
#ifdef CONFIG_BOARD_BPARASITE_LONG_NRF52840
  LOG_DBG("Soil 1: %.0f %% (%d mV)", 100 * sensors->soil1.percentage,
          sensors->soil1.adc_read.millivolts);
  LOG_DBG("Soil 2: %.0f %% (%d mV)", 100 * sensors->soil2.percentage,
          sensors->soil2.adc_read.millivolts);
  LOG_DBG("Soil 3: %.0f %% (%d mV)", 100 * sensors->soil3.percentage,
          sensors->soil3.adc_read.millivolts);
          
  LOG_DBG("Photo: %u lx (%d mV, %d mV, %d mV)", sensors->photo.brightness,
          sensors->soil1.adc_read.millivolts,sensors->soil2.adc_read.millivolts,sensors->soil3.adc_read.millivolts);
#else
  LOG_DBG("Soil: %.0f %% (%d mV)", 100 * sensors->soil.percentage,
          sensors->soil.adc_read.millivolts);
  LOG_DBG("Photo: %u lx (%d mV)", sensors->photo.brightness,
          sensors->soil.adc_read.millivolts);
#endif


  LOG_DBG("Temp: %f oC", sensors->shtc3.temp_c);
  LOG_DBG("Soil: %f oC", sensors->tmp117.temp_c);
  LOG_DBG("Humi: %.0f %%", 100 * sensors->shtc3.rel_humi);
  LOG_DBG("--------------------------------------------------");

  return 0;
}