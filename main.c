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
#define NUM_LINHAS 4
#define NUM_COLUNAS 4

// Configuração dos GPIOs - Desenvolvedor 2
void setup_gpio() {
    // Configurar linhas do teclado como saída
   
    // Configurar colunas do teclado como entrada com pull-down
 
    // Configurar LEDs e buzzer como saída
}

// Leitura do teclado matricial - Desenvolvedor 3

// Matriz representando os botões
const char KEYPAD[NUM_LINHAS][NUM_COLUNAS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

char read_keypad() {
    const uint rows[] = {ROW_1, ROW_2, ROW_3, ROW_4};
    const uint cols[] = {COL_1, COL_2, COL_3, COL_4};

    for (int linha = 0; linha < 4; linha++) {
        gpio_put(rows[linha], 0); // Ativa a linha atual (LOW)

        for (int coluna = 0; coluna < 4; coluna++) {
            if (gpio_get(cols[coluna]) == 1) { // Verifica se a coluna está HIGH
                sleep_ms(50); // Debounce
                if (gpio_get(cols[coluna]) == 1) {
                    while (gpio_get(cols[coluna]) == 1) {
                        sleep_ms(10); // Aguarda o botão ser solto
                    }
                    gpio_put(rows[linha], 1); // Restaura a linha para HIGH
                    return KEYPAD[linha][coluna];
                }
            }
        }

        gpio_put(rows[linha], 1); // Desativa a linha atual (HIGH)
    }

    return '\0'; // Nenhuma tecla pressionada
}


// Controle básico dos LEDs - Desenvolvedor 4
void control_led();

// Controle avançado dos LEDs - Desenvolvedor 5
void advanced_led_pattern();

// Controle do buzzer - Desenvolvedor 6
void control_buzzer();

// Integração e testes - Desenvolvedor 7
void run_tests();

// Função principal - Desenvolvedor 1
int main() {
    stdio_init_all();
    setup_gpio();
    printf("Sistema iniciado. Pressione uma tecla para controlar os dispositivos.\n");

}
