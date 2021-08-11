#ifndef DEFINITIONS_H
#define DEFINITIONS_H

//these define what pin each signal is connected to on the arduino
#define CE    10  //slave select
#define SCK   13
#define MOSI  11
#define MISO  12
#define CSN   9   //not controlled by SPI library

//SPI constants
#define SPI_SPEED 10000000 //this is defined to be the limit of SPI on p.47 of the NRF specification

//command constants
#define R_RX_PAYLOAD        0b01100001
#define W_TX_PAYLOAD        0b10100000
#define FLUSH_TX            0b11100001
#define FLUSH_RX            0b11100010
#define REUSE_TX_PL         0b11100011
#define R_RX_PL_WID         0b01100000
#define W_TX_PAYLOAD_NOACK  0b10110000
#define NOP                 0b11111111

//register names
#define RX_ADDR_P5 0b00001111
#define TX_ADDR       0b00010000

//other constants
#define MAX_NUM_REG_READS   100   //the maximum number of registers to read
#define SERIAL_DATA_RATE    9600
#define NIBBLE_SIZE         4     //num bits in one nibble
#define NUM_BITS_IN_BYTE    8
#define SUCCESS 1
#define FAILURE -1

#endif
