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
 * @file      main.c
 * @brief     main source file
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

#include "driver_fm11rfxx_basic.h"
#include "driver_fm11rfxx_card_test.h"
#include <getopt.h>
#include <math.h>
#include <stdlib.h>

/**
 * @brief     fm11rfxx full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *             - 0 success
 *             - 1 run failed
 *             - 5 param is invalid
 * @note      none
 */
uint8_t fm11rfxx(uint8_t argc, char **argv)
{
    int c;
    int longindex = 0;
    const char short_options[] = "hipe:t:";
    const struct option long_options[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {"port", no_argument, NULL, 'p'},
        {"example", required_argument, NULL, 'e'},
        {"test", required_argument, NULL, 't'},
        {"block", required_argument, NULL, 1},
        {"data", required_argument, NULL, 2},
        {"key", required_argument, NULL, 3},
        {"key-type", required_argument, NULL, 4},
        {"value", required_argument, NULL, 5},
        {NULL, 0, NULL, 0},
    };
    char type[33] = "unknown";
    int32_t value = 0x00000000;
    uint8_t block = 0x00;
    uint8_t data[16] = {0};
    uint8_t key[6] = {0};
    fm11rfxx_authentication_key_t key_type = FM11RFXX_AUTHENTICATION_KEY_A;
    
    /* if no params */
    if (argc == 1)
    {
        /* goto the help */
        goto help;
    }
    
    /* init 0 */
    optind = 0;
    
    /* parse */
    do
    {
        /* parse the args */
        c = getopt_long(argc, argv, short_options, long_options, &longindex);
        
        /* judge the result */
        switch (c)
        {
            /* help */
            case 'h' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "h");
                
                break;
            }
            
            /* information */
            case 'i' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "i");
                
                break;
            }
            
            /* port */
            case 'p' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "p");
                
                break;
            }
            
            /* example */
            case 'e' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "e_%s", optarg);
                
                break;
            }
            
            /* test */
            case 't' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "t_%s", optarg);
                
                break;
            }
            
            /* block */
            case 1 :
            {
                char *p;
                uint16_t l;
                uint16_t i;
                uint64_t hex_data;

                /* set the data */
                l = strlen(optarg);

                /* check the header */
                if (l >= 2)
                {
                    if (strncmp(optarg, "0x", 2) == 0)
                    {
                        p = optarg + 2;
                        l -= 2;
                    }
                    else if (strncmp(optarg, "0X", 2) == 0)
                    {
                        p = optarg + 2;
                        l -= 2;
                    }
                    else
                    {
                        p = optarg;
                    }
                }
                else
                {
                    p = optarg;
                }
                
                /* init 0 */
                hex_data = 0;

                /* loop */
                for (i = 0; i < l; i++)
                {
                    if ((p[i] <= '9') && (p[i] >= '0'))
                    {
                        hex_data += (p[i] - '0') * (uint32_t)pow(16, l - i - 1);
                    }
                    else if ((p[i] <= 'F') && (p[i] >= 'A'))
                    {
                        hex_data += ((p[i] - 'A') + 10) * (uint32_t)pow(16, l - i - 1);
                    }
                    else if ((p[i] <= 'f') && (p[i] >= 'a'))
                    {
                        hex_data += ((p[i] - 'a') + 10) * (uint32_t)pow(16, l - i - 1);
                    }
                    else
                    {
                        return 5;
                    }
                }
                
                /* set the block */
                block = hex_data & 0xFF;
                
                break;
            }
            
            /* data */
            case 2 :
            {
                uint8_t size;
                uint8_t i;
                char *p;
                
                /* get the size */
                size = (uint8_t)strlen(optarg);
                
                /* check the size */
                if ((size == 32) || (size == 34))
                {
                    /* check ok */
                }
                else
                {
                    return 5;
                }

                /* check the size */
                if (strncmp(optarg, "0x", 2) == 0)
                {
                    p = optarg + 2;
                    size -= 2;
                }
                else if (strncmp(optarg, "0X", 2) == 0)
                {
                    p = optarg + 2;
                    size -= 2;
                }
                else
                {
                    p = optarg;
                }
                
                /* check the size */
                if (size != 32)
                {
                    return 5;
                }

                /* set the data */
                for (i = 0; i < size; i += 2)
                {
                    if (('A' <= p[i]) && (p[i] <= 'Z'))
                    {
                        data[i / 2] = p[i] - 'A' + 10;
                        data[i / 2] *= 16;
                    }
                    else if (('a' <= p[i]) && (p[i] <= 'z'))
                    {
                        data[i / 2] = p[i] - 'a' + 10;
                        data[i / 2] *= 16;
                    }
                    else if (('0' <= p[i]) && (p[i] <= '9'))
                    {
                        data[i / 2] = p[i] - '0';
                        data[i / 2] *= 16;
                    }
                    else
                    {
                        return 5;
                    }
                    if (('A' <= p[i + 1]) && (p[i + 1] <= 'Z'))
                    {
                        data[i / 2 ] += p[i + 1] - 'A' + 10;
                    }
                    else if (('a' <= p[i + 1]) && (p[i + 1] <= 'z'))
                    {
                        data[i / 2 ] += p[i + 1] - 'a' + 10;
                    }
                    else if (('0' <= p[i + 1]) && (p[i + 1] <= '9'))
                    {
                        data[i / 2 ] += p[i + 1] - '0';
                    }
                    else
                    {
                        return 5;
                    }
                }

                break;
            }
            
            /* key */
            case 3 :
            {
                uint8_t size;
                uint8_t i;
                char *p;
                
                /* get the size */
                size = (uint8_t)strlen(optarg);
                
                /* check the size */
                if ((size == 12) || (size == 14))
                {
                    /* check ok */
                }
                else
                {
                    return 5;
                }

                /* check the size */
                if (strncmp(optarg, "0x", 2) == 0)
                {
                    p = optarg + 2;
                    size -= 2;
                }
                else if (strncmp(optarg, "0X", 2) == 0)
                {
                    p = optarg + 2;
                    size -= 2;
                }
                else
                {
                    p = optarg;
                }
                
                /* check the size */
                if (size != 12)
                {
                    return 5;
                }

                /* copy data */
                for (i = 0; i < size; i += 2)
                {
                    if (('A' <= p[i]) && (p[i] <= 'Z'))
                    {
                        key[i / 2] = p[i] - 'A' + 10;
                        key[i / 2] *= 16;
                    }
                    else if (('a' <= p[i]) && (p[i] <= 'z'))
                    {
                        key[i / 2] = p[i] - 'a' + 10;
                        key[i / 2] *= 16;
                    }
                    else if (('0' <= p[i]) && (p[i] <= '9'))
                    {
                        key[i / 2] = p[i] - '0';
                        key[i / 2] *= 16;
                    }
                    else
                    {
                        return 5;
                    }
                    if (('A' <= p[i + 1]) && (p[i + 1] <= 'Z'))
                    {
                        key[i / 2 ] += p[i + 1] - 'A' + 10;
                    }
                    else if (('a' <= p[i + 1]) && (p[i + 1] <= 'z'))
                    {
                        key[i / 2 ] += p[i + 1] - 'a' + 10;
                    }
                    else if (('0' <= p[i + 1]) && (p[i + 1] <= '9'))
                    {
                        key[i / 2 ] += p[i + 1] - '0';
                    }
                    else
                    {
                        return 5;
                    }
                }

                break;
            }
             
            /* key-type */
            case 4 :
            {
                /* set the key type */
                if (strcmp("A", optarg) == 0)
                {
                    key_type = FM11RFXX_AUTHENTICATION_KEY_A;
                }
                else if (strcmp("B", optarg) == 0)
                {
                    key_type = FM11RFXX_AUTHENTICATION_KEY_B;
                }
                else
                {
                    return 5;
                }

                break;
            }
            
            /* value */
            case 5 :
            {
                /* set the value */
                value = atol(optarg);

                break;
            }
            
            /* the end */
            case -1 :
            {
                break;
            }
            
            /* others */
            default :
            {
                return 5;
            }
        }
    } while (c != -1);

    /* run the function */
    if (strcmp("t_card", type) == 0)
    {
        uint8_t res;
        
        /* run the card test */
        res = fm11rfxx_card_test();
        if (res != 0)
        {
            return 1;
        }
        
        return 0;
    }
    else if (strcmp("e_halt", type) == 0)
    {
        uint8_t res;
        
        /* basic init */
        res = fm11rfxx_basic_init();
        if (res != 0)
        {
            return 1;
        }
        
        /* halt */
        res = fm11rfxx_basic_halt();
        if (res != 0)
        {
            (void)fm11rfxx_basic_deinit();
            
            return 1;
        }

        /* output */
        fm11rfxx_interface_debug_print("fm11rfxx: halt.\n");
        
        /* basic deinit */
        (void)fm11rfxx_basic_deinit();
        
        return 0;
    }
    else if (strcmp("e_wake-up", type) == 0)
    {
        uint8_t res;
        
        /* basic init */
        res = fm11rfxx_basic_init();
        if (res != 0)
        {
            return 1;
        }
        
        /* wake_up */
        res = fm11rfxx_basic_wake_up();
        if (res != 0)
        {
            (void)fm11rfxx_basic_deinit();
            
            return 1;
        }

        /* output */
        fm11rfxx_interface_debug_print("fm11rfxx: wake up.\n");
        
        /* basic deinit */
        (void)fm11rfxx_basic_deinit();
        
        return 0;
    }
    else if (strcmp("e_read", type) == 0)
    {
        fm11rfxx_type_t chip_type; 
        uint8_t res;
        uint8_t i;
        uint8_t id[4];
        
        /* basic init */
        res = fm11rfxx_basic_init();
        if (res != 0)
        {
            return 1;
        }
        
        /* search */
        res = fm11rfxx_basic_search(&chip_type, id, 50);
        if (res != 0)
        {
            (void)fm11rfxx_basic_deinit();
            
            return 1;
        }
        
        /* output */
        if (chip_type == FM11RFXX_TYPE_FM11RF08)
        {
            fm11rfxx_interface_debug_print("fm11rfxx: find fm11rf08 card.\n");
        }
        else if (chip_type == FM11RFXX_TYPE_FM11RF32)
        {
            fm11rfxx_interface_debug_print("fm11rfxx: find fm11rf32 card.\n");
        }
        else
        {
            fm11rfxx_interface_debug_print("fm11rfxx: invalid type.\n");
            (void)fm11rfxx_basic_deinit();
            
            return 1;
        }
        fm11rfxx_interface_debug_print("fm11rfxx: id is ");
        for (i = 0; i < 4; i++)
        {
            fm11rfxx_interface_debug_print("0x%02X ", id[i]);
        }
        fm11rfxx_interface_debug_print("\n");
        
        /* read */
        res = fm11rfxx_basic_read(block, data, key_type, key);
        if (res != 0)
        {
            (void)fm11rfxx_basic_deinit();
            
            return 1;
        }
        
        /* output */
        fm11rfxx_interface_debug_print("fm11rfxx: block is ");
        for (i = 0; i < 16; i++)
        {
            fm11rfxx_interface_debug_print("0x%02X ", data[i]);
        }
        fm11rfxx_interface_debug_print("\n");
        
        /* basic deinit */
        (void)fm11rfxx_basic_deinit();
        
        return 0;
    }
    else if (strcmp("e_write", type) == 0)
    {
        fm11rfxx_type_t chip_type; 
        uint8_t res;
        uint8_t i;
        uint8_t id[4];

        /* basic init */
        res = fm11rfxx_basic_init();
        if (res != 0)
        {
            return 1;
        }
        
        /* search */
        res = fm11rfxx_basic_search(&chip_type, id, 50);
        if (res != 0)
        {
            (void)fm11rfxx_basic_deinit();
            
            return 1;
        }
        
        /* output */
        if (chip_type == FM11RFXX_TYPE_FM11RF08)
        {
            fm11rfxx_interface_debug_print("fm11rfxx: find fm11rf08 card.\n");
        }
        else if (chip_type == FM11RFXX_TYPE_FM11RF32)
        {
            fm11rfxx_interface_debug_print("fm11rfxx: find fm11rf32 card.\n");
        }
        else
        {
            fm11rfxx_interface_debug_print("fm11rfxx: invalid type.\n");
            (void)fm11rfxx_basic_deinit();
            
            return 1;
        }
        fm11rfxx_interface_debug_print("fm11rfxx: id is ");
        for (i = 0; i < 4; i++)
        {
            fm11rfxx_interface_debug_print("0x%02X ", id[i]);
        }
        fm11rfxx_interface_debug_print("\n");
        
        /* output */
        fm11rfxx_interface_debug_print("fm11rfxx: data is ");
        for (i = 0; i < 16; i++)
        {
            fm11rfxx_interface_debug_print("0x%02X ", data[i]);
        }
        fm11rfxx_interface_debug_print("\n");
        
        /* write */
        res = fm11rfxx_basic_write(block, data, key_type, key);
        if (res != 0)
        {
            (void)fm11rfxx_basic_deinit();
            
            return 1;
        }
        
        /* basic deinit */
        (void)fm11rfxx_basic_deinit();
        
        return 0;
    }
    else if (strcmp("e_value-init", type) == 0)
    {
        fm11rfxx_type_t chip_type; 
        uint8_t res;
        uint8_t i;
        uint8_t id[4];

        /* basic init */
        res = fm11rfxx_basic_init();
        if (res != 0)
        {
            return 1;
        }

        /* search */
        res = fm11rfxx_basic_search(&chip_type, id, 50);
        if (res != 0)
        {
            (void)fm11rfxx_basic_deinit();
            
            return 1;
        }
        
        /* output */
        if (chip_type == FM11RFXX_TYPE_FM11RF08)
        {
            fm11rfxx_interface_debug_print("fm11rfxx: find fm11rf08 card.\n");
        }
        else if (chip_type == FM11RFXX_TYPE_FM11RF32)
        {
            fm11rfxx_interface_debug_print("fm11rfxx: find fm11rf32 card.\n");
        }
        else
        {
            fm11rfxx_interface_debug_print("fm11rfxx: invalid type.\n");
            (void)fm11rfxx_basic_deinit();
            
            return 1;
        }
        fm11rfxx_interface_debug_print("fm11rfxx: id is ");
        for (i = 0; i < 4; i++)
        {
            fm11rfxx_interface_debug_print("0x%02X ", id[i]);
        }
        fm11rfxx_interface_debug_print("\n");
        
        /* value init */
        res = fm11rfxx_basic_value_init(block, value, block, key_type, key);
        if (res != 0)
        {
            (void)fm11rfxx_basic_deinit();
            
            return 1;
        }
        fm11rfxx_interface_debug_print("fm11rfxx: init block%d as value %d.\n", block, value);
        
        /* basic deinit */
        (void)fm11rfxx_basic_deinit();
        
        return 0;
    }
    else if (strcmp("e_value-write", type) == 0)
    {
        fm11rfxx_type_t chip_type; 
        uint8_t res;
        uint8_t i;
        uint8_t id[4];

        /* basic init */
        res = fm11rfxx_basic_init();
        if (res != 0)
        {
            return 1;
        }

        /* search */
        res = fm11rfxx_basic_search(&chip_type, id, 50);
        if (res != 0)
        {
            (void)fm11rfxx_basic_deinit();
            
            return 1;
        }
        
        /* output */
        if (chip_type == FM11RFXX_TYPE_FM11RF08)
        {
            fm11rfxx_interface_debug_print("fm11rfxx: find fm11rf08 card.\n");
        }
        else if (chip_type == FM11RFXX_TYPE_FM11RF32)
        {
            fm11rfxx_interface_debug_print("fm11rfxx: find fm11rf32 card.\n");
        }
        else
        {
            fm11rfxx_interface_debug_print("fm11rfxx: invalid type.\n");
            (void)fm11rfxx_basic_deinit();
            
            return 1;
        }
        fm11rfxx_interface_debug_print("fm11rfxx: id is ");
        for (i = 0; i < 4; i++)
        {
            fm11rfxx_interface_debug_print("0x%02X ", id[i]);
        }
        fm11rfxx_interface_debug_print("\n");
        
        /* value write */
        res = fm11rfxx_basic_value_write(block, value, block, key_type, key);
        if (res != 0)
        {
            (void)fm11rfxx_basic_deinit();
            
            return 1;
        }
        fm11rfxx_interface_debug_print("fm11rfxx: write block%d %d.\n", block, value);
        
        /* basic deinit */
        (void)fm11rfxx_basic_deinit();
        
        return 0;
    }
    else if (strcmp("e_value-read", type) == 0)
    {
        fm11rfxx_type_t chip_type; 
        uint8_t addr;
        uint8_t res;
        uint8_t i;
        uint8_t id[4];
        int32_t value;

        /* basic init */
        res = fm11rfxx_basic_init();
        if (res != 0)
        {
            return 1;
        }

        /* search */
        res = fm11rfxx_basic_search(&chip_type, id, 50);
        if (res != 0)
        {
            (void)fm11rfxx_basic_deinit();
            
            return 1;
        }
        
        /* output */
        if (chip_type == FM11RFXX_TYPE_FM11RF08)
        {
            fm11rfxx_interface_debug_print("fm11rfxx: find fm11rf08 card.\n");
        }
        else if (chip_type == FM11RFXX_TYPE_FM11RF32)
        {
            fm11rfxx_interface_debug_print("fm11rfxx: find fm11rf32 card.\n");
        }
        else
        {
            fm11rfxx_interface_debug_print("fm11rfxx: invalid type.\n");
            (void)fm11rfxx_basic_deinit();
            
            return 1;
        }
        fm11rfxx_interface_debug_print("fm11rfxx: id is ");
        for (i = 0; i < 4; i++)
        {
            fm11rfxx_interface_debug_print("0x%02X ", id[i]);
        }
        fm11rfxx_interface_debug_print("\n");
        
        /* read value */
        res = fm11rfxx_basic_value_read(block, &value, &addr, key_type, key);
        if (res != 0)
        {
            (void)fm11rfxx_basic_deinit();
            
            return 1;
        }
        fm11rfxx_interface_debug_print("fm11rfxx: read block%d value %d.\n", block, value);
        
        /* basic deinit */
        (void)fm11rfxx_basic_deinit();
        
        return 0;
    }
    else if (strcmp("e_value-increment", type) == 0)
    {
        fm11rfxx_type_t chip_type; 
        uint8_t res;
        uint8_t i;
        uint8_t id[4];

        /* basic init */
        res = fm11rfxx_basic_init();
        if (res != 0)
        {
            return 1;
        }

        /* search */
        res = fm11rfxx_basic_search(&chip_type, id, 50);
        if (res != 0)
        {
            (void)fm11rfxx_basic_deinit();
            
            return 1;
        }
        
        /* output */
        if (chip_type == FM11RFXX_TYPE_FM11RF08)
        {
            fm11rfxx_interface_debug_print("fm11rfxx: find fm11rf08 card.\n");
        }
        else if (chip_type == FM11RFXX_TYPE_FM11RF32)
        {
            fm11rfxx_interface_debug_print("fm11rfxx: find fm11rf32 card.\n");
        }
        else
        {
            fm11rfxx_interface_debug_print("fm11rfxx: invalid type.\n");
            (void)fm11rfxx_basic_deinit();
            
            return 1;
        }
        fm11rfxx_interface_debug_print("fm11rfxx: id is ");
        for (i = 0; i < 4; i++)
        {
            fm11rfxx_interface_debug_print("0x%02X ", id[i]);
        }
        fm11rfxx_interface_debug_print("\n");
        
        /* value increment */
        res = fm11rfxx_basic_value_increment(block, value, key_type, key);
        if (res != 0)
        {
            (void)fm11rfxx_basic_deinit();
            
            return 1;
        }
        fm11rfxx_interface_debug_print("fm11rfxx: increment block%d %d.\n", block, value);
        
        /* basic deinit */
        (void)fm11rfxx_basic_deinit();
        
        return 0;
    }
    else if (strcmp("e_value-decrement", type) == 0)
    {
        fm11rfxx_type_t chip_type; 
        uint8_t res;
        uint8_t i;
        uint8_t id[4];

        /* basic init */
        res = fm11rfxx_basic_init();
        if (res != 0)
        {
            return 1;
        }

        /* search */
        res = fm11rfxx_basic_search(&chip_type, id, 50);
        if (res != 0)
        {
            (void)fm11rfxx_basic_deinit();
            
            return 1;
        }
        
        /* output */
        if (chip_type == FM11RFXX_TYPE_FM11RF08)
        {
            fm11rfxx_interface_debug_print("fm11rfxx: find fm11rf08 card.\n");
        }
        else if (chip_type == FM11RFXX_TYPE_FM11RF32)
        {
            fm11rfxx_interface_debug_print("fm11rfxx: find fm11rf32 card.\n");
        }
        else
        {
            fm11rfxx_interface_debug_print("fm11rfxx: invalid type.\n");
            (void)fm11rfxx_basic_deinit();
            
            return 1;
        }
        fm11rfxx_interface_debug_print("fm11rfxx: id is ");
        for (i = 0; i < 4; i++)
        {
            fm11rfxx_interface_debug_print("0x%02X ", id[i]);
        }
        fm11rfxx_interface_debug_print("\n");
        
        /* value decrement */
        res = fm11rfxx_basic_value_decrement(block, value, key_type, key);
        if (res != 0)
        {
            (void)fm11rfxx_basic_deinit();
            
            return 1;
        }

        /* output */
        fm11rfxx_interface_debug_print("fm11rfxx: decrement block%d %d.\n", block, value);
        
        /* basic deint */
        (void)fm11rfxx_basic_deinit();
        
        return 0;
    }
    else if (strcmp("h", type) == 0)
    {
        help:
        fm11rfxx_interface_debug_print("Usage:\n");
        fm11rfxx_interface_debug_print("  fm11rfxx (-i | --information)\n");
        fm11rfxx_interface_debug_print("  fm11rfxx (-h | --help)\n");
        fm11rfxx_interface_debug_print("  fm11rfxx (-p | --port)\n");
        fm11rfxx_interface_debug_print("  fm11rfxx (-t card | --test=card)\n");
        fm11rfxx_interface_debug_print("  fm11rfxx (-e halt | --example=halt)\n");
        fm11rfxx_interface_debug_print("  fm11rfxx (-e wake-up | --example=wake-up)\n");
        fm11rfxx_interface_debug_print("  fm11rfxx (-e read | --example=read) [--key-type=<A | B>] [--key=<authentication>]\n");
        fm11rfxx_interface_debug_print("           [--block=<addr>]\n");
        fm11rfxx_interface_debug_print("  fm11rfxx (-e write | --example=write) [--key-type=<A | B>] [--key=<authentication>]\n");
        fm11rfxx_interface_debug_print("           [--block=<addr>] [--data=<hex>]\n");
        fm11rfxx_interface_debug_print("  fm11rfxx (-e value-init | --example=value-init) [--key-type=<A | B>] [--key=<authentication>]\n");
        fm11rfxx_interface_debug_print("           [--block=<addr>] [--value=<dec>]\n");
        fm11rfxx_interface_debug_print("  fm11rfxx (-e value-write | --example=value-write) [--key-type=<A | B>] [--key=<authentication>]\n");
        fm11rfxx_interface_debug_print("           [--block=<addr>] [--value=<dec>]\n");
        fm11rfxx_interface_debug_print("  fm11rfxx (-e value-read | --example=value-read) [--key-type=<A | B>] [--key=<authentication>]\n");
        fm11rfxx_interface_debug_print("           [--block=<addr>]\n");
        fm11rfxx_interface_debug_print("  fm11rfxx (-e value-increment | --example=value-increment) [--key-type=<A | B>] [--key=<authentication>]\n");
        fm11rfxx_interface_debug_print("           [--block=<addr>] [--value=<dec>]\n");
        fm11rfxx_interface_debug_print("  fm11rfxx (-e value-decrement | --example=value-decrement) [--key-type=<A | B>] [--key=<authentication>]\n");
        fm11rfxx_interface_debug_print("           [--block=<addr>] [--value=<dec>]\n");
        fm11rfxx_interface_debug_print("\n");
        fm11rfxx_interface_debug_print("Options:\n");
        fm11rfxx_interface_debug_print("      --block=<addr>            Set the block address and it is hexadecimal.([default: 0x00])\n");
        fm11rfxx_interface_debug_print("      --data=<hex>              Set the input data and it is hexadecimal with 16 bytes(strlen=32).([default: 0x0123456789ABCDEF0123456789ABCDEF])\n");
        fm11rfxx_interface_debug_print("  -e <halt | wake-up | read | write | value-init | value-write | value-read | value-increment\n");
        fm11rfxx_interface_debug_print("     | value-decrement>, --example=<halt | wake-up | read | write | value-init | value-write\n");
        fm11rfxx_interface_debug_print("     | value-read | value-increment | value-decrement>\n");
        fm11rfxx_interface_debug_print("                                Run the driver example.\n");
        fm11rfxx_interface_debug_print("  -h, --help                    Show the help.\n");
        fm11rfxx_interface_debug_print("  -i, --information             Show the chip information.\n");
        fm11rfxx_interface_debug_print("      --key=<authentication>    Set the key of authentication and it is hexadecimal with 6 bytes(strlen=12).([default: 0xFFFFFFFFFFFF])\n");
        fm11rfxx_interface_debug_print("      --key-type=<A | B>        Set the key type of authentication.([default: A])\n");
        fm11rfxx_interface_debug_print("  -p, --port                    Display the pin connections of the current board.\n");
        fm11rfxx_interface_debug_print("  -t <card>, --test=<card>      Run the driver test.\n");
        fm11rfxx_interface_debug_print("      --value=<dec>             Set the input value.([default: 0])\n");

        return 0;
    }
    else if (strcmp("i", type) == 0)
    {
        fm11rfxx_info_t info;
        
        /* print fm11rfxx info */
        fm11rfxx_info(&info);
        fm11rfxx_interface_debug_print("fm11rfxx: chip is %s.\n", info.chip_name);
        fm11rfxx_interface_debug_print("fm11rfxx: manufacturer is %s.\n", info.manufacturer_name);
        fm11rfxx_interface_debug_print("fm11rfxx: interface is %s.\n", info.interface);
        fm11rfxx_interface_debug_print("fm11rfxx: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        fm11rfxx_interface_debug_print("fm11rfxx: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        fm11rfxx_interface_debug_print("fm11rfxx: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        fm11rfxx_interface_debug_print("fm11rfxx: max current is %0.2fmA.\n", info.max_current_ma);
        fm11rfxx_interface_debug_print("fm11rfxx: max temperature is %0.1fC.\n", info.temperature_max);
        fm11rfxx_interface_debug_print("fm11rfxx: min temperature is %0.1fC.\n", info.temperature_min);
        
        return 0;
    }
    else if (strcmp("p", type) == 0)
    {
        /* print pin connection */
        fm11rfxx_interface_debug_print("fm11rfxx: SPI interface SCK connected to GPIO11(BCM).\n");
        fm11rfxx_interface_debug_print("fm11rfxx: SPI interface MISO connected to GPIO9(BCM).\n");
        fm11rfxx_interface_debug_print("fm11rfxx: SPI interface MOSI connected to GPIO10(BCM).\n");
        fm11rfxx_interface_debug_print("fm11rfxx: SPI interface CS connected to GPIO8(BCM).\n");
        fm11rfxx_interface_debug_print("fm11rfxx: IIC interface SCL connected to GPIO3(BCM).\n");
        fm11rfxx_interface_debug_print("fm11rfxx: IIC interface SDA connected to GPIO2(BCM).\n");
        fm11rfxx_interface_debug_print("fm11rfxx: UART interface TX connected to GPIO14(BCM).\n");
        fm11rfxx_interface_debug_print("fm11rfxx: UART interface RX connected to GPIO15(BCM).\n");
        fm11rfxx_interface_debug_print("fm11rfxx: INT connected to GPIO17(BCM).\n");
        fm11rfxx_interface_debug_print("fm11rfxx: RESET connected to GPIO27(BCM).\n");
        
        return 0;
    }
    else
    {
        return 5;
    }
}

/**
 * @brief     main function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *             - 0 success
 * @note      none
 */
int main(uint8_t argc, char **argv)
{
    uint8_t res;

    res = fm11rfxx(argc, argv);
    if (res == 0)
    {
        /* run success */
    }
    else if (res == 1)
    {
        fm11rfxx_interface_debug_print("fm11rfxx: run failed.\n");
    }
    else if (res == 5)
    {
        fm11rfxx_interface_debug_print("fm11rfxx: param is invalid.\n");
    }
    else
    {
        fm11rfxx_interface_debug_print("fm11rfxx: unknown status code.\n");
    }

    return 0;
}
