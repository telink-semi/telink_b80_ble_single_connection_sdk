/********************************************************************************************************
 * @file     ll_conn_phy.h
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

#ifndef LL_CONN_PHY_H_
#define LL_CONN_PHY_H_

#if(LL_FEATURE_SUPPORT_LE_2M_PHY)

/* Type define */
typedef struct{
    u8 llid;
    u8 rf_len;
    u8 opcode;
    u8 tx_phys;
    u8 rx_phys;
} rf_pkt_ll_phy_req_rsp_t; //phy_req, phy_rsp

typedef struct{
    u8 llid;
    u8 rf_len;
    u8 opcode;
    u8 m_to_s_phy;
    u8 s_to_m_phy;
    u8 instant0;
    u8 instant1;
} rf_pkt_ll_phy_update_ind_t; //phy_req, phy_rsp

typedef struct{
    u8 dft_tx_prefer_phys;
    u8 dft_rx_prefer_phys;
    u8 dft_prefer_phy;
    u8 cur_llPhy;
} ll_phy_t;


//do not support Asymmetric PHYs, conn_phys = tx_phys & rx_phys
typedef struct{
    u8 conn_prefer_phys; // conn_prefer_phys = tx_prefer_phys & rx_prefer_phys
    u8 conn_cur_phy;     //
    u8 conn_next_phy;    //
    u8 phy_req_pending;
    //u8 phy_req_trigger;  // 1: means current device triggers phy_req, due to API "blc_ll_setPhy" called by Host or Application
} ll_conn_phy_t;


//extern u8 tx_settle_adv[];
extern u8 tx_settle_slave[];

typedef enum{
    BLE_PHY_1M    = BIT(0),
    BLE_PHY_2M    = BIT(1),
    TLK_NORDIC_2M = BIT(5),
} le_phy_type_t;

typedef enum{
    PHY_PREFER_1M = BIT(0),
    PHY_PREFER_2M = BIT(1),
} le_phy_prefer_type_t;

typedef enum{
    PHY_TRX_PREFER    = 0,                 //has preference among TX & RX PHYs
    PHY_TX_NO_PREFER  = BIT(0),            //has no preference among TX PHYs
    PHY_RX_NO_PREFER  = BIT(1),            //has no preference among RX PHYs
    PHY_TRX_NO_PREFER = (BIT(0) | BIT(1)), //has no preference among TX & RX PHYs
} le_phy_prefer_mask_t;

/*-------------------------------- User Interface ----------------------------*/
void blc_ll_init2MPhy_feature(void);

ble_sts_t blc_ll_setDefaultPhy(le_phy_prefer_mask_t all_phys, le_phy_prefer_type_t tx_phys,
		                       le_phy_prefer_type_t rx_phys);
ble_sts_t blc_ll_setPhy(u16 connHandle, le_phy_prefer_mask_t all_phys,
                        le_phy_prefer_type_t tx_phys, le_phy_prefer_type_t rx_phys);


#endif /* LL_FEATURE_SUPPORT_LE_2M_PHY */

#endif /* LL_CONN_PHY_H_ */
