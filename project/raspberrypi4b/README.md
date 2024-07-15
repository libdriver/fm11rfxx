### 1. Board

#### 1.1 Board Info

Board Name: Raspberry Pi 4B.

IIC Pin: SCL/SDA GPIO3/GPIO2.

SPI Pin: SCLK/MOSI/MISO/CS GPIO11/GPIO10/GPIO9/GPIO8.

UART Pin: TX/RX GPIO14/GPIO15.

GPIO Pin: INT GPIO17.

RESET Pin: RESET GPIO27.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```

#### 2.2 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.3 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
make test
```

Find the compiled library in CMake. 

```cmake
find_package(fm11rfxx REQUIRED)
```


### 3. FM11RFXX

#### 3.1 Command Instruction

1. Show fm11rfxx chip and driver information.

   ```shell
   fm11rfxx (-i | --information)
   ```

2. Show fm11rfxx help.

   ```shell
   fm11rfxx (-h | --help)
   ```

3. Show fm11rfxx pin connections of the current board.

   ```shell
   fm11rfxx (-p | --port)
   ```

4. Run fm11rfxx card test.

   ```shell
   fm11rfxx (-t card | --test=card)
   ```

5. Run chip halt function.

   ```shell
   fm11rfxx (-e halt | --example=halt)
   ```

6. Run wake up the chip function.

   ```shell
   fm11rfxx (-e wake-up | --example=wake-up)
   ```

7. Run read block function, addr is the read block address and it is hexadecimal, authentication is the authentication keys and it is hexadecimal with 6 bytes(strlen=12).

   ```shell
   fm11rfxx (-e read | --example=read) [--key-type=<A | B>] [--key=<authentication>] [--block=<addr>]
   ```

8. Run write block function, addr is the write block address and it is hexadecimal, authentication is the authentication keys and it is hexadecimal with 6 bytes(strlen=12), data is the write data and it is hexadecimal with 16 bytes(strlen=32).

   ```shell
   fm11rfxx (-e write | --example=write) [--key-type=<A | B>] [--key=<authentication>] [--block=<addr>] [--data=<hex>]
   ```

9. Run init as a value block function, addr is the set block address and it is hexadecimal, authentication is the authentication keys and it is hexadecimal with 6 bytes(strlen=12), dec is the inted value.

   ```shell
   fm11rfxx (-e value-init | --example=value-init) [--key-type=<A | B>] [--key=<authentication>] [--block=<addr>] [--value=<dec>]
   ```

10. Run write value to the block function, addr is the set block address and it is hexadecimal, authentication is the authentication keys and it is hexadecimal with 6 bytes(strlen=12), dec is the write value.

    ```shell
    fm11rfxx (-e value-write | --example=value-write) [--key-type=<A | B>] [--key=<authentication>] [--block=<addr>] [--value=<dec>]
    ```

11. Run read value from the block function, addr is the set block address and it is hexadecimal, authentication is the authentication keys and it is hexadecimal with 6 bytes(strlen=12).

    ```shell
    fm11rfxx (-e value-read | --example=value-read) [--key-type=<A | B>] [--key=<authentication>] [--block=<addr>]
    ```

12. Run increment value function, addr is the set block address and it is hexadecimal, authentication is the authentication keys and it is hexadecimal with 6 bytes(strlen=12), dec is the increment value.

    ```shell
    fm11rfxx (-e value-increment | --example=value-increment) [--key-type=<A | B>] [--key=<authentication>] [--block=<addr>] [--value=<dec>]
    ```

13. Run decrement value function, addr is the set block address and it is hexadecimal, authentication is the authentication keys and it is hexadecimal with 6 bytes(strlen=12), dec is the decrement value.

    ```shell
    fm11rfxx (-e value-decrement | --example=value-decrement) [--key-type=<A | B>] [--key=<authentication>] [--block=<addr>] [--value=<dec>]
    ```

#### 3.2 Command Example

```shell
./fm11rfxx -i

fm11rfxx: chip is FMSH FM11RFXX.
fm11rfxx: manufacturer is FMSH.
fm11rfxx: interface is RF.
fm11rfxx: driver version is 1.0.
fm11rfxx: min supply voltage is 3.3V.
fm11rfxx: max supply voltage is 4.0V.
fm11rfxx: max current is 30.00mA.
fm11rfxx: max temperature is 70.0C.
fm11rfxx: min temperature is -25.0C.
```

```shell
./fm11rfxx -p

fm11rfxx: SPI interface SCK connected to GPIO11(BCM).
fm11rfxx: SPI interface MISO connected to GPIO9(BCM).
fm11rfxx: SPI interface MOSI connected to GPIO10(BCM).
fm11rfxx: SPI interface CS connected to GPIO8(BCM).
fm11rfxx: IIC interface SCL connected to GPIO3(BCM).
fm11rfxx: IIC interface SDA connected to GPIO2(BCM).
fm11rfxx: UART interface TX connected to GPIO14(BCM).
fm11rfxx: UART interface RX connected to GPIO15(BCM).
fm11rfxx: INT connected to GPIO17(BCM).
fm11rfxx: RESET connected to GPIO27(BCM).
```

```shell
./fm11rfxx -t card

fm11rfxx: chip is FMSH FM11RFXX.
fm11rfxx: manufacturer is FMSH.
fm11rfxx: interface is RF.
fm11rfxx: driver version is 1.0.
fm11rfxx: min supply voltage is 3.3V.
fm11rfxx: max supply voltage is 4.0V.
fm11rfxx: max current is 30.00mA.
fm11rfxx: max temperature is 70.0C.
fm11rfxx: min temperature is -25.0C.
fm11rfxx: start card test.
fm11rfxx: find fm11rf08 card.
fm11rfxx: id is 0x9A 0x70 0x4E 0xEB.
fm11rfxx: authentication block 0 ok.
fm11rfxx: block 0 is 0x9A 0x70 0x4E 0xEB 0x4F 0x08 0x04 0x00 0x03 0xA5 0x50 0xD9 0xA6 0x54 0xB0 0x1D 
fm11rfxx: authentication block 1 ok.
fm11rfxx: write block 1: 0x67 0xC6 0x69 0x73 0x51 0xFF 0x4A 0xEC 0x29 0xCD 0xBA 0xAB 0xF2 0xFB 0xE3 0x46 
fm11rfxx: read block 1: 0x67 0xC6 0x69 0x73 0x51 0xFF 0x4A 0xEC 0x29 0xCD 0xBA 0xAB 0xF2 0xFB 0xE3 0x46 
fm11rfxx: check data ok.
fm11rfxx: authentication block 2 ok.
fm11rfxx: init value is 0.
fm11rfxx: read value is 0.
fm11rfxx: write value is -10.
fm11rfxx: read value is -10.
fm11rfxx: increment 6.
fm11rfxx: read value is -4.
fm11rfxx: increment 6.
fm11rfxx: read value is 2.
fm11rfxx: increment 6.
fm11rfxx: read value is 8.
fm11rfxx: decrement 5.
fm11rfxx: read value is 3.
fm11rfxx: decrement 5.
fm11rfxx: read value is -2.
fm11rfxx: decrement 5.
fm11rfxx: read value is -7.
fm11rfxx: read block 2: 0xF9 0xFF 0xFF 0xFF 0x06 0x00 0x00 0x00 0xF9 0xFF 0xFF 0xFF 0x02 0xFD 0x02 0xFD 
fm11rfxx: block0 to sector is 0.
fm11rfxx: block15 to sector is 3.
fm11rfxx: block30 to sector is 7.
fm11rfxx: block45 to sector is 11.
fm11rfxx: block60 to sector is 15.
fm11rfxx: block75 to sector is 18.
fm11rfxx: block90 to sector is 22.
fm11rfxx: block105 to sector is 26.
fm11rfxx: block120 to sector is 30.
fm11rfxx: block135 to sector is 32.
fm11rfxx: block150 to sector is 33.
fm11rfxx: block165 to sector is 34.
fm11rfxx: block180 to sector is 35.
fm11rfxx: block195 to sector is 36.
fm11rfxx: sector0 block count is 4.
fm11rfxx: sector5 block count is 4.
fm11rfxx: sector10 block count is 4.
fm11rfxx: sector15 block count is 4.
fm11rfxx: sector20 block count is 4.
fm11rfxx: sector25 block count is 4.
fm11rfxx: sector30 block count is 4.
fm11rfxx: sector35 block count is 16.
fm11rfxx: sector0: block 0 - 3.
fm11rfxx: sector5: block 20 - 23.
fm11rfxx: sector10: block 40 - 43.
fm11rfxx: sector15: block 60 - 63.
fm11rfxx: sector20: block 80 - 83.
fm11rfxx: sector25: block 100 - 103.
fm11rfxx: sector30: block 120 - 123.
fm11rfxx: sector35: block 176 - 191.
fm11rfxx: authentication block 3 ok.
fm11rfxx: permission block0 block1 block2 block3 0x00 0x00 0x00 0x01.
fm11rfxx: user data is 0x00.
fm11rfxx: keyb is 0xFF 0xFF 0xFF 0xFF 0xFF 0xFF.
fm11rfxx: finish card test.
```

```shell
./fm11rfxx -e halt

fm11rfxx: halt.
```

```shell
./fm11rfxx -e wake-up

fm11rfxx: wake up.
```

```shell
./fm11rfxx -e read --key-type=A --key=FFFFFFFFFFFF --block=0

fm11rfxx: find fm11rf08 card.
fm11rfxx: id is 0x9A 0x70 0x4E 0xEB 
fm11rfxx: block is 0x9A 0x70 0x4E 0xEB 0x4F 0x08 0x04 0x00 0x03 0xA5 0x50 0xD9 0xA6 0x54 0xB0 0x1D 
```

```shell
./fm11rfxx -e write --key-type=A --key=FFFFFFFFFFFF --block=1 --data=0123456789ABCDEF0123456789ABCDEF

fm11rfxx: find fm11rf08 card.
fm11rfxx: id is 0x9A 0x70 0x4E 0xEB 
fm11rfxx: data is 0x01 0x23 0x45 0x67 0x89 0xAB 0xCD 0xEF 0x01 0x23 0x45 0x67 0x89 0xAB 0xCD 0xEF 
```

```shell
./fm11rfxx -e value-init --key-type=A --key=FFFFFFFFFFFF --block=2 --value=10

fm11rfxx: find fm11rf08 card.
fm11rfxx: id is 0x9A 0x70 0x4E 0xEB 
fm11rfxx: init block2 as value 10.
```

```shell
./fm11rfxx -e value-write --key-type=A --key=FFFFFFFFFFFF --block=2 --value=200

fm11rfxx: find fm11rf08 card.
fm11rfxx: id is 0x9A 0x70 0x4E 0xEB 
fm11rfxx: write block2 200.
```

```shell
./fm11rfxx -e value-read --key-type=A --key=FFFFFFFFFFFF --block=2

fm11rfxx: find fm11rf08 card.
fm11rfxx: id is 0x9A 0x70 0x4E 0xEB 
fm11rfxx: read block2 value 200.
```

```shell
./fm11rfxx -e value-increment --key-type=A --key=FFFFFFFFFFFF --block=2 --value=20

fm11rfxx: find fm11rf08 card.
fm11rfxx: id is 0x9A 0x70 0x4E 0xEB 
fm11rfxx: increment block2 20.
```

```shell
./fm11rfxx -e value-decrement --key-type=A --key=FFFFFFFFFFFF --block=2 --value=10

fm11rfxx: find fm11rf08 card.
fm11rfxx: id is 0x9A 0x70 0x4E 0xEB 
fm11rfxx: decrement block2 10.
```

```shell
./fm11rfxx -h

Usage:
  fm11rfxx (-i | --information)
  fm11rfxx (-h | --help)
  fm11rfxx (-p | --port)
  fm11rfxx (-t card | --test=card)
  fm11rfxx (-e halt | --example=halt)
  fm11rfxx (-e wake-up | --example=wake-up)
  fm11rfxx (-e read | --example=read) [--key-type=<A | B>] [--key=<authentication>]
           [--block=<addr>]
  fm11rfxx (-e write | --example=write) [--key-type=<A | B>] [--key=<authentication>]
           [--block=<addr>] [--data=<hex>]
  fm11rfxx (-e value-init | --example=value-init) [--key-type=<A | B>] [--key=<authentication>]
           [--block=<addr>] [--value=<dec>]
  fm11rfxx (-e value-write | --example=value-write) [--key-type=<A | B>] [--key=<authentication>]
           [--block=<addr>] [--value=<dec>]
  fm11rfxx (-e value-read | --example=value-read) [--key-type=<A | B>] [--key=<authentication>]
           [--block=<addr>]
  fm11rfxx (-e value-increment | --example=value-increment) [--key-type=<A | B>] [--key=<authentication>]
           [--block=<addr>] [--value=<dec>]
  fm11rfxx (-e value-decrement | --example=value-decrement) [--key-type=<A | B>] [--key=<authentication>]
           [--block=<addr>] [--value=<dec>]

Options:
      --block=<addr>            Set the block address and it is hexadecimal.([default: 0x00])
      --data=<hex>              Set the input data and it is hexadecimal with 16 bytes(strlen=32).([default: 0x0123456789ABCDEF0123456789ABCDEF])
  -e <halt | wake-up | read | write | value-init | value-write | value-read | value-increment
     | value-decrement>, --example=<halt | wake-up | read | write | value-init | value-write
     | value-read | value-increment | value-decrement>
                                Run the driver example.
  -h, --help                    Show the help.
  -i, --information             Show the chip information.
      --key=<authentication>    Set the key of authentication and it is hexadecimal with 6 bytes(strlen=12).([default: 0xFFFFFFFFFFFF])
      --key-type=<A | B>        Set the key type of authentication.([default: A])
  -p, --port                    Display the pin connections of the current board.
  -t <card>, --test=<card>      Run the driver test.
      --value=<dec>             Set the input value.([default: 0])

```
