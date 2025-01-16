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
#define LED1_RED 11
#define LED1_GREEN 12
#define LED1_BLUE 13
#define LED2_RED 14
#define LED2_GREEN 15
#define LED2_BLUE 16
#define LED3_RED 17
#define LED3_GREEN 18
#define LED3_BLUE 19
#define BUZZER 21
#define NUM_LINHAS 4
#define NUM_COLUNAS 4

// Configuração dos GPIOs - Desenvolvedor 2
void setup_gpio() {
    // inicializando cada tecla 
    gpio_init(ROW_1);
    gpio_init(ROW_2);
    gpio_init(ROW_3);
    gpio_init(ROW_4);
    gpio_set_dir(ROW_1, GPIO_OUT);
    gpio_set_dir(ROW_2, GPIO_OUT);
    gpio_set_dir(ROW_3, GPIO_OUT);
    gpio_set_dir(ROW_4, GPIO_OUT);
    gpio_put(ROW_1, 1);
    gpio_put(ROW_2, 1);
    gpio_put(ROW_3, 1);
    gpio_put(ROW_4, 1);
   
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
void control_led() {
    char key = read_keypad();

    switch (key) {
        case '1':
            gpio_put(LED1_RED, 1);
            printf("LED 1: Vermelho ativado.\n");
            break;
        case '2':
            gpio_put(LED1_GREEN, 1);
            printf("LED 1: Verde ativado.\n");
            break;
        case '3':
            gpio_put(LED1_BLUE, 1);
            printf("LED 1: Azul ativado.\n");
            break;
        case '4':
            gpio_put(LED1_RED, 0);
            gpio_put(LED1_GREEN, 0);
            gpio_put(LED1_BLUE, 0);
            printf("LED 1 desativado.\n");
            break;
        case '5':
            gpio_put(LED2_RED, 1);
            printf("LED 2: Vermelho ativado.\n");
            break;
        case '6':
            gpio_put(LED2_GREEN, 1);
            printf("LED 2: Verde ativado.\n");
            break;
        case '7':
            gpio_put(LED2_BLUE, 1);
            printf("LED 2: Azul ativado.\n");
            break;
        case '8':
            gpio_put(LED2_RED, 0);
            gpio_put(LED2_GREEN, 0);
            gpio_put(LED2_BLUE, 0);
            printf("LED 2 desativado.\n");
            break;
        case '9':
            gpio_put(LED3_RED, 1);
            printf("LED 3: Vermelho ativado.\n");
            break;
        case 'A':
            gpio_put(LED3_GREEN, 1);
            printf("LED 3: Verde ativado.\n");
            break;
        case 'B':
            gpio_put(LED3_BLUE, 1);
            printf("LED 3: Azul ativado.\n");
            break;
        case 'C':
            gpio_put(LED3_RED, 0);
            gpio_put(LED3_GREEN, 0);
            gpio_put(LED3_BLUE, 0);
            printf("LED 3 desativado.\n");
            break;
        default:
            break;
    }
}


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
