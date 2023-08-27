#include "main.h"

#define TAG "UI"

SSD1306_t dev;
uint8_t gChannelNum =	0;
uint8_t gVolume  	=	0;
uint8_t gVox     	=	0;
float   gRFV	 	=	0;
float   gTFV	  	=	0;
bool    gPowerLevel = 	LOW_LEVEL; //0:High, 1:Low
bool 	gBand   	=	WIDE_BAND; 
bool    gBusyLock	=   false;

bool	gScreenRefresh = false;
uint8_t gRxCtcss	=	0;
uint8_t gTxCtcss	=	0;
bool menuActive = false;
bool chanListActive = false;
uint8_t menuCurentItem	=	1;
bool voxMenuActive = false;

channel_config_t channelInfo[MAX_CHANNEL_NUM] = {
	//RFV		TFV		  RxCT,TxCT,Vox, BAND,		 PowerLevel
	{446.00625,	446.00625,	0,	0,	0,	WIDE_BAND,	HIGH_LEVEL},
	{446.01875,	446.01875,	0,	0,	0,	WIDE_BAND,	HIGH_LEVEL},
	{446.03125,	446.03125,	0,	0,	0,	WIDE_BAND,	HIGH_LEVEL},
	{446.04375,	446.04375,	0,	0,	0,	WIDE_BAND,	HIGH_LEVEL},
	{446.05625,	446.05625,	0,	0,	0,	WIDE_BAND,	HIGH_LEVEL},
	{446.06875,	446.06875,	0,	0,	0,	WIDE_BAND,	HIGH_LEVEL},
	{446.08125,	446.08125,	0,	0,	0,	WIDE_BAND,	HIGH_LEVEL},
	{446.09375,	446.09375,	0,	0,	0,	WIDE_BAND,	HIGH_LEVEL},
	{446.10625,	446.10625,	0,	0,	0,	WIDE_BAND,	HIGH_LEVEL},
	{446.11875,	446.11875,	0,	0,	0,	WIDE_BAND,	HIGH_LEVEL},
	{446.13125,	446.13125,	0,	0,	0,	WIDE_BAND,	HIGH_LEVEL},
	{446.14375,	446.14375,	0,	0,	0,	WIDE_BAND,	HIGH_LEVEL},
	{446.15625,	446.15625,	0,	0,	0,	WIDE_BAND,	HIGH_LEVEL},
	{446.16875,	446.16875,	0,	0,	0,	WIDE_BAND,	HIGH_LEVEL},
	{446.18125,	446.18125,	0,	0,	0,	WIDE_BAND,	HIGH_LEVEL},
	{446.19375,	446.19375,	0,	0,	0,	WIDE_BAND,	HIGH_LEVEL},
	{423.225,	423.225,	17,	17,	3,	WIDE_BAND,	HIGH_LEVEL},
	{424.050,	424.050,	18,	18,	3,	WIDE_BAND,	HIGH_LEVEL},
	{424.875,	424.875,	19,	19,	3,	WIDE_BAND,	HIGH_LEVEL},
	{425.700,	425.700,	20,	20,	3,	WIDE_BAND,	HIGH_LEVEL},
	{426.525,	426.525,	21,	21,	3,	WIDE_BAND,	HIGH_LEVEL},
	{427.350,	427.350,	22,	22,	3,	WIDE_BAND,	HIGH_LEVEL},
	{428.175,	428.175,	23,	23,	3,	WIDE_BAND,	HIGH_LEVEL},
	{429.000,	429.000,	24,	24,	3,	WIDE_BAND,	HIGH_LEVEL},
	{429.825,	429.825,	25,	25,	3,	WIDE_BAND,	HIGH_LEVEL},
	{430.650,	430.650,	26,	26,	3,	WIDE_BAND,	HIGH_LEVEL},
	{431.475,	431.475,	27,	27,	3,	WIDE_BAND,	HIGH_LEVEL},
	{432.300,	432.300,	28,	28,	3,	WIDE_BAND,	HIGH_LEVEL},
	{433.125,	433.125,	29,	29,	3,	WIDE_BAND,	HIGH_LEVEL},
	{433.950,	433.950,	30,	30,	3,	WIDE_BAND,	HIGH_LEVEL},
	{434.775,	434.775,	31,	31,	3,	WIDE_BAND,	HIGH_LEVEL},
	{435.600,	435.600,	32,	32,	3,	WIDE_BAND,	HIGH_LEVEL},
	{436.425,	436.425,	33,	33,	3,	WIDE_BAND,	HIGH_LEVEL},
	{437.250,	437.250,	34,	34,	3,	WIDE_BAND,	HIGH_LEVEL},
	{438.075,	438.075,	35,	35,	3,	WIDE_BAND,	HIGH_LEVEL},
	{438.900,	438.900,	36,	36,	3,	WIDE_BAND,	HIGH_LEVEL},
	{439.725,	439.725,	37,	37,	3,	WIDE_BAND,	HIGH_LEVEL},
	{440.550,	440.550,	38,	38,	3,	WIDE_BAND,	HIGH_LEVEL},
	{441.375,	441.375,	1,	1,	3,	WIDE_BAND,	HIGH_LEVEL},
	{442.200,	442.200,	2,	2,	3,	WIDE_BAND,	HIGH_LEVEL},
	{443.025,	443.025,	3,	3,	3,	WIDE_BAND,	HIGH_LEVEL},
	{443.850,	443.850,	4,	4,	3,	WIDE_BAND,	HIGH_LEVEL},
	{444.675,	444.675,	5,	5,	3,	WIDE_BAND,	HIGH_LEVEL},
	{445.500,	445.500,	6,	6,	3,	WIDE_BAND,	HIGH_LEVEL},
	{446.325,	446.325,	7,	7,	3,	WIDE_BAND,	HIGH_LEVEL},
	{447.150,	447.150,	8,	8,	3,	WIDE_BAND,	HIGH_LEVEL},
	{447.975,	447.975,	9,	9,	3,	WIDE_BAND,	HIGH_LEVEL},
	{448.800,	448.800,	10,	10,	3,	WIDE_BAND,	HIGH_LEVEL},
	{449.625,	449.625,	11,	11,	3,	WIDE_BAND,	HIGH_LEVEL},
	{450.450,	450.450,	12,	12,	3,	WIDE_BAND,	HIGH_LEVEL},
};

const uint8_t	gCtcssList[39][2] = {
  //ToneFrequency H,   L
  {/*0,*/ 	0xff, 0xff},		//disable CT / DCS
	{/*1,*/ 	0x70, 0x06},		//67.0Hz 0670  -> 0x70 0x06
	{/*2,*/ 	0x19, 0x07},		//71.9Hz 0719  -> 0x19 0x07
	{/*3,*/ 	0x44, 0x07},		//74.4Hz 0744  -> 0x44 0x07
	{/*4,*/ 	0x70, 0x07},		//77.0Hz 0770  -> 0x70 0x07
	{/*5,*/ 	0x97, 0x07},		//79.7Hz 0797  -> 0x97 0x07
	{/*6,*/ 	0x25, 0x08},		//82.5Hz 0825  -> 0x25 0x08
	{/*7,*/ 	0x54, 0x08},		//85.4Hz 0854  -> 0x54 0x08
	{/*8,*/ 	0x85, 0x08},		//88.5Hz 0885  -> 0x85 0x08
	{/*9,*/ 	0x15, 0x09},		//91.5Hz 0915  -> 0x15 0x09
	{/*10,*/ 	0x48, 0x09},		//94.8Hz 0948  -> 0x48 0x09
	{/*11,*/ 	0x74, 0x09},		//97.4Hz 0974  -> 0x74 0x09
	{/*12,*/ 	0x00, 0x10},		//100.0Hz 1000 -> 0x00 0x10
	{/*13,*/ 	0x35, 0x10},		//103.5Hz 1035 -> 0x35 0x10
	{/*14,*/ 	0x72, 0x10},		//107.2Hz 1072 -> 0x72 0x10
	{/*15,*/ 	0x09, 0x11},		//110.9Hz 1109 -> 0x09 0x11
	{/*16,*/ 	0x48, 0x11},		//114.8Hz 1148 -> 0x48 0x11
	{/*17,*/ 	0x88, 0x11},		//118.8Hz 1188 -> 0x88 0x11
	{/*18,*/ 	0x30, 0x12},		//123.0Hz 1230 -> 0x30 0x12
	{/*19,*/ 	0x73, 0x12},		//127.3Hz 1273 -> 0x73 0x12
	{/*20,*/ 	0x18, 0x13},		//131.8Hz 1318 -> 0x18 0x13
	{/*21,*/ 	0x65, 0x13},		//136.5Hz 1365 -> 0x65 0x13
	{/*22,*/ 	0x13, 0x14},		//141.3Hz 1413 -> 0x13 0x14
	{/*23,*/ 	0x62, 0x14},		//146.2Hz 1462 -> 0x62 0x14
	{/*24,*/ 	0x14, 0x15},		//151.4Hz 1514 -> 0x14 0x15
	{/*25,*/ 	0x67, 0x15},		//156.7Hz 1567 -> 0x67 0x15
	{/*26,*/ 	0x22, 0x16},		//162.2Hz 1622 -> 0x22 0x16
	{/*27,*/ 	0x79, 0x16},		//167.9Hz 1679 -> 0x79 0x16
	{/*28,*/ 	0x38, 0x17},		//173.8Hz 1738 -> 0x38 0x17
	{/*29,*/ 	0x99, 0x17},		//179.9Hz 1799 -> 0x99 0x17
	{/*30,*/ 	0x62, 0x18},		//186.2Hz 1862 -> 0x62 0x18
	{/*31,*/ 	0x28, 0x19},		//192.8Hz 1928 -> 0x28 0x19
	{/*32,*/ 	0x35, 0x20},		//203.5Hz 2035 -> 0x35 0x20
	{/*33,*/ 	0x07, 0x21},		//210.7Hz 2107 -> 0x07 0x21
	{/*34,*/ 	0x81, 0x21},		//218.1Hz 2181 -> 0x81 0x21
	{/*35,*/ 	0x57, 0x22},		//225.7Hz 2257 -> 0x57 0x22
	{/*36,*/ 	0x36, 0x23},		//233.6Hz 2336 -> 0x36 0x23
	{/*37,*/ 	0x18, 0x24},		//241.8Hz 2418 -> 0x18 0x24
	{/*38,*/ 	0x03, 0x25}			//250.3Hz 2503 -> 0x03 0x25
};

const static float tone_freq[38] = {
	67.0,   71.9,  74.4,  77.0,	 79.7,  82.5,  85.4,  88.5,	 91.5,  94.8,	
	97.4,  100.0, 103.5, 107.2, 110.9, 114.8, 118.8, 123.0, 127.3, 131.8, 
	136.5, 141.3, 146.2, 151.4, 156.7, 162.2, 167.9, 173.8, 179.9, 186.2, 
	192.8, 203.5, 210.7, 218.1, 225.7, 233.6, 241.8, 250.3
};

// https://www.mischianti.org/2021/07/14/ssd1306-oled-display-draw-images-splash-and-animations-2/
uint8_t Volume_0 []  = {
	// // 'Volume_0, 16x14px
	// 0x00, 0x00, 0x04, 0x00, 0x0c, 0x00, 0x14, 0x00, 0xe4, 0x84, 0x84, 0x48, 0x84, 0x30, 0x84, 0x30, 
	// 0x84, 0x48, 0xe4, 0x84, 0x14, 0x00, 0x0c, 0x00, 0x04, 0x00, 0x00, 0x00
    
    // 'Volume_0', 16x8px
    0x0c, 0x00, 0x14, 0x00, 0xe4, 0x90, 0x84, 0x60, 0x84, 0x60, 0xe4, 0x90, 0x14, 0x00, 0x0c, 0x00
};
uint8_t Volume_1 []  = {
	// // 'Volume_1, 16x14px
	// 0x00, 0x00, 0x04, 0x00, 0x0c, 0x00, 0x14, 0x00, 0xe4, 0x80, 0x84, 0x40, 0x84, 0x40, 0x84, 0x40, 
	// 0x84, 0x40, 0xe4, 0x80, 0x14, 0x00, 0x0c, 0x00, 0x04, 0x00, 0x00, 0x00
    
    // 'Volume_1', 16x8px
    0x0c, 0x00, 0x14, 0x00, 0xe5, 0x00, 0x84, 0x80, 0x84, 0x80, 0xe5, 0x00, 0x14, 0x00, 0x0c, 0x00
};

uint8_t Volume_2 [] = {
	// // 'Volume_2, 16x14px
	// 0x00, 0x00, 0x04, 0x00, 0x0c, 0x20, 0x14, 0x10, 0xe4, 0x98, 0x84, 0x48, 0x84, 0x48, 0x84, 0x48, 
	// 0x84, 0x48, 0xe4, 0x98, 0x14, 0x10, 0x0c, 0x20, 0x04, 0x00, 0x00, 0x00

    // 'Volume_2', 16x8px
    0x0c, 0x00, 0x14, 0x40, 0xe5, 0x20, 0x84, 0xa0, 0x84, 0xa0, 0xe5, 0x20, 0x14, 0x40, 0x0c, 0x00
};

uint8_t Volume_3 [] = {
	// // 'Volume_3, 16x14px
	// 0x00, 0x04, 0x04, 0x06, 0x0c, 0x22, 0x14, 0x13, 0xe4, 0x99, 0x84, 0x49, 0x84, 0x49, 0x84, 0x49, 
	// 0x84, 0x49, 0xe4, 0x99, 0x14, 0x13, 0x0c, 0x22, 0x04, 0x06, 0x00, 0x04

    // 'Volume_3', 16x8px
    0x0c, 0x10, 0x14, 0x48, 0xe5, 0x24, 0x84, 0xa4, 0x84, 0xa4, 0xe5, 0x24, 0x14, 0x48, 0x0c, 0x10
};


uint8_t Volume_4 []  = {
	// 'Volume_1, 8x16px
	0x0C, 0x90, 0x14, 0x48, 0xE5, 0x28, 0x84, 0xA8,
	0x84, 0xA8, 0xE5, 0x28, 0x14, 0x48, 0x0C, 0x90
	/*
	0  0  0  0  1  1  0  0  1  0  0  1  0  0  0  0  
	0  0  0  1  0  1  0  0  0  1  0  0  1  0  0  0  
	1  1  1  0  0  1  0  1  0  0  1  0  1  0  0  0  
	1  0  0  0  0  1  0  0  1  0  1  0  1  0  0  0  
	1  0  0  0  0  1  0  0  1  0  1  0  1  0  0  0  
	1  1  1  0  0  1  0  1  0  0  1  0  1  0  0  0  
	0  0  0  1  0  1  0  0  0  1  0  0  1  0  0  0  
	0  0  0  0  1  1  0  0  1  0  0  1  0  0  0  0  
	*/
};

unsigned char Bootup [] = {
	// 'Bootup, 128x64px
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x06, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x06, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x03, 0x00, 0xf0, 0xf0, 0x76, 0x63, 0x60, 0xec, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x03, 0x01, 0xf8, 0xf8, 0xfe, 0x63, 0xf1, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x03, 0x03, 0x1c, 0x0d, 0xc6, 0x63, 0x1b, 0x8c, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x03, 0x03, 0x0c, 0x0d, 0x86, 0x63, 0x1b, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x03, 0x03, 0x0c, 0xfd, 0x86, 0x63, 0x1b, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x03, 0x03, 0x0d, 0x8d, 0x86, 0x63, 0x1b, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x03, 0x03, 0x1d, 0x8d, 0xc6, 0x63, 0x1b, 0x8c, 0x44, 0x40, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x03, 0xf1, 0xf9, 0xfc, 0xfe, 0x63, 0x19, 0xfc, 0xee, 0xe0, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x03, 0xf8, 0xf0, 0xec, 0x76, 0x63, 0x18, 0xec, 0xcc, 0xc0, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 
	0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 
	0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 
	0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 
	0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 
	0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

unsigned char Progress [] = {
	// 'Progress, 24x4px
	0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff
};

static void uiInit(void)
{
    #if CONFIG_I2C_INTERFACE
	ESP_LOGI(TAG, "INTERFACE is i2c");
	ESP_LOGI(TAG, "CONFIG_SDA_GPIO=%d",CONFIG_SDA_GPIO);
	ESP_LOGI(TAG, "CONFIG_SCL_GPIO=%d",CONFIG_SCL_GPIO);
	ESP_LOGI(TAG, "CONFIG_RESET_GPIO=%d",CONFIG_RESET_GPIO);
	i2c_master_init(&dev, CONFIG_SDA_GPIO, CONFIG_SCL_GPIO, CONFIG_RESET_GPIO);
#endif // CONFIG_I2C_INTERFACE

#if CONFIG_SPI_INTERFACE
	ESP_LOGI(TAG, "INTERFACE is SPI");
	ESP_LOGI(TAG, "CONFIG_MOSI_GPIO=%d",CONFIG_MOSI_GPIO);
	ESP_LOGI(TAG, "CONFIG_SCLK_GPIO=%d",CONFIG_SCLK_GPIO);
	ESP_LOGI(TAG, "CONFIG_CS_GPIO=%d",CONFIG_CS_GPIO);
	ESP_LOGI(TAG, "CONFIG_DC_GPIO=%d",CONFIG_DC_GPIO);
	ESP_LOGI(TAG, "CONFIG_RESET_GPIO=%d",CONFIG_RESET_GPIO);
	spi_master_init(&dev, CONFIG_MOSI_GPIO, CONFIG_SCLK_GPIO, CONFIG_CS_GPIO, CONFIG_DC_GPIO, CONFIG_RESET_GPIO);
#endif // CONFIG_SPI_INTERFACE

#if CONFIG_FLIP
	dev._flip = true;
	ESP_LOGW(TAG, "Flip upside down");
#endif

#if CONFIG_SSD1306_128x64
	ESP_LOGI(TAG, "Panel is 128x64");
	ssd1306_init(&dev, 128, 64);
#endif // CONFIG_SSD1306_128x64
#if CONFIG_SSD1306_128x32
	ESP_LOGI(TAG, "Panel is 128x32");
	ssd1306_init(&dev, 128, 32);
#endif // CONFIG_SSD1306_128x32

	ssd1306_contrast(&dev, 0xff);
}

static float getToneFreq(uint8_t ctcss_code)
{
	if (ctcss_code >= 0 && ctcss_code <= 39)
		return tone_freq[ctcss_code];
	else
		return 0;
}

void getChannelInfo(uint8_t channel)
{
	if(channel < MAX_CHANNEL_NUM)
	{
		gRFV = channelInfo[gChannelNum].rfv;
		gTFV = channelInfo[gChannelNum].tfv;
		//gToneFreq = getToneFreq(channelInfo.rx_ctcss);
		gRxCtcss = channelInfo[gChannelNum].rx_ctcss;
		gTxCtcss = channelInfo[gChannelNum].tx_ctcss;

		gBand = channelInfo[gChannelNum].band;
		//gVox  = channelInfo[gChannelNum].vox;
		gPowerLevel = channelInfo[gChannelNum].power_level;
	}
}
void uiBootScreenLoad(uint16_t delayms)
{
	// gChannelNum = 3;
	// saveChannelInfo();

	readChannelInfo();//read from eeprom
		
	gVolume = 5;

	getChannelInfo(gChannelNum);	

    uint16_t delay = delayms/3;
    ssd1306_clear_screen(&dev, false);
	ssd1306_bitmaps(&dev, 0, 0, Bootup, 128, 64, false);
	ssd1306_bitmaps(&dev, 23, 51, Progress, 24, 4, false);
	vTaskDelay(delay / portTICK_PERIOD_MS);
	ssd1306_bitmaps(&dev, 40, 51, Progress, 24, 4, false);
	vTaskDelay(delay / portTICK_PERIOD_MS);
	ssd1306_bitmaps(&dev, 61, 51, Progress, 24, 4, false);
	vTaskDelay(delay / portTICK_PERIOD_MS);
	ssd1306_bitmaps(&dev, 81, 51, Progress, 24, 4, false);
}

void uiMainScreenLoad(void)
{
    ssd1306_clear_screen(&dev, false);
	// ssd1306_display_text(&dev, 0, "CH:CH35,Vol:8 ", 14, false);
	// ssd1306_bitmaps(&dev, 110, 0, Volume_4, 16, 8, false);
	// ssd1306_display_text(&dev, 2, "Tx:450.025M, P:H", 16, false);
	// ssd1306_display_text(&dev, 5, "Rx:450.025M", 11, false);
	// ssd1306_display_text(&dev, 7, "Vox   BAND   Cts", 16, false);

    setChannelAndVolume();
    setTxFreqAndPower();
    setRxFreq();
    setVoxBandCts();
}

static void setVolumeImg(void)
{
    if(gVolume == 0)                         ssd1306_bitmaps(&dev, 112, 0, Volume_0, 16, 8, false);
    else if(gVolume == 1 || gVolume == 2)    ssd1306_bitmaps(&dev, 112, 0, Volume_1, 16, 8, false);
    else if(gVolume >= 3 && gVolume <= 5)    ssd1306_bitmaps(&dev, 112, 0, Volume_2, 16, 8, false);
    else if(gVolume >= 6 && gVolume <= 8)    ssd1306_bitmaps(&dev, 112, 0, Volume_3, 16, 8, false);
}

void setChannelAndVolume()
{
    char buf[20];
    memset(buf, 0, sizeof(buf));
    sprintf(buf, "CH:CH%02d Vol:%01d", gChannelNum+1, gVolume);
    ssd1306_clear_line(&dev, 0, 0);
    ssd1306_display_text(&dev, 0, buf, 14, false);
    setVolumeImg();
}

void setTxFreqAndPower()
{
    char buf[20];
    memset(buf, 0, sizeof(buf));
    if(gPowerLevel == HIGH_LEVEL)
        sprintf(buf, "Tx:%.5fM H", gTFV);
    else if(gPowerLevel == LOW_LEVEL)
        sprintf(buf, "Tx:%.5fM L", gTFV);
    
    ssd1306_clear_line(&dev, 2, 0);
    ssd1306_display_text(&dev, 2, buf, 16, false);
}

void setRxFreq()
{
    char buf[20];
    memset(buf, 0, sizeof(buf));
    sprintf(buf, "Rx:%.5fM", gRFV);
    
    ssd1306_clear_line(&dev, 3, 0);
    ssd1306_display_text(&dev, 3, buf, 16, false);
}

void setVoxBandCts()
{
    char buf[22];
    memset(buf, 0, sizeof(buf));
	if(gBand == WIDE_BAND)
    	sprintf(buf, "Vox:%d B:W, %d %d", gVox, gRxCtcss, gTxCtcss);
	else if(gBand == NARROW_BAND)
		sprintf(buf, "Vox:%d B:N, %d %d", gVox, gRxCtcss, gTxCtcss);
    
	// ssd1306_clear_line(&dev, 6, 0);
	// ssd1306_display_text(&dev, 6, "         Cts(Hz)", 16, false);
	ssd1306_clear_line(&dev, 7, 0);
    ssd1306_display_text(&dev, 7, buf, 16, false);
}

void showMenu()
{
		gScreenRefresh = true;
		ssd1306_clear_screen(&dev, false);
    char buf[20];
    
    switch (menuCurentItem){
      case 1:
      	memset(buf, 0, sizeof(buf));
      	ssd1306_clear_screen(&dev, false);
      	sprintf(buf, "------MENU------");
		    ssd1306_clear_line(&dev, 0, 0);
		    ssd1306_display_text(&dev, 0, buf, 16, false);
		    memset(buf, 0, sizeof(buf));
        sprintf(buf, "> Channels");
        ssd1306_clear_line(&dev, 1, 0);
        ssd1306_display_text(&dev, 1, buf, 16, false);
        memset(buf, 0, sizeof(buf));
        sprintf(buf, "Exit");
        ssd1306_clear_line(&dev, 2, 0);
        ssd1306_display_text(&dev, 2, buf, 16, false);
        memset(buf, 0, sizeof(buf));
        sprintf(buf, "Vox");
        ssd1306_clear_line(&dev, 3, 0);
        ssd1306_display_text(&dev, 3, buf, 16, false);
        memset(buf, 0, sizeof(buf));
        break;

      case 2:
      	memset(buf, 0, sizeof(buf));
      	ssd1306_clear_screen(&dev, false);
        sprintf(buf, "------MENU------");
		    ssd1306_clear_line(&dev, 0, 0);
		    ssd1306_display_text(&dev, 0, buf, 16, false);
		    memset(buf, 0, sizeof(buf));
        sprintf(buf, "Channels");
        ssd1306_clear_line(&dev, 1, 0);
        ssd1306_display_text(&dev, 1, buf, 16, false);
        memset(buf, 0, sizeof(buf));
        sprintf(buf, "> Exit");
        ssd1306_clear_line(&dev, 2, 0);
        ssd1306_display_text(&dev, 2, buf, 16, false);
        memset(buf, 0, sizeof(buf));
        sprintf(buf, "Vox");
        ssd1306_clear_line(&dev, 3, 0);
        ssd1306_display_text(&dev, 3, buf, 16, false);
        memset(buf, 0, sizeof(buf));
        break;
        
      case 3:
      	memset(buf, 0, sizeof(buf));
      	ssd1306_clear_screen(&dev, false);
        sprintf(buf, "------MENU------");
		    ssd1306_clear_line(&dev, 0, 0);
		    ssd1306_display_text(&dev, 0, buf, 16, false);
		    memset(buf, 0, sizeof(buf));
        sprintf(buf, "Channels");
        ssd1306_clear_line(&dev, 1, 0);
        ssd1306_display_text(&dev, 1, buf, 16, false);
        memset(buf, 0, sizeof(buf));
        sprintf(buf, "Exit");
        ssd1306_clear_line(&dev, 2, 0);
        ssd1306_display_text(&dev, 2, buf, 16, false);
        memset(buf, 0, sizeof(buf));
        sprintf(buf, "> Vox");
        ssd1306_clear_line(&dev, 3, 0);
        ssd1306_display_text(&dev, 3, buf, 16, false);
        memset(buf, 0, sizeof(buf));
        break;

      default:
        if (menuCurentItem < 1){
          menuCurentItem = 3;
          showMenu();
          break;
        }
        else if(menuCurentItem > 3){menuCurentItem = 1;}
        showMenu();
        break;
    }
    
    //ssd1306_clear_line(&dev, 0, 0);
    //ssd1306_display_text(&dev, 0, buf, 16, false);

}

void showChannels(){
		gScreenRefresh = true;
		ssd1306_clear_screen(&dev, false);
    char buf[20];

		sprintf(buf, "CHANNEL: %d", gChannelNum+1);
		ssd1306_clear_line(&dev, 3, 0);
    ssd1306_display_text(&dev, 3, buf, 16, false);
    memset(buf, 0, sizeof(buf));
}

void showVox(){
		gScreenRefresh = true;
		ssd1306_clear_screen(&dev, false);
    char buf[20];

		sprintf(buf, "VOX: %d", gVox);
		ssd1306_clear_line(&dev, 3, 0);
    ssd1306_display_text(&dev, 3, buf, 16, false);
    memset(buf, 0, sizeof(buf));
}

void uiTask(void *arg)
{
    uiInit();
  uiBootScreenLoad(1000);
	//uiMainScreenLoad();

    gScreenRefresh = true;

    while(1)
    {
    	if(menuActive==true){
 		    		//ssd1306_clear_screen(&dev, false);
 		    		if(gScreenRefresh)
 						{
 								showMenu();
 		    				gScreenRefresh = false;
 		    		}
 		    		vTaskDelay(pdMS_TO_TICKS(10));
 		    }
 		    else if(chanListActive==true){
 		    		if(gScreenRefresh)
 						{
 								showChannels();
 		    				gScreenRefresh = false;
 		    		}
 		    		vTaskDelay(pdMS_TO_TICKS(10));
 		    }
 		    else if(voxMenuActive==true){
 		    		if(gScreenRefresh)
 						{
 								showVox();
 		    				gScreenRefresh = false;
 		    		}
 		    		vTaskDelay(pdMS_TO_TICKS(10));
 		    }
 		    else{
 		    		//uiMainScreenLoad();
 						if(gScreenRefresh)
 						{
 							uiMainScreenLoad();
 							gScreenRefresh = false;
 						}
 				    vTaskDelay(pdMS_TO_TICKS(10));
 			  }
 		}
}