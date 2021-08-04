#include <SPI.h> //https://www.arduino.cc/en/reference/SPI

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

//other constants
#define MAX_NUM_REG_READS   100   //the maximum number of registers to read
#define SERIAL_DATA_RATE    9600
#define NIBBLE_SIZE         4     //num bits in one nibble
#define NUM_BITS_IN_BYTE    8

//global variables
char hex_vals[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

void setup()
{
  //initializations
  SPI.begin(); //https://www.arduino.cc/en/Reference/SPIBegin
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  pinMode(CSN, OUTPUT);
  pinMode(CE, OUTPUT);
  Serial.begin(SERIAL_DATA_RATE);

  //initial pin settings
  digitalWrite(CSN, HIGH);
  digitalWrite(CE, LOW);
}

void loop()
{
  //according to spec: "Change to active modes only happens if CE is set high and
  //when CE is set low, the nRF24L01 returns to standby-I mode.
  digitalWrite(CE, HIGH);
  unsigned int * reg_value = calloc(MAX_NUM_REG_READS, sizeof(int)); //declaration of variable to store register values
  int counter = 0; //will count how many registers we have read
  
  //write to register
  digitalWrite(CSN, LOW);
  reg_value[counter] = SPI.transfer(0b00101111); //001 (write) 01111 (0x0F)
  counter++;
  reg_value[counter] = SPI.transfer(0b01010111); //LSB of address for Data Pipe 5
  counter++;
  digitalWrite(CSN, HIGH);

  //read from the same register
  digitalWrite(CSN, LOW);
  reg_value[counter] = SPI.transfer(0b00001111); //000 (read) 01111 (0x0F)
  counter++;
  reg_value[counter] = SPI.transfer(NOP); //we are just triggering the SCK to read the actual register contents
  counter++;
  digitalWrite(CSN, HIGH);

  //read from TX_ADDR register
  digitalWrite(CSN, LOW);
  reg_value[counter] = SPI.transfer(0b00010000); //000 (read) 00111 (0x10)
  counter++;
  char * tx_addr = calloc(5, sizeof(char));
   //read 5 bytes (the value that we transfer over MOSI doesn't matter, we just want SCK to trigger MISO read)
  for(int i = 0; i < 5; i++)
  {
    tx_addr[i] = SPI.transfer(NOP);
  }
  digitalWrite(CSN, HIGH);

  //print results
  for(int i = 0; i < counter; i++)
  {
    print_bytes(reg_value[i], true);
  }
  for(int i = 0; i < 5; i++)
  {
    print_bytes((int) tx_addr[i], false);
  }

  //reset the CE pin and terminate SPI
  digitalWrite(CE, LOW);
  SPI.end(); //https://www.arduino.cc/en/Reference/SPIEnd
  free(reg_value);
  free(tx_addr);
}

void print_bytes(unsigned int value, bool print_binary)
{
  unsigned int mask_value;
  int num_bits = sizeof(value) * NUM_BITS_IN_BYTE; //convert # bytes to # bits
  if(print_binary)
  {
    mask_value = pow(2, num_bits - 1);
    Serial.print("0b");
    for(unsigned int i = 0; i < num_bits; i++)
    {
      int result = (value << i) & mask_value;
      Serial.print((result >> (num_bits - 1)) & 1);
    }
  }
  else
  {
    int num_nibbles = sizeof(value) * (NUM_BITS_IN_BYTE/NIBBLE_SIZE); //convert # bytes to # nibbles
    for(int i = 0; i < NIBBLE_SIZE; i++)
    {
      mask_value += pow(2, num_bits - (i + 1));
    }
    Serial.print("0x");
    for(unsigned int i = 0; i < num_nibbles; i++)
    {
      int result = (value << i * NIBBLE_SIZE) & mask_value;
      Serial.print(hex_vals[(result >> (num_bits - NIBBLE_SIZE)) & 15]);
    }
  }
  Serial.println();
  return;
}
