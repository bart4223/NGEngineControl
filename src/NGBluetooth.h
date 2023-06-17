//
//  NGBluetooth.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 12.06.23.
//

#ifndef NGBluetooth_h
#define NGBluetooth_h

// Bluetooth-Module
//
// AT-Mode
// RX->RX, TX->TX
//
// AT -> OK
// AT+UART? -> Baud-Rate
// AT+ROLE? = 0 Slave, 1 MASTER
// AT+ADDR? -> 98D3:41:F69E98
// AT+CMODE? = 0 Fix
// AT+BIND? -> 98D3:41:F69E98
//
// Normal-Mode
// RX->TX, TX->RX

// Command Structure
//
// 1. und 2. Byte - Header
// 3. Byte - Kind
// 4. Byte - Context
// from 5. Bytes - Parameter
#define BT_CMD_HEADER1          0x2A
#define BT_CMD_HEADER2          0x17
#define BT_CMD_KIND_SOUNDCHECK  0x00
#define BT_CMD_KIND_SWITCH      0x01
#define BT_CMD_KIND_SWITCH_OFF  0x00
#define BT_CMD_KIND_SWITCH_ON   0x01
#define BT_CMD_KIND_COUNTER     0x02

#define BT_NO_KIND    -1
#define BT_NO_CONTEXT -1

#endif /* NGBluetooth_h */
