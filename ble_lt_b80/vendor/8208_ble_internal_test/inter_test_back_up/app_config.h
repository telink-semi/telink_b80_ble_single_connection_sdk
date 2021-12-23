/********************************************************************************************************
 * @file     app_config.h
 *
 * @brief    for TLSR chips
 *
 * @author	 BLE Group
 * @date     May. 12, 2018
 *
 * @par      Copyright (c) Telink Semiconductor (Shanghai) Co., Ltd.
 *           All rights reserved.
 *           
 *			 The information contained herein is confidential and proprietary property of Telink 
 * 		     Semiconductor (Shanghai) Co., Ltd. and is available under the terms 
 *			 of Commercial License Agreement between Telink Semiconductor (Shanghai) 
 *			 Co., Ltd. and the licensee in separate contract or the terms described here-in. 
 *           This heading MUST NOT be removed from this file.
 *
 * 			 Licensees are granted free, non-transferable use of the information in this 
 *			 file under Mutual Non-Disclosure Agreement. NO WARRENTY of ANY KIND is provided. 
 *           
 *******************************************************************************************************/
#pragma once

/* Enable C linkage for C++ Compilers: */
#if defined(__cplusplus)
extern "C" {
#endif

#if(INTERNAL_TEST_MODE == TEST_INTERNAL_TEST_BACKUP)

/* Function Select -----------------------------------------------------------*/
#define BLE_REMOTE_PM_ENABLE			0
#define BLE_REMOTE_SECURITY_ENABLE      0
#define RC_BTN_ENABLE               	1
#define	KEY_PRESS_ENABLE				1
#define	LED_EN							1


/***firmware check***/
#define FIRMWARES_SIGNATURE_ENABLE      0
#define APP_DEFAULT_HID_BATTERY_OTA_SPP_ATTRIBUTE_TABLE		1

/* Matrix Key Configuration --------------------------------------------------*/
#if(KEY_PRESS_ENABLE)
	#define	SW1_GPIO				GPIO_PC4
	#define	SW2_GPIO				GPIO_PC5
	#define	SW3_GPIO				GPIO_PC6
	#define	SW4_GPIO				GPIO_PC7
	#define	SW5_GPIO				GPIO_PF0
	#define	SW6_GPIO				GPIO_PF1


	#define	PULL_WAKEUP_SRC_PC4		PM_PIN_PULLUP_1M
	#define	PULL_WAKEUP_SRC_PC5		PM_PIN_PULLUP_1M
	#define	PULL_WAKEUP_SRC_PC6		PM_PIN_PULLUP_1M
	#define	PULL_WAKEUP_SRC_PC7		PM_PIN_PULLUP_1M
	#define	PULL_WAKEUP_SRC_PF0		PM_PIN_PULLUP_1M
	#define	PULL_WAKEUP_SRC_PF1		PM_PIN_PULLUP_1M


	#define PC4_INPUT_ENABLE		1
	#define PC5_INPUT_ENABLE		1
	#define PC6_INPUT_ENABLE		1
	#define PC7_INPUT_ENABLE		1
	#define PF0_INPUT_ENABLE		1
	#define PF1_INPUT_ENABLE		1

#endif

/* System clock initialization -----------------------------------------------*/
#define CLOCK_SYS_CLOCK_HZ      16000000
enum{
	CLOCK_SYS_CLOCK_1S  = CLOCK_SYS_CLOCK_HZ,
	CLOCK_SYS_CLOCK_1MS = (CLOCK_SYS_CLOCK_1S / 1000),
	CLOCK_SYS_CLOCK_1US = (CLOCK_SYS_CLOCK_1S / 1000000),
};


/* WatchDog ------------------------------------------------------------------*/
#define MODULE_WATCHDOG_ENABLE	0
#define WATCHDOG_INIT_TIMEOUT	500  //Unit:ms


/* Simulate uart debug Interface ---------------------------------------------*/
#define SIMULATE_UART_EN       0
#define DEBUG_TX_PIN           GPIO_PB4
#define DEBUG_BAUDRATE         (115200)

#if(LED_EN)

	#define	LED_BLUE	GPIO_PB3
	#define	LED_GREEN	GPIO_PB4
	#define	LED_WHITE	GPIO_PB5
	#define	LED_RED		GPIO_PB6

#endif


/* Debug Interface -----------------------------------------------------------*/
#define  DEBUG_GPIO_ENABLE					1

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


		#define PA0_INPUT_ENABLE        0
		#define PA4_INPUT_ENABLE		0
		#define PA5_INPUT_ENABLE		0
		#define PA6_INPUT_ENABLE		0
		#define PA7_INPUT_ENABLE        0
		#define PB0_INPUT_ENABLE		0
		#define PB1_INPUT_ENABLE		0
		#define PB2_INPUT_ENABLE		0

		#define PD0_INPUT_ENABLE		0
		#define PD1_INPUT_ENABLE        0
		#define PD2_INPUT_ENABLE		0
		#define PD3_INPUT_ENABLE        0
		#define PD4_INPUT_ENABLE		0
		#define PD5_INPUT_ENABLE        0
		#define PD6_INPUT_ENABLE		0
		#define PD7_INPUT_ENABLE        0


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

/* Disable C linkage for C++ Compilers: */
#if defined(__cplusplus)
}
#endif

#endif	//endif of intertest ==
