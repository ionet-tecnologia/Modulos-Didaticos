;*******************************************************************************
; Arquivo: main.asm
; DATA:    01/03/2019 
; AUTOR:   Silvano Fonseca Paganoto
;*******************************************************************************  
; KIT/MODULO: KDPIC4550
;  
; OBJETIVO: Representar o estado do botao SW3 atraves do led L3 
; 
;******************************************************************************/

;===============================================================================
; Inclusão de bibliotecas
;===============================================================================
LIST P=18F4550          ; Definicacao do tipo de micocontrolador usado
#INCLUDE <P18F4550.INC> ; Biblioteca padrao para o microcontrolador PIC18F4550
CONFIG FOSC = XT_XT, PWRT = ON, WDT=OFF, MCLRE = ON, DEBUG = ON, LVP = OFF
;===============================================================================
; Definicao de nomes de variaveis (alocadas na memoria RAM de uso geral)
;===============================================================================
    CBLOCK  0x60        ;Endereco inicial do bloco de memoria RAM de uso geral
        W_TEMP          ;Variavel para armazenar temporariamente o valor do Registrador W
        STATUS_TEMP     ;Variavel para armazenar temporariamente o valor do Registrador STATUS
    ENDC                ;Fin do bloco 

;===============================================================================
; Definicoes gerais
;===============================================================================
#DEFINE SW3	    PORTC,RC0        ; Endereco do SW4
#DEFINE SW3_Init    BSF TRISC,TRISC0 ; Configura o pino em que o SW3 esta conectado como entrada

#DEFINE LED_L3      LATE,LATE2       ; Endereco do LED_L3
#DEFINE LED_L3_Init BCF TRISE,TRISE2 ; Configurao o pino em que o LED_L3 esta conectado como saida

;===============================================================================
; Vetor de reset
;===============================================================================
    ORG 0x1000          ; Endereco de execucao do programa apos o reset
    GOTO    INICIO    ; Vai para label INICIO

;===============================================================================
; Vetor de interrupcao
;===============================================================================
    ORG 0x1008  ; Endereco de execucao do codigo na ocorrencia de interrupcao de alta prioridade
    RETFIE      ; Retorna da interrupcao

    ORG 0x1018  ; Endereco de execucao do codigo na ocorrencia de interrupcao de baixa prioridade
    RETFIE      ; Retorna da interrupcao

;===============================================================================
; Inicio do programa
;===============================================================================
;ORG 0x102A              ; Endereco inicial de alocacao do inicio do programa
INICIO                  ; Label de inicio do programa
    MOVLW 0x0F		; Valor para configuracao do ADCON1
    MOVWF ADCON1	; Configura todos os pinos (digital/analogico) para o tipo digital
    MOVLW 07h		; Valor para configuracao do CMCON
    MOVWF CMCON		; Desabilite o comparador analogico para utilização dos pinos como digital
    SW3_Init		; Inicializa o SW3
    LED_L3_Init		; Inicializa o LED_L3

TEST                    ; Label de test do botao
    BTFSC SW3	; Testa se o botao esta precionado
	BRA NAO_ESTA	; Nao precionado, vai para label NAO_ESTA
    ESTA		; Label para para tratamento quando esta precionado
	BSF LED_L3	; Liga o led
	BRA TEST	; Vai para o label TEST
    NAO_ESTA		; Label para para tratamento quando nao esta precionado
    BCF LED_L3		; Desliga o led
    BRA TEST		; Vai para o label TEST
END                     ; Fim do programa
