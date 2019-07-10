/*******************************************************************************
 * Arquivo: adc.c
 * DATA:    01/03/2019 
 * AUTOR:   Silvano Fonseca Paganoto
 *******************************************************************************  
 * 
 * Biblioteca do conversor analogico para digital
 * 
 ******************************************************************************/

//==============================================================================
// Inclusao de bibliotecas
//==============================================================================
#include "adc.h"

/*******************************************************************************
 * Configuração do modulo de entradas analógicas
 ******************************************************************************/
void adc_init(void) {
    ADCON1 = 0x0E; // Seleciona AD0 como entrada analógica, Vref+ = Vcc e Vref- = 0   
    CMCON = 0x07; // Comparador desligado    
    ADCON2 = 0b10010100; // formato justificado a direita, 4 TAD e FOSC/4   
    ADCON0 = 0x01; // Conversor habilitado
}

/*******************************************************************************
 * Leitura do canal analogico
 ******************************************************************************/
unsigned int adc_read(unsigned char canal) {
    unsigned char x, y;
    ADCON0 = (canal << 2) | 0x01;
    ADCON0bits.GO_DONE = 1;
    while (ADCON0bits.GO_DONE);
    x = ADRESH & 0x03;
    y = ADRESL;
    return (unsigned int) (x << 8 | y);
}
