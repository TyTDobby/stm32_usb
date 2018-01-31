#include "library/cmsis/inc/stm32f103xb.h"
#include "library/cmsis/inc/system_stm32f1xx.h"
#include "library/usb/usb.h"

uint16_t *buffSend[64];
/*
 * Name: RCCConfig
 * Description: System Clock Configuration
 * Parametrs: none
 */
void RCCConfig(void){

 	RCC->CR |= RCC_CR_HSEON;               /* Run HSE */
 	while((RCC->CR & RCC_CR_HSERDY) == 0); /* Waiting to switch to PLL HSE */
 	
 	RCC->CFGR |= RCC_CFGR_HPRE_DIV1 | RCC_CFGR_PPRE2_DIV1 | RCC_CFGR_PPRE1_DIV1; /* HCLK = SYSCLK ;  PCLK2 = HCLK ; PCLK1 = HCLK */
 	RCC->CFGR &= ~((RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL));    /* Clear */
 	
 	RCC->CFGR |= RCC_CFGR_PLLSRC; 		   /* Clock PLL to HSE (8 MHz) */
	RCC->CFGR |= RCC_CFGR_PLLMULL9;        /* Multiply frequency on 9 (8*9=72 MHz) */
	RCC->CR |= RCC_CR_PLLON; 			   /* Run PLL */
	while((RCC->CR & RCC_CR_PLLRDY) == 0); /* Waiting to switch to PLL */
	
	RCC->CFGR &= ~RCC_CFGR_SW; 							 /* Clear bits SW0, SW1 */
	RCC->CFGR |= RCC_CFGR_SW_PLL; 						 /* PLL selected as system clock */
	while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_1); /* Waiting to switch to PLL */
	
	FLASH->ACR |= FLASH_ACR_PRFTBE;      /* On prefetch buffer */
 	FLASH->ACR |= FLASH_ACR_LATENCY_2;   /* Skip 2 measures */

	RCC->CFGR &= ~RCC_CFGR_USBPRE; 	  		/* Prescaler USB 1.5 */
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPCEN | RCC_APB2ENR_AFIOEN; /* GPIO clock enable */


}
/*
 * Name: GPIOConfig
 * Description: GPIO Configuration
 * Parametrs: none
 */
void GPIOConfig(void){
	GPIOA->CRH |= GPIO_CRH_MODE11_1 | GPIO_CRH_MODE12_1 
			   |  GPIO_CRH_CNF11_1  | GPIO_CRH_CNF12_1;
	
	GPIOC->CRH |= GPIO_CRH_MODE13 | GPIO_CRH_CNF13_0; 
}

/*
 * Name: Config
 * Description: STM32 Configuration
 * Parametrs: none
 */
void Config(void){
	RCCConfig();
	GPIOConfig();
	USBConfig();

}

int main(void){
	Config(); 
	*buffSend = 0x30;
	*(buffSend + 1) = 0x31;
	*(buffSend + 2) = 0x32;
	*(buffSend + 3) = 0x33;
	while(1) {
		// USBSendData(buffSend);
		// for (int i = 0; i < 0xfffff; ++i)
		// {
		// 	/* code */
		// }
	}
	return 0;

}