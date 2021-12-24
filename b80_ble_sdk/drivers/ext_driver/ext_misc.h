/********************************************************************************************************
 * @file	ext_misc.h
 *
 * @brief	This is the header file for B85
 *
 * @author	Driver Group
 * @date	May 8,2018
 *
 * @par		Copyright (c) 2018, Telink Semiconductor (Shanghai) Co., Ltd.
 *			All rights reserved.
 *
 *          The information contained herein is confidential property of Telink
 *          Semiconductor (Shanghai) Co., Ltd. and is available under the terms
 *          of Commercial License Agreement between Telink Semiconductor (Shanghai)
 *          Co., Ltd. and the licensee or the terms described here-in. This heading
 *          MUST NOT be removed from this file.
 *
 *          Licensee shall not delete, modify or alter (or permit any third party to delete, modify, or
 *          alter) any information contained herein in whole or in part except as expressly authorized
 *          by Telink semiconductor (shanghai) Co., Ltd. Otherwise, licensee shall be solely responsible
 *          for any claim to the extent arising out of or relating to such deletion(s), modification(s)
 *          or alteration(s).
 *
 *          Licensees are granted free, non-transferable use of the information in this
 *          file under Mutual Non-Disclosure Agreement. NO WARRENTY of ANY KIND is provided.
 *
 *******************************************************************************************************/
#ifndef DRIVERS_8208_EXT_MISC_H_
#define DRIVERS_8208_EXT_MISC_H_
#include "../register.h"
#include "../compiler.h"
#include "../driver.h"

#define _attribute_ram_code_ _attribute_ram_code_sec_
#define _attribute_data_no_init_     _attribute_session_(".data_no_init")    //save retention ram size
/******************************* analog_end ********************************************************************/
/**
 * @brief   system Timer : 16Mhz, Constant
 */
enum{
	SYSTEM_TIMER_TICK_1US 		= 16,
	SYSTEM_TIMER_TICK_1MS 		= 16000,
	SYSTEM_TIMER_TICK_1S 		= 16000000,

	SYSTEM_TIMER_TICK_625US  	= 10000,  //625*16
	SYSTEM_TIMER_TICK_1250US 	= 20000,  //1250*16
};

/******************************* random_start ******************************************************************/
/**
 * @brief      This function performs to get a serial of random number.
 * @param[in]  len- the length of random number
 * @param[in]  data - the first address of buffer store random number in
 * @return     the result of a serial of random number..
 */
void generateRandomNum(int len, unsigned char *data);

unsigned short myrand(void);
/******************************* random_end ********************************************************************/


/******************************* watchdog_start ******************************************************************/
#define WATCHDOG_TIMEOUT_COEFF	18		//  check register definition, 0x622
/******************************* watchdog_end ********************************************************************/


/******************************* RF_start ******************************************************************/
#define			reg_system_tick_irq				reg_system_tick_irq_level
#define			reg_sys_timer_ctrl				reg_system_ctrl
#define			reg_timeout_nesn				reg_rf_ll_ctrl_1
#define			FLD_RF_IRQ_CRC					FLD_RF_IRQ_RX_CRC_2
#define			RF_1M_500K_PACKET_CRC_OK		RF_BLE_PACKET_CRC_OK
#define			rf_ble_set_crc					rf_set_ble_crc

void rf_ble_1m_param_init(void);
/******************************* RF_end ********************************************************************/


/******************************* dma_start ******************************************************************/

/**
 * @brief	ACL RX Data buffer length = maxRxOct + 21, then 16 Byte align
 *			maxRxOct + 21 = 4(DMA_len) + 2(BLE header) + maxRxOct + 4(MIC) + 3(CRC) + 8(ExtraInfor)
			RX buffer size must be be 16*n, due to MCU design
 */
//actually +21.The purpose of +22 is to deal with extreme situations. Due to DMA design,at least one byte buffer can not be unusable.
#define 	CAL_LL_ACL_RX_FIFO_SIZE(maxRxOct)	(((maxRxOct+22) + 15) / 16 *16)


/**
 * @brief	ACL TX Data buffer length = maxTxOct + 10, then 4 Byte align
 *			maxTxOct + 10 = 4(DMA_len) + 2(BLE header) + maxTxOct + 4(MIC)
			TX buffer size must be be 4*n, due to MCU design
 */
#define 	CAL_LL_ACL_TX_FIFO_SIZE(maxTxOct)	(((maxTxOct+10) + 3) / 4 *4)


/******************************* dma_end ******************************************************************/


/******************************* CLOCK_start ******************************************************************/
// check if the current time_tick is exceed span from ref time
//static inline u32 clock_time_exceed_tick(u32 ref, u32 span){
//	return ((u32)(clock_time() - ref) > span);
//}
static inline unsigned int clock_time_exceed_tick(unsigned int ref, unsigned int span){
	return ((unsigned int)(clock_time() - ref) > span);
}
/******************************* CLOCK_end ********************************************************************/



/******************************* stimer_start ******************************************************************/
enum {
	FLD_SYSTEM_TICK_IRQ_EN  = 		BIT(2),
};


enum{
	FLD_DMA_RPTR_MASK =			0x0F, // max 15
};

#define	    sys_tick_per_us   				16

/**
 * @brief    This function serves to set system timer capture tick.
 * @return  none
 */
void systimer_set_irq_capture(unsigned int sys_timer_tick);

/**
 * @brief    This function serves to get system timer capture tick.
 * @return  none
 */
static inline unsigned int systimer_get_irq_capture(void)
{
	return reg_system_tick_irq;
}

/**
 * @brief    This function serves to set system timer interrupt mask.
 * @return  none
 */
static inline void systimer_set_irq_mask(void)
{
	reg_system_irq_mask |= FLD_SYSTEM_TICK_IRQ_EN;
}

/**
 * @brief    This function serves to enable system timer interrupt.
 * @return  none
 */
static inline void systimer_irq_enable(void)
{
	reg_irq_mask |= FLD_IRQ_SYSTEM_TIMER;
}

/**
 * @brief    This function serves to disable system timer interrupt.
 * @return  none
 */
static inline void systimer_irq_disable(void)
{
	reg_irq_mask &= ~FLD_IRQ_SYSTEM_TIMER;
}

/**
 * @brief    This function serves to clear system timer interrupt status.
 * @return  none
 */
static inline void systimer_clr_irq_status(void)
{
	reg_irq_src = FLD_IRQ_SYSTEM_TIMER;
}

/**
 * @brief    This function serves to get system timer interrupt status.
 * @return  none
 */
static inline unsigned int systimer_get_irq_status(void)
{
	return reg_irq_src & FLD_IRQ_SYSTEM_TIMER;
}

static inline int tick1_exceed_tick2(unsigned int tick1, unsigned int tick2)
{
	return (unsigned int)(tick1 - tick2) < BIT(30);
}

/*
 * @brief     This function performs to get system timer tick.
 * @param[in] none.
 * @return    system timer tick value.
**/
static inline unsigned int sys_get_stimer_tick(void)
{
	return reg_system_tick; //same as API: clock_time()
}

/******************************* stimer_end ********************************************************************/


#include "../analog.h"
#define  analog_write_reg8  analog_write
#define  analog_read_reg8   analog_read

/******************************* analog_end ********************************************************************/


#define aeskey_reg_start		0x710				//attention: used in aes_ccm





/******************************* other ********************************************************************/
/**
 * @brief 	Multiple boot address enumeration
 */
typedef enum{
	MULTI_BOOT_ADDR_0x10000 	= 0x10000,	//64 K
	MULTI_BOOT_ADDR_0x20000 	= 0x20000,	//128 K
	MULTI_BOOT_ADDR_0x40000		= 0x40000,  //256 K
}multi_boot_addr_e;
/******************************* other ********************************************************************/

#endif



