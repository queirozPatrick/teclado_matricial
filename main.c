#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

// Definição dos pinos GPIO
#define ROW_1 2
#define ROW_2 3
#define ROW_3 4
#define ROW_4 5
#define COL_1 6
#define COL_2 7
#define COL_3 8
#define COL_4 9
#define LED_GREEN 11
#define LED_BLUE 12
#define LED_RED 13
#define BUZZER 21

// Configuração dos GPIOs - Desenvolvedor 2
void setup_gpio() {
    // Configurar linhas do teclado como saída
   
    // Configurar colunas do teclado como entrada com pull-down
 
    // Configurar LEDs e buzzer como saída

// Leitura do teclado matricial - Desenvolvedor 3
char read_keypad()

// Controle básico dos LEDs - Desenvolvedor 4
void control_led()

// Controle avançado dos LEDs - Desenvolvedor 5
void advanced_led_pattern()

// Controle do buzzer - Desenvolvedor 6
void control_buzzer()

// Integração e testes - Desenvolvedor 7
void run_tests()

// Função principal - Desenvolvedor 1
int main() {
    stdio_init_all();
    setup_gpio();
    printf("Sistema iniciado. Pressione uma tecla para controlar os dispositivos.\n");

}
