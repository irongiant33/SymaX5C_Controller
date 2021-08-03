## Syma X5C

## Resources

- http://inductivekickback.blogspot.com/2015/11/
  - this is a similar project where he thinks that the transmitter is a copy of a nRF24L01 hence the PDF in this folder
- controller_eeprom.pdf is supposedly the eeprom for the controller
- possible_ARM_datasheet.pdf is the possible datasheet for the microcontroller on the quad
- 

## Images

<img src="antenna_pins.jpg" style="zoom:10%;" />

- The picture above shows my poor soldering job to the antenna. The blue wire represents CIPO/MISO, yellow SCK, black GND, green COPI/MOSI. By the time I got used to my new soldering iron, I partially tore the connection to CIPO/MOSI but I got lucky that the 1k resistor was connected in parallel to this pin. 

## Troubleshooting

- Permission denied when attempting to upload Arduino code to `/dev/ttyACM0`
  - Solution: in the terminal, enter the command `sudo chmod a+rw /dev/ttyACM0`

## Logs

### August 2, 2021

- Attempting to write simple transmitter and receiver programs for the NRF24L01. Combed through the entire datasheet and I just want to see if I can get both ends working.
- Started an Arduino program for the transmitter but have not had any luck with reading/writing. The Arduino SPI library is not very helpful.

### August 3, 2021

- Connecting the PicoScope to the output of the Arduino to see if it is actually doing any SPI signaling. So far, there have been no good results. 
- Connected LED to CSN pin and added some delays around setting the output to HIGH/LOW so that I could see the LED blink on and off. It did just that, but there was still no output on the PicoScope, even on the D3 channel. I must've configured somethign incorrectly with the scope. 
  - needed to modify the trigger. it was set to "rapid" but after moving it to "none" I was able to see the digital signal.
  - to properly view the digital signals, I would suggest lowering their threshold from the "select digital channels/groups" menu. Even though the signals are supposed to be 5V, selecting 3V ensures good looking digital waveforms.