#include "bme280.h"

int8_t main()
{
    int8_t status;
    
    bme280_config_t config;
    bme280_measure_date_t measure_data;

    config.dev_addr = 0x76;
    config.oversamp_rate_tem = BME280_OVERSAMP_RATE_X1;
    config.oversamp_rate_pre = BME280_OVERSAMP_RATE_X1;
    config.oversamp_rate_hum = BME280_OVERSAMP_RATE_X1;

    printf("Content-type:text/html\n\n");

    status = bme280_init(&config);

    if (status == BME280_ERROR) {
        printf("Initialization is failed.\n");
        return 0;
    }

    status = bme280_measure(&measure_data);
    if (status == BME280_ERROR) {
        printf("Measurement is failed.\n");
        return 0;
    }

    printf("tempreture is %f (degree)\n", measure_data.tempreture / 100.0);
    printf("pressure is %f (Pa)\n", measure_data.pressure / 256.0);
    printf("humidity is %f (%)\n", measure_data.humidity / 1024.0);

    return 0;
}
