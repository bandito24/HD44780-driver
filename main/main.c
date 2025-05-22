#include <stdio.h>
#include <string.h>

#include "HD44780.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define SDA_PIN GPIO_NUM_14
#define SCL_PIN GPIO_NUM_13
#define LCD_ADDR 0x27
#define row_count 2
#define col_count 16

void app_main(void) {
  lcd_init(row_count, col_count, LCD_ADDR, SDA_PIN, SCL_PIN);
  vTaskDelay(pdMS_TO_TICKS(500));

  // clear_display();

  // Print a static message on row 1
  set_cursor(0, 0);
  lcd_write_string("HD7780 Ready");

  // Scroll a message on row 0
  const char* message = "  Let's Party!  ";
  int len = strlen(message);
  char buffer[17] = {0};  // 16 chars + null terminator

  while (1) {
    for (int offset = 0; offset <= len - 16; offset++) {
      strncpy(buffer, message + offset, 16);
      buffer[16] = '\0';

      set_cursor(1, 0);
      lcd_write_string(buffer);

      vTaskDelay(pdMS_TO_TICKS(300));
    }
  }
}
