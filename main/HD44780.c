#include "HD44780.h"

#include <stdint.h>
// #define SDA_GPIO GPIO_NUM_14
// #define SCL_GPIO GPIO_NUM_13
// #define LCD_ADDR 0x27

#define LCD_WRITE 0x01
#define LCD_COMMAND 0x00

#define LCD_DISPLAY_OFF 0x08
#define LCD_DISPLAY_ON 0x0C
#define LCD_FUNCTION_RESET 0x30
#define LCD_FUNCTION_SET_4BIT 0x28
#define LCD_CHAR 0x01
#define LCD_BACKLIGHT 0x08
#define LCD_ENABLE 0x04
#define LCD_CLEAR_DISPLAY 0x01
#define LCD_ENTRY_MODE_INCREMENT 0x06
#define LCD_SET_CURSOR 0x80
#define LCD_SET_DDRAM_ADDR 0x80

#define LCD_FIRST_ROW 0x00
#define LCD_SECOND_ROW 0x40
#define LCD_THIRD_ROW 0x14
#define LCD_FOURTH_ROW 0x54

static uint8_t LCD_ROWS;
static uint8_t LCD_COLS;
static uint8_t SDA_GPIO;
static uint8_t SCL_GPIO;
static uint8_t LCD_ADDR;

static const uint8_t lcd_row_offsets[] = {LCD_FIRST_ROW, LCD_SECOND_ROW,
                                          LCD_THIRD_ROW, LCD_FOURTH_ROW};

i2c_master_bus_handle_t bus_handle;
i2c_master_dev_handle_t dev_handle;

static void lcd_pulse_enable(uint8_t byte);
static void lcd_write_nibble(uint8_t byte, uint8_t mode);
static void lcd_write_word(uint8_t byte, uint8_t mode);
static void lcd_write_char(uint8_t c);

void i2c_init() {
  i2c_master_bus_config_t i2c_bus_conf = {.i2c_port = -1,
                                          .sda_io_num = SDA_GPIO,
                                          .scl_io_num = SCL_GPIO,
                                          .clk_source = I2C_CLK_SRC_DEFAULT,
                                          .flags.enable_internal_pullup = true};
  i2c_device_config_t dev_conf = {.dev_addr_length = I2C_ADDR_BIT_7,
                                  .scl_speed_hz = 5000,
                                  .device_address = LCD_ADDR};
  ESP_ERROR_CHECK(i2c_new_master_bus(&i2c_bus_conf, &bus_handle));
  ESP_ERROR_CHECK(
      i2c_master_bus_add_device(bus_handle, &dev_conf, &dev_handle));
}

void lcd_init(uint8_t rows, uint8_t cols, uint8_t address, gpio_num_t sda_pin,
              gpio_num_t scl_pin) {
  LCD_ROWS = rows;
  LCD_COLS = cols;
  LCD_ADDR = address;
  SDA_GPIO = sda_pin;
  SCL_GPIO = scl_pin;
  i2c_init();

  lcd_write_nibble(LCD_FUNCTION_RESET, LCD_COMMAND);
  vTaskDelay(pdMS_TO_TICKS(10));
  lcd_write_nibble(LCD_FUNCTION_RESET, LCD_COMMAND);
  ets_delay_us(200);
  lcd_write_nibble(LCD_FUNCTION_RESET, LCD_COMMAND);
  lcd_write_nibble(LCD_FUNCTION_SET_4BIT, LCD_COMMAND);
  ets_delay_us(80);

  lcd_write_word(LCD_FUNCTION_SET_4BIT, LCD_COMMAND);
  ets_delay_us(80);

  lcd_write_word(LCD_CLEAR_DISPLAY, LCD_COMMAND);
  vTaskDelay(pdMS_TO_TICKS(2));

  lcd_write_word(LCD_ENTRY_MODE_INCREMENT, LCD_COMMAND);
  ets_delay_us(80);

  lcd_write_word(LCD_DISPLAY_ON, LCD_COMMAND);
}

void clear_display() {
  lcd_write_word(LCD_CLEAR_DISPLAY, LCD_COMMAND);
  vTaskDelay(pdMS_TO_TICKS(pdMS_TO_TICKS(2)));
}

void set_cursor(uint8_t row, uint8_t col) {
  while (row >= LCD_ROWS || col >= LCD_COLS) {
    if (row >= LCD_ROWS) {
      ESP_LOGI("Out of bounds",
               "Row %d is beyond the out of range of provided %d rows", row,
               LCD_ROWS);
      row = LCD_ROWS - 1;
    }
    if (col >= LCD_COLS) {
      ESP_LOGI("Out of bounds",
               "Column %d is beyond the out of range of provided %d columns",
               col, LCD_COLS);
      col = LCD_COLS - 1;
    }
  }
  uint8_t addr = lcd_row_offsets[row] + col;
  lcd_write_word(LCD_SET_DDRAM_ADDR | addr, LCD_COMMAND);
}

static void lcd_pulse_enable(uint8_t byte) {
  uint8_t buf = byte | LCD_ENABLE;
  ESP_ERROR_CHECK(
      i2c_master_transmit(dev_handle, &buf, 1, pdMS_TO_TICKS(2000)));
  buf = byte & ~LCD_ENABLE;
  ESP_ERROR_CHECK(
      i2c_master_transmit(dev_handle, &buf, 1, pdMS_TO_TICKS(2000)));
}
void lcd_write_string(char* string) {
  for (int i = 0; string[i] != '\0'; i++) {
    lcd_write_char(string[i]);
  }
}

static void lcd_write_nibble(uint8_t byte, uint8_t mode) {
  uint8_t buf = (byte & 0xF0) | mode | LCD_BACKLIGHT;
  lcd_pulse_enable(buf);
}
static void lcd_write_word(uint8_t byte, uint8_t mode) {
  lcd_write_nibble(byte & 0xF0, mode);
  lcd_write_nibble((byte << 4) & 0xF0, mode);
}
static void lcd_write_char(uint8_t c) { lcd_write_word(c, LCD_WRITE); }
