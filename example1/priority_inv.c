/*----------------------------------------------------------------------------
 * CMSIS-RTOS 'main' function template
 *---------------------------------------------------------------------------*/

#define osObjectsPublic                     // define objects in main module
#include "osObjects.h"                      // RTOS object definitions
 #include "cmsis_os.h"                                           // CMSIS RTOS header file
#include <stdio.h>
#include <math.h>
#include "Board_LED.h"                  // ::Board Support:LED
#include "RTE_Components.h"             // Component selection

void PA (void const *argument);
void PB (void const *argument);
void PC (void const *argument);

osThreadDef(PA, osPriorityHigh, 1, 0);
osThreadDef(PB, osPriorityNormal, 1, 0);
osThreadDef(PC, osPriorityBelowNormal, 1, 0);

osThreadId t_main,t_PA,t_PB,t_PC;

void delay(int timer){ 
	long k, count = 0;
	for(k = 0; k < timer; k++){
					count++;
			}
	}

void PA (void const *argument) {
	{
		delay(20000); //execute something, and after requires service from PC
    //osThreadSetPriority(t_PC, osPriorityAboveNormal); // uncomment line 33 and 35 to show inversion
		osSignalWait(0x02,osWaitForever);			
	 //osThreadSetPriority(t_PC,osPriorityBelowNormal);
		delay(80000); //continue executing 
	
	}
}

void PB (void const *argument) {
	delay(100000); // execute something 
}

void PC (void const *argument) {
	
		delay(20000); //do whats needed to release resource for Process A
	   osSignalSet(t_PA,0x02);	
		 delay(80000);

}

int main(void)
{    
	osKernelInitialize (); 
	LED_Initialize();
	t_main = osThreadGetId ();
	osThreadSetPriority(t_main,osPriorityHigh);
	t_PC = osThreadCreate(osThread(PC), NULL);
	
	osDelay(5);

	t_PB = osThreadCreate(osThread(PB), NULL);
	
	osDelay(5);
	t_PA = osThreadCreate(osThread(PA), NULL);
	
	osThreadTerminate(t_main);
	 osKernelStart ();    
	for (;;) {}
}

