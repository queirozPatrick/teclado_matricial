#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

// ------------------- Desenvolvedor 1 -------------------
// Definição dos pinos GPIO (conforme o "código anterior")
#define ROW_1    16
#define ROW_2    17
#define ROW_3    9
#define ROW_4    8
#define COL_1    18
#define COL_2    19
#define COL_3    20
#define COL_4    4

// ------------------- Desenvolvedor 2 -------------------
// Apenas LED1 (três cores)
#define LED1_RED   13
#define LED1_GREEN 11
#define LED1_BLUE  12

// Buzzer
#define BUZZER     10

// Dimensões do teclado
#define NUM_LINHAS 4
#define NUM_COLUNAS 4

volatile bool stop_pattern = false;  // Controle global

// ------------------- Desenvolvedor 2 -------------------
// Inicialização dos GPIOs do teclado matricial e LED1
void setup_gpio() {
    // ------------ Configuração das linhas (saída) ------------
    gpio_init(ROW_1);
    gpio_init(ROW_2);
    gpio_init(ROW_3);
    gpio_init(ROW_4);

    gpio_set_dir(ROW_1, GPIO_OUT);
    gpio_set_dir(ROW_2, GPIO_OUT);
    gpio_set_dir(ROW_3, GPIO_OUT);
    gpio_set_dir(ROW_4, GPIO_OUT);

    // Define todas as linhas em HIGH (1) inicialmente
    gpio_put(ROW_1, 1);
    gpio_put(ROW_2, 1);
    gpio_put(ROW_3, 1);
    gpio_put(ROW_4, 1);

    // ------------ Configuração das colunas (entrada, pull-up) ------------
    gpio_init(COL_1);
    gpio_init(COL_2);
    gpio_init(COL_3);
    gpio_init(COL_4);

    gpio_set_dir(COL_1, GPIO_IN);
    gpio_set_dir(COL_2, GPIO_IN);
    gpio_set_dir(COL_3, GPIO_IN);
    gpio_set_dir(COL_4, GPIO_IN);

    // Pull-up em cada coluna (0 = pressionado)
    gpio_pull_up(COL_1);
    gpio_pull_up(COL_2);
    gpio_pull_up(COL_3);
    gpio_pull_up(COL_4);

    // ------------ Inicialização do LED1 (3 cores) ------------
    gpio_init(LED1_RED);
    gpio_init(LED1_GREEN);
    gpio_init(LED1_BLUE);

    gpio_set_dir(LED1_RED, GPIO_OUT);
    gpio_set_dir(LED1_GREEN, GPIO_OUT);
    gpio_set_dir(LED1_BLUE, GPIO_OUT);

    // ------------ Configuração do buzzer como saída ------------
    gpio_init(BUZZER);
    gpio_set_dir(BUZZER, GPIO_OUT);

    printf("GPIO configurados com sucesso.\n");
}

// ------------------- Desenvolvedor 3 -------------------
// Matriz representando os botões do teclado
const char KEYPAD[NUM_LINHAS][NUM_COLUNAS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

// --------------- NOVAS FUNÇÕES: Tocar notas no buzzer ---------------
/**
 * Gera onda quadrada em freq Hz, durante durationMs milissegundos.
 */
void play_note(unsigned int freq, unsigned int durationMs) {
    if (freq == 0) {
        // Se freq=0, apenas aguarda
        sleep_ms(durationMs);
        return;
    }

    // Período de cada ciclo em microssegundos
    float period_us = 1000000.0f / (float)freq;
    // Quantidade de meio-ciclos necessária
    unsigned long cycles = (durationMs * 1000UL) / (unsigned long)period_us;

    // Gera a onda quadrada
    for (unsigned long i = 0; i < cycles; i++) {
        gpio_put(BUZZER, 1);
        sleep_us(period_us / 2);
        gpio_put(BUZZER, 0);
        sleep_us(period_us / 2);
    }
}

/**
 * Toca Dó (262 Hz), Ré (294 Hz) e Mi (330 Hz),
 * cada uma por 2 segundos (2000 ms).
 */
void play_do_re_mi() {
    printf("Tocando DÓ (2s)...\n");
    play_note(262, 2000); // Dó
    sleep_ms(200);

    printf("Tocando RÉ (2s)...\n");
    play_note(294, 2000); // Ré
    sleep_ms(200);

    printf("Tocando MI (2s)...\n");
    play_note(330, 2000); // Mi
    sleep_ms(200);
}

// ------------------- Desenvolvedor 3 (continuação) ---------------
// Leitura do teclado matricial (usando pull-up, 0 = pressionado)
char read_keypad() {
    // Arrays de linhas e colunas
    const uint rows[] = {ROW_1, ROW_2, ROW_3, ROW_4};
    const uint cols[] = {COL_1, COL_2, COL_3, COL_4};

    // Faz a varredura linha a linha
    for (int linha = 0; linha < 4; linha++) {
        // Coloca a linha atual em LOW (0) para "ativar"
        gpio_put(rows[linha], 0);

        // Lê cada coluna
        for (int coluna = 0; coluna < 4; coluna++) {
            // Se a coluna estiver em 0, significa tecla pressionada
            if (gpio_get(cols[coluna]) == 0) {
                sleep_ms(50); // Debounce

                if (gpio_get(cols[coluna]) == 0) {
                    // Espera o botão ser solto
                    while (gpio_get(cols[coluna]) == 0) {
                        sleep_ms(10);
                    }
                    // Desativa a linha (retorna a HIGH)
                    gpio_put(rows[linha], 1);

                    // Retorna o caractere correspondente
                    return KEYPAD[linha][coluna];
                }
            }
        }
        // Desativa a linha atual (HIGH)
        gpio_put(rows[linha], 1);
    }

    return '\0'; // Nenhuma tecla pressionada
}

// ------------------- Desenvolvedor 4 -------------------
// Controle básico do LED1 + Dó-Ré-Mi no buzzer
void control_led() {
    char key = read_keypad();
    if (key == '\0') return; // Se não detectou tecla, não faz nada

    switch (key) {
        case '1':
            // Liga vermelho
            gpio_put(LED1_RED, 1);
            printf("LED1: Vermelho ativado.\n");
            break;
        case '2':
            // Liga verde
            gpio_put(LED1_GREEN, 1);
            printf("LED1: Verde ativado.\n");
            break;
        case '3':
            // Liga azul
            gpio_put(LED1_BLUE, 1);
            printf("LED1: Azul ativado.\n");
            break;
        case '4':
            // Desliga todas as cores do LED1
            gpio_put(LED1_RED, 0);
            gpio_put(LED1_GREEN, 0);
            gpio_put(LED1_BLUE, 0);
            printf("LED1 desativado.\n");
            break;

        // EFEITO DÓ-RÉ-MI AO PRESSIONAR TECLA '5'
        case '5':
            printf("Iniciando efeito DÓ-RÉ-MI...\n");
            play_do_re_mi();
            break;

        default:
            // Não faz nada se for outra tecla
            break;
    }
}

// ------------------- Desenvolvedor 5 -------------------
// Controle avançado do LED1 (pattern)
void control_led_pattern() {
    const int tempo = 250;
    char key = read_keypad();
    if (key == '\0') return; // Se não detectou tecla, sai

    switch(key) {
        case '0':
            // Efeito blink alternando as cores do LED1
            printf("efeito visual blink alternando as cores do LED1.\n");
            stop_pattern = false;
            while(!stop_pattern) {
                // Azul
                gpio_put(LED1_BLUE, 1);
                sleep_ms(tempo);
                gpio_put(LED1_BLUE, 0);
                sleep_ms(tempo);

                // Vermelho
                gpio_put(LED1_RED, 1);
                sleep_ms(tempo);
                gpio_put(LED1_RED, 0);
                sleep_ms(tempo);

                // Verde
                gpio_put(LED1_GREEN, 1);
                sleep_ms(tempo);
                gpio_put(LED1_GREEN, 0);
                sleep_ms(tempo);

                // Se pressionar 'D', sair do loop
                if (read_keypad() == 'D') {
                    stop_pattern = true;
                }
            }
            break;

        case 'D':
            // Efeito visual S.O.S em LED vermelho
            printf("efeito visual S.O.S em código morse no LED1.\n");
            stop_pattern = false;
            while (!stop_pattern) {
                // 3 pontos (S)
                for (int i = 0; i < 3; i++) {
                    gpio_put(LED1_RED, 1);
                    sleep_ms(200);
                    gpio_put(LED1_RED, 0);
                    sleep_ms(200);
                }
                sleep_ms(tempo);

                // 3 traços (O)
                for (int i = 0; i < 3; i++) {
                    gpio_put(LED1_RED, 1);
                    sleep_ms(800);
                    gpio_put(LED1_RED, 0);
                    sleep_ms(200);
                }
                sleep_ms(tempo);

                // 3 pontos (S)
                for (int i = 0; i < 3; i++) {
                    gpio_put(LED1_RED, 1);
                    sleep_ms(200);
                    gpio_put(LED1_RED, 0);
                    sleep_ms(200);
                }
                sleep_ms(3000);

                // Se pressionar 'D', sair do loop
                if (read_keypad() == 'D') {
                    stop_pattern = true;
                }
            }
            break;
        default:
            // Não faz nada se for outra tecla
            break;
    }
}

// ------------------- Desenvolvedor 6 -------------------
// Controle do buzzer ON/OFF (simples)
void control_buzzer(int estado, int duracao) {
    if (estado == 1) {
        gpio_put(BUZZER, 1);
        if (duracao > 0) {
            sleep_ms(duracao);
            gpio_put(BUZZER, 0);
        }
    } else {
        gpio_put(BUZZER, 0);
    }
}

// ------------------- Desenvolvedor 7 -------------------
// Integração e testes
void run_tests() {
    printf("Iniciando testes de integração...\n");

    // Teste do LED1
    printf("Teste: LED1 (Vermelho, Verde, Azul)...\n");
    gpio_put(LED1_RED, 1);
    sleep_ms(100);
    gpio_put(LED1_RED, 0);
    gpio_put(LED1_GREEN, 1);
    sleep_ms(100);
    gpio_put(LED1_GREEN, 0);
    gpio_put(LED1_BLUE, 1);
    sleep_ms(100);
    gpio_put(LED1_BLUE, 0);
    printf("GPIOs do LED1 testados com sucesso.\n");

    // Teste do buzzer
    printf("Teste: Buzzer...\n");
    control_buzzer(1, 500); // beep simples
    control_buzzer(0, 0);
    printf("Buzzer testado com sucesso.\n");

    // Teste do teclado matricial
    printf("Teste: Leitura do teclado matricial...\n");
    printf("Pressione uma tecla no teclado matricial.\n");
    char tecla = read_keypad();
    if (tecla != '\0') {
        printf("Tecla '%c' detectada com sucesso.\n", tecla);
    } else {
        printf("Nenhuma tecla detectada. Verifique a configuração do teclado.\n");
    }

    // Teste simples de piscar o LED1
    printf("Teste: Piscar rapidamente o LED1...\n");
    gpio_put(LED1_RED, 1);
    sleep_ms(200);
    gpio_put(LED1_RED, 0);
    printf("Piscar LED1 executado com sucesso.\n");

    printf("Testes de integração concluídos.\n");
}

// ------------------- Desenvolvedor 1 -------------------
// Função principal
int main() {
    stdio_init_all();
    setup_gpio();
    control_buzzer(0, 0);  // Desativa o buzzer
    run_tests();           // Executa testes de integração

    printf("Sistema iniciado. Pressione uma tecla para controlar os dispositivos.\n");
    
    while (true) {
        // 1) Controla LED (inclui Dó-Ré-Mi na tecla '5')
        control_led();

        // 2) Controla efeitos blink e S.O.S
        control_led_pattern();
    }
    
    return 0;
}
