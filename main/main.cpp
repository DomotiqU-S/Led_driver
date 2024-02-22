#include "led_driver.hpp"

extern "C" void app_main()
{
    LedDriver *led_driver = new LedDriver();
    while (true)
    {
        ESP_LOGI("LED", "LED ON");
        led_driver->switchState(false);
        led_driver->setIntensity(100);
        ESP_LOGI("LED", "setTemperature(6500)");
        led_driver->setTemperature(6500);
        ESP_LOGI("LED", "setIntensity 10");
        led_driver->setIntensity(90);
        vTaskDelay(5000 / portTICK_PERIOD_MS);
        ESP_LOGI("LED", "setIntensity 50");
        led_driver->setIntensity(50);
        vTaskDelay(5000 / portTICK_PERIOD_MS);
        ESP_LOGI("LED", "setIntensity 100");
        led_driver->setIntensity(0);
        vTaskDelay(5000 / portTICK_PERIOD_MS);
        ESP_LOGI("LED", "LED OFF");
        led_driver->switchState(true);
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}
