/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      driver_fm11rfxx.h
 * @brief     driver fm11rfxx header file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2024-07-30
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2024/07/30  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#ifndef DRIVER_FM11RFXX_H
#define DRIVER_FM11RFXX_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup fm11rfxx_driver fm11rfxx driver function
 * @brief    fm11rfxx driver modules
 * @{
 */

/**
 * @addtogroup fm11rfxx_basic_driver
 * @{
 */

/**
 * @brief fm11rfxx type enumeration definition
 */
typedef enum
{
    FM11RFXX_TYPE_INVALID  = 0x00,        /**< invalid */
    FM11RFXX_TYPE_FM11RF08 = 0x01,        /**< fm11rf08 */
    FM11RFXX_TYPE_FM11RF32 = 0x02,        /**< fm11rf32 */
} fm11rfxx_type_t;

/**
 * @brief fm11rfxx load modulation enumeration definition
 */
typedef enum
{
    FM11RFXX_LOAD_MODULATION_NORMAL = 0x00,        /**< normal load modulation */
    FM11RFXX_LOAD_MODULATION_STRONG = 0x01,        /**< strong load modulation */
} fm11rfxx_load_modulation_t;

/**
 * @brief fm11rfxx personalized uid enumeration definition
 */
typedef enum
{
    FM11RFXX_PERSONALIZED_UID_0 = 0x00,        /**< anti-collision and selection with the double size UID according to ISO/IEC
                                                    14443-3 */
    FM11RFXX_PERSONALIZED_UID_1 = 0x40,        /**< anti-collision and selection with the double size UID according to ISO/IEC
                                                    14443-3 and optional usage of a selection process shortcut */
    FM11RFXX_PERSONALIZED_UID_2 = 0x20,        /**< anti-collision and selection with a single size random ID according to ISO/IEC
                                                    14443-3 */
    FM11RFXX_PERSONALIZED_UID_3 = 0x60,        /**< anti-collision and selection with a single size NUID according to ISO/IEC
                                                    14443-3 where the NUID is calculated out of the 7-byte UID */
} fm11rfxx_personalized_uid_t;

/**
 * @brief fm11rfxx authentication key enumeration definition
 */
typedef enum
{
    FM11RFXX_AUTHENTICATION_KEY_A = 0x00,        /**< authentication key a */
    FM11RFXX_AUTHENTICATION_KEY_B = 0x01,        /**< authentication key b */
} fm11rfxx_authentication_key_t;

/**
 * @brief fm11rfxx handle structure definition
 */
typedef struct fm11rfxx_handle_s
{
    uint8_t (*contactless_init)(void);                                             /**< point to a contactless_init function address */
    uint8_t (*contactless_deinit)(void);                                           /**< point to a contactless_deinit function address */
    uint8_t (*contactless_transceiver)(uint8_t *in_buf, uint8_t in_len, 
                                       uint8_t *out_buf, uint8_t *out_len);        /**< point to a contactless_transceiver function address */
    void (*delay_ms)(uint32_t ms);                                                 /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);                               /**< point to a debug_print function address */
    uint8_t type;                                                                  /**< classic type */
    uint8_t inited;                                                                /**< inited flag */
} fm11rfxx_handle_t;

/**
 * @brief fm11rfxx information structure definition
 */
typedef struct fm11rfxx_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} fm11rfxx_info_t;

/**
 * @}
 */

/**
 * @defgroup fm11rfxx_link_driver fm11rfxx link driver function
 * @brief    fm11rfxx link driver modules
 * @ingroup  fm11rfxx_driver
 * @{
 */

/**
 * @brief     initialize fm11rfxx_handle_t structure
 * @param[in] HANDLE points to a fm11rfxx handle structure
 * @param[in] STRUCTURE is fm11rfxx_handle_t
 * @note      none
 */
#define DRIVER_FM11RFXX_LINK_INIT(HANDLE, STRUCTURE)                  memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link contactless_init function
 * @param[in] HANDLE points to a fm11rfxx handle structure
 * @param[in] FUC points to a contactless_init function address
 * @note      none
 */
#define DRIVER_FM11RFXX_LINK_CONTACTLESS_INIT(HANDLE, FUC)           (HANDLE)->contactless_init = FUC

/**
 * @brief     link contactless_deinit function
 * @param[in] HANDLE points to a fm11rfxx handle structure
 * @param[in] FUC points to a contactless_deinit function address
 * @note      none
 */
#define DRIVER_FM11RFXX_LINK_CONTACTLESS_DEINIT(HANDLE, FUC)         (HANDLE)->contactless_deinit = FUC

/**
 * @brief     link contactless_transceiver function
 * @param[in] HANDLE points to a fm11rfxx handle structure
 * @param[in] FUC points to a contactless_transceiver function address
 * @note      none
 */
#define DRIVER_FM11RFXX_LINK_CONTACTLESS_TRANSCEIVER(HANDLE, FUC)    (HANDLE)->contactless_transceiver = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE points to a fm11rfxx handle structure
 * @param[in] FUC points to a delay_ms function address
 * @note      none
 */
#define DRIVER_FM11RFXX_LINK_DELAY_MS(HANDLE, FUC)                   (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE points to a fm11rfxx handle structure
 * @param[in] FUC points to a debug_print function address
 * @note      none
 */
#define DRIVER_FM11RFXX_LINK_DEBUG_PRINT(HANDLE, FUC)                (HANDLE)->debug_print = FUC

/**
 * @}
 */

/**
 * @defgroup fm11rfxx_basic_driver fm11rfxx basic driver function
 * @brief    fm11rfxx basic driver modules
 * @ingroup  fm11rfxx_driver
 * @{
 */

/**
 * @brief      get chip information
 * @param[out] *info points to a fm11rfxx info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t fm11rfxx_info(fm11rfxx_info_t *info);

/**
 * @brief     initialize the chip
 * @param[in] *handle points to a fm11rfxx handle structure
 * @return    status code
 *            - 0 success
 *            - 1 contactless initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 * @note      none
 */
uint8_t fm11rfxx_init(fm11rfxx_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle points to a fm11rfxx handle structure
 * @return    status code
 *            - 0 success
 *            - 1 contactless deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t fm11rfxx_deinit(fm11rfxx_handle_t *handle);

/**
 * @brief      fm11rfxx request
 * @param[in]  *handle points to a fm11rfxx handle structure
 * @param[out] *type points to a type buffer
 * @return     status code
 *             - 0 success
 *             - 1 request failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 output_len is invalid
 *             - 5 type is invalid
 * @note       none
 */
uint8_t fm11rfxx_request(fm11rfxx_handle_t *handle, fm11rfxx_type_t *type);

/**
 * @brief      fm11rfxx wake up
 * @param[in]  *handle points to a fm11rfxx handle structure
 * @param[out] *type points to a type buffer
 * @return     status code
 *             - 0 success
 *             - 1 wake up failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 output_len is invalid
 *             - 5 type is invalid
 * @note       none
 */
uint8_t fm11rfxx_wake_up(fm11rfxx_handle_t *handle, fm11rfxx_type_t *type);

/**
 * @brief      fm11rfxx halt
 * @param[in]  *handle points to a fm11rfxx handle structure
 * @return     status code
 *             - 0 success
 *             - 1 halt failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t fm11rfxx_halt(fm11rfxx_handle_t *handle);

/**
 * @brief     fm11rfxx set the load modulation
 * @param[in] *handle points to a fm11rfxx handle structure
 * @param[in] mod is the load modulation
 * @return    status code
 *            - 0 success
 *            - 1 set modulation failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 output_len is invalid
 *            - 5 ack error
 * @note      none
 */
uint8_t fm11rfxx_set_modulation(fm11rfxx_handle_t *handle, fm11rfxx_load_modulation_t mod);

/**
 * @brief     fm11rfxx set the personalized uid
 * @param[in] *handle points to a fm11rfxx handle structure
 * @param[in] type is the personalized uid type
 * @return    status code
 *            - 0 success
 *            - 1 set personalized uid failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 output_len is invalid
 *            - 5 ack error
 * @note      none
 */
uint8_t fm11rfxx_set_personalized_uid(fm11rfxx_handle_t *handle, fm11rfxx_personalized_uid_t type);

/**
 * @brief      fm11rfxx anti collision cl1
 * @param[in]  *handle points to a fm11rfxx handle structure
 * @param[out] *id points to an id buffer
 * @return     status code
 *             - 0 success
 *             - 1 anti collision cl1 failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 output_len is invalid
 *             - 5 check error
 * @note       none
 */
uint8_t fm11rfxx_anticollision_cl1(fm11rfxx_handle_t *handle, uint8_t id[4]);

/**
 * @brief      fm11rfxx anti collision cl2
 * @param[in]  *handle points to a fm11rfxx handle structure
 * @param[out] *id points to an id buffer
 * @return     status code
 *             - 0 success
 *             - 1 anti collision cl2 failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 output_len is invalid
 *             - 5 check error
 * @note       none
 */
uint8_t fm11rfxx_anticollision_cl2(fm11rfxx_handle_t *handle, uint8_t id[4]);

/**
 * @brief     fm11rfxx select cl1
 * @param[in] *handle points to a fm11rfxx handle structure
 * @param[in] *id points to an id buffer
 * @return    status code
 *            - 0 success
 *            - 1 select cl1 failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 output_len is invalid
 *            - 5 sak error
 * @note      none
 */
uint8_t fm11rfxx_select_cl1(fm11rfxx_handle_t *handle, uint8_t id[4]);

/**
 * @brief     fm11rfxx select cl2
 * @param[in] *handle points to a fm11rfxx handle structure
 * @param[in] *id points to an id buffer
 * @return    status code
 *            - 0 success
 *            - 1 select cl2 failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 output_len is invalid
 *            - 5 sak error
 * @note      none
 */
uint8_t fm11rfxx_select_cl2(fm11rfxx_handle_t *handle, uint8_t id[4]);

/**
 * @brief     fm11rfxx authentication
 * @param[in] *handle points to a fm11rfxx handle structure
 * @param[in] *id points to an id buffer
 * @param[in] block is the block of authentication
 * @param[in] key_type is the authentication key type
 * @param[in] *key points to a key buffer
 * @return    status code
 *            - 0 success
 *            - 1 authentication failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t fm11rfxx_authentication(fm11rfxx_handle_t *handle, uint8_t id[4], uint8_t block,
                                fm11rfxx_authentication_key_t key_type, uint8_t key[6]);

/**
 * @brief      fm11rfxx read
 * @param[in]  *handle points to a fm11rfxx handle structure
 * @param[in]  block is the block of read
 * @param[out] *data points to a data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 output_len is invalid
 *             - 5 crc error
 * @note       none
 */
uint8_t fm11rfxx_read(fm11rfxx_handle_t *handle, uint8_t block, uint8_t data[16]);

/**
 * @brief     fm11rfxx write
 * @param[in] *handle points to a fm11rfxx handle structure
 * @param[in] block is the block of write
 * @param[in] *data points to a data buffer
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 output_len is invalid
 *            - 5 ack error
 * @note      none
 */
uint8_t fm11rfxx_write(fm11rfxx_handle_t *handle, uint8_t block, uint8_t data[16]);

/**
 * @brief     fm11rfxx init one block as a value block
 * @param[in] *handle points to a fm11rfxx handle structure
 * @param[in] block is the set block
 * @param[in] value is the inited value
 * @param[in] addr is the set addr
 * @return    status code
 *            - 0 success
 *            - 1 value init failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 output_len is invalid
 *            - 5 ack error
 * @note      none
 */
uint8_t fm11rfxx_value_init(fm11rfxx_handle_t *handle, uint8_t block, int32_t value, uint8_t addr);

/**
 * @brief     fm11rfxx value write
 * @param[in] *handle points to a fm11rfxx handle structure
 * @param[in] block is the set block
 * @param[in] value is the write value
 * @param[in] addr is the set addr
 * @return    status code
 *            - 0 success
 *            - 1 value write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 output_len is invalid
 *            - 5 ack error
 * @note      none
 */
uint8_t fm11rfxx_value_write(fm11rfxx_handle_t *handle, uint8_t block, int32_t value, uint8_t addr);

/**
 * @brief      fm11rfxx value read
 * @param[in]  *handle points to a fm11rfxx handle structure
 * @param[in]  block is the block of read
 * @param[out] *value points to a value buffer
 * @param[out] *addr points to an address buffer
 * @return     status code
 *             - 0 success
 *             - 1 value read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 output_len is invalid
 *             - 5 crc error
 *             - 6 value is invalid
 *             - 7 block is invalid
 * @note       none
 */
uint8_t fm11rfxx_value_read(fm11rfxx_handle_t *handle, uint8_t block, int32_t *value, uint8_t *addr);

/**
 * @brief     fm11rfxx increment
 * @param[in] *handle points to a fm11rfxx handle structure
 * @param[in] block is the block of increment
 * @param[in] value is the increment value
 * @return    status code
 *            - 0 success
 *            - 1 increment failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 output_len is invalid
 *            - 5 ack error
 *            - 6 invalid operation
 * @note      none
 */
uint8_t fm11rfxx_increment(fm11rfxx_handle_t *handle, uint8_t block, uint32_t value);

/**
 * @brief     fm11rfxx decrement
 * @param[in] *handle points to a fm11rfxx handle structure
 * @param[in] block is the block of decrement
 * @param[in] value is the decrement value
 * @return    status code
 *            - 0 success
 *            - 1 decrement failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 output_len is invalid
 *            - 5 ack error
 *            - 6 invalid operation
 * @note      none
 */
uint8_t fm11rfxx_decrement(fm11rfxx_handle_t *handle, uint8_t block, uint32_t value);

/**
 * @brief     fm11rfxx transfer
 * @param[in] *handle points to a fm11rfxx handle structure
 * @param[in] block is the block of transfer
 * @return    status code
 *            - 0 success
 *            - 1 transfer failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 output_len is invalid
 *            - 5 ack error
 *            - 6 invalid operation
 * @note      none
 */
uint8_t fm11rfxx_transfer(fm11rfxx_handle_t *handle, uint8_t block);

/**
 * @brief     fm11rfxx restore
 * @param[in] *handle points to a fm11rfxx handle structure
 * @param[in] block is the block of restore
 * @return    status code
 *            - 0 success
 *            - 1 restore failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 output_len is invalid
 *            - 5 ack error
 *            - 6 invalid operation
 * @note      none
 */
uint8_t fm11rfxx_restore(fm11rfxx_handle_t *handle, uint8_t block);

/**
 * @brief      fm11rfxx block number to sector number
 * @param[in]  *handle points to a fm11rfxx handle structure
 * @param[in]  block is the block number
 * @param[out] *sector points to a sector number buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t fm11rfxx_block_to_sector(fm11rfxx_handle_t *handle, uint8_t block, uint8_t *sector);

/**
 * @brief      fm11rfxx get the sector's block counter
 * @param[in]  *handle points to a fm11rfxx handle structure
 * @param[in]  sector is the sector number
 * @param[out] *count points to a count buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t fm11rfxx_sector_block_count(fm11rfxx_handle_t *handle, uint8_t sector, uint8_t *count);

/**
 * @brief      fm11rfxx get the sector's first block
 * @param[in]  *handle points to a fm11rfxx handle structure
 * @param[in]  sector is the sector number
 * @param[out] *block points to a block number buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t fm11rfxx_sector_first_block(fm11rfxx_handle_t *handle, uint8_t sector, uint8_t *block);

/**
 * @brief      fm11rfxx get the sector's last block
 * @param[in]  *handle points to a fm11rfxx handle structure
 * @param[in]  sector is the sector number
 * @param[out] *block points to a block number buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t fm11rfxx_sector_last_block(fm11rfxx_handle_t *handle, uint8_t sector, uint8_t *block);

/**
 * @brief     fm11rfxx set the sector permission
 * @param[in] *handle points to a fm11rfxx handle structure
 * @param[in] sector is the set sector
 * @param[in] *key_a points to a key a buffer
 * @param[in] block_0_0_4 is the block0(block0-4) permission
 * @param[in] block_1_5_9 is the block1(block5-9) permission
 * @param[in] block_2_10_14 is the block2(block10-14) permission
 * @param[in] block_3_15 is the block3(block15) permission
 * @param[in] user_data is the user data
 * @param[in] *key_b points to a key b buffer
 * @return    status code
 *            - 0 success
 *            - 1 set sector permission failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 output_len is invalid
 *            - 5 ack error
 * @note      block_0_0_4, block_1_5_9, block_2_10_14, permission(c1_c2_c3) definition is below
 *            c1  c2  c3        read        write        increment        decrement/transfer/restore
 *            0   0   0        keya|b       keya|b         keya|b                  keya|b
 *            0   1   0        keya|b       never          never                   never
 *            1   0   0        keya|b       keyb           never                   never
 *            1   1   0        keya|b       keyb           keyb                    keya|b
 *            0   0   1        keya|b       never          never                   keya|b
 *            0   1   1        keyb         keyb           never                   never
 *            1   0   1        keyb         never          never                   never
 *            1   1   1        never        never          never                   never
 *                                                                                      
 *            block_3_15 permission(c1_c2_c3) definition is below
 *            c1  c2  c3    keya_read    keya_write    access_read    access_write    keyb_read    keyb_write
 *            0   0   0      never        keya            keya           never          keya          keya
 *            0   1   0      never        never           keya           never          keya          never
 *            1   0   0      never        keyb           keya|b          never          never         keyb
 *            1   1   0      never        never          keya|b          never          never         never
 *            0   0   1      never        keya            keya           keya           keya          keya
 *            0   1   1      never        keyb           keya|b          keyb           never         keyb
 *            1   0   1      never        never          keya|b          keyb           never         never
 *            1   1   1      never        never          keya|b          never          never         never
 */
uint8_t fm11rfxx_set_sector_permission(fm11rfxx_handle_t *handle,
                                       uint8_t sector, uint8_t key_a[6], 
                                       uint8_t block_0_0_4, uint8_t block_1_5_9,
                                       uint8_t block_2_10_14, uint8_t block_3_15,
                                       uint8_t user_data, uint8_t key_b[6]);

/**
 * @brief      fm11rfxx get the sector permission
 * @param[in]  *handle points to a fm11rfxx handle structure
 * @param[in]  sector is the get sector
 * @param[out] *block_0_0_4 points to a block0(block0-4) permission buffer
 * @param[out] *block_1_5_9 points to a block1(block5-9) permission buffer
 * @param[out] *block_2_10_14 points to a block2(block10-14) permission buffer
 * @param[out] *block_3_15 points to a block3(block15) permission buffer
 * @param[out] *user_data points to a user data buffer
 * @param[out] *key_b points to a key b buffer
 * @return     status code
 *             - 0 success
 *             - 1 get sector permission failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 output_len is invalid
 *             - 5 crc error
 *             - 6 data is invalid
 * @note       none
 */
uint8_t fm11rfxx_get_sector_permission(fm11rfxx_handle_t *handle,
                                       uint8_t sector, uint8_t *block_0_0_4, uint8_t *block_1_5_9,
                                       uint8_t *block_2_10_14, uint8_t *block_3_15,
                                       uint8_t *user_data, uint8_t key_b[6]);

/**
 * @}
 */

/**
 * @defgroup fm11rfxx_extern_driver fm11rfxx extern driver function
 * @brief    fm11rfxx extern driver modules
 * @ingroup  fm11rfxx_driver
 * @{
 */

/**
 * @brief         transceiver data
 * @param[in]     *handle points to a fm11rfxx handle structure
 * @param[in]     *in_buf points to an input buffer
 * @param[in]     in_len is the input length
 * @param[out]    *out_buf points to an output buffer
 * @param[in,out] *out_len points to an output length buffer
 * @return        status code
 *                - 0 success
 *                - 1 transceiver failed
 * @note          none
 */
uint8_t fm11rfxx_transceiver(fm11rfxx_handle_t *handle, uint8_t *in_buf, uint8_t in_len, uint8_t *out_buf, uint8_t *out_len);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
