/********************************************************************************************************
 * @file     spp.h 
 *
 * @brief    for TLSR chips
 *
 * @author	 public@telink-semi.com;
 * @date     Sep. 18, 2015
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
/*
 * spp.h
 *
 *  Created on: 2016-11-3
 *      Author: Administrator
 */

#ifndef SPP_H_
#define SPP_H_


#define SPP_CMD_SET_ADV_INTV								0xFF01
#define SPP_CMD_SET_ADV_DATA								0xFF02

#define SPP_CMD_SET_ADV_ENABLE                             	0xFF0A
#define SPP_CMD_GET_BUF_SIZE								0xFF0C
#define SPP_CMD_SET_ADV_TYPE								0xFF0D
#define SPP_CMD_SET_ADV_ADDR_TYPE							0xFF0E
#define SPP_CMD_ADD_WHITE_LST_ENTRY							0xFF0F
#define SPP_CMD_DEL_WHITE_LST_ENTRY							0xFF10
#define SPP_CMD_RST_WHITE_LST								0xFF11
#define SPP_CMD_SET_FLT_POLICY								0xFF12
#define SPP_CMD_SET_DEV_NAME								0xFF13
#define SPP_CMD_GET_CONN_PARA								0xFF14
#define SPP_CMD_SET_CONN_PARA								0xFF15
#define SPP_CMD_GET_CUR_STATE								0xFF16
#define SPP_CMD_TERMINATE									0xFF17
#define SPP_CMD_RESTART_MOD									0xFF18
#define SPP_CMD_SET_ADV_DIRECT_ADDR							0xFF19
#define SPP_CMD_SEND_NOTIFY_DATA                            0xFF1C

extern volatile u8 isUartTxDone;
#define   Tr_clrUartTxDone()    (isUartTxDone = 0)
#define   Tr_SetUartTxDone()    (isUartTxDone = 1)
#define   Tr_isUartTxDone()     (!isUartTxDone)


typedef struct {
	u16 cmdId;
	u16 paramLen;
	u8  param[0];
} spp_cmd_t;


typedef struct {
	u8	token;
	u8  paramLen;
	u16 eventId;
	u8  param[0];
} spp_event_t;

/**
 * @brief		this function is used to process rx uart data to remote device.
 * @param[in]   p - data pointer
 * @param[in]   n - data length
 * @return      0 is ok
 */
int bls_uart_handler (u8 *p, int n);

/**
 * @brief		this function is used to process tx uart data to remote device.
 * @param[in]   header - hci event type
 * @param[in]   pEvent - event data
 * @return      0 is ok
 */
int spp_send_data (u32 header, spp_event_t * pEvt);

/**
 * @brief		this function is used to restart module.
 * @param[in]	none
 * @return      none
 */
void spp_restart_proc(void);

/**
 * @brief      BLE host event handler call-back.
 * @param[in]  h       event type
 * @param[in]  para    Pointer point to event parameter buffer.
 * @param[in]  n       the length of event parameter.
 * @return
 */
int app_host_event_callback (u32 h, u8 *para, int n);

#endif /* SPP_H_ */
