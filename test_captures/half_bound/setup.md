# 4 May Test 4

## Testing half bound

### Description

The controller is on and has been throttled up to the max. The controller has been in this state for a short period of time before this capture

### Files

All iterations are tested according to the configuration_settings.pssettings. Within each folder you will find:

- captures.pdf -> shows a visual of all of the 30 captures
- decoded_miso_msb.csv -> I set up a serial decoding session on the MISO pin, this is the decoded output for all 30 captures
- decoded_mosi_lsb.csv - >I set up a serial decoding session on the MOSI pin, this is the decoded output for all 30 captures
- raw_data.psdata -> psdata file for this capture

### Setup

1. Connect D0 to SCK, D1 to MOSI, D2 to MISO. Channel A is also connected to MISO and B is connected to MOSI. 
2. Power the board, enable the switch. You should hear a loud beep and see rapid flashing. Throttle up to max
3. Capture according to the above files.

### Observations

- Interestingly there is no significant difference between the half bound state and the unbound state. It must take switching to full throttle and back in order to enable switching from the bind channels apparent in the unbound/half bound state to the control channels in the idle bound state. 
- No significant difference between iteration 1 and 2
