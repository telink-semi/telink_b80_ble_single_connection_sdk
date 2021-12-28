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
#define FLASH_SIZE_OPTION							FLASH_SIZE_OPTION_512K //very important, user need confirm !!!
#define BLE_APP_PM_ENABLE							1
#define PM_DEEPSLEEP_RETENTION_ENABLE            	0 //Todo SunWei
#define APP_SECURITY_ENABLE      					1



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
		//---------------  KeyMatrix PA0/PD4/PF0/PF1 -----------------------------
		#define	MATRIX_ROW_PULL					PM_PIN_PULLDOWN_100K
		#define	MATRIX_COL_PULL					PM_PIN_PULLUP_10K

			#define	KB_LINE_HIGH_VALID				0   //dirve pin output 0 when keyscan, scanpin read 0 is valid



			#define			CR_VOL_UP				0xf0
			#define			CR_VOL_DN				0xf1


			/**
			 *  @brief  Normal keyboard map
			 */
			#define		KB_MAP_NORMAL	{	{CR_VOL_UP,		VK_1},	 \
											{CR_VOL_DN,		VK_2}, }



			//////////////////// KEY CONFIG (EVK board) ///////////////////////////
			#define  KB_DRIVE_PINS  {GPIO_PF0, GPIO_PF1}
			#define  KB_SCAN_PINS   {GPIO_PA0, GPIO_PD4}

			//drive pin as gpio
			#define	PF0_FUNC				AS_GPIO
			#define	PF1_FUNC				AS_GPIO

			//drive pin need 100K pulldown
			#define	PULL_WAKEUP_SRC_PF0		MATRIX_ROW_PULL
			#define	PULL_WAKEUP_SRC_PF1		MATRIX_ROW_PULL

			//drive pin open input to read gpio wakeup level
			#define PF0_INPUT_ENABLE		1
			#define PF1_INPUT_ENABLE		1

			//scan pin as gpio
			#define	PA0_FUNC				AS_GPIO
			#define	PD4_FUNC				AS_GPIO

			//scan  pin need 10K pullup
			#define	PULL_WAKEUP_SRC_PA0		MATRIX_COL_PULL
			#define	PULL_WAKEUP_SRC_PD4		MATRIX_COL_PULL

		//scan pin open input to read gpio level
		#define PA0_INPUT_ENABLE		1
		#define PD4_INPUT_ENABLE		1

		#define		KB_MAP_NUM		KB_MAP_NORMAL
		#define		KB_MAP_FN			KB_MAP_NORMAL
#endif




#if(UI_LED_ENABLE)
		/**
		 *  @brief  Definition gpio for led
		 */
	#define	GPIO_LED_BLUE  	GPIO_PA4
	#define	GPIO_LED_GREEN	GPIO_PA5
	#define	GPIO_LED_WHITE	GPIO_PA6
	#define	GPIO_LED_RED		GPIO_PA7
	#define LED_ON_LEVAL 			1 		//gpio output high voltage to turn on led

	#define PA4_FUNC				AS_GPIO
	#define PA5_FUNC				AS_GPIO
	#define PA6_FUNC				AS_GPIO
	#define PA7_FUNC				AS_GPIO

	#define	PA4_OUTPUT_ENABLE		1
	#define	PA5_OUTPUT_ENABLE		1
	#define PA6_OUTPUT_ENABLE		1
	#define	PA7_OUTPUT_ENABLE		1
#endif








/**
 *  @brief  Definition for gpio debug
 */

#if(DEBUG_GPIO_ENABLE)
		#define PB0_FUNC				AS_GPIO //debug gpio chn1 : PB0
		#define PB1_FUNC				AS_GPIO //debug gpio chn2 : PB1
		#define PB2_FUNC				AS_GPIO //debug gpio chn3 : PB2
		#define PB3_FUNC                AS_GPIO //debug gpio chn4 : PB3
		#define PB4_FUNC				AS_GPIO //debug gpio chn5 : PB4
		#define PB5_FUNC				AS_GPIO //debug gpio chn6 : PB5
		#define PB6_FUNC				AS_GPIO //debug gpio chn7 : PB6
		#define PB7_FUNC				AS_GPIO //debug gpio chn0 : PB7

		#define PC0_FUNC				AS_GPIO //debug gpio chn8 : PC0
		#define PC1_FUNC                AS_GPIO //debug gpio chn9 : PC1
		#define PC2_FUNC				AS_GPIO //debug gpio chn10: PC2
		#define PC3_FUNC                AS_GPIO //debug gpio chn11: PC3
		#define PC4_FUNC				AS_GPIO //debug gpio chn12: PC4
		#define PC5_FUNC                AS_GPIO //debug gpio chn13: PC5
		#define PC6_FUNC				AS_GPIO //debug gpio chn14: PC6
		#define PC7_FUNC                AS_GPIO //debug gpio chn15: PC7

		#define GPIO_CHN0				GPIO_PB0
		#define GPIO_CHN1				GPIO_PB1
		#define GPIO_CHN2				GPIO_PB2
		#define GPIO_CHN3				GPIO_PB3
		#define GPIO_CHN4				GPIO_PB4
		#define GPIO_CHN5				GPIO_PB5
		#define GPIO_CHN6				GPIO_PB6
		#define GPIO_CHN7				GPIO_PB7

		#define GPIO_CHN8 				GPIO_PC0
		#define GPIO_CHN9 				GPIO_PC1
		#define GPIO_CHN10				GPIO_PC2
		#define GPIO_CHN11				GPIO_PC3
		#define GPIO_CHN12				GPIO_PC4
		#define GPIO_CHN13				GPIO_PC5
		#define GPIO_CHN14				GPIO_PC6
		#define GPIO_CHN15				GPIO_PC7

#endif  //end of DEBUG_GPIO_ENABLE








/////////////////// set default   ////////////////
#include "../common/default_config.h"

#endif //end of (FEATURE_TEST_MODE == xxx)
