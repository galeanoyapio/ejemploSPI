#include "MKL25Z4.h"

// Para SPI 0
void SPI_Init(void) {
    SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK; 
    SIM->SCGC4 |= SIM_SCGC4_SPI0_MASK;  //spi activo

    PORTD->PCR[0] = PORT_PCR_MUX(2);   //  SCK
    PORTD->PCR[2] = PORT_PCR_MUX(2);   //  MOSI ENVIO
    PORTD->PCR[3] = PORT_PCR_MUX(2);   //  MISO RECIBO

    SPI0->C1 = 0x50;  // Habilitar el SPI
    SPI0->BR = SPI_BR_SPPR(0) | SPI_BR_SPR(2);  // Establecer la velocidad de reloj en 6MHz
}

void SPI_Send(uint8_t data) {
    while (!(SPI0->S & SPI_S_SPTEF_MASK));  // Esperar a que el registro de transmisión esté vacío
    SPI0->D = data;  // Enviar
}


uint8_t SPI_Receive(void) {
    while (!(SPI0->S & SPI_S_SPRF_MASK));  // Esperar a que se reciba un byte
    return SPI0->D;  // Leer 
}

char conversion(char var){
    uint8_t decimal = 0;
    uint8_t base = 1;

    while (var > 0) {
        uint8_t decena = var % 10;
        var = var / 10;
        decimal += decena * base;
        base = base * 2;
    }
    return decimal;
}

uint8_t humedad(void){
    char hum = SPI_Receive();
    char humDec = SPI_Receive();
    char humedad = hum + "," + humDec;
    conversion(humedad);
}

uint8_t temperatura(void){
    char temp = SPI_Receive();
    char tempDec = SPI_Receive();
    char temperatura = temp + "," + tempDec;
    conversion(temperatura);
}

