#ifndef UART_H
#define UART_H

#define ADDRESS_CHANNEL 0x000000
#define EEPROM_ADDRESS_VOX 0x000003
#define EEPROM_ADDRESS_POWER 0x000006
void readChannelInfo();
void saveChannelInfo();
void createUartTasks(void);
void saveVoxEEPROM();
void readVoxEEPROM();
void savePowerEEPROM();
void readPowerEEPROM();
#endif