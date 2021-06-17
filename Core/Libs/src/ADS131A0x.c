/*
 * ADS131A0x.c
 *
 *  Created on: Apr 25, 2014
 *      Author: a0406726
 */

#include "ADS131A0x.h"	// All other required source files are declared here






int32_t intLUT_V_CH1[LUT_SIZE_V] = { -100, 82550, 206150, 412250, 824500,
		1030600, 1236780, 1442900, 1649020, 1855170, 2061300, 2267450, 2473550,
		2679200, 2885300, 3091500, 3297600, 3503800, 3710000, 3916160, 4122350,
		4328480, 4534600, 4740700, 4946880, 5152500, 5358600, 5564700, 5770800,
		5976900, 6183000, 6389100, 6595200, 6801300, 7007400, 7213500, 7419600,
		7625700, 7831800, 8037900, 8244000 };
float floatLUT_V[LUT_SIZE_V] = { 0.0, 10.0, 25.0, 50.0, 100.0, 125.0, 150.0,
		175.0, 200.0, 225.0, 250.0, 275.0, 300.0, 325.0, 350.0, 375.0, 400.0, 425.0, 450.0, 475.0,
		500.0, 525.0, 550.0, 575.0, 600.0, 625.0, 650.0, 675.0, 700.0, 725.0, 750.0, 775.0, 800.0, 825.0, 850.0, 875.0, 900.0, 925.0, 950.0, 975.0, 1000.0 };

int32_t intLUT_V_CH2[LUT_SIZE_V] = { -100, 82550, 206250, 412570, 825160,
		1031500, 1237800, 1444120, 1650450, 1856750, 2063100, 2269400, 2475680,
		2681500, 2887900, 3094200, 3300550, 3506850, 3713180, 3919520, 4125880,
		4332160, 4538470, 4744770, 4951120, 5156875, 5363150, 5569425, 5775700,
		5981975, 6188250, 6394525, 6600800, 6807075, 7013350, 7219625, 7425900,
		7632175, 7838450, 8044725, 8251000

};


int32_t intLUT_I_CH1[LUT_SIZE_I] = {
		-1575000, -1351000, -1127000, -902000,
		-676500, -450900, -225000, -134600, -90000, -44600, 0, 47000, 92200,
		137400, 227300, 453500, 679200, 905400, 1130590, 1355600, 1582000



};

int32_t intLUT_I_CH2[LUT_SIZE_I] = {
		-1583900, -1357100, -1132800, -906000,
		-680000, -453000, -226100, -135800, -90200, -45200, -300, 46300, 91500,
		136600, 227000, 454400, 681800, 908200, 1135000, 1363000, 1589000

};
float floatLUT_I[LUT_SIZE_I] = {
		-35.0, -30.0, -25.0, -20.0, -15.0, -10.0, -5.0, -3.0, -2.0, -1.0, 0.0, 1.0, 2.0, 3.0, 5.0, 10.0, 15.0, 20.0, 25.0, 30.0, 35.0
};






/*****begin low level functions*************************************************/
// Perform hardware reset of ADC
void ADS131A0xReset(void) {
	HAL_GPIO_WritePin(ADS131A0x_RST_GPIO_Port, ADS131A0x_RST_Pin, GPIO_PIN_RESET);
	HAL_Delay(20);
	HAL_GPIO_WritePin(ADS131A0x_RST_GPIO_Port, ADS131A0x_RST_Pin, GPIO_PIN_SET);
	HAL_Delay(20);
}
// manage CS pin
void ADS131A0xSetCS(uint8_t state)
{
	if (0 == state) {
		HAL_GPIO_WritePin(ADS131A0x_CS_GPIO_Port, ADS131A0x_CS_Pin, GPIO_PIN_RESET);
	}
	else if (1 == state) {
		HAL_GPIO_WritePin(ADS131A0x_CS_GPIO_Port, ADS131A0x_CS_Pin, GPIO_PIN_SET);
	}
	else
		assert(0);		//Aborts program
}

// receive 32 bit, simultaneously send data
void ADS131A0xXferWord(uint8_t* txData, uint8_t* rxData) {
	ADS131A0xSetCS(0);

	while(ADS131A0x_SPI_PORT.State == HAL_SPI_STATE_BUSY);
	HAL_SPI_TransmitReceive(&ADS131A0x_SPI_PORT, txData, rxData, ADS131A0x_WORD_SIZE, 100);

	ADS131A0xSetCS(1);
}
uint32_t ADS131A0xSendCmd(uint16_t cmd) {

	uint8_t txData[ADS131A0x_WORD_SIZE] = {0};
	uint8_t zeros[ADS131A0x_WORD_SIZE] = {0};
	static uint8_t rxData[ADS131A0x_WORD_SIZE];
	uint16_t res = 0;
	//split 16bit cmd in 8bit array
	txData[1] = (cmd & 0xff);
	txData[0] = (cmd >> 8);
	//Send the command
	ADS131A0xXferWord(txData, rxData);
	//The response of the previous cmd is in the next response
	//So send another empty cmd to get the response
	ADS131A0xXferWord(zeros, rxData);
	//Collapse response


	return rxData[1] + (rxData[0] << 8);

}



void ADS131A0xCalibrate(void)
{

	HAL_Delay(100);
	CH1_OffsetCal = ch.Ch1Avg;
	CH2_OffsetCal = ch.Ch2Avg;
	CH3_OffsetCal = ch.Ch3Avg;
	CH4_OffsetCal = ch.Ch4Avg;

	measf.Q_CH1 = 0.0;
	measf.Q_CH2 = 0.0;
}








/*****end low level functions***************************************************/

/*****begin higher level functions***********************************************/



// read one register and return the result
uint16_t ADS131A0xReadRegister(uint8_t RegAddress) {

	static uint16_t value = 0;

	uint16_t word = ADS131A0x_CMD_RREG | (RegAddress << 8);

	value = ADS131A0xSendCmd(word);

	//uint8_t ucBuf[128] = {};
	//snprintf((char*)ucBuf, sizeof(ucBuf), "RREG %lu Addr: %x, Word: %x, Value: %x ;\r\n", osKernelSysTick(), RegAddress, word, value);
	//CDC_Transmit_FS(ucBuf, strlen((const char *)ucBuf));

	return value;
}
//write single register function
uint16_t ADS131A0xWriteRegister(uint8_t addr, uint8_t data) {

	uint16_t word = ADS131A0x_CMD_WREG | (addr<<8) | data;

	uint16_t value = ADS131A0xSendCmd(word);

	//uint8_t ucBuf[128] = {};
	//snprintf((char*)ucBuf, sizeof(ucBuf), "WREG %lu Addr: %x,Value: %x, ret_val: %x;\r\n", osKernelSysTick(), addr, data, value);
	//CDC_Transmit_FS(ucBuf, strlen((const char *)ucBuf));

	return value;

}
// write a number of consecutive registers from a given array pointer
void ADS131A0xWriteMultiRegister(uint8_t addr, int NumRegs, uint8_t* pdata) {
	//TODO: implement function
}

void ADS131A0xInit(void){



	ch.Ch1Avg = 0;
	ch.Ch2Avg = 0;
	ch.Ch3Avg = 0;
	ch.Ch4Avg = 0;

	ch.Ch1Sum = 0;
	ch.Ch2Sum = 0;
	ch.Ch3Sum = 0;
	ch.Ch4Sum = 0;

	measf.Q_CH1 = 0.0;
	measf.Q_CH2 = 0.0;

	measf.EnergyCH1 = 0.0;
	measf.EnergyCH1 = 0.0;


	CH1_OffsetCal = 0;
	CH2_OffsetCal = 0;
	CH3_OffsetCal = 0;
	CH4_OffsetCal = 0;

	uint16_t res_unlocked;

	ADS131A0xReset();
//	ADS131A0xSetCS(0);
//	HAL_Delay(10);
	uint16_t status;
//	uint16_t status = ADS131A0xSendCmd(0x0000);
//	HAL_Delay(10);
//	ADS131A0xSetCS(1);
do{

	ADS131A0xSetCS(0);
	HAL_Delay(10);
	status = ADS131A0xSendCmd(0x0000);
	HAL_Delay(10);
	ADS131A0xSetCS(1);
HAL_Delay(50);
}
while(status != 0xff04);
	//device ready
	if(status == 0xff04) {
		//Unlock device
		res_unlocked = ADS131A0xSendCmd(ADS131A0x_CMD_UNLOCK);

		if(res_unlocked == ADS131A0x_CMD_UNLOCK) {
			//Read/write regs and check results
			ADS131A0xReadRegister(ADS131A0x_REG_A_SYS_CFG);

			ADS131A0xWriteRegister(ADS131A0x_REG_A_SYS_CFG, 0x60);

			ADS131A0xReadRegister(ADS131A0x_REG_A_SYS_CFG);

	//		ADS131A0xWriteRegister(ADS131A0x_REG_CLK1, 0x00);

	//		ADS131A0xWriteRegister(ADS131A0x_REG_CLK2, 0x25);

			ADS131A0xWriteRegister(ADS131A0x_REG_CLK1, 0x02);

			ADS131A0xWriteRegister(ADS131A0x_REG_CLK2, 0x25);

			ADS131A0xWriteRegister(ADS131A0x_REG_ADC_ENA, 0x0F);

			ADS131A0xSendCmd(ADS131A0x_CMD_WAKEUP);

			ADS131A0xSendCmd(ADS131A0x_CMD_LOCK);
		}

	}
	else {
		//TODO: report error
	}


}
t_ADS131A0xData ADS131A0xGetChannels(void){
	static uint8_t cnt;
	long val;

	ch.Status = ADS131A0x_DataBuf[0] << 8 | ADS131A0x_DataBuf[1];

//	ch.Ch1 = ((ADS131A0x_DataBuf[4] << 16) | (ADS131A0x_DataBuf[5] << 8) | (ADS131A0x_DataBuf[6]));
//	ch.Ch2 = ((ADS131A0x_DataBuf[8] << 16) | (ADS131A0x_DataBuf[9] << 8) | (ADS131A0x_DataBuf[10]));
//	ch.Ch3 = ((ADS131A0x_DataBuf[12] << 16) | (ADS131A0x_DataBuf[13] << 8) | (ADS131A0x_DataBuf[14]));
//	ch.Ch4 = ((ADS131A0x_DataBuf[16] << 16) | (ADS131A0x_DataBuf[17] << 8) | (ADS131A0x_DataBuf[18]));

	if (ADS131A0x_DataBuf[4] & 0x80)
	{
	val = 0xff;
	val = (val << 8) | ADS131A0x_DataBuf[4];
	val = (val << 8) | ADS131A0x_DataBuf[5];
	val = (val << 8) | ADS131A0x_DataBuf[6];
	ch.Ch1 = val;
	}
	else
	{
		ch.Ch1 = ((ADS131A0x_DataBuf[4] << 16) | (ADS131A0x_DataBuf[5] << 8) | (ADS131A0x_DataBuf[6]));
	}
	if (ADS131A0x_DataBuf[8] & 0x80)
	{
	val = 0xff;
	val = (val << 8) | ADS131A0x_DataBuf[8];
	val = (val << 8) | ADS131A0x_DataBuf[9];
	val = (val << 8) | ADS131A0x_DataBuf[10];
	ch.Ch2 = val;
	}
	else
	{
		ch.Ch2 = ((ADS131A0x_DataBuf[8] << 16) | (ADS131A0x_DataBuf[9] << 8) | (ADS131A0x_DataBuf[10]));
	}
	if (ADS131A0x_DataBuf[12] & 0x80)
	{
	val = 0xff;
	val = (val << 8) | ADS131A0x_DataBuf[12];
	val = (val << 8) | ADS131A0x_DataBuf[13];
	val = (val << 8) | ADS131A0x_DataBuf[14];
	ch.Ch3 = val;
	}
	else
	{
		ch.Ch3 = ((ADS131A0x_DataBuf[12] << 16) | (ADS131A0x_DataBuf[13] << 8) | (ADS131A0x_DataBuf[14]));
	}
	if (ADS131A0x_DataBuf[16] & 0x80)
	{
	val = 0xff;
	val = (val << 8) | ADS131A0x_DataBuf[16];
	val = (val << 8) | ADS131A0x_DataBuf[17];
	val = (val << 8) | ADS131A0x_DataBuf[18];
	ch.Ch4 = val;
	}
	else
	{
		ch.Ch4 = ((ADS131A0x_DataBuf[16] << 16) | (ADS131A0x_DataBuf[17] << 8) | (ADS131A0x_DataBuf[18]));
	}


	meas.CH1_Current[cnt] = ch.Ch1;

	meas.CH2_Current[cnt] = ch.Ch3;

	meas.CH2_Voltage[cnt] = ch.Ch2;

	meas.CH1_Voltage[cnt] = ch.Ch4;

	ch.Ch1Sum = ch.Ch1Sum + ch.Ch1;

	ch.Ch2Sum = ch.Ch2Sum + ch.Ch2;

	ch.Ch3Sum = ch.Ch3Sum + ch.Ch3;

	ch.Ch4Sum = ch.Ch4Sum + ch.Ch4;





	cnt++;
	if(cnt > BUFFER_SIZE)
	{
		cnt = 0;
//		ch.Ch1Avg = ch.Ch1Sum / BUFFER_SIZE - CH1_OffsetCal;
//		ch.Ch2Avg = ch.Ch2Sum / BUFFER_SIZE - CH2_OffsetCal;
//		ch.Ch3Avg = ch.Ch3Sum / BUFFER_SIZE - CH3_OffsetCal;
//		ch.Ch4Avg = ch.Ch4Sum / BUFFER_SIZE - CH4_OffsetCal;

		ch.Ch1Avg = ch.Ch1Sum / BUFFER_SIZE ;
		ch.Ch2Avg = ch.Ch2Sum / BUFFER_SIZE ;
		ch.Ch3Avg = ch.Ch3Sum / BUFFER_SIZE ;
		ch.Ch4Avg = ch.Ch4Sum / BUFFER_SIZE ;

		ch.Ch1Sum = 0;
		ch.Ch2Sum = 0;
		ch.Ch3Sum = 0;
		ch.Ch4Sum = 0;
	}
	else
	{
		return ch;
	}



//	measf.Ch1 = ((float)ch.Ch1Avg - CH1_OffsetCal) / 8388608.0 * 2.5 * 37.5 * 2.0 ;
	//measf.Ch2 = ((float)ch.Ch2Avg- CH2_OffsetCal) / 8388608.0 * 2.5 * 328.0;
//	measf.Ch3 = ((float)ch.Ch3Avg- CH3_OffsetCal) / 8388608.0 * 2.5 * 37.5 * 2.0 ;
	//measf.Ch4 = ((float)ch.Ch4Avg- CH4_OffsetCal) / 8388608.0 * 2.5 * 328.0;
	measf.Ch1 = interpolateValue(ch.Ch1Avg - CH1_OffsetCal, intLUT_I_CH2, floatLUT_I, LUT_SIZE_I);
	measf.Ch3 = interpolateValue(ch.Ch3Avg - CH3_OffsetCal, intLUT_I_CH1, floatLUT_I, LUT_SIZE_I);
	measf.Ch4 = interpolateValue(ch.Ch4Avg - CH4_OffsetCal, intLUT_V_CH1, floatLUT_V, LUT_SIZE_V);
	measf.Ch2 = interpolateValue(ch.Ch2Avg - CH2_OffsetCal, intLUT_V_CH2, floatLUT_V, LUT_SIZE_V);
//	measf.Ch2 = interpolateValue(ch.Ch2Avg- CH2_OffsetCal, intLUT_V_CH1, floatLUT_V_CH1);
	measf.P1 = measf.Ch3 * measf.Ch4;
	measf.P2 = measf.Ch1 * measf.Ch2;

//	if (measf.P1 / measf.P2 > 1.0)
//		measf.Eff = measf.P1 / measf.P2;
//	else
//		measf.Eff = measf.P2 / measf.P1;
//
//	if (measf.Ch3 >= 0.05)
//		measf.Q_CH1 = measf.Q_CH1 + measf.Ch3 * 0.001;
//
//	if (measf.Ch1 >= 0.05)
//		measf.Q_CH2 = measf.Q_CH2 + measf.Ch1 * 0.001;
//
//	if (measf.P1 >= 1.0)
//		measf.EnergyCH1 = measf.EnergyCH1 + measf.P1 * 0.001;
//
//	if (measf.P2 >= 1.0)
//		measf.EnergyCH2 = measf.EnergyCH2 + measf.P2 * 0.001;


	return ch;
}
void StartExtADC(void) {
	ADS131A0xInit();
	ADS131A0x_Init_Done = 1;
}



int movingAvg(int *ptrArrNumbers, long *ptrSum, int pos, int len, int nextNum)
{
  //Subtract the oldest number from the prev sum, add the new number
  *ptrSum = *ptrSum - ptrArrNumbers[pos] + nextNum;
  //Assign the nextNum to the position in the array
  ptrArrNumbers[pos] = nextNum;
  //return the average
  return *ptrSum / len;
}

float interpolateValue(int32_t input, int32_t* intLUT, float* fLUT, uint8_t LUT_Size)
{

	int i;
	static short MatchFound;

	float x0,y0,x1,y1;


	i = 0;
	MatchFound = 0;
	do {

		if ((*(intLUT + i + 1) >= input) && *(intLUT + i)  < input) {
			MatchFound = 1;
			x0 = (float)(*(intLUT + i));
			x1 = (float)(*(intLUT + i + 1));

			y0 = *(fLUT + i);
			y1 = *(fLUT + i + 1);


			return y0 + (y1 - y0)/(x1 - x0) * (input - x0) ;
		}
		i++;
		if (i > LUT_Size)

			return -255.0;

	} while (MatchFound != 1);

	return -255.0;

}



/*****end higher level functions*************************************************/
