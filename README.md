# Reversing the Controller for the Syma X5C Explorer 

## Purpose

To re-create the controller functions in order to fly the Syma X5C with any device like a computer, phone, or custom circuit.

## Methodology

I found a [blog post](http://inductivekickback.blogspot.com/2015/11/) where someone reversed the controller for the Syma X4 quadcopter. After creating a model of the Syma X5C's circuit (controller_circuit.asc), their description of the antenna's pinout was identical to mine, so I assumed that the Syma X5C also uses SPI to communicate between the microcontroller and the antenna. I probed the SCK, MOSI, and MISO pins on the antenna to compare the signal with what the blog reported but have yet to determine whether the flight control protocol is identical. Once I identify the packet structure for flight control, I can recreate it in a C program that can be uploaded to an Arduino or executed by a computer to fly the Syma X5C.

## Future Improvements

- Replace camera peripheral on the syma x5c with TX unit to do closed loop control?

