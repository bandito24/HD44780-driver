# HD44780 I2C Driver – Minimal, Educational Implementation for ESP32

This project is a **bare-metal I2C implementation** of an HD44780-compatible LCD driver, designed specifically to help **computer science students and embedded learners** go deeper than high-level libraries typically allow.

> 🧠 This is **my own implementation** of an HD44780 LCD driver over I2C, with a focus on clarity, control, and educational value.

---

## 🎯 Motivation

Frameworks like Arduino’s `LiquidCrystal_I2C` are incredibly easy to use — but that convenience comes at the cost of **understanding what's really happening** under the hood. For learners trying to grasp embedded fundamentals like:
- How the HD44780 operates in 4-bit mode
- How I2C communication works on a byte level
- How display control and timing are manually orchestrated

…those libraries are **too high-level**.

This project strips it down to the essentials — no magic, no hidden abstractions.

---

## 🛠️ Core Functions

Only the minimum you need to communicate with the LCD:

```c
void lcd_init(uint8_t rows, uint8_t cols, uint8_t address, gpio_num_t sda_pin, gpio_num_t scl_pin);
void lcd_write_string(char* string);
void clear_display();
void set_cursor(uint8_t row, uint8_t col);

💡 How to Use
1. Initialize

lcd_init(2, 16, 0x27, GPIO_NUM_21, GPIO_NUM_22);

    2, 16: for a 2-row, 16-column display

    0x27: common I2C address for LCD backpacks

    GPIO_NUM_21, GPIO_NUM_22: your chosen SDA and SCL pins

2. Display Text

set_cursor(0, 0);
lcd_write_string("Hello, world!");

3. Clear Display

clear_display();


```c

📚 What You’ll Learn

    How to manually write to an HD44780 over I2C using 4-bit mode

    How to pulse the enable line and handle bit packing over I2C

    How to structure a display driver without relying on frameworks

    How to debug I2C and LCD hardware from a low-level perspective

📦 Requirements

    ESP32 with ESP-IDF (v5.0+ recommended)

    HD44780-compatible I2C LCD (16x2, 20x4, etc.)

    Basic familiarity with C and ESP32 GPIO/I2C APIs

🙋 About This Project

This is a personal implementation written from scratch to better understand how LCDs work at the protocol and signal level. It is intentionally minimal, clean, and meant for learning.


🙋‍♂️ Contributions

Feel free to open issues or submit pull requests — especially if you're adding:

    Shift/display animations

    Custom character generator support

    20x4 or multi-device bus compatibility


---

Let me know if you were referring to **HD7780** instead of HD44780 — if that’s actually a different chip, I’ll update the references accordingly.

