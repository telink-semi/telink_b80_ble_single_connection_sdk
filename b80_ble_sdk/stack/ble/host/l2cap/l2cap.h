/********************************************************************************************************
 * @file     l2cap.h 
 *
 * @brief    for TLSR chips
 *
 * @author	 BLE Group
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

#ifndef _L2CAP_H
#define _L2CAP_H




typedef enum{
	CONN_PARAM_UPDATE_ACCEPT = 0x0000,
	CONN_PARAM_UPDATE_REJECT = 0x0001,
}conn_para_up_rsp;


typedef int (*l2cap_handler_t) (u16 conn, u8 * p);

/******************************* User Interface  ************************************/
void		bls_l2cap_requestConnParamUpdate (u16 min_interval, u16 max_interval, u16 latency, u16 timeout);  //Slave

void        bls_l2cap_setMinimalUpdateReqSendingTime_after_connCreate(int time_ms);

//GaoQiu add. use for register the function of user customize l2cap data packet process(CID == 0x0004).
/**
 * @Brief  : use for register user customize function of l2cap data handle
 * @Param  : p->
 * @Return : 1-> l2cap data has been handled by user
 *           0-> l2cap data will be handle by BLE stack
 */
void        blc_l2cap_register_customize_handler(l2cap_handler_t p);
void		blc_l2cap_register_handler (void *p);

int 		blc_l2cap_packet_receive (u16 connHandle, u8 * p);
int 		blc_l2cap_send_data (u16 cid, u8 *p, int n);

void 		blc_l2cap_reg_att_sig_hander(void *p);//signaling pkt proc



void 		blc_l2cap_SendConnParamUpdateResponse(u16 connHandle, int result);

#if CHANGE_NEW_CODE
	void blc_l2cap_initMtuBuffer(u8 *pMTU_rx_buff, u16 mtu_rx_size, u8 *pMTU_tx_buff, u16 mtu_tx_size);
#endif


#endif
//Master
