/********************************************************************************************************
 * @file	clock.h
 *
 * @brief	This is the header file for b89
 *
 * @author	Driver Group
 * @date	2020
 *
 * @par     Copyright (c) 2018, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *          All rights reserved.
 *
 *          Redistribution and use in source and binary forms, with or without
 *          modification, are permitted provided that the following conditions are met:
 *
 *              1. Redistributions of source code must retain the above copyright
 *              notice, this list of conditions and the following disclaimer.
 *
 *              2. Unless for usage inside a TELINK integrated circuit, redistributions
 *              in binary form must reproduce the above copyright notice, this list of
 *              conditions and the following disclaimer in the documentation and/or other
 *              materials provided with the distribution.
 *
 *              3. Neither the name of TELINK, nor the names of its contributors may be
 *              used to endorse or promote products derived from this software without
 *              specific prior written permission.
 *
 *              4. This software, with or without modification, must only be used with a
 *              TELINK integrated circuit. All other usages are subject to written permission
 *              from TELINK and different commercial license may apply.
 *
 *              5. Licensee shall be solely responsible for any claim to the extent arising out of or
 *              relating to such deletion(s), modification(s) or alteration(s).
 *
 *          THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 *          ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *          WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *          DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDER BE LIABLE FOR ANY
 *          DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *          (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *          LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 *          ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *          (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *          SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *******************************************************************************************************/
#pragma once


#include "compiler.h"
#include "register.h"
#include "gpio.h"


#define 	_ASM_NOP_			asm("tnop")

/**
 * @brief  instruction delay.
 */
#define		CLOCK_DLY_1_CYC    _ASM_NOP_
#define		CLOCK_DLY_2_CYC    _ASM_NOP_;_ASM_NOP_
#define		CLOCK_DLY_3_CYC    _ASM_NOP_;_ASM_NOP_;_ASM_NOP_
#define		CLOCK_DLY_4_CYC    _ASM_NOP_;_ASM_NOP_;_ASM_NOP_;_ASM_NOP_
#define		CLOCK_DLY_5_CYC    _ASM_NOP_;_ASM_NOP_;_ASM_NOP_;_ASM_NOP_;_ASM_NOP_
#define		CLOCK_DLY_6_CYC    _ASM_NOP_;_ASM_NOP_;_ASM_NOP_;_ASM_NOP_;_ASM_NOP_;_ASM_NOP_
#define		CLOCK_DLY_7_CYC    _ASM_NOP_;_ASM_NOP_;_ASM_NOP_;_ASM_NOP_;_ASM_NOP_;_ASM_NOP_;_ASM_NOP_
#define		CLOCK_DLY_8_CYC    _ASM_NOP_;_ASM_NOP_;_ASM_NOP_;_ASM_NOP_;_ASM_NOP_;_ASM_NOP_;_ASM_NOP_;_ASM_NOP_
#define		CLOCK_DLY_9_CYC    _ASM_NOP_;_ASM_NOP_;_ASM_NOP_;_ASM_NOP_;_ASM_NOP_;_ASM_NOP_;_ASM_NOP_;_ASM_NOP_;_ASM_NOP_
#define		CLOCK_DLY_10_CYC   _ASM_NOP_;_ASM_NOP_;_ASM_NOP_;_ASM_NOP_;_ASM_NOP_;_ASM_NOP_;_ASM_NOP_;_ASM_NOP_;_ASM_NOP_;_ASM_NOP_

/**
 * @brief select RC as system clock
 */
#ifndef SYSCLK_RC_CLOCK_EN
#define SYSCLK_RC_CLOCK_EN			0
#endif

extern unsigned char system_clk_type;


/**
 * @brief 	external XTAL type,
 * 			0- 24M , 1-48M
 */
#define  CLK_48M_XTAL_EN   			0

#define  VULTURE_A0   				0

/**
 * @brief 	crystal for different application
 */
typedef enum{
	EXTERNAL_XTAL_24M	= 0,
	EXTERNAL_XTAL_48M	= 1,
}XTAL_TypeDef;
/**
 * @brief system clock type, to optimize the code and reduce the code size, add bit8-bit10 and bit11,
 * |                 |                  |               |
 * | :-------------- | :--------------- | :------------ |
 * |      <11>       |     <10:8>       |    <7:0>      |
 * |reg_otp_paio<6>  |reg_otp_ctrl2<7:5>|      clk      |
 */
typedef enum{
	SYS_CLK_12M_Crystal = 0x00<<11|0x01<<8|0x44,
	SYS_CLK_16M_Crystal = 0x00<<11|0x02<<8|0x43,
	SYS_CLK_24M_Crystal = 0x00<<11|0x03<<8|0x42,
	SYS_CLK_32M_Crystal = 0x01<<11|0x05<<8|0x60,
	SYS_CLK_48M_Crystal = 0x01<<11|0x07<<8|0x20,


	SYS_CLK_24M_RC 	 = 0x00<<16|0x03<<8|0x00,
//	SYS_CLK_32M_RC 	 = 0x01,
//	SYS_CLK_48M_RC 	 = 0x02,
}SYS_CLK_TypeDef;

/**
 * @brief 32K clock type.
 */

typedef enum{
	CLK_32K_RC   =0,
	CLK_32K_XTAL =1,
}CLK_32K_TypeDef;

typedef enum{
	PROB_CLK_7816,
	PROB_CLK_32K,
	PROB_CLK_SYS,
	PROB_CLK_24M_RC,
	PROB_CLK_24M_XTAL,
	PROB_CLK_HS,
	PROB_CLK_STIMER,
	PROB_CLK_USBPHY,
}prob_clock_src_e;

/**
 * @brief       This function to select the system clock source.
 * @param[in]   SYS_CLK - the clock source of the system clock.
 * @return      none
 */
void clock_init(SYS_CLK_TypeDef SYS_CLK);

/**
 * @brief       This function to get the system clock source.
 * @param[in]   none
 * @return      system clock source
 */

static inline int clock_get_system_clk(void)
{
	return system_clk_type;
}

/**
 * @brief   This function serves to set 32k clock source.
 * @param   variable of 32k type.
 * @return  none.
 */
void clock_32k_init (CLK_32K_TypeDef src);

/**
 * @brief     This function performs to select 24M as the system clock source.
 * @param[in] none.
 * @return    none.
 */
void rc_24m_cal (void);

/**
 * @brief     This function performs to select 48M RC as the system clock source.
 * @param[in] none.
 * @return    none.
 */
void rc_48m_cal (void);

/**
 * @brief     This function performs to select 32K as the system clock source.
 * @param[in] none.
 * @return    none.
 */
void rc_32k_cal (void);

/**
 * @brief     This function performs to probe clock to IO.
 * @param[in] src - the clock source which you want to probe.
 * @param[in] pin - the pin to probe clock.exclude PA[1]/PA[2]/PA[3]/B[0]/B[1]/B[3]/PD[4]/PE[3:0]/PF[1:0]
 * @return    none.
 */
void clock_prob(prob_clock_src_e src, GPIO_PinTypeDef pin);

