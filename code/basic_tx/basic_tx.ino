#include <SPI.h> //https://www.arduino.cc/en/reference/SPI

//these define what pin each signal is connected to on the arduino
#define CE 10 //slave select
#define SCK 13
#define MOSI 11
#define MISO 12
#define CSN 9 //not controlled by SPI library

//SPI constants
#define SPI_SPEED 10000000 //this is defined to be the limit of SPI on p.47 of the NRF specification

void setup()
{
  //initializations
  SPI.begin(); //https://www.arduino.cc/en/Reference/SPIBegin
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  pinMode(CSN, OUTPUT);
  pinMode(CE, OUTPUT);
  Serial.begin(9600);

  //initial pin settings
  digitalWrite(CSN, HIGH);
  digitalWrite(CE, LOW);
}

void loop()
{
  //according to spec: "Change to active modes only happens if CE is set high and
  //when CE is set low, the nRF24L01 returns to standby-I mode.
  digitalWrite(CE, HIGH);
  
  //write to register
  digitalWrite(CSN, LOW);
  SPI.transfer(0b00101111); //001 (write) 01111 (0x0F)
  SPI.transfer(0b01010111); //LSB of address for Data Pipe 5
  delay(100);
  digitalWrite(CSN, HIGH);
  delay(100);

  //read from the same register
  digitalWrite(CSN, LOW);
  int reg_value = SPI.transfer(0b00001111); //000 (read) 01111 (0x0F)
  //Serial.print(reg_value);
  SPI.end(); //https://www.arduino.cc/en/Reference/SPIEnd
  delay(100);
  digitalWrite(CSN, HIGH);
  delay(100);

  //reset the CE pin
  digitalWrite(CE, LOW);
}
