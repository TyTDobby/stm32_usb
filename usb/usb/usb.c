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

uint8_t debug1 = 0;

// #define EP_RX_STATUS(epr, status) { \
// 	register uint16_t valReg = USB->EPR[epr] & USB_EP_STAT_RX;\
// 	if(status & USB_EP_STAT_RX_0){\
// 		valReg ^= USB_EP_STAT_RX_0;\
// 	}\
// 	if(status & USB_EP_STAT_RX_1){\
// 		valReg ^= USB_EP_STAT_RX_1;\
// 	}\
// 	USB->EPR[epr] = valReg | USB_EP_CTR_RX | USB_EP_CTR_TX;\
// }/* EP_TX_STATUS */

// #define EP_CONTROL_RX_STATUS(epr, status) { \
// 	register uint16_t valReg = USB->EPR[epr] & USB_EP_STAT_RX;\
// 	if(valReg & USB_EP_STAT_RX_0){\
// 		valReg ^= USB_EP_STAT_RX_1;\
// 	}\
// 	if(valReg & USB_EP_STAT_RX_1){\
// 		valReg ^= USB_EP_STAT_RX_0;\
// 	}\
// 	USB->EPR[epr] = valReg | USB_EP_CONTROL;\
// }/* EP_CONTROL_RX_STATUS */

// #define EP_TX_STATUS(epr, status) { \
// 	register uint16_t valReg = USB->EPR[epr] & USB_EP_STAT_TX;\
// 	if(status & USB_EP_STAT_TX_0){\
// 		valReg ^= USB_EP_STAT_TX_0;\
// 	}\
// 	if(status & USB_EP_STAT_TX_1){\
// 		valReg ^= USB_EP_STAT_TX_1;\
// 	}\
// 	USB->EPR[epr] = valReg | USB_EP_CTR_RX | USB_EP_CTR_TX;\
// }/* EP_TX_STATUS */

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
 	0x01,		/* bUSB_HIDUSTOM_HID: USB_HID Class Spec release number */
 	0x01,
 	0x00,		/* bCountryCode: Hardware target country */
 	0x01,		/* bNumDescriptors: Number of USB_HID class descriptors to follow */
 	0x22,		/* bDescriptorType */
 	0x02,		/* wItemLength: Total length of Report descriptor */ 
 	0x00,
/*
 * Descriptor of endpoint (IN) 
 */
 	0x07,		/* bLength: Endpoint Descriptor size */
 	0x05,		/* bDescriptorType: */
 	0x81,		/* bEndpointAddress: Endpoint Address (IN) */
 	0x02,		/* bmAttributes: Bulk */
 	0x10,		/* wMaxPacketSize: 2 Byte max */
 	0x00,
 	0x20,		/* bInterval: Polling Interval (20 ms) */
/*
 * Descriptor of endpoint (OUT) 
 */
 	0x07,		/* bLength: Endpoint Descriptor size */
 	0x05,		/* bDescriptorType: */
 	0x01,		/* bEndpointAddress: Endpoint Address (OUT) */
 	0x02,		/* bmAttributes: Bulk */
 	0x10,		/* wMaxPacketSize: 2 Bytes max */
 	0x00,
 	0x20,		/* bInterval: Polling Interval (20 ms) */
};
uint8_t descStringLangID[] = 
{
	0x04,
	USB_STR_DESC_TYPE,
	LOBYTE(USB_LANGID_STRING),
	HIBYTE(USB_LANGID_STRING)
};

uint8_t descStringProduct[] = 
{
	0x12,
	USB_STR_DESC_TYPE,
	'S','T','M','3','2',' ','C','u','s','t','o','m',' ','H','I','D'
};

uint8_t descStringMFC[] = 
{
	0x0e, 
	USB_STR_DESC_TYPE,
	'S','T','M','3','2',' ','D','e','v','i','c','e'
};
 
uint8_t descStringSerialNumber[] = 
{
	0x0e,  
	USB_STR_DESC_TYPE,
	'0','0','0','0','0','0','0','0','0','0','1','A'
};

uint8_t descStringConfig[] = 
{
	0x13,  
	USB_STR_DESC_TYPE,
	'C','u','s','t','o','m',' ','H','I','D',' ','C','o','n','f','i','g'
};

uint8_t descStringInterface[] = 
{
	0x16,  
	USB_STR_DESC_TYPE,
	'C','u','s','t','o','m',' ','H','I','D',' ','I','n','t','e','r','f','a','c','e'
};
/* Prototype functoin */
void USBWriteEP(uint8_t number);
void USBReadEP(uint8_t *buffer, uint16_t len, uint8_t number);
void USBRequest(USBSetupPacket *req, uint8_t *pdata);
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

/* Private */
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
void USBReadEP(uint8_t *buffer, uint16_t len, uint8_t number){
    uint16_t nBytes = (len + 1) >> 1;
    uint32_t *addrRx = (uint32_t *)((uint16_t)EPBuffTable[number]->ADDR_RX * 2 + USB_PMA_ADDR);
    uint16_t *temp = (uint16_t *)buffer;
    while(nBytes--)
        *temp++ = *addrRx++;
}
void USBStatusTx(uint8_t numEp, uint16_t status)
{
    register uint16_t val = USB->EPR[numEp];
    USB->EPR[numEp] = (val ^ (status & USB_EP_STAT_TX)) & (USB_EP_MASK | USB_EP_STAT_TX);
}

void USBStatusRx(uint8_t numEp, uint16_t status)
{
    register uint16_t val = USB->EPR[numEp];
    USB->EPR[numEp] = (val ^ (status & USB_EP_STAT_RX)) & (USB_EP_MASK | USB_EP_STAT_RX);
}
void USBSendData(uint8_t *buffer, uint8_t len, uint8_t number){
	heap.buffTx = buffer;
	heap.cntTx = len;

	if(len > 0){
        USBWriteEP(number);
    }else{
        EPBuffTable[number]->COUNT_TX = 0;
    }
	USBStatusTx(number, USB_EP_TX_VALID);
	while(!(USB->EPR[number] & USB_EP_CTR_TX)){}
}
void USBRequest(USBSetupPacket *req, uint8_t *pdata){
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

	EPBuffTable[USB_EP0]->ADDR_TX = 0x80;
	EPBuffTable[USB_EP0]->ADDR_RX = 0x100;
	EPBuffTable[USB_EP0]->COUNT_RX = 0xbc00;

	USB->EPR[USB_EP0] = USB_EP_CONTROL | USB_EP_RX_VALID;

	USB->CNTR   = USB_CNTR_CTRM | USB_CNTR_RESETM | USB_CNTR_SUSPM;
    USB->ISTR   = 0x00;
    USB->BTABLE = 0x00;
    USB->DADDR  = USB_DADDR_EF;
}
void USBGetDescriptor(void){
	switch(SetupPacket.wValue.high){
		case USB_DEVICE_DESC_TYPE:
			USBSendData(descDevice, sizeof(descDevice), 0);
			break;
		case USB_DEVICE_QR_DESC_TYPE:
			USBSendData(descDeviceQualifier, sizeof(descDeviceQualifier), 0);
			break;
		case USB_CFG_DESC_TYPE:
			USBSendData(descConfiguration, SetupPacket.wLength.low, 0);
			break;
		case USB_STR_DESC_TYPE:
			switch(SetupPacket.wValue.low){
				case USB_IDX_LANGID_STR:
					USBSendData(descStringLangID, sizeof(descStringLangID), 0);
					break;
				case USB_IDX_MFC_STR:
					USBSendData(descStringMFC, sizeof(descStringMFC), 0);
					break;
				case USB_IDX_PRODUCT_STR:
					USBSendData(descStringProduct, sizeof(descStringProduct), 0);
					break;
				case USB_IDX_SERIAL_STR:
					USBSendData(descStringSerialNumber, sizeof(descStringSerialNumber), 0);
					break;
				case USB_IDX_CONFIG_STR:
					USBSendData(descStringConfig, sizeof(descStringConfig), 0);
					break;
				case USB_IDX_INTERFACE_STR:
					USBSendData(descStringInterface, sizeof(descStringInterface), 0);
					break;
			}
			break;
	}
}
void USBSetup(void){
	debug1++;
	switch(SetupPacket.bmRequestType){
		case 0x00:
			switch(SetupPacket.bRequest){
				case USB_REQUEST_SET_ADDRESS:
					heap.devAddress = SetupPacket.wValue.low;
					USBSendData(0, 0, 0);
					break;
				case USB_REQUEST_SET_CONFIGURATION:
					USBSendData(0, 0, 0);
					break;
			}
			break;
		case 0x21:
	
			break;
		case 0x80:
			if(SetupPacket.bRequest == USB_REQUEST_GET_DESCRIPTOR){
				USBGetDescriptor();
			}
			break;
		case 0x81:

			break;
	}
	if(heap.devAddress){
		// GPIOC->BSRR = GPIO_BSRR_BS13;
		USB->DADDR = USB_DADDR_EF | heap.devAddress;
		heap.devAddress = 0;
	}
}


void USBCtrHandler(void){
	uint8_t numEp = USB->ISTR & USB_ISTR_EP_ID;
	if(numEp == USB_EP0){ 
		if(USB->EPR[0] & USB_EP_CTR_RX){ 
			USBReadEP((uint8_t *)heap.buffSetup, 8, numEp);
			USBRequest(&SetupPacket, (uint8_t *)heap.buffSetup);
			if(USB->EPR[0] & USB_EP_SETUP){
				USBSetup();
			}
			USB->EPR[0] = USB_EP_CONTROL | USB_EP_STAT_RX_0;
			// EP_CONTROL_RX_STATUS(0, USB_EP_RX_VALID);
			if(heap.cntTx){
				USBSendData(heap.buffTx, heap.cntTx, 0);
			}
		}
		if(USB->EPR[0] & USB_EP_CTR_TX){
			
			if(heap.devAddress){
				USB->DADDR = USB_DADDR_EF | heap.devAddress;
				heap.devAddress = 0;
			}
			if(heap.cntTx){
				// USBSendData()
			}
			USBStatusTx(0, USB_EP_TX_VALID);
		}
	}
}
/* Interrupt */

void USB_LP_CAN1_RX0_IRQHandler()
{
    if (USB->ISTR & USB_ISTR_RESET) { /* Reset */
        USB->ISTR &= ~USB_ISTR_RESET;
        USBReset();
        return;
    }
    if (USB->ISTR & USB_ISTR_CTR) { /* CTR */
        USBCtrHandler();
        USB->ISTR &= ~USB_ISTR_CTR;
        return;
    }
    if (USB->ISTR & USB_ISTR_PMAOVR) {
        USB->ISTR &= ~USB_ISTR_PMAOVR;
        // Handle PMAOVR status
        return;
    }
    if (USB->ISTR & USB_ISTR_SUSP) {
        USB->ISTR &= ~USB_ISTR_SUSP;
        if (USB->DADDR & 0x7f) {
            USB->DADDR = 0;
            USB->CNTR &= ~USB_CNTR_SUSPM;
        }
        return;
    }
    if (USB->ISTR & USB_ISTR_ERR) {
        USB->ISTR &= ~USB_ISTR_ERR;
        // Handle Error
        return;
    }
    if (USB->ISTR & USB_ISTR_WKUP) {
        USB->ISTR &= ~USB_ISTR_WKUP;
        // Handle Wakeup
        return;
    }
    if (USB->ISTR & USB_ISTR_SOF) {
        USB->ISTR &= ~USB_ISTR_SOF;
        // Handle SOF
        return;
    }
    if (USB->ISTR & USB_ISTR_ESOF) {
        USB->ISTR &= ~USB_ISTR_ESOF;
        // Handle ESOF
        return;
    }
    USB->ISTR = 0;
}