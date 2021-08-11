#include <SPI.h> //https://www.arduino.cc/en/reference/SPI
#include "definitions.h"

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
  unsigned char * reg_value = (unsigned char *) calloc(MAX_NUM_REG_READS, sizeof(char)); //declaration of variable to store register values
  int * counter = (int *) calloc(1, sizeof(int)); //will count how many registers we have read
  *counter = 0;
  
  //write to register
  unsigned char * message = (unsigned char * ) calloc(1, sizeof(char));
  message[0] = 0b01010111; //LSB of address for Data Pipe 5
  reg_write(RX_ADDR_P5, reg_value, counter, 2, message, 1);

  //read from the same register
  reg_read(RX_ADDR_P5, reg_value, counter, 2);

  //read from TX_ADDR register
  reg_read(TX_ADDR, reg_value, counter, 6); 

  //print results
  for(int i = 0; i < *counter; i++)
  {
    print_bytes(reg_value[i], false);
  }
  Serial.println(*counter);

  //reset the CE pin and terminate SPI
  digitalWrite(CE, LOW);
  SPI.end(); //https://www.arduino.cc/en/Reference/SPIEnd
  free(reg_value);
  reg_value = NULL;
  free(counter);
  counter = NULL;
  free(message);
  message = NULL;
}


int reg_write(char reg_name, unsigned char * reg_contents, int * offset, int num_bytes_to_read, unsigned char * message, int message_len)
{
  digitalWrite(CSN, LOW);
  unsigned char * temp_contents = (unsigned char *) calloc(message_len + 1, sizeof(char));
  int counter = 0;
  char write_command = 0b00100000;
  char write_mask = 0b00011111;
  char masked_reg_name = reg_name & write_mask;
  temp_contents[counter] = SPI.transfer(write_command | masked_reg_name);
  counter++;
  for(int i = 0; i < message_len; i++)
  {
    temp_contents[counter] = SPI.transfer(message[i]);
    counter++;
  }
  if(NULL != offset && 0 < num_bytes_to_read)
  {
    for(int i = 0; i < num_bytes_to_read; i++)
    {
      reg_contents[*offset + i] = temp_contents[i];
    }
    *offset += num_bytes_to_read;
  }
  digitalWrite(CSN, HIGH);
  free(temp_contents);
  temp_contents = NULL;
}

int reg_read(char reg_name, unsigned char * reg_contents, int * offset, int num_bytes_to_read)
{
  int index = 0;
  if(NULL != offset)
  {
    index = *offset;
  }
  digitalWrite(CSN, LOW);
  int counter = 0;
  char read_command = 0b00000000;
  char reg_name_mask = 0b00011111;
  char masked_reg_name = reg_name & reg_name_mask;
  reg_contents[index] = SPI.transfer(read_command | masked_reg_name);
  counter++;
  for(int i = counter; i < num_bytes_to_read; i++)
  {
    reg_contents[index + i] = SPI.transfer(NOP);
  }
  digitalWrite(CSN, HIGH);
  if(NULL != offset)
  {
    *offset += num_bytes_to_read;
  }
  return SUCCESS;
}
