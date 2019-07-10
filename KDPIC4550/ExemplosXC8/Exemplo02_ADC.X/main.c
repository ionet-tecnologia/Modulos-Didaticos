/*******************************************************************************
 * Arquivo: main.c
 * DATA:    01/03/2019 
 * AUTOR:   Silvano Fonseca Paganoto
 *******************************************************************************  
 * KIT/MODULO: KDPIC4550
 * 
 * OBJETIVO: Ler o valor do canal analogico AN0, caso este valor seja 
 *           maior que 500 acende o led L3, caso contrario, apaga o led L3. 
 * 
 * CONEXOES NECESSARIAS: Usando um jumper ou fio, conecte o pino POT ao
 *                       pino RA0 presente no soquete J4.
 * 
 * ORIENTAÇÕES PARA TESTES: Gire o potenciometro RV1 usando uma pequena chave
 *                          de fenda para visualizar o comportamento do led L3.   
 * 
 ******************************************************************************/

//==============================================================================
// Configuracao dos bits de hardware
//==============================================================================
#pragma config DEBUG 	= ON
#pragma config MCLRE 	= ON
#pragma config FOSC 	= XTPLL_XT
#pragma config WDT      = OFF
#pragma config LVP      = OFF
#pragma config PWRT 	= ON
#pragma config CPUDIV   = OSC1_PLL2

//==============================================================================
// Inclusao de bibliotecas
//==============================================================================
#include <xc.h>
#include "adc.h"

//==============================================================================
// Definicoes
//==============================================================================
#define _XTAL_FREQ (48000000)            // Frequencia do clock em Hz

#define LED_L3 LATEbits.LATE2            // Endereco do LED_L3
#define LED_L3_Init() TRISEbits.TRISE2=0 // Configura o pino do LED_L3 como saida

/*******************************************************************************
 * Rotina principal
 * ****************************************************************************/
void main(void) {
    int valor;

    ADCON1 = 0x0F; // Configura todos os pinos para IO digital
    CMCON = 0x07; // Desabilita todos os comparadores analogicos   
    LED_L3_Init();
    adc_init();

    while (1) {
        valor = adc_read(0);
        if (valor > 500)
            LED_L3 = 1;
        else
            LED_L3 = 0;
    }
}
// Fim do programa
