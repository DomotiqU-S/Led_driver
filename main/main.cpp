#include "led_driver.hpp"

extern "C" void app_main()
{
    LedDriver *led_driver = new LedDriver(LEDC_COOL, LEDC_WARM, LEDC_FREQUENCY, 100, 4600, true);
    //led_driver->setIntensity(100);
    while (true)
    {
        vTaskDelay(2500 / portTICK_PERIOD_MS);
        printf("Switching on\n");
        led_driver->switchState(true);
        vTaskDelay(5000 / portTICK_PERIOD_MS);

        led_driver->setTemperature(6000);
        vTaskDelay(5000 / portTICK_PERIOD_MS);

        led_driver->setIntensity(40);
        vTaskDelay(5000 / portTICK_PERIOD_MS);

        printf("Switching off\n");
        led_driver->switchState(false);
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}
