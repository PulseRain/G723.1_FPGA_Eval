# G723.1_FPGA_Eval
Evulation G723.1 Audio Quality on FPGA board

<br />

## Hardware

* [Digilent Arty A7-100T](https://digilent.com/shop/arty-a7-artix-7-fpga-development-board/)

* [PMOD Rotary Encoder](https://digilent.com/shop/pmod-enc-rotary-encoder/) 

* [Stereo Audio Input and Output ](https://digilent.com/shop/pmod-i2s2-stereo-audio-input-and-output/)


<img src="https://github.com/PulseRain/G723.1_FPGA_Eval/raw/main/docs/board_with_pmod_audio_rotary.png" width = "400" />

  Assemble the PMOD modules to the FPGA board as shown above.

<br />

## Program the FPGA board

* Connect the FPGA board to a Windows PC through USB

* Open Vivado Hardware Manager, auto detect the device. If there is no flash device showing up down below, right click and device and choose the "Add Configuration Memory Device" from the context menu.

* Choose the s25fl128sxxxxxxx0-spi-x1_x2_x4 as the memory device (illustrated below)

<img src = "https://github.com/PulseRain/G723.1_FPGA_Eval/raw/main/docs/hardware.png" />

* Program the flash devide with [this bin file](https://github.com/PulseRain/G723.1_FPGA_Eval/raw/main/bitstream/ArtyA7_100T.bin)

<br />


## Load the Sketch

* Install and Open [Arduino IDE](https://www.arduino.cc/en/Main/Software_)

* Load the Sketch

