#pragma once
#include <driver/i2c.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdint.h>
#include <stdio.h>

#include "driver/i2c_master.h"
#include "esp_err.h"
#include "rom/ets_sys.h"

void lcd_init(uint8_t rows, uint8_t cols, uint8_t address, gpio_num_t sda_pin, gpio_num_t scl_pin);
void lcd_write_string(char* string);
void clear_display();
void set_cursor(uint8_t row, uint8_t col);