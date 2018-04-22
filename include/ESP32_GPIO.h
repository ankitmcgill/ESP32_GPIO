//////////////////////////////////////////////////////////////////
// GPIO DRIVER - ESP32
//
// LIBRARY FOR GPIO OPERATIONS ON ESP32
//
// NOTE : FROM ESP-IDF MANUAL
//        http://esp-idf.readthedocs.io/en/latest/api-reference/peripherals/gpio.html
//
//        GPIO 6-11 ARE USUALLY USED FOR SPI FLASH
//        GPIO 34-39 CAN ONLY BE SET IN INPUT MODE AND DO NOT
//        PROVIDE SOFTWARE PULLUP / PULLDOWN  
//
//        THIS LIBRARY DOES NOT SUPPORT RTC GPIO
//
// APRIL 19, 2018
//
// ANKIT BHATNAGAR
// ANKIT.BHATNAGARINDIA@GMAIL.COM
//////////////////////////////////////////////////////////////////

#ifndef _ESP32_GPIO_
#define _ESP32_GPIO_

#include "esp_system.h"
#include "esp_err.h"
#include "esp_log.h"
#include "driver/gpio.h"

#define ESP32_GPIO_TAG       "ESP32:GPIO"

typedef enum
{
    GPIO_DIRECTION_DISABLE = 0,
    GPIO_DIRECTION_INPUT,
    GPIO_DIRECTION_OUTPUT
}esp32_gpio_pin_direction_t;

typedef enum
{
    GPIO_PULLUP= 0,
    GPIO_PULLDOWN
}esp32_gpio_pull_updown_type_t;

esp_err_t ESP32_GPIO_SetDirection(uint8_t gpio_num, esp32_gpio_pin_direction_t direction);
esp_err_t ESP32_GPIO_SetValue(uint8_t gpio_num, uint8_t val);
esp_err_t ESP32_GPIO_GetValue(uint8_t gpio_num, uint8_t* retval);

esp_err_t ESP32_GPIO_SetPullUpDown(uint8_t gpio_num, esp32_gpio_pull_updown_type_t type);
esp_err_t ESP32_GPIO_RemovePullUpDown(uint8_t gpio_num);

#endif