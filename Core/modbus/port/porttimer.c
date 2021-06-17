/*
 * FreeModbus Libary: BARE Port
 * Copyright (C) 2006 Christian Walter <wolti@sil.at>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * File: $Id: porttimer.c,v 1.1 2006/08/22 21:35:13 wolti Exp $
 */

/* ----------------------- Platform includes --------------------------------*/
#include "port.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"
#include "stm32l4xx_hal.h"

extern TIM_HandleTypeDef htim16;
/* ----------------------- Start implementation -----------------------------*/
BOOL xMBPortTimersInit( USHORT usTim1Timerout50us ) //����50usʱ��
{
	
	TIM_OC_InitTypeDef sConfigOC;
	sConfigOC.OCMode = TIM_OCMODE_ACTIVE;
	sConfigOC.Pulse = usTim1Timerout50us;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
	sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
	HAL_TIM_OC_ConfigChannel(&htim16, &sConfigOC, TIM_CHANNEL_1);
	return TRUE;
}


void vMBPortTimersEnable(  ) //��ʱ��
{
	/* Clear IT flag */
	__HAL_TIM_CLEAR_IT(&htim16, TIM_IT_CC1);
	
	/* Reset counter */
	__HAL_TIM_SET_COUNTER(&htim16,0);

	/* Enable the TIM Update interrupt */
	__HAL_TIM_ENABLE_IT(&htim16, TIM_IT_CC1);

	/* Enable the Peripheral */
	__HAL_TIM_ENABLE(&htim16);
}

void vMBPortTimersDisable(  ) //�ر�ʱ��
{
	/* Enable the Peripheral */
	__HAL_TIM_DISABLE(&htim16);

	/* Clear IT flag */
	__HAL_TIM_CLEAR_IT(&htim16, TIM_IT_CC1);

	/* Reset counter */
	__HAL_TIM_SET_COUNTER(&htim16,0);
	
	/* Enable the TIM Update interrupt */
	__HAL_TIM_DISABLE_IT(&htim16, TIM_IT_CC1);
}

/* Create an ISR which is called whenever the timer has expired. This function
 * must then call pxMBPortCBTimerExpired( ) to notify the protocol stack that
 * the timer has expired.
 */
void prvvTIMERExpiredISR( void ) //��ʱ���ж��ڵ���
{
    ( void )pxMBPortCBTimerExpired(  );
}

