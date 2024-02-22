#include "led_driver.hpp"

LedDriver::~LedDriver()
{
    ledc_stop(LEDC_MODE, LEDC_CHANNEL_0, 0);
    ledc_stop(LEDC_MODE, LEDC_CHANNEL_1, 0);
}

esp_err_t LedDriver::switchState(bool state)
{
    esp_err_t ret = ledc_set_duty(LEDC_MODE, LEDC_CHANNEL_0, state ? 0 : this->dutyCool);
    if (ret != ESP_OK)
    {
#ifdef DEBUG_SENSOR
        ESP_LOGE(TAG_SENSOR, "failed to set duty for LEDC channel 0");
#endif
        return ret;
    }
    ret = ledc_update_duty(LEDC_MODE, LEDC_CHANNEL_0);
    if (ret != ESP_OK)
    {
#ifdef DEBUG_SENSOR
        ESP_LOGE(TAG_SENSOR, "failed to update duty for LEDC channel 0");
#endif
        return ret;
    }
    ret = ledc_set_duty(LEDC_MODE, LEDC_CHANNEL_1, state ? 0 : this->dutyWarm);
    if (ret != ESP_OK)
    {
#ifdef DEBUG_SENSOR
        ESP_LOGE(TAG_SENSOR, "failed to set duty for LEDC channel 1");
#endif
        return ret;
    }
    ret = ledc_update_duty(LEDC_MODE, LEDC_CHANNEL_1);
    if (ret != ESP_OK)
    {
#ifdef DEBUG_SENSOR
        ESP_LOGE(TAG_SENSOR, "failed to update duty for LEDC channel 1");
#endif
        return ret;
    }
    return ret;
}

esp_err_t LedDriver::setIntensity(int intensity)
{
    this->intensity = intensity;
    return this->setTemperature(this->temperature);
}

esp_err_t LedDriver::setTemperature(int temperature)
{
    esp_err_t ret;
    this->temperature = temperature;
    if (temperature == 2700)
    {
        this->dutyWarm = 0;
        this->dutyCool = (uint32_t)MAX_DUTY * ((100.0 - this->intensity) / 100.0);
    }
    else if (temperature == 6500)
    {
        this->dutyWarm = (uint32_t)MAX_DUTY * ((100.0 - this->intensity) / 100.0);
        this->dutyCool = 0;
    }
    else
    {
        this->dutyWarm = (uint32_t)MAX_DUTY * ((100.0 - this->intensity) / 100.0) * (6500.0 - temperature) / 3800.0;
        this->dutyCool = (uint32_t)MAX_DUTY * ((100.0 - this->intensity) / 100.0) * (temperature - 2700.0) / 3800.0;
    }
    ret = ledc_set_duty(LEDC_MODE, LEDC_CHANNEL_0, this->dutyCool);
    if (ret != ESP_OK)
    {
#ifdef DEBUG_SENSOR
        ESP_LOGE(TAG_SENSOR, "failed to set duty for LEDC channel 0");
#endif
        return ret;
    }
    ret = ledc_update_duty(LEDC_MODE, LEDC_CHANNEL_0);
    if (ret != ESP_OK)
    {
#ifdef DEBUG_SENSOR
        ESP_LOGE(TAG_SENSOR, "failed to update duty for LEDC channel 0");
#endif
        return ret;
    }
    ledc_set_duty(LEDC_MODE, LEDC_CHANNEL_1, this->dutyWarm);
    if (ret != ESP_OK)
    {
#ifdef DEBUG_SENSOR
        ESP_LOGE(TAG_SENSOR, "failed to set duty for LEDC channel 1");
#endif
        return ret;
    }
    ret = ledc_update_duty(LEDC_MODE, LEDC_CHANNEL_1);
    if (ret != ESP_OK)
    {
#ifdef DEBUG_SENSOR
        ESP_LOGE(TAG_SENSOR, "failed to update duty for LEDC channel 1");
#endif
        return ret;
    }
    return ret;
}

uint16_t LedDriver::getTemperature()
{
    return this->temperature;
}

uint16_t LedDriver::getIntensity()
{
    return this->intensity;
}

uint32_t LedDriver::getDuty(int channel)
{
    if (channel == 0)
    {
        return this->dutyCool;
    }
    else
    {
        return this->dutyWarm;
    }
}