# Aluno: Wilton Lacerda Silva Júnior
## Grupo 6 Subgrupo 5
# Atividade 2: Temporizador de Um Disparo (One Shot) com Sequência de LEDs

Este projeto implementa uma sequência de mudança de estados dos LEDs acionada pelo pressionamento de um botão. Utilizando a função `add_alarm_in_ms()` do SDK Pico, o programa realiza a transição entre três estados distintos dos LEDs, cumprindo os requisitos estabelecidos:

1. **Estado 1:** Ao pressionar o botão, todos os LEDs (vermelho, amarelo e verde) são ligados.
2. **Estado 2:** Após 3 segundos, o LED verde é desligado, permanecendo os LEDs vermelho e amarelo ligados.
3. **Estado 3:** Após mais 3 segundos, o LED amarelo é desligado, ficando apenas o LED vermelho aceso.
4. **Finalização:** Ao final da sequência, a rotina é encerrada, os leds se apagam e o botão fica disponível para reiniciar a sequência.

> **Observação:** Todas as mudanças de estado dos LEDs são realizadas através de funções de callback do temporizador, conforme exigido (semelhante à rotina `turn_off_callback()` utilizada em aula).

## Funcionalidades

- **Sequência One Shot:**  
  - Inicia com todos os LEDs acesos.
  - Transição para dois LEDs acesos (vermelho e amarelo) após 3 segundos.
  - Transição para apenas um LED aceso (vermelho) após mais 3 segundos.
  - Finaliza a sequência e permite novo acionamento do botão somente após o término da rotina.

- **Interrupção do Botão:**  
  - O pressionamento do botão (GPIO 5) é detectado via interrupção, iniciando a sequência somente se nenhuma sequência estiver em andamento.

- **Temporizadores:**  
  - Utiliza `add_alarm_in_ms()` para agendar os eventos de transição com intervalos de 3000 ms (3 segundos).

## Hardware Utilizado

- **Placa:** BitDogLab (ou Raspberry Pi Pico adaptado)
- **Componentes Wokwi:**  
  - LED Vermelho no GPIO 11  
  - LED Amarelo no GPIO 12  
  - LED Verde no GPIO 13
  - 3 Resistores de 330 ohms
  - Botão no GPIO 5 (configurado com resistor de pull-up)
  - Placa Raspberry Pi Pico

## Instruções de uso

  - **Placa BitDogLab:**
    Para usar na placa BitDogLab, o programa deve ser importado no Visual Studio Code com a extensão do Raspberry Pi Pico, conectar a placa no computador no modo de bootloader, e clicar na opção "Run". Para verificar a saída serial, deve iniciar o Serial Monitor.

- **Wokwi:**
  Para usar no simulador wokwi, deve seguir os mesmos passos descritos anteriormente, porém com a extensão wokwi instalada. Quando abrir o programa no VsCode, clicar sobre o diagram.json, compilar o programa, e clicar na seta para rodar o programa no simulador.
