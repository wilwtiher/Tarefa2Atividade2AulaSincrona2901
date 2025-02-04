#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/gpio.h"

// Definição dos pinos
#define LED_PIN_RED    11
#define LED_PIN_YELLOW 12
#define LED_PIN_GREEN  13
#define BUTTON_PIN     5

// Variáveis globais para controle da sequência
volatile bool sequence_in_progress = false; // Indica se a sequência está em andamento
volatile int sequence_state = 0;            // 0: inativo, 1: todos acesos, 2: vermelho e amarelo, 3: apenas vermelho

/*
 * Callback do alarme que gerencia a sequência dos LEDs.
 * O retorno indica o próximo intervalo (em microssegundos) para o alarme;
 * se retornar 0, o alarme não será reprogramado.
 */
int64_t sequence_alarm_callback(alarm_id_t id, void *user_data) {
    if (sequence_state == 1) {
        // Estado 1: Todos os LEDs acesos.
        // Transição para o Estado 2: desliga o LED verde.
        gpio_put(LED_PIN_GREEN, 0);
        sequence_state = 2;
        printf("Transição: Estado 2 (vermelho e amarelo ligados)\n");
        return 3000 * 1000; // Próximo callback após 3000 ms
    } else if (sequence_state == 2) {
        // Estado 2: Vermelho e amarelo acesos.
        // Transição para o Estado 3: desliga o LED amarelo.
        gpio_put(LED_PIN_YELLOW, 0);
        sequence_state = 3;
        printf("Transição: Estado 3 (apenas vermelho ligado)\n");
        return 3000 * 1000; // Próximo callback após 3000 ms
    } else if (sequence_state == 3) {
        // Estado 3: Apenas o LED vermelho aceso.
        // Finaliza a sequência e permite novo acionamento do botão.
        gpio_put(LED_PIN_RED, 0);
        sequence_state = 0;
        sequence_in_progress = false;
        printf("Sequência finalizada. Botão disponível para novo acionamento.\n");
        return 0; // Retorna 0 para encerrar o alarme
    }
    return 0;
}

/**
 * Callback de interrupção do botão.
 * Quando o botão é pressionado (borda de descida, considerando pull-up),
 * a sequência de LEDs é iniciada, desde que não haja uma sequência em andamento.
 */
void gpio_callback(uint gpio, uint32_t events) {
    if (gpio == BUTTON_PIN && !sequence_in_progress) {
        // Inicia a sequência
        sequence_in_progress = true;
        sequence_state = 1;
        
        // Liga todos os LEDs
        gpio_put(LED_PIN_RED, 1);
        gpio_put(LED_PIN_YELLOW, 1);
        gpio_put(LED_PIN_GREEN, 1);
        printf("Botão pressionado! Iniciando a sequência de LEDs.\n");
        
        // Agenda o primeiro alarme para 3000 ms
        add_alarm_in_ms(3000, sequence_alarm_callback, NULL, false);
    }
}

int main() {
    stdio_init_all();
    
    // Inicializa e configura os pinos dos LEDs como saída
    gpio_init(LED_PIN_RED);
    gpio_set_dir(LED_PIN_RED, GPIO_OUT);
    
    gpio_init(LED_PIN_YELLOW);
    gpio_set_dir(LED_PIN_YELLOW, GPIO_OUT);
    
    gpio_init(LED_PIN_GREEN);
    gpio_set_dir(LED_PIN_GREEN, GPIO_OUT);
    
    // Inicializa o pino do botão como entrada com pull-up
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);
    
    // Registra o callback de interrupção para o botão (borda de descida)
    gpio_set_irq_enabled_with_callback(BUTTON_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_callback);
    
    // Loop principal: pode ser usado para outras tarefas ou apenas manter o programa em execução
    while (true) {
        sleep_ms(1000);
        // Opcional: imprimir status ou executar outras rotinas
        // printf("Loop principal executando...\n");
    }
    
    return 0;
}
