#include "usb.h"

extern uint8_t descDevice[USB_DESC_SIZE_DEVICE];
extern uint8_t descDeviceQualifier[USB_DESC_SIZE_DEVICE_QUALIFIER];
extern uint8_t descConfiguration[USB_DESC_SIZE_CONFIGURATION];
extern uint8_t descStringLangID[USB_STR_SIZE_LANGID];
extern uint8_t descStringProduct[USB_STR_SIZE_PRODUCT];
extern uint8_t descStringMFC[USB_STR_SIZE_MFC];
extern uint8_t descStringSerialNumber[USB_STR_SIZE_SERIALNUMBER];
extern uint8_t descStringConfig[USB_STR_SIZE_CONFIG];
extern uint8_t descStringInterface[USB_STR_SIZE_INTERFACE];
extern uint8_t descHIDReport[USB_DESC_SIZE_HID_REPORT];

uint8_t devAddress = 0;
USB_SETUP_PACKET SetupPacket;
uint8_t *bufferSetup[12];

void USBReset(void){
    
    USB->ISTR = 0x0;

    USB->BTABLE = BTABLE_ADDRESS; /* Set a address table buffer in memory USB */
    
    USB->CNTR = USB_CNTR_RESETM | USB_CNTR_SUSPM | USB_CNTR_WKUPM | USB_CNTR_CTRM;
    
    /* Set a address buffer */
    USB_ADDR0_RX = USB_EP0_RX;
    USB_ADDR0_TX = USB_EP0_TX;
    USB_COUNT0_TX = 0x40;
    USB_COUNT0_RX = 0x8400;

    /* Endpoints 0; Type: CONTROL; RX: VALID; TX: NAK */
    USB->EP0R = USB_EP_CONTROL | USB_EP_RX_VALID | USB_EP_TX_NAK | USB_EP_AE_0;

    USB->DADDR = USB_DADDR_EF;   /* Activation device */

    USB->ISTR &= ~USB_ISTR_RESET;
}

void USBZeroLengthPacket(void){
    USB_COUNT0_TX = 0x0;
    USB->EP0R = USB_EP_TX_VALID | USB_EP_CONTROL;
    while(!(USB->EP0R & USB_EP_CTR_TX)){}  
}

void USBRequest(USB_SETUP_PACKET *req, uint8_t *pdata){
    req->bmRequestType     = *pdata;
    req->bRequest          = *(pdata + 1);
    req->wValue.low        = *(pdata + 2);
    req->wValue.high       = *(pdata + 3);
    req->wIndex.low        = *(pdata + 4);
    req->wIndex.high       = *(pdata + 5);
    req->wLength.low       = *(pdata + 6);
}

void USBReadPMA(uint16_t *buff, uint16_t offset, uint16_t numBytes) {
    uint32_t nBytes = (numBytes + 1) >> 1;
    uint32_t *addrRx = (uint32_t *)(offset * 2 + USB_PMAADDR);
    while(nBytes--) {
        *buff++ = *addrRx++;
    }
}
void USBWritePMA(uint16_t *buff, uint16_t offset, uint16_t numBytes){
    uint32_t nBytes = (numBytes + 1) >> 1;
    uint32_t *addrTx = (uint32_t *)(offset * 2 + USB_PMAADDR);
    while(nBytes--) {
        *addrTx++ = *buff++;
    }
}

void USBSetup(void){
    USB->ISTR &= ~USB_ISTR_CTR;
    USB->EP0R &= ~USB_EP_CTR_RX;
    USB->EP0R |= USB_EP_DTOG_TX;
    USBReadPMA((uint16_t *)bufferSetup, USB_EP0_RX, 8);
    USBRequest(&SetupPacket, (uint8_t *)bufferSetup);
    if(SetupPacket.bmRequestType == 0x00){
    	if(SetupPacket.bRequest == USB_REQ_SET_ADDRESS){
          	devAddress = SetupPacket.wValue.low;
           	USBZeroLengthPacket();
           	USB->DADDR = devAddress | USB_DADDR_EF;
    	}else if(SetupPacket.bRequest == USB_REQ_SET_CONFIGURATION){
    		USBZeroLengthPacket();
    	}
    }else if(SetupPacket.bmRequestType == 0x21){

    }else if(SetupPacket.bmRequestType == 0x80){
    	if(SetupPacket.bRequest == USB_REQ_GET_DESCRIPTOR){
    		if(SetupPacket.wValue.high == USB_DESC_TYPE_DEVICE){
    			USBWritePMA((uint16_t *)descDevice, USB_EP0_TX, USB_DESC_SIZE_DEVICE);
    			USB_COUNT0_TX = USB_DESC_SIZE_DEVICE;
    			USB->EP0R = USB_EP_TX_VALID | USB_EP_CONTROL;
    			while(!(USB->EP0R & USB_EP_CTR_TX)){} 
    		}else if(SetupPacket.wValue.high == USB_DESC_TYPE_DEVICE_QUALIFIER){
    			USBWritePMA((uint16_t *)descDeviceQualifier, USB_EP0_TX, USB_DESC_SIZE_DEVICE_QUALIFIER);
    			USB_COUNT0_TX = USB_DESC_SIZE_DEVICE_QUALIFIER;
    			USB->EP0R = USB_EP_TX_VALID | USB_EP_CONTROL;
    			while(!(USB->EP0R & USB_EP_CTR_TX)){} 
    		}else if(SetupPacket.wValue.high == USB_DESC_TYPE_CONFIGURATION){
    			
    			USBWritePMA((uint16_t *)descConfiguration, USB_EP0_TX, SetupPacket.wLength.low);
    			USB_COUNT0_TX = SetupPacket.wLength.low;
    			USB->EP0R = USB_EP_TX_VALID | USB_EP_CONTROL;
    			while(!(USB->EP0R & USB_EP_CTR_TX)){} 

    		}else if(SetupPacket.wValue.high == USB_DESC_TYPE_STRING){
    			if(SetupPacket.wValue.low == USB_IDX_LANGID_STR){
    				USBWritePMA((uint16_t *)descStringLangID, USB_EP0_TX, USB_STR_SIZE_LANGID);
    				USB_COUNT0_TX = USB_STR_SIZE_LANGID;
    				USB->EP0R = USB_EP_TX_VALID | USB_EP_CONTROL;
    				while(!(USB->EP0R & USB_EP_CTR_TX)){}
    			}else if(SetupPacket.wValue.low == USB_IDX_MFC_STR){
    				USBWritePMA((uint16_t *)descStringMFC, USB_EP0_TX, USB_STR_SIZE_MFC);
    				USB_COUNT0_TX = USB_STR_SIZE_MFC;
    				USB->EP0R = USB_EP_TX_VALID | USB_EP_CONTROL;
    				while(!(USB->EP0R & USB_EP_CTR_TX)){}
    			}else if(SetupPacket.wValue.low == USB_IDX_PRODUCT_STR){
    				USBWritePMA((uint16_t *)descStringProduct, USB_EP0_TX, USB_STR_SIZE_PRODUCT);
    				USB_COUNT0_TX = USB_STR_SIZE_PRODUCT;
    				USB->EP0R = USB_EP_TX_VALID | USB_EP_CONTROL;
    				while(!(USB->EP0R & USB_EP_CTR_TX)){}
    			}else if(SetupPacket.wValue.low == USB_IDX_SERIAL_STR){
    				USBWritePMA((uint16_t *)descStringSerialNumber, USB_EP0_TX, USB_STR_SIZE_SERIALNUMBER);
    				USB_COUNT0_TX = USB_STR_SIZE_SERIALNUMBER;
    				USB->EP0R = USB_EP_TX_VALID | USB_EP_CONTROL;
    				while(!(USB->EP0R & USB_EP_CTR_TX)){}
    			}else if(SetupPacket.wValue.low == USB_IDX_CONFIG_STR){
    				USBWritePMA((uint16_t *)descStringConfig, USB_EP0_TX, USB_STR_SIZE_CONFIG);
    				USB_COUNT0_TX = USB_STR_SIZE_CONFIG;
    				USB->EP0R = USB_EP_TX_VALID | USB_EP_CONTROL;
    				while(!(USB->EP0R & USB_EP_CTR_TX)){}
    			}else if(SetupPacket.wValue.low == USB_IDX_INTERFACE_STR){
    				USBWritePMA((uint16_t *)descStringInterface, USB_EP0_TX, USB_STR_SIZE_INTERFACE);
    				USB_COUNT0_TX = USB_STR_SIZE_INTERFACE;
    				USB->EP0R = USB_EP_TX_VALID | USB_EP_CONTROL;
    				while(!(USB->EP0R & USB_EP_CTR_TX)){}
    			}
    		}
		}
	}else if(SetupPacket.bmRequestType == 0x81){

	}
	USB->EP0R = USB_EP_CONTROL | USB_EP_RX_VALID;
}


/* Public functoin */

/*
 * Name: usb_config
 * Description: USB Configuration
 * Parametrs: none
 */
void USBConfig(void){
    RCC->APB1ENR |= RCC_APB1ENR_USBEN; /* USB clock enable */

	USB->CNTR = USB_CNTR_FRES;/* CNTR_FRES = 1 */
     
    USB->CNTR = 0; /* CNTR_FRES = 0 */

	USB->CNTR |= USB_CNTR_PDWN; 

	/* Reset driver */
	USB->CNTR = 0x0;

    /* Reset registr flag interrput */
	USB->ISTR = 0x0;

    /* Allow interrput */
    //USB->CNTR |= USB_CNTR_RESETM | USB_CNTR_SUSPM | USB_CNTR_WKUPM | USB_CNTR_SOFM | USB_CNTR_ESOFM | USB_CNTR_CTRM | USB_CNTR_ERRM | USB_CNTR_PMAOVRM;
	USB->CNTR = USB_CNTR_RESETM | USB_CNTR_SUSPM | USB_CNTR_WKUPM | USB_CNTR_CTRM;

    /* Clean up buffer */
	// for(uint16_t *i = USB_PMAADDR; i <= USB_PMAADDR + 0x3FF; i+=2) *i = 0;

   	/* Activation interrput */
	NVIC_EnableIRQ(USBWakeUp_IRQn);
	// NVIC_EnableIRQ(USB_HP_CAN1_TX_IRQn);
	NVIC_EnableIRQ(USB_LP_CAN1_RX0_IRQn);

}

/* Interrput */

void USB_LP_IRQHandler(void){
    uint32_t num;
	if(USB->ISTR & USB_ISTR_RESET){ 
    	USBReset();
	}
    if(USB->ISTR & USB_ISTR_SUSP){
        USB->CNTR |= USB_CNTR_FSUSP;                       /* Force Suspend */
        USB->CNTR |= USB_CNTR_LP_MODE;                     /* Low Power Mode */
    }
    if(USB->ISTR & USB_ISTR_WKUP){  
        USB->CNTR &= ~USB_CNTR_FSUSP;
    }
    while((USB->ISTR & USB_ISTR_CTR) != 0){
        num = USB->ISTR & USB_ISTR_EP_ID;
        if(num == 0){ /* Endpoint 0 */
            if((USB->ISTR & USB_ISTR_DIR) != 0){
                if(USB->EP0R & USB_EP_SETUP){ /* SETUP */
                    USBSetup();
                }else{ /* OUT */

                }
            }else{ /* IN */
                USB->EP0R &= ~USB_EP_CTR_TX;
            }
        }else{ /* num > 0 */

        }
    }
    USB->ISTR = 0x0;
}
