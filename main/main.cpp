#include "led_driver.hpp"

extern "C" void app_main()
{
    LedDriver *led_driver = new LedDriver(LEDC_COOL, LEDC_WARM, LEDC_FREQUENCY, 100, 6500, true, (ledc_fade_mode_t)2000);
    led_driver->setIntensity(0);
    while (true)
    {
        ESP_LOGI("LED", "LED ON");
        led_driver->switchState(false);
        ESP_LOGI("LED", "setTemperature(2700)");
        led_driver->setTemperature(2700);
        vTaskDelay(5000 / portTICK_PERIOD_MS);
        ESP_LOGI("LED", "setTemperature(4600)");
        led_driver->setTemperature(4600);
        vTaskDelay(5000 / portTICK_PERIOD_MS);
        ESP_LOGI("LED", "setTemperature(6500)");
        led_driver->setTemperature(6500);
        vTaskDelay(5000 / portTICK_PERIOD_MS);
        
        // ESP_LOGI("LED", "setIntensity 10");
        // led_driver->setIntensity(90);
        // vTaskDelay(5000 / portTICK_PERIOD_MS);
        // ESP_LOGI("LED", "setIntensity 50");
        // led_driver->setIntensity(50);
        // vTaskDelay(5000 / portTICK_PERIOD_MS);
        // ESP_LOGI("LED", "setIntensity 100");
        // led_driver->setIntensity(0);
        // vTaskDelay(5000 / portTICK_PERIOD_MS);
        ESP_LOGI("LED", "LED OFF");
        led_driver->switchState(true);
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}
