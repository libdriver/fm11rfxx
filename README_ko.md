[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver FM11RFXX

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/fm11rfxx/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

FM11RFXX는 Shanghai FM Co. Ltd.에서 개발한 비접촉 IC 카드 칩입니다. 칩에는 1K x 8비트 EEPROM 또는 4K x 8비트 EEPROM 구성이 있으며 리더 안테나와 비접촉 카드 사이의 최대 통신 범위는 약 10cm이며 데이터는 반이중 방식으로 교환됩니다. FM11RFXX는 하드웨어 로직으로 구현된 프로세서 카드의 기능을 갖춘 진정한 다중 애플리케이션 스마트 카드이며 암호화 및 통신 회로를 통해 매우 높은 보안 성능을 갖추고 있으므로 FM11RFXX는 특별히 맞춤화될 수 있습니다. 대중 교통 티켓 발권 시스템 및 이에 상응하는 애플리케이션에 사용할 수 있는 지불 카드의 요구 사항을 충족합니다. 비접촉식 스마트 카드에는 FM11RFXX 칩 안테나와 PVC(또는 PET) 소재의 카드 베이스라는 세 가지 구성 요소가 포함되어 있습니다. 배터리가 필요하지 않습니다. 칩이 결합 장치 안테나 근처에 위치하면 고속 RF 통신 인터페이스를 통해 106Kbit/s로 데이터를 전송할 수 있습니다.

LibDriver FM11RFXX은 LibDriver에서 출시한 FM11RFXX의 전체 기능 드라이버입니다. 읽기 블록, 쓰기 블록, 값 증가, 값 감소 등의 기능을 제공합니다. LibDriver는 MISRA를 준수합니다.

이 리포지토리에는 하위 모듈이 포함되어 있으며 전체 프로젝트를 복제하려면 "--recursive"를 추가해야 합니다.

```shell
git clone https://github.com/libdriver/fm11rfxx.git --recursive
```

### 콘텐츠

  - [설명](#설명)
  - [설치](#설치)
  - [사용](#사용)
    - [example basic](#example-basic)
  - [문서](#문서)
  - [기고](#기고)
  - [저작권](#저작권)
  - [문의하기](#문의하기)

### 설명

/src 디렉토리에는 LibDriver FM11RFXX의 소스 파일이 포함되어 있습니다.

/interface 디렉토리에는 LibDriver FM11RFXX용 플랫폼 독립적인 RF 버스 템플릿이 포함되어 있습니다.

/test 디렉토리에는 LibDriver FM11RFXX드라이버 테스트 프로그램이 포함되어 있어 칩의 필요한 기능을 간단히 테스트할 수 있습니다.

/example 디렉토리에는 LibDriver FM11RFXX프로그래밍 예제가 포함되어 있습니다.

/doc 디렉토리에는 LibDriver FM11RFXX오프라인 문서가 포함되어 있습니다.

/datasheet 디렉토리에는 FM11RFXX데이터시트가 있습니다.

/project 디렉토리에는 일반적으로 사용되는 Linux 및 마이크로컨트롤러 개발 보드의 프로젝트 샘플이 포함되어 있습니다. 모든 프로젝트는 디버깅 방법으로 셸 스크립트를 사용하며, 자세한 내용은 각 프로젝트의 README.md를 참조하십시오.

/misra 에는 LibDriver misra 코드 검색 결과가 포함됩니다.

### 설치

/interface 디렉토리에서 플랫폼 독립적인 RF 버스 템플릿을 참조하여 지정된 플랫폼에 대한 RF 버스 드라이버를 완성하십시오.

/src 디렉터리, 플랫폼용 인터페이스 드라이버 및 자체 드라이버를 프로젝트에 추가합니다. 기본 예제 드라이버를 사용하려면 /example 디렉터리를 프로젝트에 추가합니다.

### 사용

/example 디렉터리의 예제를 참조하여 자신만의 드라이버를 완성할 수 있습니다. 기본 프로그래밍 예제를 사용하려는 경우 사용 방법은 다음과 같습니다.

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

### 문서

온라인 문서: [https://www.libdriver.com/docs/fm11rfxx/index.html](https://www.libdriver.com/docs/fm11rfxx/index.html).

오프라인 문서: /doc/html/index.html.

### 기고

CONTRIBUTING.md 를 참조하십시오.

### 저작권

저작권 (c) 2015 - 지금 LibDriver 판권 소유

MIT 라이선스(MIT)

이 소프트웨어 및 관련 문서 파일("소프트웨어")의 사본을 얻은 모든 사람은 이에 따라 무제한 사용, 복제, 수정, 통합, 출판, 배포, 2차 라이선스를 포함하여 소프트웨어를 처분할 수 있는 권리가 부여됩니다. 소프트웨어의 사본에 대한 라이선스 및/또는 판매, 그리고 소프트웨어가 위와 같이 배포된 사람의 권리에 대한 2차 라이선스는 다음 조건에 따릅니다.

위의 저작권 표시 및 이 허가 표시는 이 소프트웨어의 모든 사본 또는 내용에 포함됩니다.

이 소프트웨어는 상품성, 특정 목적에의 적합성 및 비침해에 대한 보증을 포함하되 이에 국한되지 않는 어떠한 종류의 명시적 또는 묵시적 보증 없이 "있는 그대로" 제공됩니다. 어떤 경우에도 저자 또는 저작권 소유자는 계약, 불법 행위 또는 기타 방식에 관계없이 소프트웨어 및 기타 소프트웨어 사용으로 인해 발생하거나 이와 관련하여 발생하는 청구, 손해 또는 기타 책임에 대해 책임을 지지 않습니다.

### 문의하기

연락주세요lishifenging@outlook.com.