/*******************************************************************************************
* Author:	Ussash Arafat
* Project:	LedCounter_Zedboard
* File:		LedCounter.c
* Tools:  	Vivado 2020.2
*           Xilinx Vitis 2020.2
* Device: 	Zedboard
********************************************************************************************/
// Include Files
#include "xparameters.h"
#include "xgpio.h"
#include "xstatus.h"
#include "xil_printf.h"
// Definitions
#define GPIO_DEVICE_ID_0 XPAR_AXI_GPIO_0_DEVICE_ID   //GPIO that SWITCHes are connected to
#define GPIO_DEVICE_ID_1 XPAR_AXI_GPIO_1_DEVICE_ID	// GPIO that LEDs are connected to
#define LED 0x00									// Initial LED value
#define LED_DELAY 80000000							// Software delay length
#define SWITCH_CHANNEL 1							// GPIO port for SWITCHes
#define LED_CHANNEL 1								// GPIO port for LEDs
#define printf xil_printf							// smaller, optimized printf
// GPIO Device driver instance
XGpio input, output;
//All LEDs are on
void LedOn(int *led){
    *led = 0xFF;
}
void LedOff(int *led){    //All LEDs are off
     *led = 0x00;
}
void LedBlinking(int *led){    //Blinking LEDs
    *led = ~*led;
}
void RingCounter(int *led){   //Ring counter
    if(*led == 0x80 || *led == 0x00)
       *led = 0x01;
    else
        *led = 2 * (*led);
}
void BinaryCounter(int *led){    //Binary counter
    *led = *led + 1;
}
int LEDOutput(void)    //LED controlling function
{
    volatile int Delay;
    int Status0;
    int Status1;
    int led = LED; // Initialize to LED definition
    int switchValue;
    int johnsonDecriment = 1;
    int binaryCounter = 0;
    int fibonacciT0 = 0;
    int fibonacciT1 = 1;
    int fibonacciNext;
        Status0 = XGpio_Initialize(&input, GPIO_DEVICE_ID_0); //GPIO driver initialization
        if (Status0 != XST_SUCCESS) {
            return XST_FAILURE;
        }
        Status1 = XGpio_Initialize(&output, GPIO_DEVICE_ID_1); //GPIO driver initialization
        if (Status1 != XST_SUCCESS) {
            return XST_FAILURE;
        }
        XGpio_SetDataDirection(&output, SWITCH_CHANNEL, 0xFF); // Setting SWITCHes to input
        XGpio_SetDataDirection(&input, LED_CHANNEL, 0x00);	// Setting LEDs to output
            while (1) {                                       // Forever loop for controlling LEDs
                switchValue = XGpio_DiscreteRead(&input, SWITCH_CHANNEL); // Reading SWITCH status
                switch(switchValue){
                case 0x00:									//All LEDs are off
                    printf("Switch = 000 --> All LEDs are off\r\n");
                    LedOff(&led);
                    XGpio_DiscreteWrite(&output, LED_CHANNEL, led);
                    break;
                case 0x01: 									//All LEDs are on
                    printf("Switch = 001 --> All LEDs are on\r\n");
                    LedOn(&led);
                    XGpio_DiscreteWrite(&output, LED_CHANNEL, led);
                    break;
                case 0x02:									//Blinking LEDs
                    printf("Switch = 010 --> LEDs are blinking\r\n");
                    LedBlinking(&led);
                    XGpio_DiscreteWrite(&output, LED_CHANNEL, led);
                    break;
                case 0x03:									//Ring counter
                    printf("Switch = 011 --> Ring counter\r\n");
                    RingCounter(&led);
                    XGpio_DiscreteWrite(&output, LED_CHANNEL, led);
                    break;
                case 0x04:									//Johnson counter
                    printf("Switch = 100 --> Johnson counter\r\n");
                    if (led == 0x00)
                        led = 0x01;
                    else if(led % 2 == 0){
                        johnsonDecriment = 2 * johnsonDecriment;
                        led = led - johnsonDecriment;
                    }
                    else if(led == 0xFF){
                        led = led - 1;
                        johnsonDecriment = 1;
                    }
                    else
                        led = (2 * led) + 1;
                    XGpio_DiscreteWrite(&output, LED_CHANNEL, led);
                    break;
                case 0x05:									//Binary Counter
                    printf("Switch = 101 --> Binary counter\r\n");
                    BinaryCounter(&led);
                    XGpio_DiscreteWrite(&output, LED_CHANNEL, led);
                    break;
                case 0x06:									//Gray Counter
                    printf("Switch = 110 --> Gray Counter\r\n");
                    binaryCounter = binaryCounter + 1;
                    led = binaryCounter ^ (binaryCounter >> 1);
                    XGpio_DiscreteWrite(&output, LED_CHANNEL, led);
                    break;
                case 0x07:									//Fibonacci Counter
                    printf("Switch = 111 --> Fibonacci counter\r\n");
                    fibonacciNext = fibonacciT0 + fibonacciT1;
                    fibonacciT0 = fibonacciT1;
                    fibonacciT1 = fibonacciNext;
                    led = fibonacciT0;
                    XGpio_DiscreteWrite(&output, LED_CHANNEL, led);
                    break;
                }
                // Wait a small amount of time so that the LED blinking is visible
                for (Delay = 0; Delay < LED_DELAY; Delay++);
            }
        return XST_SUCCESS;
}
int main(void){    // Main function
    int Status;
    // Execute the LED output
    Status = LEDOutput();
    if (Status != XST_SUCCESS) {
        xil_printf("GPIO output to the LEDs failed!\r\n");
    }
    return 0;
}
