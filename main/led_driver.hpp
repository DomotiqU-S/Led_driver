#ifndef LED_SENSOR_HPP
#define LED_SENSOR_HPP

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "driver/ledc.h"
#include "esp_err.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define LEDC_TIMER      LEDC_TIMER_0         // LEDC timer
#define LEDC_MODE       LEDC_LOW_SPEED_MODE   // LEDC speed mode
#define LEDC_WARM       5                     // Define the output GPIO
#define LEDC_COOL       6                     // Define the output GPIO
#define LEDC_DUTY_RES   LEDC_TIMER_10_BIT // Set duty resolution to 13 bits
#define MAX_DUTY        (uint32_t)1024         // Maximum duty for 13 bits
#define LEDC_FREQUENCY  (uint32_t)25000  // Frequency in Hertz. Set frequency at 50 kHz for hearing protection
// #define DEBUG_SENSOR    0                   // Enable debug logs for the temperature sensor

class LedDriver
{
private:
    esp_err_t ret;
    uint32_t dutyWarm = 0;
    uint32_t dutyCool = 0;
    uint16_t temperature = 4600;
    uint16_t intensity = 0;

public:
    /**
     * @brief Construct a new Led Driver object
     *
     * @param cool_pin The GPIO pin for the cool LED
     * @param warm_pin The GPIO pin for the warm LED
     * @param frequency The frequency of the PWM signal
     * @param intensity The intensity of the LED in percentage
     * @param temperature The temperature of the LED in degrees kelvin
     */
    LedDriver(int cool_pin = LEDC_COOL, int warm_pin = LEDC_WARM, uint32_t frequency = LEDC_FREQUENCY, uint16_t intensity = 50, uint16_t temperature = 4600)
    {
        this->intensity = intensity;
        this->temperature = temperature;
        ledc_timer_config_t ledc_timer = {
            .speed_mode = LEDC_MODE,
            .duty_resolution = LEDC_DUTY_RES,
            .timer_num = LEDC_TIMER,
            .freq_hz = frequency, // Set output frequency
            .clk_cfg = LEDC_AUTO_CLK};
        ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));
        // Prepare and then apply the LEDC PWM channel configuration
        ledc_channel_config_t cool_channel;
        cool_channel.speed_mode = LEDC_MODE;
        cool_channel.channel = LEDC_CHANNEL_0;
        cool_channel.timer_sel = LEDC_TIMER;
        cool_channel.intr_type = LEDC_INTR_DISABLE;
        cool_channel.gpio_num = cool_pin;
        cool_channel.duty = (uint32_t)256; // Set duty to 25%
        cool_channel.hpoint = 0;
        ledc_channel_config_t warm_channel;
        warm_channel.speed_mode = LEDC_MODE;
        warm_channel.channel = LEDC_CHANNEL_1;
        warm_channel.timer_sel = LEDC_TIMER;
        warm_channel.intr_type = LEDC_INTR_DISABLE;
        warm_channel.gpio_num = warm_pin;
        warm_channel.duty = (uint32_t)256; // Set duty to 25%
        warm_channel.hpoint = 0;
        ESP_ERROR_CHECK(ledc_channel_config(&cool_channel));
        ESP_ERROR_CHECK(ledc_channel_config(&warm_channel));
    }
    ~LedDriver();
    /**
     * @brief Switch the state of the LED
     * The state of the LED
     * @param state The state of the LED
     * @return esp_err_t the error code
     */
    esp_err_t switchState(bool state);
    /**
     * @brief Set the intensity of the LED
     * The intensity of the LED in percentage
     * @param intensity The intensity of the LED in percentage
     * @return esp_err_t the error code
     */
    esp_err_t setIntensity(int intensity);
    /**
     * @brief Set the temperature of the LED in degrees kelvin
     * The temperature color of the light bulb.
     * MAX 6500K
     * MIN 2700K
     * @param temperature The temperature of the LED in degrees kelvin
     * @return esp_err_t the error code
     */
    esp_err_t setTemperature(int temperature);
    /**
     * @brief Get the temperature of the LED
     * The temperature color of the light bulb.
     * @return uint16_t The temperature of the LED in degrees kelvin
     */
    uint16_t getTemperature();
    /**
     * @brief Get the intensity of the LED
     * The intensity of the LED in percentage
     * @return uint16_t The intensity of the LED in percentage
     */
    uint16_t getIntensity();
    /**
     * @brief Get the duty of the LED
     * The duty of the LED in percentage
     * @return uint16_t The duty of the LED in percentage
     */
    uint32_t getDuty(int channel);
};

#endif // LED_SENSOR_HPP