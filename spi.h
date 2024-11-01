#ifndef SPI_H
#define SPI_H

void SPI_Init(void);
void SPI_Send(uint8_t data);
uint8_t SPI_Receive(void);
uint8_t humedad(void);
uint8_t temperatura(void);
char conversion(char var);

#endif