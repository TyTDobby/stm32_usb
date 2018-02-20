#include "usb.h"

/* Variables */

volatile USB_TypeDef       *USB = (USB_TypeDef *)USB_BASE; 
volatile USBEpBuf_TypeDef *EPBuffTable[3] = {
	(USBEpBuf_TypeDef *)USB_PMA_ADDR,
	(USBEpBuf_TypeDef *)USB_PMA_ADDR + 0x10,
	(USBEpBuf_TypeDef *)USB_PMA_ADDR + 0x20
};

USBHeap heap;
USBSetupPacket SetupPacket; 

uint8_t exitFun = 0;
uint16_t test = 0;

#define USBEpClearCtrRx(reg, epNum)   (USB->EPR[epNum] = USB->EPR[epNum] & 0x7FFF & USB_EP_MASK)
#define USBEpClearCtrTx(reg, epNum)   (USB->EPR[epNum] = USB->EPR[epNum] & 0xFF7F & USB_EP_MASK)

uint8_t descDevice[] = 
{   
    0x12,				/* bLength */
    0x01,				/* bDescriptorType */
    0x00,				/* bcdUSB */  
    0x02,
    0x00,				/* bDeviceClass */
    0x00,				/* bDeviceSubClass */
    0x00,				/* bDeviceProtocol */
    0x40,				/* bMaxPacketSize */
    LOBYTE(USB_VID),	/* idVendor */ 
    HIBYTE(USB_VID),	/* idVendor */
    LOBYTE(USB_PID),	/* idProduct */  
    HIBYTE(USB_PID),	/* idProduct */
    0x00,				/* bcdDevice rel. 2.00 */
    0x02,
    0x01,				/* Index of manufacturer  string */
    0x02,				/* Index of product string */
    0x03,				/* Index of serial number string */
    0x01 				/* bNumConfigurations */
};
/************** Descriptor of device qualifier ****************/
uint8_t descDeviceQualifier[] = 
{  
    0x0a,	/* bLength */
    0x06,	/* bDescriptorType */
    0x00,	/* bcdUSB */  
    0x02,
    0x00,	/* bDeviceClass */
    0x00,	/* bDeviceSubClass */
    0x00,	/* bDeviceProtocol */
    0x40,	/* bMaxPacketSize */
    0x01,	/* bNumConfigurations */
    0x00 	/* bReserve */ 
};
/*
 * Descriptor of configuration 
 */ 
uint8_t descConfiguration[] =
{
 	0x09,		/* bLength: Configuration Descriptor size */
 	0x02,		/* bDescriptorType: Configuration */
 	0x29,		/* wTotalLength: Bytes returned */
 	0x00,
 	0x01,		/* bNumInterfaces: 1 interface */
 	0x01,		/* bConfigurationValue: Configuration value */
 	0x00,		/* iConfiguration: Index of string descriptor describing the configuration */
 	0xC0,		/* bmAttributes: bus powered */
 	0x32,		/* MaxPower 100 mA: this current is used for detecting Vbus */
/*
 * Descriptor of interface 
 */
 	0x09,		/* bLength: Interface Descriptor size */
 	0x04,		/* bDescriptorType: Interface descriptor type */
 	0x00,		/* bInterfaceNumber: Number of Interface */
 	0x00,		/* bAlternateSetting: Alternate setting */
 	0x02,		/* bNumEndpoints */
 	0x03,		/* bInterfaceClass: USB_HID */
 	0x00,		/* bInterfaceSubClass : 1=BOOT, 0=no boot */
 	0x00,		/* nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse */
 	0x05,		/* iInterface: Index of string descriptor */
/*
 * Descriptor of USB_HID 
 */
 	0x09,		/* bLength: USB_HID Descriptor size */
 	0x21,		/* bDescriptorType: USB_HID */ 
 	0x11,		/* bUSB_HIDUSTOM_HID: USB_HID Class Spec release number */
 	0x01,
 	0x00,		/* bCountryCode: Hardware target country */
 	0x01,		/* bNumDescriptors: Number of USB_HID class descriptors to follow */
 	0x22,		/* bDescriptorType */
 	0x24,		/* wItemLength: Total length of Report descriptor */ 
 	0x00,
/*
 * Descriptor of endpoint (IN) 
 */
 	0x07,		/* bLength: Endpoint Descriptor size */
 	0x05,		/* bDescriptorType: */
 	0x81,		/* bEndpointAddress: Endpoint Address (IN) */
 	0x03,		/* bmAttributes: Bulk */
 	0x20,		/* wMaxPacketSize: 2 Byte max */
 	0x00,
 	0x32,		/* bInterval: Polling Interval (20 ms) */
/*
 * Descriptor of endpoint (OUT) 
 */
 	0x07,		/* bLength: Endpoint Descriptor size */
 	0x05,		/* bDescriptorType: */
 	0x02,		/* bEndpointAddress: Endpoint Address (OUT) */
 	0x03,		/* bmAttributes: Bulk */
 	0x20,		/* wMaxPacketSize: 2 Bytes max */
 	0x00,
 	0x32		/* bInterval: Polling Interval (20 ms) */
};
uint8_t descStringLangID[] = 
{
	0x04,
	0x03,
	0x09,
	0x04
};

uint8_t descStringProduct[] = 
{
	0x0e, 
	0x03,
	'D',0x00,
	'i',0x00,
	'g',0x00,
	'D',0x00,
	'e',0x00,
	'v',0x00
};

uint8_t descStringMFC[] = 
{
	0x0e, 
	0x03,
	'D',0x00,
	'i',0x00,
	'g',0x00,
	'D',0x00,
	'e',0x00,
	'v',0x00
};
 
uint8_t descStringSerialNumber[] = 
{
	0x1a,  
	0x03,
	'0',0x00,
	'0',0x00,
	'0',0x00,
	'0',0x00,
	'0',0x00,
	'0',0x00,
	'0',0x00,
	'0',0x00,
	'0',0x00,
	'0',0x00,
	'1',0x00,
	'A',0x00
};

uint8_t descStringConfig[] = 
{
	0x24,  
	0x03,
	'C',0x00,
	'u',0x00,
	's',0x00,
	't',0x00,
	'o',0x00,
	'm',0x00,
	' ',0x00,
	'H',0x00,
	'I',0x00,
	'D',0x00,
	' ',0x00,
	'C',0x00,
	'o',0x00,
	'n',0x00,
	'f',0x00,
	'i',0x00,
	'g',0x00
};

uint8_t descStringInterface[] = 
{
	0x2a,  
	0x03,
	'C',0x00,
	'u',0x00,
	's',0x00,
	't',0x00,
	'o',0x00,
	'm',0x00,
	' ',0x00,
	'H',0x00,
	'I',0x00,
	'D',0x00,
	' ',0x00,
	'I',0x00,
	'n',0x00,
	't',0x00,
	'e',0x00,
	'r',0x00,
	'f',0x00,
	'a',0x00,
	'c',0x00,
	'e',0x00
};
uint8_t descHIDReport[] = 
{ 
    0x06, 0x00, 0xff,	/* USAGE_PAGE (Generic Desktop) */
    0x09, 0x01,			/* USAGE (Vendor Usage 1) */
    0xa1, 0x01,			/* COLLECTION (Application) */
    0x85, 0x01,			/*   REPORT_ID (1) */
    0x09, 0x01,			/*   USAGE (Vendor Usage 1) */
    0x15, 0x00,			/*   LOGICAL_MINIMUM (0) */
    0x25, 0x7f,			/*   LOGICAL_MAXIMUM (255) */
    0x75, 0x08,			/*   REPORT_SIZE (256) */
    0x95, 0x04,			/*   REPORT_COUNT (1) */
    0x91, 0x92,			/*   OUTPUT (Data,Var,Abs,NLin,Vol) */
    0x85, 0x02,			/*   REPORT_ID (2) */
    0x09, 0x01,			/*   USAGE (Vendor Usage 1) */
    0x15, 0x00,			/*   LOGICAL_MINIMUM (0) */
    0x25, 0x7f,			/*   LOGICAL_MAXIMUM (127) */
    0x75, 0x08,			/*   REPORT_SIZE (8) */
    0x95, 0x04,			/*   REPORT_COUNT (4) */
    0x81, 0x92,			/*   INPUT (Data,Var,Abs,NLin,Vol) */
    0xc0				/* END COLLECTION */
};

/* Prototype functoin */
void USBWriteEP(uint8_t number);
void USBReadEP(uint8_t *buffer, 
			   uint16_t len, 
			   uint8_t number);
void USBRequest(USBSetupPacket *req, 
				uint8_t *pdata);
void USBReset(void);
void USBSetup(void);
void USBCtrHandler(void);
/* Public */
void USBConfig(void){

	heap.cntMaxEp0 = 64;
	
	NVIC_DisableIRQ(USB_LP_CAN1_RX0_IRQn);
    RCC->APB1ENR |= RCC_APB1ENR_USBEN;

    USB->CNTR   = USB_CNTR_FRES; /* Force USB Reset */
    USB->BTABLE = 0;
    USB->DADDR  = 0;
    USB->ISTR   = 0;
    USB->CNTR   = USB_CNTR_RESETM; 
    NVIC_EnableIRQ(USB_LP_CAN1_RX0_IRQn);
}
void USBRead(uint8_t *buff){
	heap.cntRx = (uint8_t)EPBuffTable[1]->COUNT_RX;
	USBReadEP((uint8_t *)buff, heap.cntRx, 1);
	USB->EPR[1] = USB_EP_INTERRUPT | USB_EP_RX_VALID;
}
void USBWrite(uint8_t *buff){

}

/* Private */

void USBGetString(uint8_t *str, uint8_t *buff, uint16_t *len)
{
  uint8_t cnt = 0;
  
  if (str != 0) 
  {
    *len =  sizeof(str);    
    buff[cnt++] = *len;
    buff[cnt++] =  0x03;
    
    while (*str != '\0') 
    {
      buff[cnt++] = *str++;
      buff[cnt++] =  0x00;
    }
  } 
}

void USBWriteEP(uint8_t number){
	uint16_t len = heap.cntTx >= heap.cntMaxEp0 ? heap.cntMaxEp0 : heap.cntTx;
	uint16_t nBytes = (len + 1) >> 1;
    uint32_t *addrTx = (uint32_t *)((uint16_t)EPBuffTable[number]->ADDR_TX * 2 + USB_PMA_ADDR);
    uint16_t *temp = (uint16_t *)heap.buffTx;
    while(nBytes--)
        *addrTx++ = *temp++;
    EPBuffTable[number]->COUNT_TX = len;
    heap.cntTx -= len;
    heap.buffTx += len;
}
void USBReadEP(uint8_t *buffer, 
			   uint16_t len, 
			   uint8_t number){
    uint16_t nBytes = (len + 1) >> 1;
    uint32_t *addrRx = (uint32_t *)((uint16_t)EPBuffTable[number]->ADDR_RX * 2 + USB_PMA_ADDR);
    uint16_t *temp = (uint16_t *)buffer;
    while(nBytes--)
        *temp++ = *addrRx++;
}
void USBStatusTx(uint8_t numEp, 
				 uint16_t status)
{
    register uint16_t val = USB->EPR[numEp];
    // USB->EPR[numEp] = val;
    // USB->EPR[numEp] |= status;
    USB->EPR[numEp] = (val ^ (status & USB_EP_STAT_TX)) & (USB_EP_MASK | USB_EP_STAT_TX);
}

void USBStatusRx(uint8_t numEp, 
			     uint16_t status)
{
    register uint16_t val = USB->EPR[numEp];
	// register uint16_t val = USB->EPR[numEp] & USB_EP_STAT_RX;
    // USB->EPR[numEp] = val;
    // USB->EPR[numEp] |= status;

    USB->EPR[numEp] = (val ^ (status & USB_EP_STAT_RX)) & (USB_EP_MASK | USB_EP_STAT_RX);
}
void USBSendData(uint8_t *buffer, 
				 uint8_t len, 
				 uint8_t number){
	heap.buffTx = buffer;
	heap.cntTx = len;

	if(len > 0){
        USBWriteEP(number);
    }else{
        EPBuffTable[number]->COUNT_TX = 0;
    }
    // uint16_t val = USB->EPR[number];
    // USB->EPR[number] ^= USB_EP_STAT_TX_0;
	USBStatusTx(0, USB_EP_TX_VALID);
	while(!(USB->EPR[number] & USB_EP_CTR_TX)){}
}
void USBRequest(USBSetupPacket *req, 
				uint8_t *pdata){
    req->bmRequestType     = *pdata;
    req->bRequest          = *(pdata + 1);
    req->wValue.low        = *(pdata + 2);
    req->wValue.high       = *(pdata + 3);
    req->wIndex.low        = *(pdata + 4);
    req->wIndex.high       = *(pdata + 5);
    req->wLength.low       = *(pdata + 6);
    req->wLength.high      = *(pdata + 7);
}
void USBReset(void){

	EPBuffTable[0]->ADDR_TX = 0x80;
	EPBuffTable[0]->ADDR_RX = 0x100;
	EPBuffTable[0]->COUNT_RX = 0xbc00;

    EPBuffTable[1]->ADDR_TX = 0x180;
    EPBuffTable[1]->ADDR_RX = 0x200;
    EPBuffTable[1]->COUNT_RX = 0xbc00;

    USB->EPR[0] = USB_EP_CONTROL | USB_EP_RX_VALID;

	USB->EPR[1] = USB_EP_INTERRUPT | USB_EP_RX_VALID | USB_EP_TX_VALID | 0x01;

	USB->CNTR   = USB_CNTR_CTRM | USB_CNTR_RESETM | USB_CNTR_SUSPM;
    USB->ISTR   = 0x00;
    USB->BTABLE = 0x00;
    USB->DADDR  = USB_DADDR_EF;
}
void USBGetDescriptor(void){
	switch(SetupPacket.wValue.high){
		case USB_DEVICE_DESC_TYPE:
			heap.cntTx = MIN(SetupPacket.wLength.low, sizeof(descDevice));
			heap.buffTx = descDevice;
			break;
		case USB_DEVICE_QR_DESC_TYPE:
			heap.cntTx = MIN(SetupPacket.wLength.low, sizeof(descDeviceQualifier));
			heap.buffTx = descDeviceQualifier;
			break;
		case USB_CFG_DESC_TYPE:
			heap.cntTx = MIN(SetupPacket.wLength.low, sizeof(descConfiguration));
			heap.buffTx = descConfiguration;
			break;
		case USB_STR_DESC_TYPE:
			switch(SetupPacket.wValue.low){
				case USB_IDX_LANGID_STR:
					heap.cntTx = MIN(SetupPacket.wLength.low, sizeof(descStringLangID));
					heap.buffTx = descStringLangID;
					break;
				case USB_IDX_MFC_STR:
					heap.cntTx = MIN(SetupPacket.wLength.low, sizeof(descStringMFC));
					heap.buffTx = descStringMFC;
					break;
				case USB_IDX_PRODUCT_STR:
					heap.cntTx = MIN(SetupPacket.wLength.low, sizeof(descStringProduct));
					heap.buffTx = descStringProduct;
					break;
				case USB_IDX_SERIAL_STR:
					heap.cntTx = MIN(SetupPacket.wLength.low, sizeof(descStringSerialNumber));
					heap.buffTx = descStringSerialNumber;
					break;
				case USB_IDX_CONFIG_STR:
					heap.cntTx = MIN(SetupPacket.wLength.low, sizeof(descStringConfig));
					heap.buffTx = descStringConfig;
					break;
				case USB_IDX_INTERFACE_STR:
					heap.cntTx = MIN(SetupPacket.wLength.low, sizeof(descStringInterface));
					heap.buffTx = descStringInterface;
					break;
			}
			break;
        case USB_HID_DESC_TYPE:
            heap.cntTx = MIN(SetupPacket.wLength.low, sizeof(descHIDReport));
			heap.buffTx = descHIDReport;
            break;

	}
}
void USBSetup(void){
	switch(SetupPacket.bmRequestType & 0x1f){
		case USB_DEVICE:
			if(SetupPacket.bRequest == USB_GET_DESCRIPTOR){
				USBGetDescriptor();
			}else if(SetupPacket.bRequest == USB_SET_ADDRESS){
				heap.devAddress = SetupPacket.wValue.low;
				heap.cntTx = 0;
				heap.buffTx = 0;
			}else if(SetupPacket.bRequest == USB_SET_CONFIGURATION){
				heap.cntTx = 0;
				heap.buffTx = 0;
			}
			break;
		case USB_INTERFACE:
			if(SetupPacket.bRequest == 0x01){
				exitFun = 1;
				// heap.cntTx = 0;
				// heap.buffTx = 0;
				heap.ep = USB->EPR[0];
				USB->EPR[0] = heap.ep;
				USB->EPR[0] = USB_EP_CONTROL | USB_EP_TX_STALL; 
				// return;
            }else if(SetupPacket.bRequest == USB_GET_DESCRIPTOR){
                USBGetDescriptor();
            }else if(SetupPacket.bRequest == 0x0a){
                heap.cntTx = 0;
				heap.buffTx = 0;
            }
			break;
		case USB_ENDPOINT:

			break;
		case USB_OTHER:

			break;
	}
	if(exitFun){
		heap.ep = USB->EPR[0] & USB_EP_STAT_RX;
		USB->EPR[0] = heap.ep;
		USB->EPR[0] = USB_EP_CONTROL | USB_EP_RX_VALID; 
		exitFun = 0;
		return;
	}

	USBWriteEP(0);
	// USBStatusTx(0, USB_EP_TX_VALID);
	heap.ep = USB->EPR[0] & USB_EP_STAT_TX;
	USB->EPR[0] = heap.ep;
	USB->EPR[0] = USB_EP_CONTROL | USB_EP_TX_VALID;
	while(!(USB->EPR[0] & USB_EP_CTR_TX)){}
	if(heap.devAddress){
		// GPIOC->BSRR = GPIO_BSRR_BS13;
		USB->DADDR = USB_DADDR_EF | heap.devAddress;
		heap.devAddress = 0;
	}

} 

void USBCtrHandler(void){
	uint8_t numEp = heap.istr & USB_ISTR_EP_ID;
	if(USB->EPR[numEp] & USB_EP_CTR_RX){ 
		if(numEp == 0){ 
			if(USB->EPR[0] & USB_EP_SETUP){
				test++;
				if(test > 16){
					GPIOC->BSRR = GPIO_BSRR_BS13;
				}
				USBReadEP((uint8_t *)heap.buffSetup, 8, numEp);
				USBRequest(&SetupPacket, (uint8_t *)heap.buffSetup);
				USBSetup();
			}
		}else{

		}
		heap.ep = USB->EPR[numEp];
		USB->EPR[numEp] = heap.ep;;
		USB->EPR[numEp] = USB_EP_CONTROL | USB_EP_RX_VALID; 
	}else if(USB->EPR[numEp] & USB_EP_CTR_TX){
		GPIOC->BSRR = GPIO_BSRR_BS13;
		if(heap.cntTx){
			USBSendData(heap.buffTx, heap.cntTx, numEp);
		}
		// heap.ep = USB->EPR[0] & USB_EP_STAT_TX;
		// USB->EPR[0] = heap.ep;
		// USB->EPR[0] = USB_EP_CONTROL | USB_EP_TX_VALID;
	}
}
/* Interrupt */

void USB_LP_CAN1_RX0_IRQHandler()
{
	heap.istr = USB->ISTR; 
    if(USB->ISTR & USB_ISTR_RESET) { /* Reset */
        USB->ISTR &= ~USB_ISTR_RESET;
        USBReset();
        return;
    }
    while(USB->ISTR & USB_ISTR_CTR) { /* CTR */
		heap.istr = USB->ISTR;
        USBCtrHandler();
        USB->ISTR &= ~USB_ISTR_CTR;
        return;
    }
    if(USB->ISTR & USB_ISTR_PMAOVR) {
        USB->ISTR &= ~USB_ISTR_PMAOVR;
        /* Handle PMAOVR status */
        return;
    }
    if(USB->ISTR & USB_ISTR_SUSP) {
        USB->ISTR &= ~USB_ISTR_SUSP;
        return;
    }
    if(USB->ISTR & USB_ISTR_ERR) {
        USB->ISTR &= ~USB_ISTR_ERR;
        /* Handle Error */
        return;
    }
    if(USB->ISTR & USB_ISTR_WKUP) {
        USB->ISTR &= ~USB_ISTR_WKUP;
        /* Handle Wakeup */
        return;
    }
    if(USB->ISTR & USB_ISTR_SOF) {
        USB->ISTR &= ~USB_ISTR_SOF;
        /* Handle SOF */
        return;
    }
    if(USB->ISTR & USB_ISTR_ESOF) {
        USB->ISTR &= ~USB_ISTR_ESOF;
        /* Handle ESOF */
        return;
    }
    USB->ISTR = 0;
}