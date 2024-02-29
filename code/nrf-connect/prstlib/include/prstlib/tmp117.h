#ifndef _PRST_TMP117_H_
#define _PRST_TMP117_H_

#define PRST_TMP117_ADDR 0x49
#define PRST_TMP117_TEMP_RESULT 0X00
#define PRST_TMP117_CONFIGURATION 0x01
#define PRST_TMP117_T_HIGH_LIMIT 0X02
#define PRST_TMP117_T_LOW_LIMIT 0X03
#define PRST_TMP117_EEPROM_UL 0X04
#define PRST_TMP117_EEPROM1 0X05
#define PRST_TMP117_EEPROM2 0X06
#define PRST_TMP117_TEMP_OFFSET 0X07
#define PRST_TMP117_EEPROM3 0X08
#define PRST_TMP117_DEVICE_ID 0X0F

#define PRST_TMP117_RESOLUTION 0.0078125f

// Thank you https://github.com/sparkfunX/Qwiic_TMP117

typedef struct {
  // Temperature in Celcius.
  float temp_c;
} prst_tmp117_read_t;

int prst_tmp117_read(prst_tmp117_read_t *out);



#endif  // _PRST_TMP117_H_