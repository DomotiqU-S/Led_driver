#include "led_driver.hpp"

extern "C" void app_main()
{
    LedDriver *led_driver = new LedDriver();
    led_driver->switchState(true);
    vTaskDelay(5000);
    led_driver->setTemperature(2700);
    vTaskDelay(5000);
    led_driver->setTemperature(6500);
    vTaskDelay(5000);
    led_driver->setIntensity(10);
    vTaskDelay(5000);
    led_driver->setIntensity(100);
    
}
