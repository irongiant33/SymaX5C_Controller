# 4 May Test 2

## Testing startup state

### Description

The controller transitions from off to on and has **NOT** been bound.

### Files

Each iteration was performed with the same configuration_settings.pssettings file.

- captures.pdf -> shows a visual of all of the 30 captures
- decoded_miso_msb.csv -> I set up a serial decoding session on the MISO pin, this is the decoded output for all 30 captures
- decoded_mosi_lsb.csv - >I set up a serial decoding session on the MOSI pin, this is the decoded output for all 30 captures
- raw_data.psdata -> psdata file for this capture

### Setup

1. Connect D0 to SCK, D1 to MOSI, D2 to MISO. Channel A is also connected to MISO and B is connected to MOSI. 
2. Power the board and start capturing. Nothing should capture yet as nothing should trigger.
3. Switch the board on. You should see the capture start to fill up. Do not mess with the throttle or any other controls.

### Observations

- Buffer 13-30 look very similar in structure to the idle state captures from 4May_Test1. There are 19 bytes. Here is a side by side comparison of buffer 13 with one of the buffers from 4May_Test1:

  ```
  4MayTest1: E0 00 E4 74 A4 28 87 00 05 00 00 00 00 00 26 00 C0 00 3D
  4MayTest2: E0 00 E4 74 A4 D2 87 00 05 45 00 10 D9 5E 55 55 55 00 6C
  ```

  - the first 5 bytes are the same, could this possibly be some sort of address or constant preamble?

  - The 5th byte (0 indexed) which we hypothesized was the channel to transmit as a result of the 4May_Test1, actually carries different values but in the same pattern of every 2 packets:

    ```
    4MayTest1: 28 -> 2C -> 38 -> 3C -> 28 -> 2C ...
    4MayTest2: D2 -> 0C -> 02 -> 90 -> D2 -> 0C ...
    ```

  - For the rest of the packet, it is hard to say what is a coincidence that it is similar versus what is significant. We'll wait for further testing.

- No significant differences between iteration 1 and 2. 