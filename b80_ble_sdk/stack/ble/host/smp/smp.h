/********************************************************************************************************
 * @file     smp.h
 *
 * @brief    This is the header file for BLE SDK
 *
 * @author	 BLE GROUP
 * @date         12,2021
 *
 * @par     Copyright (c) 2021, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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
 *******************************************************************************************************/

/*
 * ble_smp.h
 *
 *  Created on: 2016-9-27
 *      Author: Telink
 */

#ifndef BLE_SMP_H_
#define BLE_SMP_H_

#include <stack/ble/ble_common.h>


#define 		BOND_DEVICE_WHITELIST_MANAGEMANT_ENABLE		1


#ifndef			SMP_BONDING_DEVICE_MAX_NUM
#define 		SMP_BONDING_DEVICE_MAX_NUM					4
#endif


#if (LL_MASTER_MULTI_CONNECTION || LL_MASTER_SINGLE_CONNECTION)
	#define 		SMP_SLAVE_SAVE_PERR_LTK_ENABLE				1
#else
	#define 		SMP_SLAVE_SAVE_PERR_LTK_ENABLE				0
#endif


#define 		SMP_SAVE_PEER_CSRK_ENABLE					0

#if (SMP_SLAVE_SAVE_PERR_LTK_ENABLE)
	#define 		SMP_PARAM_NV_UNIT						96

	#define 		SMP_PARAM_INIT_CLEAR_MAGIN_ADDR 		3072
	#define 		SMP_PARAM_LOOP_CLEAR_MAGIN_ADDR 		3584

#else
	#define 		SMP_PARAM_NV_UNIT						64

	#define 		SMP_PARAM_INIT_CLEAR_MAGIN_ADDR 		3072  //64 * 48
	#define 		SMP_PARAM_LOOP_CLEAR_MAGIN_ADDR 		3520  //64 * 55 (56 device most)
#endif


#define			SMP_PARAM_NV_MAX_LEN						4096


extern 			int				SMP_PARAM_NV_ADDR_START;

#define			SMP_PARAM_NV_SEC_ADDR_START				(SMP_PARAM_NV_ADDR_START + SMP_PARAM_NV_MAX_LEN)
#define			SMP_PARAM_NV_SEC_ADDR_END				(SMP_PARAM_NV_SEC_ADDR_START + SMP_PARAM_NV_MAX_LEN - 1)


#ifndef SIMPLE_MULTI_MAC_EN
#define SIMPLE_MULTI_MAC_EN    1
#endif

#if SIMPLE_MULTI_MAC_EN
	extern u8 device_mac_index;
	#define DEVICE_INDEX_MASK            0x0F
	#define FLAG_SMP_PARAM_SAVE_BASE     (0x40 + (device_mac_index & DEVICE_INDEX_MASK))
#else
	#define FLAG_SMP_PARAM_SAVE_BASE     (0x40)
#endif
	#define FLAG_SMP_PARAM_MASK           0xC0
	#define FLAG_SMP_PARAM_VALID          0x40

//#define		FLAG_SMP_PARAM_SAVE_OK					0x5A  // 0101 1010
#define		FLAG_SMP_PARAM_SAVE_PENDING				0xCF//0x7B  // 0111 1011
#define		FLAG_SMP_PARAM_SAVE_ERASE				0x00  //


#define		FLAG_SMP_SECTOR_USE						0x3C
#define		FLAG_SMP_SECTOR_CLEAR					0x00

#define     FLASH_SECTOR_OFFSET						4080

#define		TYPE_WHITELIST							BIT(0)
#define		TYPE_RESOLVINGLIST						BIT(1)





#define SMP_STANDARD_PAIR   	0
#define SMP_FAST_CONNECT   		1

/* pairing phase stated define */
#define PAIRING_IDLE_PHASE                   0x00000000UL
#define PAIRING_FEARTURE_EXCHANGE_PHASE_OK   0x00000001UL
#define PAIRING_KEY_GENERATE_PHASE_OK        0x00000002UL
//#define  PAIRING_KEY_TRANSPORT_PHASE_OK      0x00000004UL

typedef union {
	struct{
		u8 bondingFlag : 2;
		u8 MITM : 1;
		u8 SC	: 1;
		u8 keyPress: 1;
		u8 rsvd: 3;
	};
	u8 authType;
}smp_authReq_t;

typedef union{
	struct {
		u8 encKey : 1;
		u8 idKey : 1;
		u8 sign  : 1;
		u8 linkKey : 1;
		u8 rsvd : 4;
	};
	u8 keyIni;
}smp_keyDistribution_t;

typedef struct{
	u8 code;  //req = 0x01; rsp = 0x02;
	u8 ioCapablity;
	u8 oobDataFlag;
	smp_authReq_t authReq;
	u8 maxEncrySize;

	smp_keyDistribution_t initKeyDistribution;
	smp_keyDistribution_t rspKeyDistribution;
}smp_paring_req_rsp_t;



typedef struct{
	u8  code; //0x04
	u16 randomValue[16];
}smp_paring_random_t;

typedef struct{
	u8  code; //0x03
	u16 confirmValue[16];
}smp_paring_confirm_t;

typedef struct{
	u8 code; // 0x05
	u8 reason;
}smp_paring_failed_t;

typedef struct{
	u8 code;//0x0b

	smp_authReq_t authReq;
}smp_secure_req_t;

typedef struct{
	u8  code;//0xa
	u8 	signalKey[16];
}smp_signal_info_t;

typedef struct{
	u8 code;//0x9
	u8 addrType;
	u8 bdAddr[6];
}smp_id_addr_info_t;

typedef struct{
	u8 code;//0x8
	u8 idResolveKey[16];
}smp_id_info_t;

typedef struct{
	u8  code;//0x7
	u16 edivPtr[2];
	u8 	masterRand[8];
}smp_master_id_t;

typedef struct{
	u8  code;//0x6
	u8 	LTK[16];
}smp_enc_info_t;

// -------add core 4.2 ------
typedef struct{
	u8  code;//0xc
	u8  publicKeyX[32];
	u8  publicKeyY[32];
}smp_paring_public_key_t;

typedef struct{
	u8  code;//0xd
	u8  DHKeyCheck[16];
}smp_DHkey_check_t;

typedef struct{
	u8  code;//0xe
	u8  notifyType;
}smp_key_notify_t;

/*
 * smp parameter about peer device.
 * */
typedef struct{
	u8		paring_enable;
	u8 		peer_addr_type;  //address used in link layer connection
	u8		peer_addr[6];

	u8		peer_key_size;   //bond and key_size
	u8		peer_id_address_type;//peer identity address information in key distribution, used to identify
	u8		peer_id_address[6];

	u8		paring_peer_rand[16];
	u8		paring_confirm[16];  //in security connection oob mode to keep peer random

	u8		peer_csrk[16];
	u8		peer_irk[16];	//stored in big endian
}smp_param_peer_t;



typedef struct {  //82
	u8		flag;
	u8		peer_addr_type;  //address used in link layer connection
	u8		peer_addr[6];

	u8 		peer_key_size;
	u8		peer_id_adrType; //peer identity address information in key distribution, used to identify
	u8		peer_id_addr[6];

	u8 		own_ltk[16];      //own_ltk[16]
	u8		peer_irk[16];
	u8		peer_csrk[16];

#if (SMP_SLAVE_SAVE_PERR_LTK_ENABLE)
	u8		peer_ltk[16];
	u8		peer_random[8];
	u16		peer_ediv;
#endif



}smp_param_save_t;

/*
 * smp parameter about own device.
 * */
typedef struct{
	smp_paring_req_rsp_t  	paring_req;
	smp_paring_req_rsp_t  	paring_rsp;
	u16						save_key_flag;
	smp_authReq_t			auth_req;
	u8						own_conn_type;  //current connection peer own type
	u8						own_conn_addr[6];
	u8						paring_tk[16];   // in security connection to keep own random
	u8						paring_confirm[16];  // in security connection oob mode to keep peer random
	u8						own_ltk[16];   //used for generate ediv and random
}smp_param_own_t;

u8 cur_enc_keysize;

typedef struct {
	/* data */
	u8 csrk[16];
	u32 signCounter;
} smp_secSigInfo_t;



#define  ADDR_NOT_BONDED	0xFF
#define  ADDR_NEW_BONDED	0xFE
#define  ADDR_DELETE_BOND	0xFD

#define  KEY_FLAG_IDLE		0xFF
#define  KEY_FLAG_NEW		0xFE
#define  KEY_FLAG_FAIL		0xFD


typedef struct {
	u8 maxNum;
	u8 curNum;
	u8 addrIndex;
	u8 keyIndex;
	//u8 dev_wl_en;
	//u8 dev_wl_maxNum;  //device in whilteList max number

	u32 bond_flash_idx[SMP_BONDING_DEVICE_MAX_NUM];  //mark paired slave mac address in flash
} bond_device_t;


typedef struct{
	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(5)_RFU(3)
	u16	l2capLen;
	u16	chanId;
	u8  opcode;
	u8 data[21];
}smp2llcap_type_t;



typedef void (*smp_check_handler_t)(u32);
typedef void (*smp_init_handler_t)(u8 *p);
typedef u8 * (*smp_info_handler_t)(void);
typedef void (*smp_bond_clean_handler_t)(void);
typedef int (*smp_enc_done_cb_t)(void);


extern smp_check_handler_t		func_smp_check; //HID on android 7.0
extern smp_init_handler_t		func_smp_init;
extern smp_info_handler_t		func_smp_info;
extern smp_bond_clean_handler_t func_bond_check_clean;
extern smp_enc_done_cb_t		func_smp_enc_done_cb;


extern smp_param_peer_t   	    smp_param_peer;
extern smp_param_own_t		    smp_param_own;

extern smp2llcap_type_t 		smpResSignalPkt;

typedef enum {
	JUST_WORKS,
	PK_RESP_INPUT,  // Initiator displays PK, responder inputs PK
	PK_INIT_INPUT,  // Responder displays PK, initiator inputs PK
	PK_BOTH_INPUT,  // Only input on both, both input PK
	OOB,             // OOB available on both sides
	NUMERIC_COMPARISON,

} stk_generationMethod_t;

// IO Capability Values
typedef enum {
	IO_CAPABILITY_DISPLAY_ONLY = 0,
	IO_CAPABILITY_DISPLAY_YES_NO,
	IO_CAPABILITY_KEYBOARD_ONLY,
	IO_CAPABILITY_NO_INPUT_NO_OUTPUT,
	IO_CAPABILITY_KEYBOARD_DISPLAY, // not used by secure simple pairing
	IO_CAPABILITY_UNKNOWN = 0xff
} io_capability_t;

/////////////////////////// smp method map table ///////////////////////////////////////
// horizontal: initiator capabilities
// vertial:    responder capabilities
static const stk_generationMethod_t gen_method_legacy[5][5] = {
	{ JUST_WORKS,      JUST_WORKS,       PK_INIT_INPUT,   JUST_WORKS,    PK_INIT_INPUT },
	{ JUST_WORKS,      JUST_WORKS,       PK_INIT_INPUT,   JUST_WORKS,    PK_INIT_INPUT },
	{ PK_RESP_INPUT,   PK_RESP_INPUT,    PK_BOTH_INPUT,   JUST_WORKS,    PK_RESP_INPUT },
	{ JUST_WORKS,      JUST_WORKS,       JUST_WORKS,      JUST_WORKS,    JUST_WORKS    },
	{ PK_RESP_INPUT,   PK_RESP_INPUT,    PK_INIT_INPUT,   JUST_WORKS,    PK_RESP_INPUT },
};

#if SECURE_CONNECTION_ENABLE
/////////////////////////// smp method map table ///////////////////////////////////////
static const stk_generationMethod_t gen_method_sc[5][5] = {
	{ JUST_WORKS,      JUST_WORKS,       	PK_INIT_INPUT,   JUST_WORKS,    PK_INIT_INPUT },
	{ JUST_WORKS,      NUMERIC_COMPARISON,  PK_INIT_INPUT,   JUST_WORKS,    NUMERIC_COMPARISON },
	{ PK_RESP_INPUT,   PK_RESP_INPUT,   	PK_BOTH_INPUT,   JUST_WORKS,    PK_RESP_INPUT },
	{ JUST_WORKS,      JUST_WORKS,       	JUST_WORKS,      JUST_WORKS,    JUST_WORKS    },
	{ PK_RESP_INPUT,   NUMERIC_COMPARISON,  PK_INIT_INPUT,   JUST_WORKS,    NUMERIC_COMPARISON },
};

typedef u8* (* smp_sc_cmd_handler_t)(u16 conn, u8*p);
typedef void (* smp_sc_pushPkt_handler_t)( u32 type );

extern smp_sc_cmd_handler_t		 func_smp_sc_cmd_proc;
extern smp_sc_pushPkt_handler_t  func_smp_sc_pushPkt_proc;

extern	const	u8	PublicKey[64];
extern	const	u8	PrivateKey[32];

typedef struct{
	u8 sc_sk_dhk_own[32];  // keep sk before receive Ea. and keep dhkey after that.
	u8 sc_prk_own[32];     // own  private key
	u8 sc_pk_own[64];      // own  public key
	u8 sc_pk_peer[64];     // peer public key
}smp_sc_key_t;

extern smp_sc_key_t smp_sc_key;

#endif

#define IO_CAPABLITY_DISPLAY_ONLY		0x00
#define IO_CAPABLITY_DISPLAY_YESNO		0x01
#define IO_CAPABLITY_KEYBOARD_ONLY		0x02
#define IO_CAPABLITY_NO_IN_NO_OUT		0x03
#define IO_CAPABLITY_KEYBOARD_DISPLAY	0x04

#define PASSKEY_TYPE_ENTRY_STARTED		0x00
#define PASSKEY_TYPE_DIGIT_ENTERED		0x01
#define PASSKEY_TYPE_DIGIT_ERASED		0x02
#define PASSKEY_TYPE_CLEARED			0x03
#define PASSKEY_TYPE_ENTRY_COMPLETED	0x04

#define PAIRING_FAIL_REASON_PASSKEY_ENTRY			0x01
#define PAIRING_FAIL_REASON_OOB_NOT_AVAILABLE		0x02
#define PAIRING_FAIL_REASON_AUTH_REQUIRE				0x03
#define PAIRING_FAIL_REASON_CONFIRM_FAILED			0x04
#define PAIRING_FAIL_REASON_PAIRING_NOT_SUPPORTED		0x05
#define PAIRING_FAIL_REASON_ENCRYPT_KEY_SIZE			0x06
//-- core 4.2
#define PAIRING_FAIL_REASON_CMD_NOT_SUPPORT			0x07
#define PAIRING_FAIL_REASON_UNSPECIFIED_REASON		0x08
#define PAIRING_FAIL_REASON_REPEATED_ATTEMPT			0x09
#define PAIRING_FAIL_REASON_INVAILD_PARAMETER		0x0a
#define PAIRING_FAIL_REASON_DHKEY_CHECK_FAIL			0x0b
#define PAIRING_FAIL_REASON_NUMUERIC_FAILED			0x0c
#define PAIRING_FAIL_REASON_BREDR_PAIRING				0x0d
#define PAIRING_FAIL_REASON_CROSS_TRANSKEY_NOT_ALLOW		0x0e

#define	ENCRYPRION_KEY_SIZE_MAXINUM				16
#define	ENCRYPRION_KEY_SIZE_MINIMUN				7

typedef enum{
	SMP_PAIRING_DISABLE_TRRIGER = 0,
	SMP_PAIRING_CONN_TRRIGER ,
	SMP_PAIRING_PEER_TRRIGER,
}smp_pairingTrriger_t;














/////////////////////////////////////////////////////////////////////////////////////////////////
//								SLAVE
/////////////////////////////////////////////////////////////////////////////////////////////////


/******************************* User Interface  ************************************/


/**************************************************
 * API used for slave enable the device pairing.
 * encrypt_en	SMP_PAIRING_DISABLE_TRRIGER   -  not allow encryption
 * 				SMP_PAIRING_CONN_TRRIGER      -  pairing process start once connect.
 * 				SMP_PAIRING_PEER_TRRIGER      -  pairing process start once peer device start.
 */
int 		bls_smp_enableParing (smp_pairingTrriger_t encrypt_en);



void 		blc_smp_configPairingSecurityInfoStorageAddress (int addr);

ble_sts_t  	blc_smp_param_setBondingDeviceMaxNumber ( int device_num);

u8			blc_smp_param_getCurrentBondingDeviceNumber(void);


u32 		blc_smp_param_loadByIndex(u8 index, smp_param_save_t* smp_param_load);

u32			blc_smp_param_loadByAddr(u8 addr_type, u8* addr, smp_param_save_t* smp_param_load);

extern int	blc_smp_param_deleteByIndex(u8 index);
extern bool blc_smp_param_delete(u8 peerAddrType, u8 *peerAddr);
extern void blc_smp_param_delete_all(void);



/*************************************************
 * 	used for enable oob flag
 */
void blc_smp_enableOobFlag (int en, u8 *oobData);

/*************************************************
 * 	used for set MAX key size
 * */
void blc_smp_setMaxKeySize (u8 maxKeySize);

/*************************************************
 * 	@brief 		used for enable authentication MITM
 * 	@return  	0 - setting success
 * 				others - pin code not in ranged.(0 ~ 999,999)
 */
int blc_smp_enableAuthMITM (int en, u32 pinCodeInput);

/*************************************************
 * 	@brief 		used for set MITM protect input pinCode
 * 	@return  	0 - setting failure
 * 				others - pin code in ranged.(0 ~ 999,999)
 */
int blc_smp_set_pinCode(u32 pinCodeInput);

/*************************************************
 * 	@brief 		used for enable authentication bonding flag.
 */
int blc_smp_enableBonding (int en);

/*************************************************
 * 	used for set IO capability
 * */
void blc_smp_setIoCapability (u8 ioCapablility);


#if (SECURE_CONNECTION_ENABLE)
/*************************************************
 * 	used for enable sc flag
 * */
void blc_smp_enableScFlag (int en);
/*************************************************
 * 	used for enable sc only
 * 	set sc only.if master do not support sc,
 * 	slave disconnect the link layer
 * */
void set_smp_sc_only(u8 flg);

/*************************************************
 * 	used for ecdh debug mode
 * */
u8   blc_smp_getEcdhDebugMode(void);
void blc_smp_setEcdhDebugMode(u8 mode);
#endif



/*
 * API used for set distribute key enable.
 * */
smp_keyDistribution_t blc_smp_setInitiatorKey (u8 LTK_distributeEn, u8 IRK_distributeEn, u8 CSRK_DistributeEn);
smp_keyDistribution_t blc_smp_setResponderKey (u8 LTK_distributeEn, u8 IRK_distributeEn, u8 CSRK_DistributeEn);







#endif /* BLE_SMP_H_ */
