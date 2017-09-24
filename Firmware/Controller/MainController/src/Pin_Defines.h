#ifndef PIN_DEFINES_H
#define PIN_DEFINES_H

#include "mbed.h"

//LED
#define STATUS_LED PB_14

//Valves
#define SUPPLY_V PA_5
#define PURGE_V PA_6
#define EXTRA_V PA_7

//relays
#define CAP_R PD_14
#define CHARGE_R PD_15
#define FCC_R PF_12
#define START_R PF_13
#define MOTOR_R PE_9

//analog voltage readings
#define CAPVOLT PC_0
#define FCCURR PC_3
#define FCVOLT PF_3
#define CAPCURR PF_5
#define FCPRES PF_10

//Multiplexor pins
#define MULTO2 PF_15
#define MULTA PE_13
#define MULTB PF_14
#define MULTO1 PE_11

//Serial
//data link
#define LINK_RX PE_7//Rx7
#define LINK_TX PE_8//Tx7
//open log
#define OL_RX PB_11//Rx3
#define OL_TX PB_10//Tx3

//I2C
#define I2C_SDA PD_13 //I2C4_SDA
#define I2C_SCL PD_12 //I2C4_SCL

#endif
