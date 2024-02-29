#include "prstlib/tmp117.h"

#include <zephyr/drivers/i2c.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include "prstlib/macros.h"

LOG_MODULE_REGISTER(tmp117, CONFIG_PRSTLIB_LOG_LEVEL);
static const struct i2c_dt_spec tmp117 = I2C_DT_SPEC_GET(DT_NODELABEL(tmp117));

static int write_cmd(uint8_t command) {
  static uint8_t cmd[1];
  cmd[0] = command;
  RET_IF_ERR(i2c_write_dt(&tmp117, cmd, sizeof(cmd)));
  return 0;
}

static uint8_t buff[6];

int prst_tmp117_read(prst_tmp117_read_t *out){
    RET_IF_ERR_MSG(!device_is_ready(tmp117.bus), "TMP117 is not ready");

    RET_IF_ERR(write_cmd(PRST_TMP117_TEMP_RESULT));
    k_msleep(1);

    RET_IF_ERR(i2c_read_dt(&tmp117, buff, 2));

    out->temp_c = ((float)((buff[0] << 8) | buff[1])) * PRST_TMP117_RESOLUTION;


}