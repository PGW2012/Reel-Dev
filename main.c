// Unscented Kalman Filter File
// Created by Dan Kassen
// Hand-Converted to C from Matlab file written by previous senior design team

#include <stm32f4xx.h>
#include <misc.h>			
#include <stm32f4xx_usart.h>
#include <stm32f4xx_spi.h>
#include <stm32f4xx_tim.h>
#include "stm32f4_discovery.h"
// speed setup as in delay time, larger number means slower
int cur_spd; //current motor speed
int obj_spd; //objective motor speed, read in from rx or analog
int mode; // auto or manual mode 
int dir; //direction
int i; // ramping counter



void init_GPIO(void); // gpio for debugging

void Delay(__IO uint32_t nCount) {
   while(nCount--) {
  }
}



int main(void){
	init_GPIO();
	cur_spd=0;
	obj_spd=0;
	mode=0;
	dir=0;
	while(1){
	// ead in mode, direction and speed
	//mode, 0=auto; 1=manual
	//direction, 0=feed, 1=retrack
	//speed convert from m/s to delaymicrosecond
		
	mode_read(); //call mode read function and set spd/dir accordingly
	det_ramp(); //determine if need ramp, boundary set at 100us (3600ticks). if yes, ramp inside thsi function
	run_motor(); //call run_mode function and start running
		
		


}
	
		}

void init_GPIO(void){

	GPIO_InitTypeDef GPIO_InitStruct;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1; // we want to configure all LED GPIO pins
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; 		// we want the pins to be an output
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz; 	// this sets the GPIO modules clock speed
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP; 	// this sets the pin type to push / pull (as opposed to open drain)
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL; 	// this sets the pullup / pulldown resistors to be inactive
	GPIO_Init(GPIOB, &GPIO_InitStruct); 			// this finally passes all the values to the GPIO_Init function which takes care of setting the corresponding bits.
}

void mode_read(void){ 
	//read from analog pin first, 0 is maual and 1 is auto
	if(mode==0){ // read from analog pin for direction and speed
		obj_spd=;
		dir=;
	}
	else if (mode==1){//read spd/dir from rx and set accordingly
		obj_spd=;
		dir=;
}
}

void det_ramp(void){
	if(obj_spd>=3600){
		return; //bakc to main loop and drive at input speed directly
	}
	else if(obj_spd<=3600 && cur_spd>obj_spd){ // speed up
			while(cur_spd>obj_spd){
				for(i=0;i<=20;i++){
					cur_spd=cur_spd-20;
					run_motor(dir,cur_spd);
				}
			}
		}
	else if(obj_spd<=3600 && cur_spd<obj_spd){// speed down
		while(cur_spd<obj_spd){
				for(i=0;i<=20;i++){
					cur_spd=cur_spd+20;
					run_motor(dir,cur_spd);
				}
			}
	}
		
	
	}

void run_motor(void){
	if(dir==0){
		GPIOB->BSRRL |= GPIO_Pin_1;//Feed direction 
	}
	else if(dir==1){
		GPIOB->BSRRH |= GPIO_Pin_1;// retrack direction
	}
			
		GPIOB->BSRRH |= GPIO_Pin_0; // set pin low
		Delay(obj_spd); // delay, 36 is 1 microsecond
		GPIOB->BSRRL |= GPIO_Pin_0; // set pin high
		Delay(obj_spd); // delay, 36 is 1 microsecond
					
	}
	