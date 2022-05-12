/********************************************************************************************************
 * @file     ecc_ll.h
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

#ifndef ECC_LL_H_
#define ECC_LL_H_


//extern const u8 blt_ecc_dbg_priv_key[32];
//extern const u8 blt_ecc_dbg_pub_key[64];


/**
* @brief		This function is used to register the random number function needed for ECC calculation
* @param		none
* @return		none
*/
void 			blt_ecc_init(void);


int blt_ecc_gen_rand(unsigned char *dest, unsigned int size);

//ECC implementation method selection
#define		ECC_HW_IMPLEMEMTATION		0
#define		ECC_SW_IMPLEMEMTATION		1


#if  (MCU_CORE_TYPE == MCU_CORE_827x || MCU_CORE_TYPE == MCU_CORE_9518)
#define		ECC_METHOD_SELECTION		ECC_HW_IMPLEMEMTATION //B91/B87 use hw ECC
#elif(MCU_CORE_TYPE == MCU_CORE_825x)
#define		ECC_METHOD_SELECTION		ECC_SW_IMPLEMEMTATION //B85 use sw ECC
#elif(MCU_CORE_TYPE == MCU_CORE_8208)
#define		ECC_METHOD_SELECTION		ECC_SW_IMPLEMEMTATION //B80 use sw ECC
#endif


#if (ECC_METHOD_SELECTION == ECC_SW_IMPLEMEMTATION)
#define		uECC_set_rng				swECC_set_rng
#define		uECC_make_key				swECC_make_key
#define		fake_rng					blt_ecc_gen_rand
#define		tn_crypto_f4   				blt_smp_alg_f4
#define		uECC_shared_secret			swECC_shared_secret

#elif (ECC_METHOD_SELECTION == ECC_HW_IMPLEMEMTATION)
#define		ecc_ll_set_rng				hwECC_set_rng
#define		ecc_ll_make_key				hwECC_make_key
#define		ecc_ll_gen_dhkey			hwECC_shared_secret
#endif



#endif /* ECC_LL_H_ */




