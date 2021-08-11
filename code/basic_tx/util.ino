#include "definitions.h"

/**
 * @brief
 * This function prints the binary or hex representation of an unsigned char.
 * It prints the MSB first. 
 * 
 * @params
 * value        - the unsigned char to print
 * print_binary - if true, then print the binary form. If false, print hex.
 * 
 * @return
 * None. Displays one byte per line on serial monitor.
 */
void print_bytes(unsigned char value, bool print_binary)
{
  char indicator = 'b';
  unsigned int item_size = 1;
  if(!print_binary)
  {
    indicator = 'x';
    item_size = NIBBLE_SIZE;
  }
  int num_bits = sizeof(value) * NUM_BITS_IN_BYTE;
  int num_quants = num_bits/item_size;

  //create masks
  unsigned char upper_mask_value = 0;
  unsigned char lower_mask_value = (1 << item_size) - 1;
  for(int i = 0; i < item_size; i++)
  {
    upper_mask_value += 1 << (num_bits - (i + 1));
  }

  //print value
  Serial.print(indicator);
  for(unsigned int i = 0; i < num_quants; i++)
  {
    unsigned char result = (value << (i * item_size)) & upper_mask_value;
    Serial.print(hex_vals[(result >> (num_bits - item_size)) & lower_mask_value]);
  }
  Serial.println();
  return;
}
