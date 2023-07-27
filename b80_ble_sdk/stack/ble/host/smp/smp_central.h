/********************************************************************************************************
 * @file	smp_central.h
 *
 * @brief	This is the header file for BLE SDK
 *
 * @author	BLE GROUP
 * @date	06,2020
 *
 * @par     Copyright (c) 2020, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *
 *          Licensed under the Apache License, Version 2.0 (the "License");
 *          you may not use this file except in compliance with the License.
 *          You may obtain a copy of the License at
 *
 *              http://www.apache.org/licenses/LICENSE-2.0
 *
 *          Unless required by applicable law or agreed to in writing, software
 *          distributed under the License is distributed on an "AS IS" BASIS,
 *          WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *          See the License for the specific language governing permissions and
 *          limitations under the License.
 *
 *******************************************************************************************************/
/*
 * smp_central.h
 *
 *  Created on: 2018-12-4
 *      Author: Administrator
 */

#ifndef SMP_CENTRAL_H_
#define SMP_CENTRAL_H_



typedef struct {  //82
	u8		flag;
	u8		peer_addr_type;  //address used in link layer connection
	u8		peer_addr[6];

	u8 		peer_key_size;
	u8		peer_id_adrType; //peer identity address information in key distribution, used to identify
	u8		peer_id_addr[6];


	u8 		peer_ltk[16];      //peer_ltk[16]
	u8		random[8];  //8
	u16 	ediv;       //2
	u8 		rsvd[6];    //6

	u8		peer_irk[16];
	u8		peer_csrk[16];

}smp_m_param_save_t;

typedef struct {
	u8 bond_mark;
	u8 adr_type;
	u8 address[6];
} mac_adr_t;


//  6 byte slave_MAC   8 byte rand  2 byte ediv
// 16 byte ltk
#define PAIR_INFO_SECTOR_SIZE	 				64

#define PAIR_OFFSET_SLAVE_MAC	 				2

#define PAIR_OFFSET_RAND		 				8
#define PAIR_OFFSET_EDIV		 				16
#define PAIR_OFFSET_ATT			 				18   //ATT handle
#define PAIR_OFFSET_LTK			 				32
#define PAIR_OFFSET_IRK			 				48

#if (LL_MASTER_MULTI_CONNECTION)
	#define	PAIR_SLAVE_MAX_NUM            			8
#else
	#define	PAIR_SLAVE_MAX_NUM            			1
#endif


typedef struct {
	u8 curNum;
	u8 curIndex;
	u8 isBond_fastSmp;
	u8 rsvd;  //auto smp, no need SEC_REQ
	u32 bond_flash_idx[PAIR_SLAVE_MAX_NUM];  //mark paired slave mac address in flash
	mac_adr_t bond_device[PAIR_SLAVE_MAX_NUM];
} bond_slave_t;

typedef int  (*smp_finish_callback_t)(void);



#define SLAVE_TRIGGER_SMP_FIRST_PAIRING				0   	//first pair, slave send security_request to trigger master's pairing&encryption
#define MASTER_TRIGGER_SMP_FIRST_PAIRING			BIT(0)

#define SLAVE_TRIGGER_SMP_AUTO_CONNECT				0   	//auto connect, slave send security_request to trigger master's encryption
#define MASTER_TRIGGER_SMP_AUTO_CONNECT				BIT(1)





/******************************* User Interface  *****************************************/
void    blm_host_smp_setSecurityTrigger(u8 trigger);
u8		blm_host_smp_getSecurityTrigger(void);


/**
 * @brief      This function is used to config pairing security information address.
 * @param[in]  addr - Callback function triggered when SMP is completed.
 * @return     none.
 */
void 	blm_smp_configParingSecurityInfoStorageAddr (int addr);


/**
 * @brief      This function is used to deal smp function in master role.
 * @param[in]  conn_handle - connection handle
 * @param[in]  p - packet pointer
 * @return     none.
 */
void 	blm_host_smp_handler(u16 conn_handle, u8 *p);


/**
 * @brief      This function is used to search bonding message in slave role.
 * @param[in]  adr_type - address type
 * @param[in]  addr - data address
 * @return     status 0:success  other :fail.
 */
int 	tbl_bond_slave_search(u8 adr_type, u8 * addr);


/**
 * @brief      This function is used to delete bonding message in slave role.
 * @param[in]  adr_type - address type
 * @param[in]  addr - data address
 * @return     status 0:success  other :fail.
 */
int 	tbl_bond_slave_delete_by_adr(u8 adr_type, u8 *addr);


/**
 * @brief      This function is used to delete bonding message .
 * @param[in]  adr_type - address type
 * @param[in]  addr - data address
 * @return     none.
 */
void 	tbl_bond_slave_unpair_proc(u8 adr_type, u8 *addr);


/**
 * @brief      This function is used to delete bonding message in slave role.
 * @param[in]  adr_type - address type
 * @param[in]  addr - data address
 * @return     none.
 */
void	blm_smp_encChangeEvt(u8 status, u16 connhandle, u8 enc_enable);


/**
 * @brief      This function is used to register call back of system finish
 * @param[in]  cb - Callback function triggered when SMP is completed.
 * @return     none.
 */
void 	blm_smp_registerSmpFinishCb (smp_finish_callback_t cb);






/************************* Stack Interface, user can not use!!! ***************************/


int 	blc_smp_central_init (void);


#endif /* SMP_CENTRAL_H_ */
