#ifndef PIN_DEFINES_H
#define PIN_DEFINES_H

//LED
#define STATUS_LED D13

//Valves
#define SUPPLY_V D6
#define PURGE_V D9
#define EXTRA_V D10

//relays
#define CAP_R D11
#define CHARGE_R D12
#define FCC_R D20
#define START_R D21
#define MOTOR_R D22

//analog voltage readings
#define CAPVOLT
#define FCCUR
#define FCVOLT
#define CAPCURR
#define FCPRES

//Multiplexor pins
#define MULTO2 D2
#define MULTA D3
#define MULTB D4
#define MULTO1 D5

//Serial
//can bus
#define CAN_RX Rx0
#define CAN_TX Tx0
//open log
#define OL_RX Rx2
#define OL_TX Tx2

//I2C
#define I2C_SDA SDA0
#define I2C_SCL SCL0

#endif