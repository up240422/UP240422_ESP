#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"

// Definición de los pines para el LED y el botón
#define LED    GPIO_NUM_26
#define BUTTON GPIO_NUM_27

void punto(){
    gpio_set_level(LED, 1); // Encendemos el LED
    vTaskDelay(pdMS_TO_TICKS(200)); // Esperamos 1 segundo
    gpio_set_level(LED, 0); // Apagamos el LED
    vTaskDelay(pdMS_TO_TICKS(200)); // Esperamos 1 segundo
}

void raya(){
    gpio_set_level(LED, 1); // Encendemos el LED
    vTaskDelay(pdMS_TO_TICKS(500)); // Esperamos 1 segundo
    gpio_set_level(LED, 0); // Apagamos el LED
    vTaskDelay(pdMS_TO_TICKS(500)); // Esperamos 1 segundo
}

void sos(){
    for(int i =0; i < 3; i++){
        punto();
    }
    for (int i = 0; i < 3; i++){
        raya();
    }
     for(int i =0; i < 3; i++){
        punto();
    }
}

void app_main(void)
{
    // Reinicia la configuración de los pines LED y botón
    gpio_reset_pin(LED);
    gpio_reset_pin(BUTTON);

    // Configura el pin del LED como salida
    gpio_set_direction(LED, GPIO_MODE_OUTPUT);

    // Configura el pin del botón con resistencia pull-up
    gpio_set_pull_mode(BUTTON, GPIO_PULLUP_ONLY);
    // Configura el pin del botón como entrada
    gpio_set_direction(BUTTON, GPIO_MODE_INPUT);

    // Bucle principal
    while(true)
    {
        // Lee el estado del botón (0 si está presionado, 1 si no)
        int status = gpio_get_level(BUTTON);

        // Si el botón está presionado (nivel bajo)
        if(status == false)
        {
            sos();
        }
        else
        {
            gpio_set_level(LED, 0); // Apaga el LED
        }

        // Espera 20 ms antes de repetir
        vTaskDelay(pdMS_TO_TICKS(20));
    }

}


