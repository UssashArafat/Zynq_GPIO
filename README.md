# Zynq_GPIO
### A software application on ARM processing system to control hardware that is implemented in programmable logic.
-------------------------------------------------------------------------------------------------------------------

#### Tools:  	Vivado 2020.2 | Xilinx Vitis 2020.2 | Tera Term 4.105 |
#### Device: 	Zedboard                            |
---------------------------------------------------------------------------------------------------------


##### After uploading the hardware file and the software file into the Zedboard, the LEDs are supposed to perform different types of counter operations depending the status of the switches. 


 | Switch  | Operation |
 | ------------- | ------------- |
 | 0x00  | All LEDs are off  |
 | 0x01  | All LEDs are on  |
 | 0x02  | Blinking LEDs  |
 | 0x03  | Ring Counter  |
 | 0x04  | Johnson Counter |
 | 0x05  | Binary Counter  |
 | 0x06  | Gray Counter  |
 | 0x07  | Fibonacci Counter  |


 ###### For Johnson counter and Fibonacci counter, all the LEDs need to be off before starting because these two counters need special initialization condition.

------------------------------------------------------------------------------------------------------------------------

#### For Video demonstration click the image below
[![Alt text](https://img.youtube.com/vi/9csz9CPS2k8/0.jpg)](https://www.youtube.com/watch?v=9csz9CPS2k8)
