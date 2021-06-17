#include "mb.h"
#include "mbport.h"

#define NB_REG_INPUT_SIZE  10						///< Input register size
uint16_t MB_REG_INPUT_BUF[NB_REG_INPUT_SIZE] = {50,12,30,4,54,63,71,86,9,99};		///< Input register

#define NB_REG_HOLD_SIZE  10						///< Keep register size
uint16_t MB_REG_HOLD_BUF[NB_REG_HOLD_SIZE];			///< Holding register

/**
   * CMD3 callback function
   * @param pucRegBuffer stores the value of the read input register
   * @param usAddress The starting address of the input register to be read
   * @param usNRegs The number of input registers to be read
   * @return MB_ENOERR: success other: failure
 */
eMBErrorCode eMBRegInputCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs )
{
    int iRegIndex = usAddress - 1;

	// illegal detection
	if((iRegIndex + usNRegs) > NB_REG_INPUT_SIZE)
	{
		return MB_ENOREG;
	}

	// loop reading
	while( usNRegs > 0 )
	{
		*pucRegBuffer++ =
			( unsigned char )( MB_REG_INPUT_BUF[iRegIndex] >> 8 );
		*pucRegBuffer++ =
			( unsigned char )( MB_REG_INPUT_BUF[iRegIndex] & 0xFF );
		iRegIndex++;
		usNRegs--;
	}

	// Analog input register is changed
//	for(iRegIndex = 0; iRegIndex < NB_REG_INPUT_SIZE; iRegIndex++)
//	{
//		MB_REG_INPUT_BUF[iRegIndex]++;
//	}

    return MB_ENOERR;
}

/**
   * CMD3 callback function
   * @param pucRegBuffer stores the read holding register value
   * @param usAddress The holding register address to be read
   * @param usNRegs The number of holding registers to be read
   * @param eMode mode, read or write, this example only uses read
   * @return MB_ENOERR: success other: failure
 */
eMBErrorCode eMBRegHoldingCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs, eMBRegisterMode eMode )
{
    int iRegIndex = usAddress - 1;

	// illegal detection
	if((iRegIndex + usNRegs) > NB_REG_HOLD_SIZE)
	{
		return MB_ENOREG;
	}

	// loop reading
	while( usNRegs > 0 )
	{
		*pucRegBuffer++ =
			( unsigned char )( MB_REG_HOLD_BUF[iRegIndex] >> 8 );
		*pucRegBuffer++ =
			( unsigned char )( MB_REG_HOLD_BUF[iRegIndex] & 0xFF );
		iRegIndex++;
		usNRegs--;
	}

	// The analog holding register is changed
	for(iRegIndex = 0; iRegIndex < NB_REG_HOLD_SIZE; iRegIndex++)
	{
		MB_REG_HOLD_BUF[iRegIndex]++;
	}

    return MB_ENOERR;
}

/// Unused
eMBErrorCode eMBRegCoilsCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils, eMBRegisterMode eMode )
{
    return MB_ENOREG;
}

/// Unused
eMBErrorCode eMBRegDiscreteCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete )
{
    return MB_ENOREG;
}
