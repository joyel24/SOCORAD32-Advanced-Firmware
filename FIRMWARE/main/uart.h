#ifndef UART_H
#define UART_H

#define ADDRESS_CHANNEL 0x000000
<<<<<<< Updated upstream
=======
#define EEPROM_ADDRESS_VOX 0x000003
#define EEPROM_ADDRESS_POWER 0x000006
>>>>>>> Stashed changes
void readChannelInfo();
void saveChannelInfo();
void createUartTasks(void);
#endif