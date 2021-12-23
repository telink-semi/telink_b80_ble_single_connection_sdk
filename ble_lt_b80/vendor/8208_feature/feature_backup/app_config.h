/********************************************************************************************************
 * @file	app_config.h
 *
 * @brief	This is the header file for BLE SDK
 *
 * @author	BLE GROUP
 * @date	12,2021
 *
 * @par     Copyright (c) 2020, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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



#include "../feature_config.h"

#if (FEATURE_TEST_MODE == TEST_FEATURE_BACKUP)

///////////////////////// Feature Configuration////////////////////////////////////////////////
/**
 *  @brief  Feature select in bLE Sample project
 */
#define BLE_APP_PM_ENABLE							1
#define PM_DEEPSLEEP_RETENTION_ENABLE            	0 //Todo SunWei
#define APP_SECURITY_ENABLE      					0



#define APP_DEFAULT_HID_BATTERY_OTA_ATTRIBUTE_TABLE			1


/**
 *  @brief  UI Configuration
 */
#define UI_LED_ENABLE          	 					1
#define	UI_KEYBOARD_ENABLE							1



/**
 *  @brief  DEBUG  Configuration
 */
#define DEBUG_GPIO_ENABLE							0





///////////////////////// System Clock  Configuration /////////////////////////////////////////
#define CLOCK_SYS_CLOCK_HZ      					16000000


#if (CLOCK_SYS_CLOCK_HZ == 16000000)
	#define SYS_CLK_TYPE  							SYS_CLK_16M_Crystal
#elif (CLOCK_SYS_CLOCK_HZ == 24000000)
	#define SYS_CLK_TYPE  							SYS_CLK_24M_Crystal
#elif(CLOCK_SYS_CLOCK_HZ == 32000000)
	#define SYS_CLK_TYPE  							SYS_CLK_32M_Crystal
#elif(CLOCK_SYS_CLOCK_HZ == 48000000)
	#define SYS_CLK_TYPE  							SYS_CLK_48M_Crystal
#else
	#error "unsupported system clock !"
#endif

enum{
	CLOCK_SYS_CLOCK_1S = CLOCK_SYS_CLOCK_HZ,
	CLOCK_SYS_CLOCK_1MS = (CLOCK_SYS_CLOCK_1S / 1000),
	CLOCK_SYS_CLOCK_1US = (CLOCK_SYS_CLOCK_1S / 1000000),
};








#if (UI_KEYBOARD_ENABLE)   // if test pure power, kyeScan GPIO setting all disabled
		//---------------  KeyMatrix PC4/PC5/PC6/PC7 -----------------------------
		#define	MATRIX_ROW_PULL					PM_PIN_PULLDOWN_100K
		#define	MATRIX_COL_PULL					PM_PIN_PULLUP_10K

			#define	KB_LINE_HIGH_VALID				0   //dirve pin output 0 when keyscan, scanpin read 0 is valid



			#define			CR_VOL_UP				0xf0
			#define			CR_VOL_DN				0xf1


			/**
			 *  @brief  Normal keyboard map
			 */
			#define		KB_MAP_NORMAL	{	{CR_VOL_DN,		VK_1},	 \
											{CR_VOL_UP,		VK_2}, }



			//////////////////// KEY CONFIG (EVK board) ///////////////////////////
			#define  KB_DRIVE_PINS  {GPIO_PC6, GPIO_PC7}
			#define  KB_SCAN_PINS   {GPIO_PC4, GPIO_PC5}

			//drive pin as gpio
			#define	PC6_FUNC				AS_GPIO
			#define	PC7_FUNC				AS_GPIO

			//drive pin need 100K pulldown
			#define	PULL_WAKEUP_SRC_PC6		MATRIX_ROW_PULL
			#define	PULL_WAKEUP_SRC_PC7		MATRIX_ROW_PULL

			//drive pin open input to read gpio wakeup level
			#define PC6_INPUT_ENABLE		1
			#define PC7_INPUT_ENABLE		1

			//scan pin as gpio
			#define	PC4_FUNC				AS_GPIO
			#define	PC5_FUNC				AS_GPIO

			//scan  pin need 10K pullup
			#define	PULL_WAKEUP_SRC_PC4		MATRIX_COL_PULL
			#define	PULL_WAKEUP_SRC_PC5		MATRIX_COL_PULL

		//scan pin open input to read gpio level
		#define PC4_INPUT_ENABLE		1
		#define PC5_INPUT_ENABLE		1

		#define		KB_MAP_NUM		KB_MAP_NORMAL
		#define		KB_MAP_FN			KB_MAP_NORMAL
#endif




#if(UI_LED_ENABLE)
		/**
		 *  @brief  Definition gpio for led
		 */
	#define	GPIO_LED_BLUE  	GPIO_PB3
	#define	GPIO_LED_GREEN	GPIO_PB4
	#define	GPIO_LED_WHITE	GPIO_PB5
	#define	GPIO_LED_RED		GPIO_PB6
	#define LED_ON_LEVAL 			1 		//gpio output high voltage to turn on led

	#define PB3_FUNC				AS_GPIO
	#define PB4_FUNC				AS_GPIO
	#define PB5_FUNC				AS_GPIO
	#define PB6_FUNC				AS_GPIO

	#define	PB3_OUTPUT_ENABLE		1
	#define	PB4_OUTPUT_ENABLE		1
	#define PB5_OUTPUT_ENABLE		1
	#define	PB6_OUTPUT_ENABLE		1
#endif


#if(UI_BUTTON_ENABLE)
/**
		 *  @brief  Definition gpio for button detection
		 */
		#define	SW1_GPIO				GPIO_PF0
		#define	SW2_GPIO				GPIO_PF1
		#define PF0_FUNC				AS_GPIO
		#define PF1_FUNC				AS_GPIO
		#define PF0_INPUT_ENABLE		1
		#define PF1_INPUT_ENABLE		1
		#define PULL_WAKEUP_SRC_PF0    PM_PIN_PULLUP_10K
		#define PULL_WAKEUP_SRC_PF1    PM_PIN_PULLUP_10K

#endif








/**
 *  @brief  Definition for gpio debug
 */

#if(DEBUG_GPIO_ENABLE)
		#define PA0_FUNC				AS_GPIO //debug gpio chn0 : PA0
		#define PA4_FUNC				AS_GPIO //debug gpio chn1 : PA4
		#define PA5_FUNC				AS_GPIO //debug gpio chn2 : PA5
		#define PA6_FUNC				AS_GPIO //debug gpio chn3 : PA6
		#define PA7_FUNC                AS_GPIO //debug gpio chn4 : PA7
		#define PB0_FUNC				AS_GPIO //debug gpio chn5 : PB0
		#define PB1_FUNC				AS_GPIO //debug gpio chn6 : PB1
		#define PB2_FUNC				AS_GPIO //debug gpio chn7 : PB2

		#define PD0_FUNC				AS_GPIO //debug gpio chn8 : PD0
		#define PD1_FUNC                AS_GPIO //debug gpio chn9 : PD1
		#define PD2_FUNC				AS_GPIO //debug gpio chn10: PD2
		#define PD3_FUNC                AS_GPIO //debug gpio chn11: PD3
		#define PD4_FUNC				AS_GPIO //debug gpio chn12: PD4
		#define PD5_FUNC                AS_GPIO //debug gpio chn13: PD5
		#define PD6_FUNC				AS_GPIO //debug gpio chn14: PD6
		#define PD7_FUNC                AS_GPIO //debug gpio chn15: PD7

		#define GPIO_CHN0				GPIO_PA0
		#define GPIO_CHN1				GPIO_PA4
		#define GPIO_CHN2				GPIO_PA5
		#define GPIO_CHN3				GPIO_PA6
		#define GPIO_CHN4				GPIO_PA7
		#define GPIO_CHN5				GPIO_PB0
		#define GPIO_CHN6				GPIO_PB1
		#define GPIO_CHN7				GPIO_PB2

		#define GPIO_CHN8 				GPIO_PD0
		#define GPIO_CHN9 				GPIO_PD1
		#define GPIO_CHN10				GPIO_PD2
		#define GPIO_CHN11				GPIO_PD3
		#define GPIO_CHN12				GPIO_PD4
		#define GPIO_CHN13				GPIO_PD5
		#define GPIO_CHN14				GPIO_PD6
		#define GPIO_CHN15				GPIO_PD7

#endif  //end of DEBUG_GPIO_ENABLE








/////////////////// set default   ////////////////
#include "../common/default_config.h"

#endif //end of (FEATURE_TEST_MODE == xxx)
