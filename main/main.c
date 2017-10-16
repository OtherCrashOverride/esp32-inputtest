#include "freertos/FreeRTOS.h"
#include "esp_wifi.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_event_loop.h"
#include "nvs_flash.h"
#include "driver/gpio.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"


uint8_t ADC(float v)
{
  uint8_t result;

  if (v < (1.03 / 2.0))
    result = 0;
  else if (v < (1.65 - (1.65 - 1.03) / 2))
    result = 1;
  else if (v < (1.96 - (1.96 - 1.65) / 2))
    result = 2;
  else if (v < (2.24 - (2.24 - 1.96) / 2))
    result = 3;
  else if (v < (2.38 - (2.38 - 2.24) / 2))
    result = 4;
  else if (v < (2.50 - (2.50 - 2.38) / 2))
    result = 5;
  else if (v < (2.58 - (2.58 - 2.50) / 2))
    result = 6;
  else if (v < (2.70 - (2.70 - 2.58) / 2))
    result = 7;
  else if (v < (2.75 - (2.75 - 2.70) / 2))
    result = 8;
  else if (v < (2.80 - (2.80 - 2.75) / 2))
    result = 9;
  else if (v < (2.83 - (2.83 - 2.80) / 2))
    result = 10;
  else if (v < (2.87 - (2.87 - 2.83) / 2))
    result = 11;
  else if (v < (2.89 - (2.89 - 2.87) / 2))
    result = 12;
  else if (v < (2.92 - (2.92 - 2.89) / 2))
    result = 13;
  else if (v < (2.94 - (2.94 - 2.92) / 2))
    result = 14;
  else
    result = 15;

  return result;
}

void app_main(void)
{
    nvs_flash_init();


    //  IO33 = ADC1_CHANNEL_5
    const adc_atten_t attenuation = ADC_ATTEN_11db;

    adc1_config_width(ADC_WIDTH_12Bit);
    adc1_config_channel_atten(ADC1_CHANNEL_5, attenuation);

    // Calculate ADC characteristics i.e. gain and offset factors
    const int V_REF = 1100;  // ADC reference voltage
    esp_adc_cal_characteristics_t characteristics;
    esp_adc_cal_get_characteristics(V_REF, attenuation, ADC_WIDTH_12Bit, &characteristics);


    while (true)
    {
        float v = adc1_to_voltage(ADC1_CHANNEL_5, &characteristics) * 0.001;
        uint8_t adc = ADC(v);

        printf("adc=%.2d, v=%f\n", adc, v);

        vTaskDelay(300 / portTICK_PERIOD_MS);
    }
}
