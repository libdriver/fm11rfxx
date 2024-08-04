[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver FM11RFXX

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/fm11rfxx/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

FM11RFXX是上海复旦微电子有限公司开发的非接触式IC卡芯片，该芯片具有1K×8bits EEPROM和4K×8bit EEPROM两种大小，读取器天线和非接触式卡之间的最大通信范围约为10cm，数据以106Kbit/s的速率进行半双工交换。FM11RFXX是一款真正的多应用智能卡，具有用硬件逻辑实现的处理器卡的功能，并且具有非常高的加密和通信电路安全性能，因此FM11RFX可以特别定制以满足支付卡的要求，该支付卡可用于公共交通和类似应用的票务系统。非接触式智能卡包含三个组件：FM11RFXX芯片天线和PVC（或PET）材料的卡底座。芯片不需要电池，当芯片位于耦合设备天线附近时，高速RF通信接口允许以106Kbit/s的速度传输数据。

LibDriver FM11RFXX是LibDriver推出的FM11RFXX全功能驱动，该驱动提供块读取，块写入，数值增加，数值减少等功能并且它符合MISRA标准。

本仓库包含子模块，您需要增加“--recursive”选项完整克隆整个工程。

```shell
git clone https://github.com/libdriver/fm11rfxx.git --recursive
```

### 目录

  - [说明](#说明)
  - [安装](#安装)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [文档](#文档)
  - [贡献](#贡献)
  - [版权](#版权)
  - [联系我们](#联系我们)

### 说明

/src目录包含了LibDriver FM11RFXX的源文件。

/interface目录包含了LibDriver FM11RFXX与平台无关的RF总线模板。

/test目录包含了LibDriver FM11RFXX驱动测试程序，该程序可以简单的测试芯片必要功能。

/example目录包含了LibDriver FM11RFXX编程范例。

/doc目录包含了LibDriver FM11RFXX离线文档。

/datasheet目录包含了FM11RFXX数据手册。

/project目录包含了常用Linux与单片机开发板的工程样例。所有工程均采用shell脚本作为调试方法，详细内容可参考每个工程里面的README.md。

/misra目录包含了LibDriver MISRA代码扫描结果。

### 安装

参考/interface目录下与平台无关的RF总线模板，完成指定平台的RF总线驱动。

将/src目录，您使用平台的接口驱动和您开发的驱动加入工程，如果您想要使用默认的范例驱动，可以将/example目录加入您的工程。

### 使用

您可以参考/example目录下的编程范例完成适合您的驱动，如果您想要使用默认的编程范例，以下是它们的使用方法。

#### example basic

```C
#include "driver_fm11rfxx_basic.h"

uint8_t res;
fm11rfxx_authentication_key_t key_type;
uint8_t key[6];
fm11rfxx_type_t type; 
uint8_t id[4];
uint8_t data[16];

/* init */
res = fm11rfxx_basic_init();
if (res != 0)
{
    return 1;
}

...
    
/* search */
res = fm11rfxx_basic_search(&type, id, 50);
if (res != 0)
{
    (void)fm11rfxx_basic_deinit();

    return 1;
}

/* ouput the type */
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

...

key_type = MIFARE_CLASSIC_AUTHENTICATION_KEY_A;
key[0] = 0xFF;
key[1] = 0xFF;
key[2] = 0xFF;
key[3] = 0xFF;
key[4] = 0xFF;
key[5] = 0xFF;

...
    
/* read */
res = fm11rfxx_basic_read(1, data, key_type, key);
if (res != 0)
{
    (void)fm11rfxx_basic_deinit();

    return 1;
}

...

/* write */
res = fm11rfxx_basic_write(1, data, key_type, key);
if (res != 0)
{
    (void)fm11rfxx_basic_deinit();

    return 1;
}

...

/* value init */
res = fm11rfxx_basic_value_init(2, 2, 2, key_type, key);
if (res != 0)
{
    (void)fm11rfxx_basic_deinit();

    return 1;
}

...

/* write the value */
res = fm11rfxx_basic_value_write(2, 100, 2, key_type, key);
if (res != 0)
{
    (void)fm11rfxx_basic_deinit();

    return 1;
}    

...

/* read the value */
res = fm11rfxx_basic_value_read(2, &value, &addr, key_type, key);
if (res != 0)
{
    (void)fm11rfxx_basic_deinit();

    return 1;
}

...

/* increment the value */
res = fm11rfxx_basic_value_increment(2, 10, key_type, key);
if (res != 0)
{
    (void)fm11rfxx_basic_deinit();

    return 1;
}

...

/* decrement the value */
res = fm11rfxx_basic_value_decrement(2, 20, key_type, key);
if (res != 0)
{
    (void)fm11rfxx_basic_deinit();

    return 1;
}

...

(void)fm11rfxx_basic_deinit();

return 0;    
```

### 文档

在线文档: [https://www.libdriver.com/docs/fm11rfxx/index.html](https://www.libdriver.com/docs/fm11rfxx/index.html)。

离线文档: /doc/html/index.html。

### 贡献

请参考CONTRIBUTING.md。

### 版权

版权 (c) 2015 - 现在 LibDriver 版权所有

MIT 许可证（MIT）

特此免费授予任何获得本软件副本和相关文档文件（下称“软件”）的人不受限制地处置该软件的权利，包括不受限制地使用、复制、修改、合并、发布、分发、转授许可和/或出售该软件副本，以及再授权被配发了本软件的人如上的权利，须在下列条件下：

上述版权声明和本许可声明应包含在该软件的所有副本或实质成分中。

本软件是“如此”提供的，没有任何形式的明示或暗示的保证，包括但不限于对适销性、特定用途的适用性和不侵权的保证。在任何情况下，作者或版权持有人都不对任何索赔、损害或其他责任负责，无论这些追责来自合同、侵权或其它行为中，还是产生于、源于或有关于本软件以及本软件的使用或其它处置。

### 联系我们

请联系lishifenging@outlook.com。