/********************************************************************************************************
 * @file     ble_format.h
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

#ifndef BLE_FORMAT_H
#define BLE_FORMAT_H


#include "stack/ble/ble_common.h"

typedef struct {
    u8 llid   :2;
    u8 nesn   :1;
    u8 sn     :1;
    u8 md     :1;
    u8 rfu1   :3;
    u8 rf_len;
}rf_acl_data_head_t;



typedef struct {
    u8 llid   :2;
    u8 nesn   :1;
    u8 sn     :1;
    u8 cie    :1;
    u8 rfu0   :1;
    u8 npi    :1;
    u8 rfu1   :1;
    u8 rf_len;
}rf_cis_data_hdr_t;



typedef struct {
    u8 llid   :2;
    u8 cssn   :3;
    u8 cstf   :1;
    u8 rfu0   :2;
    u8 rf_len;
}rf_bis_data_hdr_t;

typedef struct{
	union{
		rf_bis_data_hdr_t  bisPduHdr;
		rf_cis_data_hdr_t  cisPduHdr;
		rf_acl_data_head_t aclPduHdr;
		struct{
			u8 type;
			u8 rf_len;
		}pduHdr;
	}llPduHdr;        /* LL PDU Header: 2 */
	u8 	llPayload[1]; /* Max LL Payload length: 251 */
}llPhysChnPdu_t;

typedef struct{
	u32 dma_len;
	llPhysChnPdu_t llPhysChnPdu;
}rf_packet_ll_data_t;



typedef struct{
	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(5)_RFU(3)
	u16	l2capLen;
	u16	chanId;
	u8  opcode;
	u8 	errOpcode;
	u16 errHandle;
	u8  errReason;
}rf_packet_att_errRsp_t;

typedef struct{
	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(5)_RFU(3)

	u16	l2capLen;
	u16	chanId;
	u8  opcode;
	u8	startingHandle;
	u8	startingHandle1;
	u8	endingHandle;
	u8	endingHandle1;
	u8	attType[2];				//
}rf_packet_att_readByType_t;

typedef struct{
	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(5)_RFU(3)

	u16	l2capLen;
	u16	chanId;
	u8  opcode;
	u8	startingHandle;
	u8	startingHandle1;
	u8	endingHandle;
	u8	endingHandle1;
	u8	attType[2];
	u8  attValue[2];
}rf_packet_att_findByTypeReq_t;




typedef struct{
	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(5)_RFU(3)

	u16	l2capLen;
	u16	chanId;
	u8  opcode;
	u16 	data[1];
}rf_packet_att_findByTypeRsp_t;


typedef struct{
	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(5)_RFU(3)
	u16	l2capLen;
	u16	chanId;
	u8  opcode;
	u8 handle;
	u8 handle1;
}rf_packet_att_read_t;

typedef struct{
	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(5)_RFU(3)
	u16	l2capLen;
	u16	chanId;
	u8  opcode;
	u8 handle;
	u8 handle1;
	u8 offset0;
	u8 offset1;
}rf_packet_att_readBlob_t;

typedef struct{
	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(5)_RFU(3)
	u16	l2capLen;
	u16	chanId;
	u8  opcode;
	u8 	value[22];
}rf_packet_att_readRsp_t;


typedef struct{
	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(5)_RFU(3)
	u16	l2capLen;
	u16	chanId;
	u8  opcode;
	u8  datalen;
	u8  data[1];			// character_handle / property / value_handle / value
}rf_pkt_att_readByTypeRsp_t;

typedef struct{
	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(5)_RFU(3)
	u16	l2capLen;
	u16	chanId;
	u8  opcode;
	u8  datalen;
	u8  data[1];			// character_handle / property / value_handle / value
}rf_packet_att_readByTypeRsp_t;

typedef struct{
	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(5)_RFU(3)
	u16	l2capLen;
	u16	chanId;
	u8  opcode;
	u8  datalen;
	u8  data[3];
}rf_packet_att_readByGroupTypeRsp_t;

typedef struct{
	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(5)_RFU(3)
	u16	l2capLen;
	u16	chanId;
	u8  opcode;
	u8  format;
	u8  data[1];			// character_handle / property / value_handle / value
}rf_packet_att_findInfoReq_t;

typedef struct{
	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(5)_RFU(3)
	u16	l2capLen;
	u16	chanId;
	u8  opcode;
	u8 flags;
}rf_packet_att_executeWriteReq_t;

typedef struct{
	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(5)_RFU(3)
	u16	l2capLen;
	u16	chanId;
	u8  opcode;
	u8 handle;
	u8 handle1;
	u8 value;
}rf_packet_att_write_t;

typedef struct{
	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(5)_RFU(3)
	u16	l2capLen;
	u16	chanId;
	u8  opcode;
	u8 handle[2];
	u8 data;
}rf_packet_att_notification_t;

typedef struct{
	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(5)_RFU(3)
	u16	l2capLen;
	u16	chanId;
	u8  opcode;
	u8 mtu[2];
}rf_packet_att_mtu_t;

typedef struct{
	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(5)_RFU(3)
	u16	l2capLen;
	u16	chanId;
	u8  opcode;
	u8 mtu[2];
}rf_packet_att_mtu_exchange_t;

typedef struct{
	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(5)_RFU(3)
	u16	l2capLen;
	u16	chanId;
	u8  opcode;
}rf_packet_att_writeRsp_t;


#endif	/* BLE_FORMAT_H */
