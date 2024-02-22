#include "led_driver.hpp"

extern "C" void app_main()
{
    LedDriver *led_driver = new LedDriver();
    while (true)
    {
        ESP_LOGI("LED", "LED ON");
        led_driver->switchState(true);
        led_driver->setIntensity(100);
        ESP_LOGI("LED","setTemperature(2700)");
        led_driver->setTemperature(2700);
        vTaskDelay(5000 / portTICK_PERIOD_MS);
        ESP_LOGI("LED","setTemperature(6500)");
        led_driver->setTemperature(6500);
        vTaskDelay(5000 / portTICK_PERIOD_MS);
        ESP_LOGI("LED","setIntensity(10)");
        led_driver->setIntensity(10);
        vTaskDelay(5000 / portTICK_PERIOD_MS);
        ESP_LOGI("LED","setIntensity(50)");
        led_driver->setIntensity(50);
        vTaskDelay(5000 / portTICK_PERIOD_MS);
        ESP_LOGI("LED","setIntensity(100)");
        led_driver->setIntensity(100);
        vTaskDelay(5000 / portTICK_PERIOD_MS);
        ESP_LOGI("LED", "LED OFF");
        led_driver->switchState(false);
        vTaskDelay(5000 / portTICK_PERIOD_MS);
        
    }
}
