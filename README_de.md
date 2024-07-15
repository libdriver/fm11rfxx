[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver FM11RFXX

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/fm11rfxx/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE) 

FM11RFXX ist der von Shanghai FM Co. Ltd. entwickelte kontaktlose Chip für IC-Karten. Der Chip verfügt über eine 1K x 8 Bit EEPROM- oder 4K x 8 Bit EEPROM-Organisation, die maximale Kommunikationsreichweite zwischen der Antenne des Lesegeräts und der kontaktlosen Karte beträgt ungefähr 10 cm, der Datenaustausch erfolgt im Halbduplex-Verfahren mit einer Geschwindigkeit von 106 Kbit/s. Der FM11RFXX ist eine echte Chipkarte für mehrere Anwendungen mit der Funktionalität einer Prozessorkarte, die mit Hardwarelogik realisiert wurde, und verfügt mit dem Verschlüsselungs- und Kommunikationsschaltkreis außerdem über eine sehr hohe Sicherheitsleistung, sodass der FM11RFXX speziell auf die Anforderungen einer Zahlungskarte zugeschnitten werden kann, die für Ticketsysteme im öffentlichen Verkehr und vergleichbare Anwendungen verwendet werden kann. Die kontaktlose Chipkarte enthält drei Komponenten: die FM11RFXX-Chipantenne und die Kartenbasis aus PVC- (oder PET-)Material. Es wird keine Batterie benötigt. Wenn sich der Chip in der Nähe der Antenne des Koppelgeräts befindet, ermöglicht die Hochgeschwindigkeits-HF-Kommunikationsschnittstelle die Datenübertragung mit 106 Kbit/s.

LibDriver FM11RFXX ist der Vollfunktionstreiber von FM11RFXX, der von LibDriver gestartet wurde. Er bietet die Funktion von Leseblock, Schreibblock, Werterhöhung, Wertverringerung und so weiter. LibDriver ist MISRA-konform.

Dieses Repository enthält ein Submodul und Sie sollten "--recursive" hinzufügen, um das gesamte Projekt zu klonen.

```shell
git clone https://github.com/libdriver/fm11rfxx.git --recursive
```

### Inhaltsverzeichnis

  - [Anweisung](#Anweisung)
  - [Installieren](#Installieren)
  - [Nutzung](#Nutzung)
    - [example basic](#example-basic)
  - [Dokument](#Dokument)
  - [Beitrag](#Beitrag)
  - [Lizenz](#Lizenz)
  - [Kontaktieren Sie uns](#Kontaktieren-Sie-uns)

### Anweisung

/src enthält LibDriver FM11RFXX-Quelldateien.

/interface enthält die plattformunabhängige Vorlage LibDriver FM11RFXX RF.

/test enthält den Testcode des LibDriver FM11RFXX-Treibers und dieser Code kann die erforderliche Funktion des Chips einfach testen.

/example enthält LibDriver FM11RFXX-Beispielcode.

/doc enthält das LibDriver FM11RFXX-Offlinedokument.

/Datenblatt enthält FM11RFXX-Datenblatt.

/project enthält den allgemeinen Beispielcode für Linux- und MCU-Entwicklungsboards. Alle Projekte verwenden das Shell-Skript, um den Treiber zu debuggen, und die detaillierten Anweisungen finden Sie in der README.md jedes Projekts.

/misra enthält die Ergebnisse des LibDriver MISRA Code Scans.

### Installieren

Verweisen Sie auf eine plattformunabhängige RF-Schnittstellenvorlage und stellen Sie Ihren Plattform-RF-Treiber fertig.

Fügen Sie das Verzeichnis /src, den Schnittstellentreiber für Ihre Plattform und Ihre eigenen Treiber zu Ihrem Projekt hinzu. Wenn Sie die Standardbeispieltreiber verwenden möchten, fügen Sie das Verzeichnis /example zu Ihrem Projekt hinzu.

### Nutzung

Sie können auf die Beispiele im Verzeichnis /example zurückgreifen, um Ihren eigenen Treiber zu vervollständigen. Wenn Sie die Standardprogrammierbeispiele verwenden möchten, erfahren Sie hier, wie Sie diese verwenden.

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

### Dokument

Online-Dokumente: [https://www.libdriver.com/docs/fm11rfxx/index.html](https://www.libdriver.com/docs/fm11rfxx/index.html).

Offline-Dokumente: /doc/html/index.html.

### Beitrag

Bitte beachten Sie CONTRIBUTING.md.

### Lizenz

Urheberrechte © (c) 2015 - Gegenwart LibDriver Alle Rechte vorbehalten



Die MIT-Lizenz (MIT)



Hiermit wird jeder Person kostenlos die Erlaubnis erteilt, eine Kopie zu erhalten

dieser Software und zugehörigen Dokumentationsdateien (die „Software“) zu behandeln

in der Software ohne Einschränkung, einschließlich, aber nicht beschränkt auf die Rechte

zu verwenden, zu kopieren, zu modifizieren, zusammenzuführen, zu veröffentlichen, zu verteilen, unterzulizenzieren und/oder zu verkaufen

Kopien der Software und Personen, denen die Software gehört, zu gestatten

dazu eingerichtet werden, unter folgenden Bedingungen:



Der obige Urheberrechtshinweis und dieser Genehmigungshinweis müssen in allen enthalten sein

Kopien oder wesentliche Teile der Software.



DIE SOFTWARE WIRD "WIE BESEHEN" BEREITGESTELLT, OHNE JEGLICHE GEWÄHRLEISTUNG, AUSDRÜCKLICH ODER

STILLSCHWEIGEND, EINSCHLIESSLICH, ABER NICHT BESCHRÄNKT AUF DIE GEWÄHRLEISTUNG DER MARKTGÄNGIGKEIT,

EIGNUNG FÜR EINEN BESTIMMTEN ZWECK UND NICHTVERLETZUNG VON RECHTEN DRITTER. IN KEINEM FALL DARF DAS

AUTOREN ODER URHEBERRECHTSINHABER HAFTEN FÜR JEGLICHE ANSPRÜCHE, SCHÄDEN ODER ANDERE

HAFTUNG, OB AUS VERTRAG, DELIKT ODER ANDERWEITIG, ENTSTEHEND AUS,

AUS ODER IM ZUSAMMENHANG MIT DER SOFTWARE ODER DER VERWENDUNG ODER ANDEREN HANDLUNGEN MIT DER

SOFTWARE.

### Kontaktieren Sie uns

Bitte senden Sie eine E-Mail an lishifenging@outlook.com.