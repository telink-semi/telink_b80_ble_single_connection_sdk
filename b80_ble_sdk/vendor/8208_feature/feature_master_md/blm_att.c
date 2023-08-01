/********************************************************************************************************
 * @file	blm_att.c
 *
 * @brief	This is the source file for BLE SDK
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
#include "tl_common.h"
#include "drivers.h"
#include "stack/ble/ble.h"

#include "app.h"
#include "blm_att.h"
#include "blm_pair.h"
#include "blm_host.h"

#include "application/keyboard/keyboard.h"

#if (FEATURE_TEST_MODE == TEST_MASTER_MD )

#define     TELINK_UNPAIR_KEYVALUE		0xFF  //conn state, unpair

const u8 my_SppS2CUUID[16]		= WRAPPING_BRACES(TELINK_SPP_DATA_SERVER2CLIENT);
const u8 my_SppC2SUUID[16]		= WRAPPING_BRACES(TELINK_SPP_DATA_CLIENT2SERVER);

u16 	current_read_req_handle;







u8	*p_att_response = 0;

volatile u8 host_att_req_busy = 0;

/**
 * @brief       host layer client handle
 * @param[in]	connHandle - connect handle
 * @param[in]	p - Pointer point to event parameter.
 * @return      none
 */
int host_att_client_handler (u16 connHandle, u8 *p)
{
	att_readByTypeRsp_t *p_rsp = (att_readByTypeRsp_t *) p;
	if (p_att_response)
	{
		if ( p_rsp->chanId == 0x04 && (p_rsp->opcode == 0x01 || p_rsp->opcode == (host_att_req_busy | 1)))
		{
			memcpy (p_att_response, p, 32);
			host_att_req_busy = 0;
		}
	}
	return 0;
}

typedef int (*host_att_idle_func_t) (void);
host_att_idle_func_t host_att_idle_func = 0;

/**
 * @brief       host layer clear service discovery
 * @param[in]	p - Pointer point to main idle loop function.
 * @return      none
 */
int host_att_register_idle_func (void *p)
{
	if (host_att_idle_func)
		return 1;

	host_att_idle_func = p;
	return 0;
}

/**
 * @brief       host layer response
 * @param[in]	none
 * @return      none
 */
int host_att_response ()
{
	return host_att_req_busy == 0;
}

/**
 * @brief       host layer wait service
 * @param[in]	handle - connect handle
 * @param[in]	p - pointer of data event
 * @param[in]	timeout
 * @return      0
 */
int host_att_service_wait_event (u8 opcode, u8 *p, u32 timeout)
{
	host_att_req_busy = opcode;
	p_att_response = p;
	DBG_CHN0_TOGGLE;
	u32 t = clock_time ();
	while (!clock_time_exceed (t, timeout))
	{
		if (host_att_response ())
		{
			DBG_CHN1_TOGGLE;
			return 0;
		}
		if (host_att_idle_func)
		{
			if(host_att_idle_func())
			{
				break;
			}
		}
	}
	DBG_CHN2_TOGGLE;
	return 1;
}

/**
 * @brief       this function serves to find handle of uuid16
 * @param[in]	p - pointer of data attribute
 * @param[in]	uuid
 * @param[in]	ref - HID Report
 * @return      0 - fail to find handle of uuid16
 *              1 - the handle of uuid16 that find
 */
u16 blm_att_findHandleOfUuid16 (att_db_uuid16_t *p, u16 uuid, u16 ref)
{
	for (int i=0; i<p->num; i++)
	{
		if (p[i].uuid == uuid && p[i].ref == ref)
		{
			return p[i].handle;
		}
	}
	return 0;
}

/**
 * @brief       this function serves to find handle of uuid128
 * @param[in]	p - pointer of data attribute
 * @param[in]	uuid - pointer of uuid
 * @return      0 - fail to find handle of uuid128
 *              1 - the handle of uuid128 that find
 */
u16 blm_att_findHandleOfUuid128 (att_db_uuid128_t *p, const u8 * uuid)
{
	for (int i=0; i<p->num; i++)
	{
		if (memcmp (p[i].uuid, uuid, 16) == 0)
		{
			return p[i].handle;
		}
	}
	return 0;
}

/**
 * @brief       host layer discovery service
 * @param[in]	handle - connect handle
 * @param[in]	p16 - pointer of data attribute
 * @param[in]	n16 - attribute uuid16 num
 * @param[in]	p128 - pointer of data attribute
 * @param[in]   n128 - attribute uuid128 num
 * @return      ble status
 */
ble_sts_t  host_att_discoveryService (att_db_uuid16_t *p16, int n16, att_db_uuid128_t *p128, int n128)
{
	att_db_uuid16_t *ps16 = p16;
	att_db_uuid128_t *ps128 = p128;
	int i16 = 0;
	int i128 = 0;
	u8  dat[32];
	ps16->num = 0;
	ps128->num = 0;

	// char discovery: att_read_by_type
		// hid discovery: att_find_info
	u16 s = 1;
	u16 uuid = GATT_UUID_CHARACTER;
	do {
		blc_gatt_pushReadByTypeRequest(cur_conn_device.conn_handle, s, 0xffff, (u8 *)&uuid, 2);
		if (host_att_service_wait_event(ATT_OP_READ_BY_TYPE_REQ, dat, 1000000))
		{
			return  GATT_ERR_SERVICE_DISCOVERY_TIMEOUT;			//timeout
		}
		DBG_CHN3_TOGGLE;
		// process response data
		att_readByTypeRsp_t *p_rsp = (att_readByTypeRsp_t *) dat;
		if (p_rsp->opcode != ATT_OP_READ_BY_TYPE_RSP)
		{
			break;
		}
		DBG_CHN4_TOGGLE;
		if (p_rsp->datalen == 21)		//uuid128
		{
			u8 *pd = p_rsp->data;
			while (p_rsp->l2capLen > 21)
			{
				s = pd[3] + pd[4] * 256;
				if (i128 < n128)
				{
					p128->property = pd[2];
					p128->handle = s;
					memcpy (p128->uuid, pd + 5, 16);
					i128++;
					p128++;
				}
				p_rsp->l2capLen -= 21;
				pd += 21;
			}
		}
		else if (p_rsp->datalen == 7) //uuid16
		{
			u8 *pd = p_rsp->data;
			while (p_rsp->l2capLen > 7)
			{
				s = pd[3] + pd[4] * 256;
				if (i16 < n16)
				{
					p16->property = pd[2];
					p16->handle = s;
					p16->uuid = pd[5] | (pd[6] << 8);
					p16->ref = 0;
					i16 ++;
					p16++;
				}
				p_rsp->l2capLen -= 7;
				pd += 7;
			}
		}
	} while (1);

	ps16->num = i16;
	ps128->num = i128;

	//--------- use att_find_info to find the reference property for hid ----------
	p16 = ps16;
	for (int i=0; i<i16; i++)
	{
		if (p16->uuid == CHARACTERISTIC_UUID_HID_REPORT)		//find reference
		{
			blc_gatt_pushFindInformationRequest(cur_conn_device.conn_handle, p16->handle, 0xffff);
			if (host_att_service_wait_event(ATT_OP_FIND_INFO_REQ, dat, 1000000))
			{
				return  GATT_ERR_SERVICE_DISCOVERY_TIMEOUT;			//timeout
			}

			att_findInfoRsp_t *p_rsp = (att_findInfoRsp_t *) dat;
			if (p_rsp->opcode == ATT_OP_FIND_INFO_RSP && p_rsp->format == 1)
			{
				int n = p_rsp->l2capLen - 2;
				u8 *pd = p_rsp->data;
				while (n > 0)
				{
					if ((pd[2]==U16_LO(GATT_UUID_CHARACTER) && pd[3]==U16_HI(GATT_UUID_CHARACTER)) ||
						(pd[2]==U16_LO(GATT_UUID_PRIMARY_SERVICE) && pd[3]==U16_HI(GATT_UUID_PRIMARY_SERVICE))	)
					{
						break;
					}

					if (pd[2]==U16_LO(GATT_UUID_REPORT_REF) && pd[3]==U16_HI(GATT_UUID_REPORT_REF))
					{
					//-----------		read attribute ----------------
						blc_gatt_pushReadRequest(cur_conn_device.conn_handle, pd[0]);
						if (host_att_service_wait_event(ATT_OP_READ_REQ, dat, 1000000))
						{
								return  GATT_ERR_SERVICE_DISCOVERY_TIMEOUT;			//timeout
						}

						att_readRsp_t *pr = (att_readRsp_t *) dat;
						if (pr->opcode == ATT_OP_READ_RSP)
						{
							p16->ref = pr->value[0] | (pr->value[1] << 8);
						}

						break;
					}
					n -= 4;
					pd += 4;
				}
			}
		} //----- end for if CHARACTERISTIC_UUID_HID_REPORT

		p16++;
	}

	return  BLE_SUCCESS;
}

/**
 * @brief       this function serves to set current ReadRequest attribute handle
 * @param[in]	handle - connect handle
 * @return      none
 */
void app_setCurrentReadReq_attHandle(u16 handle)
{
	current_read_req_handle = handle;
}

/**
 * @brief       this function serves to get current ReadRequest attribute handle
 * @param[in]	none
 * @return      current ReadRequest attribute handle
 */
u16 app_getCurrentReadReq_attHandle(void)
{
	return current_read_req_handle;
}

#endif  //end of (FEATURE_TEST_MODE == xxx)
