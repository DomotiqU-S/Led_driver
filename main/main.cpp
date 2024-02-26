#include "led_driver.hpp"

extern "C" void app_main()
{
    LedDriver *led_driver = new LedDriver(LEDC_COOL, LEDC_WARM, LEDC_FREQUENCY, 100, 6500, true, (ledc_fade_mode_t)2000);
    led_driver->setIntensity(100);
    while (true)
    {
        led_driver->switchState(true);
        led_driver->setTemperature(2700);
        vTaskDelay(5000 / portTICK_PERIOD_MS);
        led_driver->setTemperature(4600);
        vTaskDelay(5000 / portTICK_PERIOD_MS);
        led_driver->setIntensity(75);
        vTaskDelay(5000 / portTICK_PERIOD_MS);
        led_driver->setIntensity(50);
        vTaskDelay(5000 / portTICK_PERIOD_MS);
        led_driver->setIntensity(25);
        vTaskDelay(5000 / portTICK_PERIOD_MS);
        led_driver->setIntensity(0);
        vTaskDelay(5000 / portTICK_PERIOD_MS);
        led_driver->switchState(false);
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}
