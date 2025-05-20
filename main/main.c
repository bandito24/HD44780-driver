#include <stdio.h>

#include "HD44780.h"

void app_main(void) {
  i2c_init(16, 2);


  while (1) {
    test_write();
    vTaskDelay(pdMS_TO_TICKS(10));
  }
}
