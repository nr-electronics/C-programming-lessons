#include "MDR32F9Qx_config.h"
#include "MDR32Fx.h"
#include "MDR32F9Qx_port.h"
#include "MDR32F9Qx_rst_clk.h"
#include "MDR32F9Qx_ssp.h"

#define VD7 PORT_Pin_2//define pin 2  to LED VD7
#define SA4 PORT_Pin_5//define pin 5 to Button SA4


static PORT_InitTypeDef PortInit; //init structure PortInit


int main(){
	
	RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTD, ENABLE);//switch on port d clocking
	RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTC, ENABLE);//switch on port c clocking
	
	
	//init port D like input
	PortInit.PORT_OE = PORT_OE_IN; // port mode -> input
	PortInit.PORT_FUNC = PORT_FUNC_PORT; // port mode
	PortInit.PORT_MODE = PORT_MODE_DIGITAL; // digital port mode
	PortInit.PORT_SPEED = PORT_SPEED_SLOW;  // choose slow mode for front
	PortInit.PORT_Pin = (SA4); // pin number 5 (PD5) which is connected to SA4 button
	PORT_Init(MDR_PORTD, &PortInit); // init port
	
	
	// init port C like output
	PortInit.PORT_OE = PORT_OE_OUT; // port mode -> output
	PortInit.PORT_FUNC = PORT_FUNC_PORT; // port mode
	PortInit.PORT_MODE = PORT_MODE_DIGITAL; // digital port mode
	PortInit.PORT_SPEED = PORT_SPEED_SLOW; // choose slow mode for front
	PortInit.PORT_Pin = (VD7); // pin number 2 (PC2) which is connected to VD7 LED
	PORT_Init(MDR_PORTC, &PortInit); // port C init with defined parameters
	PORT_ResetBits(MDR_PORTC, VD7); //switch off VD7 on start
	
	
		while(1){ // endless cycle
			if (PORT_ReadInputDataBit(MDR_PORTD, SA4) == 0) // if button pressed
				{
				PORT_SetBits(MDR_PORTC, VD7); // LED on
				}
			else
				{
				PORT_ResetBits(MDR_PORTC, VD7); // LED off
				}
		}
}
