#ifndef UART_H
#define UART_H

#define ADDRESS_CHANNEL 0x000000
#define EEPROM_ADDRESS_VOX 0x000003
void readChannelInfo();
void saveChannelInfo();
void createUartTasks(void);
#endif