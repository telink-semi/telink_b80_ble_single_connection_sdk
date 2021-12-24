/********************************************************************************************************
 * @file     ble_common.h 
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
#ifndef BLE_COMMON_H
#define BLE_COMMON_H

#include "tl_common.h"





#if 0

typedef enum {
    BLE_SUCCESS = 0,
    
    // HCI Status, Per the Bluetooth Core Specification, V4.0.0, Vol. 2, Part D.
    HCI_ERR_UNKNOWN_HCI_CMD                                        = 0x01,
    HCI_ERR_UNKNOWN_CONN_ID                                        = 0x02,
    HCI_ERR_HW_FAILURE                                             = 0x03,
    HCI_ERR_PAGE_TIMEOUT                                           = 0x04,
    HCI_ERR_AUTH_FAILURE                                           = 0x05,
    HCI_ERR_PIN_KEY_MISSING                                        = 0x06,
    HCI_ERR_MEM_CAP_EXCEEDED                                       = 0x07,
    HCI_ERR_CONN_TIMEOUT                                           = 0x08,
    HCI_ERR_CONN_LIMIT_EXCEEDED                                    = 0x09,
    HCI_ERR_SYNCH_CONN_LIMIT_EXCEEDED                              = 0x0A,
    HCI_ERR_ACL_CONN_ALREADY_EXISTS                                = 0x0B,
    HCI_ERR_CMD_DISALLOWED                                         = 0x0C,
    HCI_ERR_CONN_REJ_LIMITED_RESOURCES                             = 0x0D,
    HCI_ERR_CONN_REJECTED_SECURITY_REASONS                         = 0x0E,
    HCI_ERR_CONN_REJECTED_UNACCEPTABLE_BDADDR                      = 0x0F,
    HCI_ERR_CONN_ACCEPT_TIMEOUT_EXCEEDED                           = 0x10,
    HCI_ERR_UNSUPPORTED_FEATURE_PARAM_VALUE                        = 0x11,
    HCI_ERR_INVALID_HCI_CMD_PARAMS                                 = 0x12,
    HCI_ERR_REMOTE_USER_TERM_CONN                                  = 0x13,
    HCI_ERR_REMOTE_DEVICE_TERM_CONN_LOW_RESOURCES                  = 0x14,
    HCI_ERR_REMOTE_DEVICE_TERM_CONN_POWER_OFF                      = 0x15,
    HCI_ERR_CONN_TERM_BY_LOCAL_HOST                                = 0x16,
    HCI_ERR_REPEATED_ATTEMPTS                                      = 0x17,
    HCI_ERR_PAIRING_NOT_ALLOWED                                    = 0x18,
    HCI_ERR_UNKNOWN_LMP_PDU                                        = 0x19,
    HCI_ERR_UNSUPPORTED_REMOTE_FEATURE                             = 0x1A,
    HCI_ERR_SCO_OFFSET_REJ                                         = 0x1B,
    HCI_ERR_SCO_INTERVAL_REJ                                       = 0x1C,
    HCI_ERR_SCO_AIR_MODE_REJ                                       = 0x1D,
    HCI_ERR_INVALID_LMP_PARAMS                                     = 0x1E,
    HCI_ERR_UNSPECIFIED_ERROR                                      = 0x1F,
    HCI_ERR_UNSUPPORTED_LMP_PARAM_VAL                              = 0x20,
    HCI_ERR_ROLE_CHANGE_NOT_ALLOWED                                = 0x21,
    HCI_ERR_LMP_LL_RESP_TIMEOUT                                    = 0x22,
    HCI_ERR_LMP_ERR_TRANSACTION_COLLISION                          = 0x23,
    HCI_ERR_LMP_PDU_NOT_ALLOWED                                    = 0x24,
    HCI_ERR_ENCRYPT_MODE_NOT_ACCEPTABLE                            = 0x25,
    HCI_ERR_LINK_KEY_CAN_NOT_BE_CHANGED                            = 0x26,
    HCI_ERR_REQ_QOS_NOT_SUPPORTED                                  = 0x27,
    HCI_ERR_INSTANT_PASSED                                         = 0x28,
    HCI_ERR_PAIRING_WITH_UNIT_KEY_NOT_SUPPORTED                    = 0x29,
    HCI_ERR_DIFFERENT_TRANSACTION_COLLISION                        = 0x2A,
    HCI_ERR_RESERVED1                                              = 0x2B,
    HCI_ERR_QOS_UNACCEPTABLE_PARAM                                 = 0x2C,
    HCI_ERR_QOS_REJ                                                = 0x2D,
    HCI_ERR_CHAN_ASSESSMENT_NOT_SUPPORTED                          = 0x2E,
    HCI_ERR_INSUFFICIENT_SECURITY                                  = 0x2F,
    HCI_ERR_PARAM_OUT_OF_MANDATORY_RANGE                           = 0x30,
    HCI_ERR_RESERVED2                                              = 0x31,
    HCI_ERR_ROLE_SWITCH_PENDING                                    = 0x32,
    HCI_ERR_RESERVED3                                              = 0x33,
    HCI_ERR_RESERVED_SLOT_VIOLATION                                = 0x34,
    HCI_ERR_ROLE_SWITCH_FAILED                                     = 0x35,
    HCI_ERR_EXTENDED_INQUIRY_RESP_TOO_LARGE                        = 0x36,
    HCI_ERR_SIMPLE_PAIRING_NOT_SUPPORTED_BY_HOST                   = 0x37,
    HCI_ERR_HOST_BUSY_PAIRING                                      = 0x38,
    HCI_ERR_CONN_REJ_NO_SUITABLE_CHAN_FOUND                        = 0x39,
    HCI_ERR_CONTROLLER_BUSY                                        = 0x3A,
    HCI_ERR_UNACCEPTABLE_CONN_INTERVAL                             = 0x3B,
    HCI_ERR_DIRECTED_ADV_TIMEOUT                                   = 0x3C,
    HCI_ERR_CONN_TERM_MIC_FAILURE                                  = 0x3D,
    HCI_ERR_CONN_FAILED_TO_ESTABLISH                               = 0x3E,
    HCI_ERR_MAC_CONN_FAILED                                        = 0x3F,
    HCI_ERR_COARSE_CLOCK_ADJUSTMENT_REJECT						   = 0x40,
    HCI_ERR_TYPE0_SUBMAP_NOT_DEFINED							   = 0x41,
	HCI_ERR_UNKNOWN_ADV_IDENTIFIER								   = 0x42,
    HCI_ERR_LIMIT_REACHED										   = 0x43,
    HCI_ERR_OP_CANCELLED_BY_HOST								   = 0x44,
    HCI_ERR_PACKET_TOO_LONG										   = 0x45,

    

    //telink define
    HCI_ERR_CONTROLLER_TX_FIFO_NOT_ENOUGH						   = HCI_ERR_CONTROLLER_BUSY,  //0x3A
    HCI_ERR_CONN_NOT_ESTABLISH									   = HCI_ERR_CONN_FAILED_TO_ESTABLISH,  //0x3E
	HCI_ERR_CURRENT_STATE_NOT_SUPPORTED_THIS_CMD 				   = HCI_ERR_CONTROLLER_BUSY,
    


    LL_ERR_START = 0x50,
	LL_ERR_WHITE_LIST_PUBLIC_ADDR_TABLE_FULL,                        //!< The white list public addr table full
	LL_ERR_WHITE_LIST_PRIVATE_RESOLVABLE_IRK_TABLE_FULL,
	LL_EER_FEATURE_NOT_SUPPORTED,
	LL_ERR_SUPVERVISION_TIMEOUT,
	LL_ERR_IRK_NOT_FOUND_FOR_RANDOM_ADDR,
	LL_ERR_ADDR_NOT_EXIST_IN_WHITE_LIST,
	LL_ERR_ADDR_ALREADY_EXIST_IN_WHITE_LIST,
	LL_ERR_WHITE_LIST_NV_DISABLED,
	LL_ERR_CURRENT_DEVICE_ALREADY_IN_CONNECTION_STATE,
	//Telink
	LL_ERR_CONNECTION_NOT_ESTABLISH,
	LL_ERR_TX_FIFO_NOT_ENOUGH,
	LL_ERR_ENCRYPTION_BUSY,
	LL_ERR_CURRENT_STATE_NOT_SUPPORTED_THIS_CMD,
	LL_ERR_INVALID_PARAMETER,
	LL_ERR_UNKNOWN_OPCODE,

	LL_ERR_CIS_SYNC_FAIL,
	LL_ERR_CIS_DISCONNECT,
    

    

    SMP_EER_MUX_EXCCED = 0xA0,                          //!< The AUTOPEND pending all is turned on
    SMP_EER_INVALID_PACKET_LEN,                         //!< The AUTOPEND pending all is turned off 
    SMP_EER_INVALID_STATE,                              //!< received cmd in invalid state 
    SMP_EER_USER_CANCEL,                                //!< user channcel status  
    SMP_EER_SEC_FAILED,                                 //!< The l2cap was not able to enter low power mode. 
    SMP_EER_INVALID_HANDLE,                             //!< The purge request contained an invalid handle 
    SMP_EER_INVALID_PARAMETER,                          //!< The API function parameter is out of range 
    SMP_EER_UNSUPPORTED,                                //!< The operation is not supported in the current configuration 
    SMP_EER_BAD_STATE,                                  //!< The operation could not be performed in the current state 
    SMP_EER_NO_RESOURCES,                               //!< The operation could not be completed because no memory resources were available 
    SMP_EER_TIME_OUT,                                   //!< The operation is time out 
    SMP_EER_NO_HANDLER,                                 //!< The operation is time out 
    SMP_EER_LEN_NOT_MATCH,                              //!< The operation is time out 
    SMP_EER_NOT_FOUND,                                  //!< The operation is time out 
    SMP_EER_LINK_IS_ENCY,
    SMP_EER_PAIRING_IS_GOING_ON,
    SMP_EER_SIG_VERIFY_FAIL,                            //!< The operation is time out 
    SMP_EER_SIG_FAIL,                                   //!< The singature is failed
    SMP_EER_NO_SIGN_KEY,
    SMP_EER_ADDR_RESOLVE_FAIL,                          //!< The operation is time out 

    
	//GATT status
	GATT_ERR_INVALID_PARAMETER 									   = 0xB0,
	GATT_ERR_PREVIOUS_INDICATE_DATA_HAS_NOT_CONFIRMED,
	GATT_ERR_SERVICE_DISCOVERY_TIEMOUT,
	GATT_ERR_NOTIFY_INDICATION_NOT_PERMITTED,
	GATT_ERR_DATA_PENDING_DUE_TO_SERVICE_DISCOVERY_BUSY,
	GATT_ERR_DATA_LENGTH_EXCEED_MTU_SIZE,


	BLE_COMMON_ERR_START = 0xD0,
    BLE_ERR_DUPLICATE_PACKET,
	BLE_ERR_INVALID_STATE,
	BLE_ERR_INVALID_PARAMETER,
	BLE_ERR_NO_RESOURCE,

	//Application buffer check error code
	LL_ACL_RX_BUF_NO_INIT 							   	  		   = 0xE0,
	LL_ACL_RX_BUF_PARAM_INVALID,
	LL_ACL_RX_BUF_SIZE_NOT_MEET_MAX_RX_OCT,
	LL_ACL_TX_BUF_NO_INIT,
	LL_ACL_TX_BUF_PARAM_INVALID,
	LL_ACL_TX_BUF_SIZE_MUL_NUM_EXCEED_4K,
	LL_ACL_TX_BUF_SIZE_NOT_MEET_MAX_TX_OCT,
} ble_sts_t;

#else

typedef enum {
    BLE_SUCCESS = 0,

//// HCI Status, See the Core_v5.0(Vol 2/Part D/1.3 "list of Error Codes") for more information)
    HCI_ERR_UNKNOWN_HCI_CMD                                        = 0x01,
    HCI_ERR_UNKNOWN_CONN_ID                                        = 0x02,
    HCI_ERR_HW_FAILURE                                             = 0x03,
    HCI_ERR_PAGE_TIMEOUT                                           = 0x04,
    HCI_ERR_AUTH_FAILURE                                           = 0x05,
    HCI_ERR_PIN_KEY_MISSING                                        = 0x06,
    HCI_ERR_MEM_CAP_EXCEEDED                                       = 0x07,
    HCI_ERR_CONN_TIMEOUT                                           = 0x08,
    HCI_ERR_CONN_LIMIT_EXCEEDED                                    = 0x09,
    HCI_ERR_SYNCH_CONN_LIMIT_EXCEEDED                              = 0x0A,
    HCI_ERR_ACL_CONN_ALREADY_EXISTS                                = 0x0B,
    HCI_ERR_CMD_DISALLOWED                                         = 0x0C,
    HCI_ERR_CONN_REJ_LIMITED_RESOURCES                             = 0x0D,
    HCI_ERR_CONN_REJECTED_SECURITY_REASONS                         = 0x0E,
    HCI_ERR_CONN_REJECTED_UNACCEPTABLE_BDADDR                      = 0x0F,
    HCI_ERR_CONN_ACCEPT_TIMEOUT_EXCEEDED                           = 0x10,
    HCI_ERR_UNSUPPORTED_FEATURE_PARAM_VALUE                        = 0x11,
    HCI_ERR_INVALID_HCI_CMD_PARAMS                                 = 0x12,
    HCI_ERR_REMOTE_USER_TERM_CONN                                  = 0x13,
    HCI_ERR_REMOTE_DEVICE_TERM_CONN_LOW_RESOURCES                  = 0x14,
    HCI_ERR_REMOTE_DEVICE_TERM_CONN_POWER_OFF                      = 0x15,
    HCI_ERR_CONN_TERM_BY_LOCAL_HOST                                = 0x16,
    HCI_ERR_REPEATED_ATTEMPTS                                      = 0x17,
    HCI_ERR_PAIRING_NOT_ALLOWED                                    = 0x18,
    HCI_ERR_UNKNOWN_LMP_PDU                                        = 0x19,
    HCI_ERR_UNSUPPORTED_REMOTE_FEATURE                             = 0x1A,
    HCI_ERR_SCO_OFFSET_REJ                                         = 0x1B,
    HCI_ERR_SCO_INTERVAL_REJ                                       = 0x1C,
    HCI_ERR_SCO_AIR_MODE_REJ                                       = 0x1D,
    HCI_ERR_INVALID_LMP_PARAMS                                     = 0x1E,
    HCI_ERR_UNSPECIFIED_ERROR                                      = 0x1F,
    HCI_ERR_UNSUPPORTED_LMP_PARAM_VAL                              = 0x20,
    HCI_ERR_ROLE_CHANGE_NOT_ALLOWED                                = 0x21,
    HCI_ERR_LMP_LL_RESP_TIMEOUT                                    = 0x22,
    HCI_ERR_LMP_ERR_TRANSACTION_COLLISION                          = 0x23,
    HCI_ERR_LMP_PDU_NOT_ALLOWED                                    = 0x24,
    HCI_ERR_ENCRYPT_MODE_NOT_ACCEPTABLE                            = 0x25,
    HCI_ERR_LINK_KEY_CAN_NOT_BE_CHANGED                            = 0x26,
    HCI_ERR_REQ_QOS_NOT_SUPPORTED                                  = 0x27,
    HCI_ERR_INSTANT_PASSED                                         = 0x28,
    HCI_ERR_PAIRING_WITH_UNIT_KEY_NOT_SUPPORTED                    = 0x29,
    HCI_ERR_DIFFERENT_TRANSACTION_COLLISION                        = 0x2A,
    HCI_ERR_RESERVED1                                              = 0x2B,
    HCI_ERR_QOS_UNACCEPTABLE_PARAM                                 = 0x2C,
    HCI_ERR_QOS_REJ                                                = 0x2D,
    HCI_ERR_CHAN_ASSESSMENT_NOT_SUPPORTED                          = 0x2E,
    HCI_ERR_INSUFFICIENT_SECURITY                                  = 0x2F,
    HCI_ERR_PARAM_OUT_OF_MANDATORY_RANGE                           = 0x30,
    HCI_ERR_RESERVED2                                              = 0x31,
    HCI_ERR_ROLE_SWITCH_PENDING                                    = 0x32,
    HCI_ERR_RESERVED3                                              = 0x33,
    HCI_ERR_RESERVED_SLOT_VIOLATION                                = 0x34,
    HCI_ERR_ROLE_SWITCH_FAILED                                     = 0x35,
    HCI_ERR_EXTENDED_INQUIRY_RESP_TOO_LARGE                        = 0x36,
    HCI_ERR_SIMPLE_PAIRING_NOT_SUPPORTED_BY_HOST                   = 0x37,
    HCI_ERR_HOST_BUSY_PAIRING                                      = 0x38,
    HCI_ERR_CONN_REJ_NO_SUITABLE_CHAN_FOUND                        = 0x39,
    HCI_ERR_CONTROLLER_BUSY                                        = 0x3A,
    HCI_ERR_UNACCEPTABLE_CONN_INTERVAL                             = 0x3B,
    HCI_ERR_ADVERTISING_TIMEOUT                                    = 0x3C,
    HCI_ERR_CONN_TERM_MIC_FAILURE                                  = 0x3D,
    HCI_ERR_CONN_FAILED_TO_ESTABLISH                               = 0x3E,
    HCI_ERR_MAC_CONN_FAILED                                        = 0x3F,
    HCI_ERR_COARSE_CLOCK_ADJUSTMENT_REJECT						   = 0x40,
    HCI_ERR_TYPE0_SUBMAP_NOT_DEFINED							   = 0x41,
	HCI_ERR_UNKNOWN_ADV_IDENTIFIER								   = 0x42,
    HCI_ERR_LIMIT_REACHED										   = 0x43,
    HCI_ERR_OP_CANCELLED_BY_HOST								   = 0x44,
    HCI_ERR_PACKET_TOO_LONG										   = 0x45,

    //telink define
    HCI_ERR_CONTROLLER_TX_FIFO_NOT_ENOUGH						   = HCI_ERR_CONTROLLER_BUSY,  //0x3A
    HCI_ERR_CONN_NOT_ESTABLISH									   = HCI_ERR_CONN_FAILED_TO_ESTABLISH,  //0x3E
	HCI_ERR_CURRENT_STATE_NOT_SUPPORTED_THIS_CMD 				   = HCI_ERR_CONTROLLER_BUSY,


///////////////////////// TELINK define status /////////////////////////////

    //LL status
	LL_ERR_CONNECTION_NOT_ESTABLISH 							   = 0x80,
	LL_ERR_TX_FIFO_NOT_ENOUGH,
	LL_ERR_ENCRYPTION_BUSY,
	LL_ERR_CURRENT_STATE_NOT_SUPPORTED_THIS_CMD,
	LL_ERR_INVALID_PARAMETER,
	LL_ERR_UNKNOWN_OPCODE,

	LL_ERR_CIS_SYNC_FAIL,
	LL_ERR_CIS_DISCONNECT,


	//L2CAP status
    L2CAP_ERR_INVALID_PARAMETER 								   = 0x90,
    L2CAP_ERR_INVALID_HANDLE,
    L2CAP_ERR_INSUFFICIENT_RESOURCES,
    L2CAP_ERR_PSM_NOT_REGISTER,
    L2CAP_ERR_CONTROL_NOT_READY,
    L2CAP_ERR_PSM_HAVE_ESTABLISH,

    //SMP status
	SMP_ERR_INVALID_PARAMETER 									   = 0xA0,
	SMP_ERR_PAIRING_BUSY,
    SMP_ERR_NO_SIGN_KEY,
    SMP_EER_PAIRING_IS_GOING_ON,

	//GATT status
	GATT_ERR_INVALID_PARAMETER 									   = 0xB0,
	GATT_ERR_PREVIOUS_INDICATE_DATA_HAS_NOT_CONFIRMED,
	GATT_ERR_SERVICE_DISCOVERY_TIEMOUT,
	GATT_ERR_NOTIFY_INDICATION_NOT_PERMITTED,
	GATT_ERR_DATA_PENDING_DUE_TO_SERVICE_DISCOVERY_BUSY,
	GATT_ERR_DATA_LENGTH_EXCEED_MTU_SIZE,

	//GAP status
	GAP_ERR_INVALID_PARAMETER 								   	   = 0xC0,
	//IAL
	IAL_ERR_SDU_LEN_EXCEED_SDU_MAX,
	IAL_ERR_LOSS_SDU_INTRVEL,
	IAL_ERR_ISO_TX_FIFO_NOT_ENOUGH,
	IAL_ERR_SDU_BUFF_INVALID,

	//Service status
	SERVICE_ERR_INVALID_PARAMETER 								   = 0xD0,
    BLE_ERR_DUPLICATE_PACKET,

	//Application buffer check error code
	LL_ACL_RX_BUF_NO_INIT 							   	  		   = 0xE0,
	LL_ACL_RX_BUF_PARAM_INVALID,
	LL_ACL_RX_BUF_SIZE_NOT_MEET_MAX_RX_OCT,
	LL_ACL_TX_BUF_NO_INIT,
	LL_ACL_TX_BUF_PARAM_INVALID,
	LL_ACL_TX_BUF_SIZE_MUL_NUM_EXCEED_4K,
	LL_ACL_TX_BUF_SIZE_NOT_MEET_MAX_TX_OCT,

} ble_sts_t;

#endif





/////////////////////////////// BLE  MAC ADDRESS //////////////////////////////////////////////
#define BLE_ADDR_PUBLIC                  0
#define BLE_ADDR_RANDOM                  1
#define BLE_ADDR_INVALID                 0xff
#define BLE_ADDR_LEN                     6

//Definition for BLE Common Address Type
/*
 *
 *				  |--public  ..................................................... BLE_DEVICE_ADDRESS_PUBLIC
 *                |
 * Address Type --|		      |-- random static  ................................. BLE_DEVICE_ADDRESS_RANDOM_STATIC
 *           	  |           |
 *    			  |--random --|
 * 			   				  |				       |-- non_resolvable private  ... BLE_DEVICE_ADDRESS_NON_RESOLVABLE_PRIVATE
 * 			 				  |-- random private --|
 *           					                   |-- resolvable private  ....... BLE_DEVICE_ADDRESS_RESOLVABLE_PRIVATE
 *
 */

#define	BLE_DEVICE_ADDRESS_PUBLIC							1
#define BLE_DEVICE_ADDRESS_RANDOM_STATIC					2
#define BLE_DEVICE_ADDRESS_NON_RESOLVABLE_PRIVATE			3
#define BLE_DEVICE_ADDRESS_RESOLVABLE_PRIVATE				4



#define IS_PUBLIC_ADDR(Type, Addr)  					( (Type)==BLE_ADDR_PUBLIC) )
#define IS_RANDOM_STATIC_ADDR(Type, Addr)  				( (Type)==BLE_ADDR_RANDOM && (Addr[5] & 0xC0) == 0xC0 )
#define IS_NON_RESOLVABLE_PRIVATE_ADDR(Type, Addr)  	( (Type)==BLE_ADDR_RANDOM && (Addr[5] & 0xC0) == 0x00 )
#define IS_RESOLVABLE_PRIVATE_ADDR(Type, Addr)  		( (Type)==BLE_ADDR_RANDOM && (Addr[5] & 0xC0) == 0x40 )


#define		MAC_MATCH8(md,ms)	(md[0]==ms[0] && md[1]==ms[1] && md[2]==ms[2] && md[3]==ms[3] && md[4]==ms[4] && md[5]==ms[5])
#define		MAC_MATCH16(md,ms)	(md[0]==ms[0] && md[1]==ms[1] && md[2]==ms[2])
#define		MAC_MATCH32(md,ms)	(md[0]==ms[0] && md[1]==ms[1])




/******************************************** ATT ***************************************************************/
/**
 *  @brief  Definition for Attribute protocol PDUs
 */
typedef enum{
	ATT_OP_ERROR_RSP					= 0x01,
	ATT_OP_EXCHANGE_MTU_REQ				= 0x02,
	ATT_OP_EXCHANGE_MTU_RSP				= 0x03,
	ATT_OP_FIND_INFORMATION_REQ			= 0x04,		ATT_OP_FIND_INFO_REQ = 0x04,
	ATT_OP_FIND_INFORMATION_RSP			= 0x05,		ATT_OP_FIND_INFO_RSP = 0x05,
	ATT_OP_FIND_BY_TYPE_VALUE_REQ		= 0x06,
	ATT_OP_FIND_BY_TYPE_VALUE_RSP		= 0x07,
	ATT_OP_READ_BY_TYPE_REQ				= 0x08,
	ATT_OP_READ_BY_TYPE_RSP				= 0x09,
	ATT_OP_READ_REQ						= 0x0A,
	ATT_OP_READ_RSP						= 0x0B,
	ATT_OP_READ_BLOB_REQ				= 0x0C,
	ATT_OP_READ_BLOB_RSP				= 0x0D,
	ATT_OP_READ_MULTIPLE_REQ			= 0x0E,		ATT_OP_READ_MULTI_REQ = 0x0E,
	ATT_OP_READ_MULTIPLE_RSP			= 0x0F,
	ATT_OP_READ_BY_GROUP_TYPE_REQ		= 0x10,
	ATT_OP_READ_BY_GROUP_TYPE_RSP		= 0x11,
	ATT_OP_WRITE_REQ					= 0x12,
	ATT_OP_WRITE_RSP					= 0x13,
	ATT_OP_PREPARE_WRITE_REQ			= 0x16,
	ATT_OP_PREPARE_WRITE_RSP			= 0x17,
	ATT_OP_EXECUTE_WRITE_REQ			= 0x18,
	ATT_OP_EXECUTE_WRITE_RSP			= 0x19,

	ATT_OP_HANDLE_VALUE_NTF				= 0x1B,		ATT_OP_HANDLE_VALUE_NOTI = 0x1B,
	ATT_OP_HANDLE_VALUE_IND				= 0x1D,
	ATT_OP_HANDLE_VALUE_CFM				= 0x1E,

	ATT_OP_READ_MULTIPLE_VARIABLE_REQ	= 0x20,	//core_5.2
	ATT_OP_READ_MULTIPLE_VARIABLE_RSP	= 0x21, //core_5.2
	ATT_OP_MULTIPLE_HANDLE_VALUE_NTF	= 0x23, //core_5.2

	ATT_OP_WRITE_CMD					= 0x52,
	ATT_OP_SIGNED_WRITE_CMD				= 0xD2,
}att_pdu_type;

/******************************************** LINKLAYER ***************************************************************/

/**
 *  @brief  Definition for LL Control PDU Opcode
 */																		// rf_len without MIC
#define					LL_CONNECTION_UPDATE_REQ	0x00							// 12
#define					LL_CHANNEL_MAP_REQ			0x01							//	8
#define					LL_TERMINATE_IND			0x02							//	2

#define					LL_ENC_REQ					0x03	// encryption			// 23
#define					LL_ENC_RSP					0x04	// encryption			// 13
#define					LL_START_ENC_REQ			0x05	// encryption			//	1
#define					LL_START_ENC_RSP			0x06	// encryption			//	1

#define					LL_UNKNOWN_RSP				0x07							//	2
#define 				LL_FEATURE_REQ              0x08							//	9
#define 				LL_FEATURE_RSP              0x09							//	9

#define					LL_PAUSE_ENC_REQ			0x0A	// encryption			//	1
#define					LL_PAUSE_ENC_RSP			0x0B	// encryption			//	1

#define 				LL_VERSION_IND              0x0C							//	6
#define 				LL_REJECT_IND         		0x0D							//	2
#define 				LL_SLAVE_FEATURE_REQ        0x0E	//core_4.1				//	9
#define 				LL_CONNECTION_PARAM_REQ		0x0F	//core_4.1				// 24
#define 				LL_CONNECTION_PARAM_RSP		0x10	//core_4.1				// 24
#define					LL_REJECT_IND_EXT			0x11	//core_4.1				//	3
#define 				LL_PING_REQ					0x12    //core_4.1				//	1
#define					LL_PING_RSP					0x13    //core_4.1				//	1
#define 				LL_LENGTH_REQ				0x14    //core_4.2				//	9
#define					LL_LENGTH_RSP				0x15    //core_4.2				//	9
#define 				LL_PHY_REQ					0x16	//core_5.0				//	3
#define 				LL_PHY_RSP					0x17	//core_5.0				//	3
#define 				LL_PHY_UPDATE_IND			0x18	//core_5.0				//	5
#define 				LL_MIN_USED_CHN_IND			0x19	//core_5.0				//	3

#define 				LL_CTE_REQ					0x1A	//core_5.1				//	2
#define 				LL_CTE_RSP					0x1B	//core_5.1				//	2
#define 				LL_PERIODIC_SYNC_IND		0x1C	//core_5.1				// 35
#define 				LL_CLOCK_ACCURACY_REQ		0x1D	//core_5.1				//	2
#define 				LL_CLOCK_ACCURACY_RSP		0x1E	//core_5.1				//	2


#define 				LL_CIS_REQ					0x1F	//core_5.2				//	36
#define 				LL_CIS_RSP					0x20	//core_5.2				//	9
#define 				LL_CIS_IND					0x21	//core_5.2				//  16
#define 				LL_CIS_TERMINATE_IND		0x22	//core_5.2				//	4
#define 				LL_POWER_CONTROL_REQ		0x23	//core_5.2				//	4
#define 				LL_POWER_CONTROL_RSP		0x24	//core_5.2				//	5
#define 				LL_POWER_CHANGE_IND			0x25	//core_5.2				//	5

/******************************************** GAP ***************************************************************/

// https://www.bluetooth.com/specifications/assigned-numbers/generic-access-profile/
// EIR Data Type, Advertising Data Type (AD Type) and OOB Data Type Definitions

typedef enum {
	DT_FLAGS								= 0x01,		//	Flag
	DT_INCOMPLT_LIST_16BIT_SERVICE_UUID		= 0x02,		//	Incomplete List of 16-bit Service Class UUIDs
	DT_COMPLETE_LIST_16BIT_SERVICE_UUID	    = 0x03,		//	Complete List of 16-bit Service Class UUIDs
	DT_INCOMPLT_LIST_32BIT_SERVICE_UUID    	= 0x04,		//	Incomplete List of 32-bit Service Class UUIDs
	DT_COMPLETE_LIST_32BIT_SERVICE_UUID		= 0x05,		//	Complete List of 32-bit Service Class UUIDs
	DT_INCOMPLT_LIST_128BIT_SERVICE_UUID   	= 0x06,		//	Incomplete List of 128-bit Service Class UUIDs
	DT_COMPLETE_LIST_128BIT_SERVICE_UUID	= 0x07,		//	Complete List of 128-bit Service Class UUIDs
	DT_SHORTENED_LOCAL_NAME					= 0x08,		//	Shortened Local Name
	DT_COMPLETE_LOCAL_NAME					= 0x09,		//	Complete Local Name
	DT_TX_POWER_LEVEL						= 0x0A,		//	Tx Power Level

	DT_CLASS_OF_DEVICE						= 0x0D,		//	Class of Device
	DT_SERVICE_DATA							= 0x16,		//	Service Data
	DT_APPEARANCE							= 0x19,		//	Appearance

	DT_CHM_UPT_IND							= 0x28,		//	Channel Map Update Indication
	DT_BIGINFO								= 0x2C,		//	BIGInfo
	DT_BROADCAST_CODE						= 0x2D,		// 	Broadcast_Code
	DT_3D_INFORMATION_DATA					= 0x3D,		//	3D Information Data

	DATA_TYPE_MANUFACTURER_SPECIFIC_DATA 	= 0xFF,     //	Manufacturer Specific Data
}data_type_t;











typedef struct {
	u8 type   :4;
	u8 rfu1   :2;
	u8 txAddr :1;
	u8 rxAddr :1;
}rf_adv_head_t;


typedef struct {
    u8 llid   :2;
    u8 nesn   :1;
    u8 sn     :1;
    u8 md     :1;
    u8 rfu1   :3;
}rf_data_head_t;


typedef struct{
	u32 dma_len;            //won't be a fixed number as previous, should adjust with the mouse package number

	rf_adv_head_t  header;	//RA(1)_TA(1)_RFU(2)_TYPE(4)
	u8  rf_len;				//LEN(6)_RFU(2)

	u8	advA[6];			//address
#if (TEST_LONG_ADV_PACKET)
	u8	data[80];
#else
	u8	data[31];			//0-31 byte
#endif
}rf_packet_adv_t;

typedef struct{
	u32 dma_len;            //won't be a fixed number as previous, should adjust with the mouse package number
	rf_adv_head_t  header;	//RA(1)_TA(1)_RFU(2)_TYPE(4)
	u8  rf_len;				//LEN(6)_RFU(2)

	u8	scanA[6];			//
	u8	advA[6];			//
}rf_packet_scan_req_t;

typedef struct{
	u32 dma_len;            //won't be a fixed number as previous, should adjust with the mouse package number
	rf_adv_head_t  header;				//RA(1)_TA(1)_RFU(2)_TYPE(4)
	u8  rf_len;				//LEN(6)_RFU(2)

	u8	advA[6];			//address
	u8	data[31];			//0-31 byte
}rf_packet_scan_rsp_t;

typedef struct{
	u32 dma_len;            //won't be a fixed number as previous, should adjust with the mouse package number
	u8	type;				//RA(1)_TA(1)_RFU(2)_TYPE(4): connect request PDU
	u8  rf_len;				//LEN(6)_RFU(2)
	u8	scanA[6];			//
	u8	advA[6];			//
	u8	accessCode[4];		// access code
	u8	crcinit[3];
	u8	winSize;
	u16	winOffset;
	u16 interval;
	u16 latency;
	u16 timeout;
	u8	chm[5];
	u8	hop;				//sca(3)_hop(5)
}rf_packet_connect_t;

typedef struct{
	u32 dma_len;            //won't be a fixed number as previous, should adjust with the mouse package number
	rf_adv_head_t  header;				//RA(1)_TA(1)_RFU(2)_TYPE(4): connect request PDU
	u8  rf_len;				//LEN(6)_RFU(2)
	u8	scanA[6];			//
	u8	advA[6];			//
	u8	aa[4];				// access code
	u8	crcinit[3];
	u8	wsize;
	u16	woffset;
	u16 interval;
	u16 latency;
	u16 timeout;
	u8	chm[5];
	u8	hop;				//sca(3)_hop(5)
}rf_packet_ll_init_t;

typedef struct {
	u8	type;
	u8  rf_len;
	u8 	opcode;
	u8 	winSize;
	u16 winOffset;
	u16 interval;
	u16 latency;
	u16 timeout;
	u16 instant;
} rf_packet_ll_updateConnPara_t;


typedef struct {
	u16 intervalMin;      // Minimum advertising interval for non-directed advertising, time = N * 0.625ms
	u16 intervalMax;      // Maximum advertising interval for non-directed advertising, time = N * 0.625ms
	u8  advType;          // Advertising
	u8  ownAddrType;
	u8  peerAddrType;
	u8  peerAddr[BLE_ADDR_LEN];
	u8  advChannelMap;
	u8  advFilterPolicy;
} adv_para_t;

typedef struct {
	u16 connHandle;
	u16 connIntervalMin;
	u16 connIntervalMax;
	u16 connLatency;
	u16 supervisionTimeout;
	u16 minCELen;
	u16 maxCELen;
} conn_para_t;



/*
LLID(2) - NESN(1) - SN(1) - MD(1) - RFU(3) - Length(5) - RFU(3)
*/


typedef struct{
	rf_data_head_t	header;
	u8  rf_len;
	u16	l2capLen;
	u16	chanId;
	u8  opcode;
	u8 data[1];
}rf_packet_l2cap_t;


typedef struct{
	rf_data_head_t	header;
	u8  rf_len;
	u16	l2capLen;
	u16	chanId;
	u8  opcode;
	u8  handle0;
	u8  handle1;
	u8	dat[20];
}rf_packet_att_t;


typedef struct{
	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(5)_RFU(3)
	u16	l2capLen;
	u16	chanId;
	u8  opcode;
	u8 data[1];
}rf_packet_l2cap_req_t;


typedef struct{
	u8	type;
	u8  rf_len;
	u16	l2capLen;
	u16	chanId;
	u8  code;
	u8  id;
	u16 dataLen;
	u16  result;
}rf_pkt_l2cap_sig_connParaUpRsp_t;


typedef struct{
	u8	type;
	u8  rf_len;
	u16	l2capLen;
	u16	chanId;
	u8  opcode;
	u8 data[1];
}rf_pkt_l2cap_req_t;


typedef struct{
	u8	llid;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(5)_RFU(3)
	u16	l2capLen;
	u16	chanId;
	u8  opcode;
	u8	id;
	u16 data_len;
	u16 min_interval;
	u16 max_interval;
	u16 latency;
	u16 timeout;
}rf_packet_l2cap_connParaUpReq_t;


typedef struct{
	u8	llid;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(5)_RFU(3)
	u16	l2capLen;
	u16	chanId;
	u8  opcode;
	u8	id;
	u16 data_len;
	u16 result;
}rf_packet_l2cap_connParaUpRsp_t;



typedef struct{
	u8	type;				//RA(1)_TA(1)_RFU(2)_TYPE(4)
	u8  rf_len;				//LEN(6)_RFU(2)
	u8 	opcode;
	u8	data[8];
}rf_packet_feature_rsp_t;

typedef struct{
	u8	type;				//RA(1)_TA(1)_RFU(2)_TYPE(4)
	u8  rf_len;				//LEN(6)_RFU(2)
	u8 	opcode;
	u8  mainVer;
	u16 vendor;
	u16 subVer;
}rf_packet_version_ind_t;

typedef struct {
	u8 	type;				//RA(1)_TA(1)_RFU(2)_TYPE(4)
	u8  rf_len;				//LEN(6)_RFU(2)
	u8 	opcode;
	u8 	winSize;
	u16 winOffset;
	u16 interval;
	u16 latency;
	u16 timeout;
	u16 instant;
}rf_packet_connect_upd_req_t;

typedef struct {
	u8 	type;				//RA(1)_TA(1)_RFU(2)_TYPE(4)
	u8  rf_len;				//LEN(6)_RFU(2)
	u8 	opcode;
	u8 	chm[5];
	u16 instant;
} rf_packet_chm_upd_req_t;

typedef struct {
	u8  valid;
	u8 	winSize;
	u16 winOffset;
	u16 interval;
	u16 latency;
	u16 timeout;
	u16 instant;
}connect_upd_data_t;

typedef struct {
	u8  valid;
	u8 	chm[5];
	u16 instant;
}connect_chm_upd_data_t;


typedef struct{
	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(5)_RFU(3)

	u8	opcode;				//
	u8	reason;				//
}rf_packet_ll_terminate_t;


typedef struct{
	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(5)_RFU(3)

	u8	opcode;				//
	u8	dat[1];				//
}rf_packet_ll_control_t;

typedef struct{
	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(5)_RFU(3)
	u16	l2cap;
	u16	chanid;

	u8	att;
	u8	hl;					// assigned by master
	u8	hh;					//

	u8	dat[20];

}rf_packet_att_data_t;





typedef struct{
	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(5)_RFU(3)
	u16	l2capLen;
	u16	chanId;
	u8  opcode;
	u8  datalen;
	u8  data[1];			// character_handle / property / value_handle / value
}att_readByTypeRsp_t;

typedef struct{
	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(5)_RFU(3)
	u16	l2capLen;
	u16	chanId;
	u8  opcode;
	u8  format;
	u8  data[1];			// character_handle / property / value_handle / value
}att_findInfoRsp_t;

typedef struct{
	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(5)_RFU(3)
	u16	l2capLen;
	u16	chanId;
	u8  opcode;
	u8 	value[22];
}att_readRsp_t;



typedef struct {
	u8 type;
	u8 address[BLE_ADDR_LEN];
} addr_t;




////////////////////////////////////////////////////////////////////////////
















#endif