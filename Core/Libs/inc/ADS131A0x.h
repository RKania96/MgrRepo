/*
 * ADS131A0x.h
 *
 *  Created on: 		Mar 17, 2020
 *  Last Updated on: 	xxx xx, xxxx
 *  Author: 			Michele Gazzarri
 *
 *  NOTES:
 *  	TODO: Add & correct comments
 *
 */

#ifndef ADS131A0x_H_
#define ADS131A0x_H_


// C Standard Libraries
#include <assert.h>
#include <stdint.h>
//#include "cmsis_os.h"
//#include "usbd_cdc_if.h"
#include "../stm32l4xx_hal.h"
#include "main.h"

#include "math.h"

#define ADS131A0x_LSB_VOLT	(2.5 / (1 << 24))

#define LUT_SIZE_V 50
#define LUT_SIZE_I 50
//this depends on how many bytes is composed a word
//in my case M1 tied to VDD so 32bits word
#define ADS131A0x_WORD_SIZE 					4

//number of words foreach data frame.
//|STATUS|ADC1|ADC2|ADC3|ADC4|CRC|
//in my case CRC is disabled so 5 words.
#define ADS131A0x_FRAME_NUM_WORDS 				5

// SELECT A DEVICE
//#define ADS131A02		//Standard definitions for both ADS131A042 and ADS131A04 devices
#define ADS131A04		//Additional definitions to support ADS131A04 additional features



// HARDWARE CONFIG


extern SPI_HandleTypeDef hspi3;
#define ADS131A0x_SPI_PORT hspi3


#define ADS131A0x_RST_GPIO_Port SPI3_RST_GPIO_Port
#define ADS131A0x_RST_Pin SPI3_RST_Pin

#define ADS131A0x_CS_GPIO_Port SPI3_CS_GPIO_Port
#define ADS131A0x_CS_Pin SPI3_CS_Pin

#define ADS131A0x_DRDY_GPIO_Port SPI3_DRDY_GPIO_Port
#define ADS131A0x_DRDY_Pin SPI3_DRDY_Pin

#define ADS131A0x_DONE_GPIO_Port SPI3_DONE_GPIO_Port
#define ADS131A0x_DONE_Pin SPI3_DONE_Pin



//typedef struct {
//	int Ch1;
//	int Ch2;
//	int Ch3;
//	int Ch4;
//	uint16_t Status;
//	uint16_t Checksum;
//} t_ADS131A0xData;

typedef struct {
	signed long Ch1;
	signed long Ch2;
	signed long Ch3;
	signed long Ch4;


	signed long long Ch1Sum;
	signed long long Ch2Sum;
	signed long long Ch3Sum;
	signed long long Ch4Sum;

	signed long Ch1Avg;
	signed long Ch2Avg;
	signed long Ch3Avg;
	signed long Ch4Avg;

	uint16_t Status;
	uint16_t Checksum;
} t_ADS131A0xData;





typedef struct {
	float Ch1;
	float Ch2;
	float Ch3;
	float Ch4;


	float Eff;
	float P1;
	float P2;

	double EnergyCH1;
	double EnergyCH2;

	double Q_CH1;
	double Q_CH2;
}t_measf;

t_measf measf;
#define BUFFER_SIZE 80

typedef struct {
	signed long CH1_Voltage[BUFFER_SIZE];
	signed long CH2_Voltage[BUFFER_SIZE];
	signed long CH1_Current[BUFFER_SIZE];
	signed long CH2_Current[BUFFER_SIZE];

} t_Measurements;
t_Measurements meas;
//BEGIN ADC DEFINITIONS

#ifdef ADS131A02
	#define ADS131A0x_NUM_REG 					(0x00)			/* TODO: fix ADS131A02 has xx registers */
	#define ADS131A0x_NUM_CHANNELS 				2
#endif
#ifdef ADS131A04
	#define ADS131A0x_NUM_REG 					(0x00)			/* TODO: fix ADS131A04 has xx registers */
	#define ADS131A0x_NUM_CHANNELS 				4
#endif
//System Commands
#define ADS131A0x_CMD_NULL						(0x0000)
#define ADS131A0x_CMD_RESET						(0x0011)
#define ADS131A0x_CMD_STANDBY					(0x0022)
#define ADS131A0x_CMD_WAKEUP					(0x0033)
#define ADS131A0x_CMD_LOCK						(0x0555)
#define ADS131A0x_CMD_UNLOCK					(0x0655)

//Registers Read/Write Commands
#define ADS131A0x_CMD_RREG						(0x2000)
#define ADS131A0x_CMD_RREGS						(0x2000)
#define ADS131A0x_CMD_WREG						(0x4000)
#define ADS131A0x_CMD_WREGS						(0x6000)

//Read Only ID Registers
#define ADS131A0x_REG_ID_MSB					(0x00)
#define ADS131A0x_REG_ID_LSB					(0x01)
//Read Status Registers
#define ADS131A0x_REG_STAT_1					(0x02)
#define ADS131A0x_REG_STAT_P					(0x03)
#define ADS131A0x_REG_STAT_N					(0x04)
#define ADS131A0x_REG_STAT_S					(0x05)
#define ADS131A0x_REG_ERROR_CNT					(0x06)
#define ADS131A0x_REG_STAT_M2					(0x07)
//User Configuration Registers
#define ADS131A0x_REG_A_SYS_CFG					(0x0b)
#define ADS131A0x_REG_D_SYS_CFG					(0x0c)
#define ADS131A0x_REG_CLK1						(0x0d)
#define ADS131A0x_REG_CLK2						(0x0e)
#define ADS131A0x_REG_ADC_ENA					(0x0f)
#define ADS131A0x_REG_ADC1						(0x11)
#define ADS131A0x_REG_ADC2						(0x12)

/* Additional ADS131A04 Registers */
#ifdef ADS131A04

#define ADS131A0x_REG_ADC3						(0x13)
#define ADS131A0x_REG_ADC4						(0x14)

#endif /* ADS131A04 */


//END ADC DEFINITIONS

t_ADS131A0xData ch;
uint8_t emptyTxBuffer[ADS131A0x_WORD_SIZE*5];
uint8_t ADS131A0x_DataBuf[ADS131A0x_WORD_SIZE*5];
volatile uint8_t ADS131A0x_Ready_flag;
uint8_t ADS131A0x_Init_Done;
t_ADS131A0xData ExternalADCData[ADS131A0x_NUM_CHANNELS];




signed long CH1_OffsetCal;
signed long CH2_OffsetCal;
signed long CH3_OffsetCal;
signed long CH4_OffsetCal;



/* Function Prototypes */

// Low level
void ADS131A0xReset(void);
void ADS131A0xSetCS (uint8_t state);
void ADS131A0xXferWord(uint8_t* txData, uint8_t* rxData);
uint32_t ADS131A0xSendCmd(uint16_t cmd);

void ADS131A0xCalibrate(void);

// Higher level

uint16_t ADS131A0xReadRegister(uint8_t RegAddress);
uint16_t ADS131A0xWriteRegister(uint8_t reg, uint8_t data);
void ADS131A0xWriteMultiRegister(uint8_t addr, int NumRegs, uint8_t* pdata);
t_ADS131A0xData ADS131A0xReadData(uint8_t NumBytes, uint8_t DataByteStartNum);
void ADS131A0xInit(void);
t_ADS131A0xData ADS131A0xGetChannels(void);
void StartExtADC(void);


int movingAvg(int *ptrArrNumbers, long *ptrSum, int pos, int len, int nextNum);
float interpolateValue(int32_t input, int32_t* intLUT, float* fLUT, uint8_t LUT_Size);

#endif /* ADS131A0x_H_ */
