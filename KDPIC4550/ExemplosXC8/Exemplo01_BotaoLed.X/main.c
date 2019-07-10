/*******************************************************************************
 * Arquivo: main.c
 * DATA:    01/03/2019 
 * AUTOR:   Silvano Fonseca Paganoto
 *******************************************************************************  
 * KIT/MODULO: KDPIC4550
 * 
 * OBJETIVO: Representar o estado do botao SW3 atraves do led L3 
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

//==============================================================================
// Definicoes
//==============================================================================
#define _XTAL_FREQ (48000000)            // Frequencia do clock em Hz

#define SW3 PORTCbits.RC0                // Endereco de SW3
#define SW3_Init() TRISCbits.TRISC0=1    // Configura o pino de SW3 como entrada

#define LED_L3 LATEbits.LATE2            // Endereco do LED_L3
#define LED_L3_Init() TRISEbits.TRISE2=0 // Configura o pino do LED_L3 como saida

/*******************************************************************************
 * Rotina principal
 * ****************************************************************************/
void main(void) {
    ADCON1 = 0x0F; // Configura todos os pinos para IO digital
    CMCON = 0x07; // Desabilita todos os comparadores analogicos
    SW3_Init();
    LED_L3_Init();

    while (1) {
        if (SW3)
            LED_L3 = 0;
        else
            LED_L3 = 1;
    }
}
// Fim do programa
