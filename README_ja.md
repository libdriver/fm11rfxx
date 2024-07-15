[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver FM11RFXX

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/fm11rfxx/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

FM11RFXX は、上海 FM 株式会社が開発した非接触型 IC カード チップです。チップには 1K x 8 ビットの EEPROM または 4K x 8 ビットの EEPROM 構成があり、リーダー アンテナと非接触型カード間の最大通信範囲は約 10cm で、データは 106 Kbit/s の速度で半二重で交換されます。FM11RFXX は、ハードウェア ロジックで実現されたプロセッサ カードの機能を備えた真のマルチアプリケーション スマート カードであり、暗号化および通信回路による非常に高いセキュリティ パフォーマンスも備えているため、FM11RFXX は、公共交通機関のチケット システムや類似のアプリケーションに使用できる支払いカードの要件を満たすように特別にカスタマイズできます。非接触型スマート カードには、FM11RFXX チップ アンテナと PVC (または PET) 素材のカード ベースの 3 つのコンポーネントが含まれています。バッテリーは必要ありません。チップを結合デバイス アンテナの近くに配置すると、高速 RF 通信インターフェイスにより、106 Kbit/s でデータを送信できます。

LibDriver FM11RFXXは、LibDriverによって起動されるFM11RFXXの全機能ドライバーであり、読み取りブロック、書き込みブロック、値のインクリメント、値のデクリメントなどの機能を提供します。 LibDriverはMISRAに準拠しています。

このリポジトリにはサブモジュールが含まれており、「--recursive」を追加してプロジェクト全体を複製する必要があります。

```shell
git clone https://github.com/libdriver/fm11rfxx.git --recursive
```

### 目次

  - [説明](#説明)
  - [インストール](#インストール)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [ドキュメント](#ドキュメント)
  - [貢献](#貢献)
  - [著作権](#著作権)
  - [連絡して](#連絡して)

### 説明

/ srcディレクトリには、LibDriver FM11RFXXのソースファイルが含まれています。

/ interfaceディレクトリには、LibDriver FM11RFXX用のプラットフォームに依存しないRFバステンプレートが含まれています。

/ testディレクトリには、チップの必要な機能を簡単にテストできるLibDriver FM11RFXXドライバーテストプログラムが含まれています。

/ exampleディレクトリには、LibDriver FM11RFXXプログラミング例が含まれています。

/ docディレクトリには、LibDriver FM11RFXXオフラインドキュメントが含まれています。

/ datasheetディレクトリには、FM11RFXXデータシートが含まれています。

/ projectディレクトリには、一般的に使用されるLinuxおよびマイクロコントローラー開発ボードのプロジェクトサンプルが含まれています。 すべてのプロジェクトは、デバッグ方法としてシェルスクリプトを使用しています。詳細については、各プロジェクトのREADME.mdを参照してください。

/ misraはLibDriver misraコードスキャン結果を含む。

### インストール

/ interfaceディレクトリにあるプラットフォームに依存しないRFバステンプレートを参照して、指定したプラットフォームのRFバスドライバを完成させます。

/src ディレクトリ、プラットフォームのインターフェイス ドライバー、および独自のドライバーをプロジェクトに追加します。デフォルトのサンプル ドライバーを使用する場合は、/example ディレクトリをプロジェクトに追加します。

### 使用

/example ディレクトリ内のサンプルを参照して、独自のドライバーを完成させることができます。 デフォルトのプログラミング例を使用したい場合の使用方法は次のとおりです。

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

### ドキュメント

オンラインドキュメント: [https://www.libdriver.com/docs/fm11rfxx/index.html](https://www.libdriver.com/docs/fm11rfxx/index.html)。

オフラインドキュメント: /doc/html/index.html。

### 貢献

CONTRIBUTING.mdを参照してください。

### 著作権

著作権（c）2015-今 LibDriver 全著作権所有

MITライセンス（MIT）

このソフトウェアおよび関連するドキュメントファイル（「ソフトウェア」）のコピーを取得した人は、無制限の使用、複製、変更、組み込み、公開、配布、サブライセンスを含む、ソフトウェアを処分する権利を制限なく付与されます。ソフトウェアのライセンスおよび/またはコピーの販売、および上記のようにソフトウェアが配布された人の権利のサブライセンスは、次の条件に従うものとします。

上記の著作権表示およびこの許可通知は、このソフトウェアのすべてのコピーまたは実体に含まれるものとします。

このソフトウェアは「現状有姿」で提供され、商品性、特定目的への適合性、および非侵害の保証を含むがこれらに限定されない、明示または黙示を問わず、いかなる種類の保証もありません。 いかなる場合も、作者または著作権所有者は、契約、不法行為、またはその他の方法で、本ソフトウェアおよび本ソフトウェアの使用またはその他の廃棄に起因または関連して、請求、損害、またはその他の責任を負わないものとします。

### 連絡して

お問い合わせくださいlishifenging@outlook.com。