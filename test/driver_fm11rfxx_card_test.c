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
 * @file      driver_fm11rfxx_card_test.c
 * @brief     driver fm11rfxx card test source file
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

#include "driver_fm11rfxx_card_test.h"
#include <stdlib.h>

static fm11rfxx_handle_t gs_handle;        /**< fm11rfxx handle */

/**
 * @brief  card test
 * @return status code
 *         - 0 success
 *         - 1 test failed
 * @note   none
 */
uint8_t fm11rfxx_card_test(void)
{
    uint8_t res;
    uint8_t i;
    uint8_t addr;
    int32_t value_check;
    uint8_t id[4];
    uint8_t key[6];
    uint8_t data[16];
    uint8_t data_check[16];
    uint8_t block_0_0_4;
    uint8_t block_1_5_9;
    uint8_t block_2_10_14;
    uint8_t block_3_15;
    uint8_t user_data;
    uint8_t key_b[6];
    fm11rfxx_type_t type;
    fm11rfxx_info_t info;
    
    /* link function */
    DRIVER_FM11RFXX_LINK_INIT(&gs_handle, fm11rfxx_handle_t);
    DRIVER_FM11RFXX_LINK_CONTACTLESS_INIT(&gs_handle, fm11rfxx_interface_contactless_init);
    DRIVER_FM11RFXX_LINK_CONTACTLESS_DEINIT(&gs_handle, fm11rfxx_interface_contactless_deinit);
    DRIVER_FM11RFXX_LINK_CONTACTLESS_TRANSCEIVER(&gs_handle, fm11rfxx_interface_contactless_transceiver);
    DRIVER_FM11RFXX_LINK_DELAY_MS(&gs_handle, fm11rfxx_interface_delay_ms);
    DRIVER_FM11RFXX_LINK_DEBUG_PRINT(&gs_handle, fm11rfxx_interface_debug_print);
    
    /* get information */
    res = fm11rfxx_info(&info);
    if (res != 0)
    {
        fm11rfxx_interface_debug_print("fm11rfxx: get info failed.\n");
        
        return 1;
    }
    else
    {
        /* print chip info */
        fm11rfxx_interface_debug_print("fm11rfxx: chip is %s.\n", info.chip_name);
        fm11rfxx_interface_debug_print("fm11rfxx: manufacturer is %s.\n", info.manufacturer_name);
        fm11rfxx_interface_debug_print("fm11rfxx: interface is %s.\n", info.interface);
        fm11rfxx_interface_debug_print("fm11rfxx: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        fm11rfxx_interface_debug_print("fm11rfxx: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        fm11rfxx_interface_debug_print("fm11rfxx: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        fm11rfxx_interface_debug_print("fm11rfxx: max current is %0.2fmA.\n", info.max_current_ma);
        fm11rfxx_interface_debug_print("fm11rfxx: max temperature is %0.1fC.\n", info.temperature_max);
        fm11rfxx_interface_debug_print("fm11rfxx: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* start register test */
    fm11rfxx_interface_debug_print("fm11rfxx: start card test.\n");
    
    /* init */
    res = fm11rfxx_init(&gs_handle);
    if (res != 0)
    {
        fm11rfxx_interface_debug_print("fm11rfxx: init failed.\n");
        
        return 1;
    }
    
    /* wake up */
    res = fm11rfxx_wake_up(&gs_handle, &type);
    if (res != 0)
    {
        fm11rfxx_interface_debug_print("fm11rfxx: wake up failed.\n");
        (void)fm11rfxx_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output the type */
    if (type == FM11RFXX_TYPE_FM11RF08)
    {
        fm11rfxx_interface_debug_print("fm11rfxx: find fm11rf08 card.\n");
    }
    else if (type == FM11RFXX_TYPE_FM11RF32)
    {
        fm11rfxx_interface_debug_print("fm11rfxx: find fm11rf32 card.\n");
    }
    else
    {
        fm11rfxx_interface_debug_print("fm11rfxx: invalid type.\n");
        (void)fm11rfxx_deinit(&gs_handle);
        
        return 1;
    }
    
    /* get the id */
    res = fm11rfxx_anticollision_cl1(&gs_handle, id);
    if (res != 0)
    {
        fm11rfxx_interface_debug_print("fm11rfxx: anti collision cl1 failed.\n");
        (void)fm11rfxx_deinit(&gs_handle);
        
        return 1;
    }
    
    /* select cl1 */
    res = fm11rfxx_select_cl1(&gs_handle, id);
    if (res != 0)
    {
        fm11rfxx_interface_debug_print("fm11rfxx: anti collision cl1 failed.\n");
        (void)fm11rfxx_deinit(&gs_handle);
        
        return 1;
    }
    
    fm11rfxx_interface_debug_print("fm11rfxx: id is 0x%02X 0x%02X 0x%02X 0x%02X.\n", id[0], id[1], id[2], id[3]);
    
    /* authentication block 0 */
    key[0] = 0xFF;
    key[1] = 0xFF;
    key[2] = 0xFF;
    key[3] = 0xFF;
    key[4] = 0xFF;
    key[5] = 0xFF;
    res = fm11rfxx_authentication(&gs_handle, id, 0x00,
                                  FM11RFXX_AUTHENTICATION_KEY_A, key);
    if (res != 0)
    {
        fm11rfxx_interface_debug_print("fm11rfxx: authentication failed.\n");
        (void)fm11rfxx_deinit(&gs_handle);
        
        return 1;
    }
    fm11rfxx_interface_debug_print("fm11rfxx: authentication block 0 ok.\n");
    
    /* read block 0 */
    res = fm11rfxx_read(&gs_handle, 0x00, data_check);
    if (res != 0)
    {
        fm11rfxx_interface_debug_print("fm11rfxx: read failed.\n");
        (void)fm11rfxx_deinit(&gs_handle);
        
        return 1;
    }
    fm11rfxx_interface_debug_print("fm11rfxx: block 0 is ");
    for (i = 0; i < 16; i++)
    {
        fm11rfxx_interface_debug_print("0x%02X ", data_check[i]);
    }
    fm11rfxx_interface_debug_print("\n");
    
    /* authentication block 1 */
    key[0] = 0xFF;
    key[1] = 0xFF;
    key[2] = 0xFF;
    key[3] = 0xFF;
    key[4] = 0xFF;
    key[5] = 0xFF;
    res = fm11rfxx_authentication(&gs_handle, id, 0x01,
                                  FM11RFXX_AUTHENTICATION_KEY_A, key);
    if (res != 0)
    {
        fm11rfxx_interface_debug_print("fm11rfxx: authentication failed.\n");
        (void)fm11rfxx_deinit(&gs_handle);
        
        return 1;
    }
    fm11rfxx_interface_debug_print("fm11rfxx: authentication block 1 ok.\n");
    
    /* write block 1 */
    for (i = 0; i < 16; i++)
    {
        data[i] = rand() % 256;
    }
    fm11rfxx_interface_debug_print("fm11rfxx: write block 1: ");
    for (i = 0; i < 16; i++)
    {
        fm11rfxx_interface_debug_print("0x%02X ", data[i]);
    }
    fm11rfxx_interface_debug_print("\n");
    res = fm11rfxx_write(&gs_handle, 0x01, data);
    if (res != 0)
    {
        fm11rfxx_interface_debug_print("fm11rfxx: write failed.\n");
        (void)fm11rfxx_deinit(&gs_handle);
        
        return 1;
    }
    
    /* read block 1 */
    res = fm11rfxx_read(&gs_handle, 0x01, data_check);
    if (res != 0)
    {
        fm11rfxx_interface_debug_print("fm11rfxx: read failed.\n");
        (void)fm11rfxx_deinit(&gs_handle);
        
        return 1;
    }
    fm11rfxx_interface_debug_print("fm11rfxx: read block 1: ");
    for (i = 0; i < 16; i++)
    {
        fm11rfxx_interface_debug_print("0x%02X ", data_check[i]);
    }
    fm11rfxx_interface_debug_print("\n");
    fm11rfxx_interface_debug_print("fm11rfxx: check data %s.\n", memcmp(data, data_check, 16) == 0 ? "ok" : "error");
    
    /* authentication block 2 */
    key[0] = 0xFF;
    key[1] = 0xFF;
    key[2] = 0xFF;
    key[3] = 0xFF;
    key[4] = 0xFF;
    key[5] = 0xFF;
    res = fm11rfxx_authentication(&gs_handle, id, 0x02,
                                  FM11RFXX_AUTHENTICATION_KEY_A, key);
    if (res != 0)
    {
        fm11rfxx_interface_debug_print("fm11rfxx: authentication failed.\n");
        (void)fm11rfxx_deinit(&gs_handle);
        
        return 1;
    }
    fm11rfxx_interface_debug_print("fm11rfxx: authentication block 2 ok.\n");
    
    /* value init */
    res = fm11rfxx_value_init(&gs_handle, 0x02, 0, 0x02);
    if (res != 0)
    {
        fm11rfxx_interface_debug_print("fm11rfxx: value init failed.\n");
        (void)fm11rfxx_deinit(&gs_handle);
        
        return 1;
    }
    fm11rfxx_interface_debug_print("fm11rfxx: init value is %d.\n", 0);
    
    /* read */
    res = fm11rfxx_value_read(&gs_handle, 0x02, &value_check, &addr);
    if (res != 0)
    {
        fm11rfxx_interface_debug_print("fm11rfxx: value read failed.\n");
        (void)fm11rfxx_deinit(&gs_handle);
        
        return 1;
    }
    fm11rfxx_interface_debug_print("fm11rfxx: read value is %d.\n", value_check);
    
    /* value write */
    res = fm11rfxx_value_write(&gs_handle, 0x02, -10, 0x02);
    if (res != 0)
    {
        fm11rfxx_interface_debug_print("fm11rfxx: value init failed.\n");
        (void)fm11rfxx_deinit(&gs_handle);
        
        return 1;
    }
    fm11rfxx_interface_debug_print("fm11rfxx: write value is %d.\n", -10);
    
    /* read */
    res = fm11rfxx_value_read(&gs_handle, 0x02, &value_check, &addr);
    if (res != 0)
    {
        fm11rfxx_interface_debug_print("fm11rfxx: value read failed.\n");
        (void)fm11rfxx_deinit(&gs_handle);
        
        return 1;
    }
    fm11rfxx_interface_debug_print("fm11rfxx: read value is %d.\n", value_check);
    
    /* increment */
    res = fm11rfxx_increment(&gs_handle, 0x02, 6);
    if (res != 0)
    {
        fm11rfxx_interface_debug_print("fm11rfxx: increment failed.\n");
        (void)fm11rfxx_deinit(&gs_handle);
        
        return 1;
    }
    res = fm11rfxx_transfer(&gs_handle, 0x02);
    if (res != 0)
    {
        fm11rfxx_interface_debug_print("fm11rfxx: transfer failed.\n");
        (void)fm11rfxx_deinit(&gs_handle);
        
        return 1;
    }
    fm11rfxx_interface_debug_print("fm11rfxx: increment %d.\n", 6);
    res = fm11rfxx_value_read(&gs_handle, 0x02, &value_check, &addr);
    if (res != 0)
    {
        fm11rfxx_interface_debug_print("fm11rfxx: value read failed.\n");
        (void)fm11rfxx_deinit(&gs_handle);
        
        return 1;
    }
    fm11rfxx_interface_debug_print("fm11rfxx: read value is %d.\n", value_check);
    
    /* increment */
    res = fm11rfxx_increment(&gs_handle, 0x02, 6);
    if (res != 0)
    {
        fm11rfxx_interface_debug_print("fm11rfxx: increment failed.\n");
        (void)fm11rfxx_deinit(&gs_handle);
        
        return 1;
    }
    res = fm11rfxx_transfer(&gs_handle, 0x02);
    if (res != 0)
    {
        fm11rfxx_interface_debug_print("fm11rfxx: transfer failed.\n");
        (void)fm11rfxx_deinit(&gs_handle);
        
        return 1;
    }
    fm11rfxx_interface_debug_print("fm11rfxx: increment %d.\n", 6);
    res = fm11rfxx_value_read(&gs_handle, 0x02, &value_check, &addr);
    if (res != 0)
    {
        fm11rfxx_interface_debug_print("fm11rfxx: value read failed.\n");
        (void)fm11rfxx_deinit(&gs_handle);
        
        return 1;
    }
    fm11rfxx_interface_debug_print("fm11rfxx: read value is %d.\n", value_check);
    
    /* increment */
    res = fm11rfxx_increment(&gs_handle, 0x02, 6);
    if (res != 0)
    {
        fm11rfxx_interface_debug_print("fm11rfxx: increment failed.\n");
        (void)fm11rfxx_deinit(&gs_handle);
        
        return 1;
    }
    res = fm11rfxx_transfer(&gs_handle, 0x02);
    if (res != 0)
    {
        fm11rfxx_interface_debug_print("fm11rfxx: transfer failed.\n");
        (void)fm11rfxx_deinit(&gs_handle);
        
        return 1;
    }
    fm11rfxx_interface_debug_print("fm11rfxx: increment %d.\n", 6);
    res = fm11rfxx_value_read(&gs_handle, 0x02, &value_check, &addr);
    if (res != 0)
    {
        fm11rfxx_interface_debug_print("fm11rfxx: value read failed.\n");
        (void)fm11rfxx_deinit(&gs_handle);
        
        return 1;
    }
    fm11rfxx_interface_debug_print("fm11rfxx: read value is %d.\n", value_check);
    
    /* decrement */
    res = fm11rfxx_decrement(&gs_handle, 0x02, 5);
    if (res != 0)
    {
        fm11rfxx_interface_debug_print("fm11rfxx: decrement failed.\n");
        (void)fm11rfxx_deinit(&gs_handle);
        
        return 1;
    }
    res = fm11rfxx_transfer(&gs_handle, 0x02);
    if (res != 0)
    {
        fm11rfxx_interface_debug_print("fm11rfxx: transfer failed.\n");
        (void)fm11rfxx_deinit(&gs_handle);
        
        return 1;
    }
    fm11rfxx_interface_debug_print("fm11rfxx: decrement %d.\n", 5);
    res = fm11rfxx_value_read(&gs_handle, 0x02, &value_check, &addr);
    if (res != 0)
    {
        fm11rfxx_interface_debug_print("fm11rfxx: value read failed.\n");
        (void)fm11rfxx_deinit(&gs_handle);
        
        return 1;
    }
    fm11rfxx_interface_debug_print("fm11rfxx: read value is %d.\n", value_check);
    
    /* decrement */
    res = fm11rfxx_decrement(&gs_handle, 0x02, 5);
    if (res != 0)
    {
        fm11rfxx_interface_debug_print("fm11rfxx: decrement failed.\n");
        (void)fm11rfxx_deinit(&gs_handle);
        
        return 1;
    }
    res = fm11rfxx_transfer(&gs_handle, 0x02);
    if (res != 0)
    {
        fm11rfxx_interface_debug_print("fm11rfxx: transfer failed.\n");
        (void)fm11rfxx_deinit(&gs_handle);
        
        return 1;
    }
    fm11rfxx_interface_debug_print("fm11rfxx: decrement %d.\n", 5);
    res = fm11rfxx_value_read(&gs_handle, 0x02, &value_check, &addr);
    if (res != 0)
    {
        fm11rfxx_interface_debug_print("fm11rfxx: value read failed.\n");
        (void)fm11rfxx_deinit(&gs_handle);
        
        return 1;
    }
    fm11rfxx_interface_debug_print("fm11rfxx: read value is %d.\n", value_check);
    
    /* decrement */
    res = fm11rfxx_decrement(&gs_handle, 0x02, 5);
    if (res != 0)
    {
        fm11rfxx_interface_debug_print("fm11rfxx: decrement failed.\n");
        (void)fm11rfxx_deinit(&gs_handle);
        
        return 1;
    }
    res = fm11rfxx_transfer(&gs_handle, 0x02);
    if (res != 0)
    {
        fm11rfxx_interface_debug_print("fm11rfxx: transfer failed.\n");
        (void)fm11rfxx_deinit(&gs_handle);
        
        return 1;
    }
    fm11rfxx_interface_debug_print("fm11rfxx: decrement %d.\n", 5);
    res = fm11rfxx_value_read(&gs_handle, 0x02, &value_check, &addr);
    if (res != 0)
    {
        fm11rfxx_interface_debug_print("fm11rfxx: value read failed.\n");
        (void)fm11rfxx_deinit(&gs_handle);
        
        return 1;
    }
    fm11rfxx_interface_debug_print("fm11rfxx: read value is %d.\n", value_check);
    
    /* restore from block 2 */
    res = fm11rfxx_restore(&gs_handle, 0x02);
    if (res != 0)
    {
        fm11rfxx_interface_debug_print("fm11rfxx: restore failed.\n");
        (void)fm11rfxx_deinit(&gs_handle);
        
        return 1;
    }
    
    /* transfer to block 2 */
    res = fm11rfxx_transfer(&gs_handle, 0x02);
    if (res != 0)
    {
        fm11rfxx_interface_debug_print("fm11rfxx: transfer failed.\n");
        (void)fm11rfxx_deinit(&gs_handle);
        
        return 1;
    }
    
    res = fm11rfxx_read(&gs_handle, 0x02, data_check);
    if (res != 0)
    {
        fm11rfxx_interface_debug_print("fm11rfxx: read failed.\n");
        (void)fm11rfxx_deinit(&gs_handle);
        
        return 1;
    }
    fm11rfxx_interface_debug_print("fm11rfxx: read block 2: ");
    for (i = 0; i < 16; i++)
    {
        fm11rfxx_interface_debug_print("0x%02X ", data_check[i]);
    }
    fm11rfxx_interface_debug_print("\n");
    
    /* block to sector */
    for (i = 0; i < 200; i += 15)
    {
        uint8_t sector;
        
        res = fm11rfxx_block_to_sector(&gs_handle, i, &sector);
        if (res != 0)
        {
            fm11rfxx_interface_debug_print("fm11rfxx: block to sector failed.\n");
            (void)fm11rfxx_deinit(&gs_handle);
            
            return 1;
        }
        fm11rfxx_interface_debug_print("fm11rfxx: block%d to sector is %d.\n", i, sector);
    }
    
    /* sector to block count */
    for (i = 0; i < 40; i += 5)
    {
        uint8_t count;
        
        res = fm11rfxx_sector_block_count(&gs_handle, i, &count);
        if (res != 0)
        {
            fm11rfxx_interface_debug_print("fm11rfxx: sector to block count failed.\n");
            (void)fm11rfxx_deinit(&gs_handle);
            
            return 1;
        }
        fm11rfxx_interface_debug_print("fm11rfxx: sector%d block count is %d.\n", i, count);
    }
    
    /* sector to block count */
    for (i = 0; i < 40; i += 5)
    {
        uint8_t first;
        uint8_t last;
        
        /* get the first block */
        res = fm11rfxx_sector_first_block(&gs_handle, i, &first);
        if (res != 0)
        {
            fm11rfxx_interface_debug_print("fm11rfxx: first block failed.\n");
            (void)fm11rfxx_deinit(&gs_handle);
            
            return 1;
        }
        
        /* get the last block */
        res = fm11rfxx_sector_last_block(&gs_handle, i, &last);
        if (res != 0)
        {
            fm11rfxx_interface_debug_print("fm11rfxx: last block failed.\n");
            (void)fm11rfxx_deinit(&gs_handle);
            
            return 1;
        }
        fm11rfxx_interface_debug_print("fm11rfxx: sector%d: block %d - %d.\n", i, first, last);
    }
    
    /* get the last block */
    res = fm11rfxx_sector_last_block(&gs_handle, 0, &addr);
    if (res != 0)
    {
        fm11rfxx_interface_debug_print("fm11rfxx: last block failed.\n");
        (void)fm11rfxx_deinit(&gs_handle);
        
        return 1;
    }
    
    /* authentication block 3 */
    key[0] = 0xFF;
    key[1] = 0xFF;
    key[2] = 0xFF;
    key[3] = 0xFF;
    key[4] = 0xFF;
    key[5] = 0xFF;
    res = fm11rfxx_authentication(&gs_handle, id, addr,
                                  FM11RFXX_AUTHENTICATION_KEY_A, key);
    if (res != 0)
    {
        fm11rfxx_interface_debug_print("fm11rfxx: authentication failed.\n");
        (void)fm11rfxx_deinit(&gs_handle);
        
        return 1;
    }
    fm11rfxx_interface_debug_print("fm11rfxx: authentication block 3 ok.\n");
    
    /* get sector permission */
    res = fm11rfxx_get_sector_permission(&gs_handle,
                                         0, &block_0_0_4, &block_1_5_9,
                                         &block_2_10_14, &block_3_15,
                                         &user_data, key_b);
    if (res != 0)
    {
        fm11rfxx_interface_debug_print("fm11rfxx: get sector permission failed.\n");
        (void)fm11rfxx_deinit(&gs_handle);
        
        return 1;
    }
    fm11rfxx_interface_debug_print("fm11rfxx: permission block0 block1 block2 block3 0x%02X 0x%02X 0x%02X 0x%02X.\n",
                                   block_0_0_4, block_1_5_9, block_2_10_14, block_3_15);
    fm11rfxx_interface_debug_print("fm11rfxx: user data is 0x%02X.\n", user_data);
    fm11rfxx_interface_debug_print("fm11rfxx: keyb is 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X.\n",
                                   key_b[0], key_b[1], key_b[2], key_b[3], key_b[4], key_b[5]);
    
    /* set sector permission */
    res = fm11rfxx_set_sector_permission(&gs_handle, 0, key, 0x0, 0x0, 0x0, 0x1, 0x00, key);
    if (res != 0)
    {
        fm11rfxx_interface_debug_print("fm11rfxx: set sector permission failed.\n");
        (void)fm11rfxx_deinit(&gs_handle);
        
        return 1;
    }
    
    /* halt */
    res = fm11rfxx_halt(&gs_handle);
    if (res != 0)
    {
        fm11rfxx_interface_debug_print("fm11rfxx: halt failed.\n");
        (void)fm11rfxx_deinit(&gs_handle);
        
        return 1;
    }
    
    /* finish register */
    fm11rfxx_interface_debug_print("fm11rfxx: finish card test.\n");
    (void)fm11rfxx_deinit(&gs_handle);
    
    return 0;
}
