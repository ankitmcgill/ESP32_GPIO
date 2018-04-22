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

#include "ESP32_GPIO.h"

esp_err_t ESP32_GPIO_SetDirection(uint8_t gpio_num, esp32_gpio_pin_direction_t direction)
{
	//SET GPIO PIN DIRECTION

	//CHECK IF VALID GPIO
	if(!GPIO_IS_VALID_GPIO(gpio_num))
	{
		return ESP_FAIL;
	}

	//IF DIRECTION = OUTPUT, ENSURE THE SPECIFIED PIN CAN
	//ACT AS AN OUTPUT
	if(direction == GPIO_DIRECTION_OUTPUT && !GPIO_IS_VALID_OUTPUT_GPIO(gpio_num))
	{
		return ESP_FAIL;
	}

	//SET GPIO DIRECTION
	if(gpio_set_direction(gpio_num, direction) != ESP_OK)
	{
		return ESP_FAIL;
	}

	ESP_LOGI(ESP32_GPIO_TAG, "GPIO = %u Direction = %u", gpio_num, direction);
	return ESP_OK;
}

esp_err_t ESP32_GPIO_SetValue(uint8_t gpio_num, uint8_t val)
{
	//SET GPIO VALUE
	//FOR OUTPUT GPIO ONLY

	//CHECK IF VALID GPIO
	if(!GPIO_IS_VALID_GPIO(gpio_num))
	{
		return ESP_FAIL;
	}

	//ENSURE SETTING VALUE OF OUTPUT PIN ONLY
	if(!GPIO_IS_VALID_OUTPUT_GPIO(gpio_num))
	{
		return ESP_FAIL;
	}

	//SET PIN VALUE
	if(gpio_set_level(gpio_num, val) != ESP_OK)
	{
		return ESP_FAIL;
	}
	
	ESP_LOGI(ESP32_GPIO_TAG, "GPIO = %u Value Set = %u", gpio_num, val);
	return ESP_OK;
}

esp_err_t ESP32_GPIO_GetValue(uint8_t gpio_num, uint8_t* retval)
{
	//GET GPIO VALUE
	//FOR BOTH OUTPUT AND INPUT GPIO

	//CHECK IF VALID GPIO
	if(!GPIO_IS_VALID_GPIO(gpio_num))
	{
		return ESP_FAIL;
	}

	//GET PIN LEVEL VALUE
	*retval = gpio_get_level(gpio_num);
	
	ESP_LOGI(ESP32_GPIO_TAG, "GPIO = %u Value Get = %u", gpio_num, *retval);
	return ESP_OK;
}

esp_err_t ESP32_GPIO_SetPullUpDown(uint8_t gpio_num, esp32_gpio_pull_updown_type_t type)
{
	//SET PULLUP / PULLDOWN ON SPECIFIED GPIO
	//CAN ONLY BE DONE FOR GPIO IN INPUT MODE
	//GPIO 34 - 49 ARE INPUT ONLY AND DONT SUPPORT PULLUP / PULLDOWN

	//CHECK IF VALID GPIO
	if(!GPIO_IS_VALID_GPIO(gpio_num))
	{
		return ESP_FAIL;
	}

	//ENSURE PIN NOT 34 - 39
	if(gpio_num >= 34 && gpio_num <=39)
	{
		return ESP_FAIL;
	}

	//SET PULLUP/PULLDOWN
	if(gpio_set_pull_mode(gpio_num, type) != ESP_OK)
	{
		return ESP_FAIL;
	}

	ESP_LOGI(ESP32_GPIO_TAG, "GPIO = %u Pullup / pulldown set (%u)", gpio_num, type);
	return ESP_OK;
}

esp_err_t ESP32_GPIO_RemovePullUpDown(uint8_t gpio_num)
{
	//REMOVE PULLUP / PULLDOWN ON SPECIFIED GPIO
	//CAN ONLY BE DONE FOR GPIO IN INPUT MODE
	//GPIO 34 - 49 ARE INPUT ONLY AND DONT SUPPORT PULLUP / PULLDOWN

	//CHECK IF VALID GPIO
	if(!GPIO_IS_VALID_GPIO(gpio_num))
	{
		return ESP_FAIL;
	}

	//ENSURE PIN NOT 34 - 39
	if(gpio_num >= 34 && gpio_num <=39)
	{
		return ESP_FAIL;
	}

	//REMOVE PULLUP/PULLDOWN
	if(gpio_set_pull_mode(gpio_num, GPIO_FLOATING) != ESP_OK)
	{
		return ESP_FAIL;
	}

	ESP_LOGI(ESP32_GPIO_TAG, "GPIO = %u Removed pullup / pulldown", gpio_num);
	return ESP_OK;
}