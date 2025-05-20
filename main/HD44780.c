#include "HD44780.h"



#define SDA_GPIO GPIO_NUM_14
#define SCL_GPIO GPIO_NUM_13
#define LCD_ADDR 0x27


#define LCD_COMMAND = 0x00
#define LCD_WRITE 0x01

//Instructions
#define LCD_DISPLAY_OFF 0x08
#define LCD_DISPLAY_ON 0x0C
#define LCD_FUNCTION_RESET 0x30  
#define LCD_FUNCTION_SET_4BIT 0x28
#define LCD_COMMAND 0x00
#define LCD_CHAR 0x01
#define LCD_BACKLIGHT 0x08

// Pin mappings
// P0 -> RS
// P1 -> RW
// P2 -> E
// P3 -> Backlight
// P4 -> D4
// P5 -> D5
// P6 -> D6
// P7 -> D7


i2c_master_bus_handle_t bus_handle;
i2c_master_dev_handle_t dev_handle;

void i2c_init(){
    i2c_master_bus_config_t i2c_bus_conf = {
        .i2c_port = -1,
        .sda_io_num = SDA_GPIO,
        .scl_io_num = SCL_GPIO,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .flags.enable_internal_pullup = true
    };
    i2c_device_config_t dev_conf = {
        .dev_addr_length = I2C_ADDR_BIT_7,
        .scl_speed_hz = 5000,
        .device_address = LCD_ADDR
    };
    ESP_ERROR_CHECK(i2c_new_master_bus(&i2c_bus_conf, &bus_handle));
    ESP_ERROR_CHECK(i2c_master_bus_add_device(bus_handle, &dev_conf, &dev_handle));

}

void lcd_init(){
     


}

void lcd_write_nibble(uint8_t byte, uint8_t mode){
    uint8_t buffer = (byte & 0x0F) | mode;
    ESP_ERROR_CHECK(i2c_master_transmit(dev_handle, buffer, 1,  pdMS_TO_TICKS(2000)));
}



