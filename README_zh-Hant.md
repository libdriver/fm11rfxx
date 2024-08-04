[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver FM11RFXX

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/fm11rfxx/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

FM11RFXX是上海復旦微電子有限公司開發的非接觸式IC卡晶片，該晶片具有1K×8bits EEPROM和4K×8bit EEPROM兩種大小，讀取器天線和非接觸式卡之間的最大通信範圍約為10cm，數據以106Kbit/s的速率進行半雙工交換。 FM11RFXX是一款真正的多應用智慧卡，具有用硬體邏輯實現的處理器卡的功能，並且具有非常高的加密和通信電路安全性能，囙此FM11RFX可以特別定制以滿足支付卡的要求，該支付卡可用於公共交通和類似應用的票務系統。 非接觸式智慧卡包含三個組件：FM11RFXX晶片天線和PVC（或PET）資料的卡底座。 晶片不需要電池，當晶片位於耦合設備天線附近時，高速RF通信介面允許以106Kbit/s的速度傳輸數據。

LibDriver FM11RFXX是LibDriver推出的FM11RFXX全功能驅動，該驅動提供塊讀取，塊寫入，數值新增，數值减少等功能並且它符合MISRA標準。

本倉庫包含子模塊，您需要增加“--recursive”選項完整克隆整個工程。

```shell
git clone https://github.com/libdriver/fm11rfxx.git --recursive
```

### 目錄

  - [說明](#說明)
  - [安裝](#安裝)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [文檔](#文檔)
  - [貢獻](#貢獻)
  - [版權](#版權)
  - [聯繫我們](#聯繫我們)

### 說明

/src目錄包含了LibDriver FM11RFXX的源文件。

/interface目錄包含了LibDriver FM11RFXX與平台無關的RF總線模板。

/test目錄包含了LibDriver FM11RFXX驅動測試程序，該程序可以簡單的測試芯片必要功能。

/example目錄包含了LibDriver FM11RFXX編程範例。

/doc目錄包含了LibDriver FM11RFXX離線文檔。

/datasheet目錄包含了FM11RFXX數據手冊。

/project目錄包含了常用Linux與單片機開發板的工程樣例。所有工程均採用shell腳本作為調試方法，詳細內容可參考每個工程裡面的README.md。

/misra目錄包含了LibDriver MISRA程式碼掃描結果。

### 安裝

參考/interface目錄下與平台無關的RF總線模板，完成指定平台的RF總線驅動。

將/src目錄，您使用平臺的介面驅動和您開發的驅動加入工程，如果您想要使用默認的範例驅動，可以將/example目錄加入您的工程。

### 使用

您可以參考/example目錄下的程式設計範例完成適合您的驅動，如果您想要使用默認的程式設計範例，以下是它們的使用方法。

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

### 文檔

在線文檔: [https://www.libdriver.com/docs/fm11rfxx/index.html](https://www.libdriver.com/docs/fm11rfxx/index.html)。

離線文檔: /doc/html/index.html。

### 貢獻

請參攷CONTRIBUTING.md。

### 版權

版權 (c) 2015 - 現在 LibDriver 版權所有

MIT 許可證（MIT）

特此免費授予任何獲得本軟件副本和相關文檔文件（下稱“軟件”）的人不受限制地處置該軟件的權利，包括不受限制地使用、複製、修改、合併、發布、分發、轉授許可和/或出售該軟件副本，以及再授權被配發了本軟件的人如上的權利，須在下列條件下：

上述版權聲明和本許可聲明應包含在該軟件的所有副本或實質成分中。

本軟件是“如此”提供的，沒有任何形式的明示或暗示的保證，包括但不限於對適銷性、特定用途的適用性和不侵權的保證。在任何情況下，作者或版權持有人都不對任何索賠、損害或其他責任負責，無論這些追責來自合同、侵權或其它行為中，還是產生於、源於或有關於本軟件以及本軟件的使用或其它處置。

### 聯繫我們

請聯繫lishifenging@outlook.com。
