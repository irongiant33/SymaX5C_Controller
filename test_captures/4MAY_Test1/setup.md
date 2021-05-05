# 4 May Test

## Testing idle state

### Description

The controller is on and has been bound (after switching on, the throttle is maxed out and then returned to minimum value). The controller has been in this state for a long period of time before this capture

### Files

- captures.pdf -> shows a visual of all of the 30 captures
- configuration_settings.pssettings -> settings file so that someone can set up the test again
- decoded_miso_msb.csv -> I set up a serial decoding session on the MISO pin, this is the decoded output for all 30 captures
- decoded_mosi_lsb.csv - >I set up a serial decoding session on the MOSI pin, this is the decoded output for all 30 captures
- raw_data.psdata -> psdata file for this capture

### Setup

1. Connect D0 to SCK, D1 to MOSI, D2 to MISO. Channel A is also connected to MISO and B is connected to MOSI. 
2. Power the board, enable the switch. You should hear a loud beep and see rapid flashing. Increase the throttle to max (you should hear a 2nd beep) and reduce throttle to min (you should hear a 3rd and final beep). The light should be steady.
3. Capture according to the above files.

### Observations

- Nothing significant to find in MISO, but MOSI contains 19 bytes (38 hex characters) of interesting information. All bytes except the 5th byte (zero indexed) is constant throughout the capture. The 5th byte switches between the following values every **2 packets** (i.e. 4 ms/packet = 8ms):

  ```
  28 -> 2C -> 38 -> 3C -> 28 -> 2C ...
  ```

  According to the [inductive kickback blog](http://inductivekickback.blogspot.com/2015/11/) this would seem to correspond with the channel hopping behavior. So it is possible that the 5th byte controls the channel that the antenna transmits on. 

- In order to accurately capture the digital signals, you need to set the voltage level to 3V. If you set it to 5V, the thresholds will never detect when the signal goes high. 