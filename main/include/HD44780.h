#pragma once
#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "rom/ets_sys.h"
#include <esp_log.h>
#include "driver/i2c_master.h"
#include <driver/i2c.h>
#include "esp_err.h"

void i2c_init();
void test_write();