#include "usb.h"

/*
 ***********************************************************
 ********************** Variables **************************
 ***********************************************************
 */
const uint8_t descDevice[USB_DESC_SIZE_DEVICE] = 
{  
    0x12,                       /* bLength */
    USB_SETUP_DESC_DEVICE & 0xff,/* bDescriptorType */
    0x00,                       /* bcdUSB */  
    0x02,
    0x00,                       /* bDeviceClass */
    0x00,                       /* bDeviceSubClass */
    0x00,                       /* bDeviceProtocol */
    USB_MAX_EP0_SIZE,           /* bMaxPacketSize */
    LOBYTE(USB_VID),            /* idVendor */ 
    HIBYTE(USB_VID),            /* idVendor */
    LOBYTE(USB_PID),            /* idProduct */
    HIBYTE(USB_PID),            /* idProduct */
    0x00,                       /* bcdDevice rel. 2.00 */
    0x02,
    USB_IDX_MFC_STR,            /* Index of manufacturer  string */
    USB_IDX_PRODUCT_STR,        /* Index of product string */
    USB_IDX_SERIAL_STR,         /* Index of serial number string */
    USB_MAX_NUM_CONFIGURATION   /* bNumConfigurations */
};
/************** Descriptor of device qualifier ****************/
const uint8_t descDeviceQualifier[USB_DESC_SIZE_DEVICE_QUALIFIER] = 
{  
    USB_DESC_SIZE_DEVICE_QUALIFIER,/* bLength */
    0x0A,                       /* bDescriptorType */
    0x00,                       /* bcdUSB */  
    0x02,
    0x00,                       /* bDeviceClass */
    0x00,                       /* bDeviceSubClass */
    0x00,                       /* bDeviceProtocol */
    USB_MAX_EP0_SIZE,           /* bMaxPacketSize */
    USB_MAX_NUM_CONFIGURATION,  /* bNumConfigurations */
    0x0                         /* bReserve */ 
};
/************** Descriptor of configuration ****************/ 
const uint8_t descConfiguration[USB_DESC_SIZE_CONFIGURATION] =
{
  0x09,                           /* bLength: Configuration Descriptor size */
  USB_SETUP_DESC_CONFIGURATION & 0xff,  /* bDescriptorType: Configuration */
  USB_DESC_SIZE_CONFIGURATION,  /* wTotalLength: Bytes returned */
  0x00,
  0x01,                                 /* bNumInterfaces: 1 interface */
  0x01,                               /* bConfigurationValue: Configuration value */
  0x00,                                 /* iConfiguration: Index of string descriptor describing the configuration */
  0xC0,                                 /* bmAttributes: bus powered */
  0x32,                                 /* MaxPower 100 mA: this current is used for detecting Vbus */
/************** Descriptor of interface ****************/
  0x09,                                 /* bLength: Interface Descriptor size */
  USB_SETUP_DESC_INTERFACE & 0xff,         /* bDescriptorType: Interface descriptor type */
  0x00,                                 /* bInterfaceNumber: Number of Interface */
  0x00,                                 /* bAlternateSetting: Alternate setting */
  0x02,                                 /* bNumEndpoints */
  0x03,                                 /* bInterfaceClass: USB_HID */
  0x00,                                 /* bInterfaceSubClass : 1=BOOT, 0=no boot */
  0x00,                                 /* nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse */
  0,                                    /* iInterface: Index of string descriptor */
  /******************** Descriptor of USB_HID *************************/
  0x09,                                 /* bLength: USB_HID Descriptor size */
  USB_HID_DESCRIPTOR_TYPE,      /* bDescriptorType: USB_HID */ 
  0x01,                                 /* bUSB_HIDUSTOM_HID: USB_HID Class Spec release number */
  0x01,
  0x00,                                 /* bCountryCode: Hardware target country */
  0x01,                                 /* bNumDescriptors: Number of USB_HID class descriptors to follow */
  0x22,                                 /* bDescriptorType */
  USB_DESC_SIZE_HID_REPORT,       /* wItemLength: Total length of Report descriptor */ 
  0x00,
  /******************** Descriptor of endpoint (IN) ********************/
  0x07,                                 /* bLength: Endpoint Descriptor size */
  USB_SETUP_DESC_ENDPOINT & 0xff,          /* bDescriptorType: */
  USB_HID_EPIN_ADDR,              /* bEndpointAddress: Endpoint Address (IN) */
  0x03,                                 /* bmAttributes: Interrupt endpoint */
  USB_HID_EPIN_SIZE,                /* wMaxPacketSize: 2 Byte max */
  0x00,
  0x20,                                 /* bInterval: Polling Interval (20 ms) */
  /******************** Descriptor of endpoint (OUT) ********************/
  0x07,                                 /* bLength: Endpoint Descriptor size */
  USB_SETUP_DESC_ENDPOINT & 0xff,      /* bDescriptorType: */
  USB_HID_EPOUT_ADDR,             /* bEndpointAddress: Endpoint Address (OUT) */
  0x03,                                     /* bmAttributes: Interrupt endpoint */
  USB_HID_EPOUT_SIZE,             /* wMaxPacketSize: 2 Bytes max */
  0x00,
  0x20,                                     /* bInterval: Polling Interval (20 ms) */
};

const uint8_t descStringLangID[USB_STR_SIZE_LANGID] = 
{
    USB_STR_SIZE_LANGID,
    USB_SETUP_DESC_STRING & 0xff,
    LOBYTE(USB_LANGID_STRING),
    HIBYTE(USB_LANGID_STRING)
};

const uint8_t descStringProduct[USB_STR_SIZE_PRODUCT] = 
{
    USB_STR_SIZE_LANGID,
    USB_SETUP_DESC_STRING & 0xff,
    'S','T','M','3','2',' ','C','u','s','t','o','m',' ','H','I','D'
};

const uint8_t descStringMFC[USB_STR_SIZE_MFC] = 
{
    USB_STR_SIZE_MFC, 
    USB_SETUP_DESC_STRING & 0xff,
    'S','T','M','3','2',' ','D','e','v','i','c','e'
};
 
const uint8_t descStringSerialNumber[USB_STR_SIZE_SERIALNUMBER] = 
{
    USB_STR_SIZE_SERIALNUMBER,  
    USB_SETUP_DESC_STRING & 0xff,
    '0','0','0','0','0','0','0','0','0','0','1','A'
};

const uint8_t descStringConfig[USB_STR_SIZE_CONFIG] = 
{
    USB_STR_SIZE_CONFIG,  
    USB_SETUP_DESC_STRING & 0xff, 
    'C','u','s','t','o','m',' ','H','I','D',' ','C','o','n','f','i','g'
};

const uint8_t descStringInterface[USB_STR_SIZE_INTERFACE] = 
{
    USB_STR_SIZE_INTERFACE,  
    USB_SETUP_DESC_STRING & 0xff,
    'C','u','s','t','o','m',' ','H','I','D',' ','I','n','t','e','r','f','a','c','e'
};

const uint8_t descHIDReport[USB_DESC_SIZE_HID_REPORT] = 
{
        0x06, 0x00, 0xff,              // USAGE_PAGE (Vendor Defined Page 1)
    0x09, 0x01,                    // USAGE (Vendor Usage 1)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x26, 0xff, 0x00,              //   LOGICAL_MAXIMUM (255)
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x95, 0x40,                    //   REPORT_COUNT (64)
    0x09, 0x01,                    //   USAGE (Vendor Usage 1)
    0x81, 0x00,                    //   INPUT (Data,Ary,Abs)
    0x09, 0x01,                    //   USAGE (Vendor Usage 1)
    0x91, 0x00,                    //   OUTPUT (Data,Ary,Abs)
    0xc0                           // END_COLLECTION
  // 0x06, 0x00, 0xff,              /* USAGE_PAGE (Generic Desktop) */
  // 0x09, 0x01,                    /* USAGE (Vendor Usage 1) */
  // 0xa1, 0x01,                    /* COLLECTION (Application) */
  // 0x85, 0x01,                    /* REPORT_ID (1) */
  // 0x09, 0x01,                    /* USAGE (Vendor Usage 1) */
  // 0x15, 0x00,                    /* LOGICAL_MINIMUM (0) */
  // 0x25, 0x01,                    /* LOGICAL_MAXIMUM (1) */
  // 0x75, 0x08,                    /* REPORT_SIZE (8) */
  // 0x95, 0x01,                    /* REPORT_COUNT (1) */
  // 0xb1, 0x82,                    /* FEATURE (Data,Var,Abs,Vol) */
  // 0x85, 0x01,                    /* REPORT_ID (1) */
  // 0x09, 0x01,                    /* USAGE (Vendor Usage 1) */
  // 0x91, 0x82,                    /* OUTPUT (Data,Var,Abs,Vol) */
  // 0x85, 0x02,                    /* REPORT_ID (2) */
  // 0x09, 0x02,                    /* USAGE (Vendor Usage 2) */
  // 0x15, 0x00,                    /* LOGICAL_MINIMUM (0) */
  // 0x25, 0x01,                    /* LOGICAL_MAXIMUM (1) */
  // 0x75, 0x08,                    /* REPORT_SIZE (8) */
  // 0x95, 0x01,                    /* REPORT_COUNT (1) */
  // 0xb1, 0x82,                    /* FEATURE (Data,Var,Abs,Vol) */
  // 0x85, 0x02,                    /* REPORT_ID (2) */
  // 0x09, 0x02,                    /* USAGE (Vendor Usage 2) */
  // 0x91, 0x82,                    /* OUTPUT (Data,Var,Abs,Vol) */
  // 0x85, 0x03,                    /* REPORT_ID (3) */
  // 0x09, 0x03,                    /* USAGE (Vendor Usage 3) */
  // 0x15, 0x00,                    /* LOGICAL_MINIMUM (0) */
  // 0x26, 0xff, 0x00,              /* LOGICAL_MAXIMUM (255) */
  // 0x75, 0x08,                    /* REPORT_SIZE (8) */
  // 0x95, 0x01,                    /* REPORT_COUNT (N) */
  // 0xb1, 0x82,                    /* FEATURE (Data,Var,Abs,Vol) */
  // 0x85, 0x03,                    /* REPORT_ID (3) */
  // 0x09, 0x03,                    /* USAGE (Vendor Usage 3) */
  // 0x91, 0x82,                    /* OUTPUT (Data,Var,Abs,Vol) */
  // 0x85, 0x04,                    /* REPORT_ID (4) */
  // 0x09, 0x04,                    /* USAGE (Vendor Usage 4) */
  // 0x75, 0x08,                    /* REPORT_SIZE (8) */
  // 0x95, 0x04,                    /* REPORT_COUNT (N) */
  // 0x81, 0x82,                    /* INPUT (Data,Var,Abs,Vol) */
  // 0xc0                           /* END_COLLECTION */
};


uint8_t devAddress = 0;
USB_SETUP_PACKET SetupPacket;
USB_DESCRIPTORS descriptor;
uint8_t *bufferSetup[12];
/*
 ***********************************************************
 ***************** Prototype functoin **********************
 ***********************************************************
 */
void USBReset(void);
void USBRequest(USB_SETUP_PACKET *req, uint8_t *pdata);
void USBReadPMA(uint16_t *buff, uint16_t offset, uint16_t numBytes);
void USBWritePMA(uint16_t *buff, uint16_t offset, uint16_t numBytes);
void USBSetup(void);
/*
 ***********************************************************
 ****************** Private functoin ***********************
 ***********************************************************
 */
/*
 * Name: USBReset
 * Description: Reset USB device
 * Parametrs: none
 */
void USBReset(void){
    
    USB->ISTR = 0x0;

    USB->BTABLE = BTABLE_ADDRESS; /* Set a address table buffer in memory USB */
    
    USB->CNTR = USB_CNTR_RESETM | USB_CNTR_SUSPM | USB_CNTR_WKUPM | USB_CNTR_CTRM;
    
    /* Set a address buffer */
    USB_ADDR_RX(USB_EP0) = USB_EP0_RX;
    USB_ADDR_TX(USB_EP0) = USB_EP0_TX;
    USB_COUNT_TX(USB_EP0) = 0x40;
    USB_COUNT_RX(USB_EP0) = 0x8400;
 
    USB_ADDR_RX(USB_EP1) = USB_EP1_RX;
    USB_ADDR_TX(USB_EP1) = USB_EP1_TX;
    USB_COUNT_TX(USB_EP1) = 0x40;
    USB_COUNT_RX(USB_EP1) = 0x8400;

    USB_ADDR_RX(USB_EP2) = USB_EP2_RX;
    USB_ADDR_TX(USB_EP2) = USB_EP2_TX;
    USB_COUNT_TX(USB_EP2) = 0x40;
    USB_COUNT_RX(USB_EP2) = 0x8400;

    /* Endpoints 0; Type: CONTROL; RX: VALID; TX: NAK */
    USB->EP0R = USB_EP_CONTROL | USB_EP_RX_VALID | USB_EP_TX_NAK | USB_EP_AE_0;
    /* Endpoints 1; Type: BULK; RX: VALID; TX: NAK */
    USB->EP1R = USB_EP_BULK | USB_EP_RX_VALID | USB_EP_TX_NAK | USB_HID_EPIN_ADDR;
    /* Endpoints 2; Type: BULK; RX: NAK; TX: VALID */
    USB->EP2R = USB_EP_BULK | USB_EP_RX_NAK | USB_EP_TX_VALID | USB_HID_EPOUT_ADDR;

    USB->DADDR = USB_DADDR_EF;   /* Activation device */

    USB->ISTR &= ~USB_ISTR_RESET;
}
/*
 * Name: USBRequest
 * Description: Send zero length packet to host
 * Parametrs: req - structure SETUP packet
 *            pdata - buffer SETUP packet
 */
void USBRequest(USB_SETUP_PACKET *req, uint8_t *pdata){
    req->bmRequestType     = *pdata;
    req->bRequest          = *(pdata + 1);
    req->wValue.low        = *(pdata + 2);
    req->wValue.high       = *(pdata + 3);
    req->wIndex.low        = *(pdata + 4);
    req->wIndex.high       = *(pdata + 5);
    req->wLength.low       = *(pdata + 6);
    req->wLength.high      = *(pdata + 7);
}
/*
 * Name: USBReadPMA
 * Description: Read data of PMA
 * Parametrs: buff - buffer data
 *            offset - offset adress
 *            numBytes - number bytes for read
 */
void USBReadPMA(uint16_t *buff, uint16_t offset, uint16_t numBytes){
    uint32_t nBytes = (numBytes + 1) >> 1;
    uint32_t *addrRx = (uint32_t *)(offset * 2 + USB_PMAADDR);
    while(nBytes--)
        *buff++ = *addrRx++;
}
/*
 * Name: USBWritePMA
 * Description: Write data in PMA
 * Parametrs: buff - buffer data
 *            offset - offset adress
 *            numBytes - number bytes for write
 */
void USBWritePMA(uint16_t *buff, uint16_t offset, uint16_t numBytes){
    uint32_t nBytes = (numBytes + 1) >> 1;
    uint32_t *addrTx = (uint32_t *)(offset * 2 + USB_PMAADDR);
    while(nBytes--)
        *addrTx++ = *buff++;
}
/*
 * Name: USBSetup
 * Description: Hanbler SETUP packet
 * Parametrs: none
 */
void USBSetup(void){
    USB->ISTR &= ~USB_ISTR_CTR;
    USB->EP0R &= ~USB_EP_CTR_RX;
    USB->EP0R |= USB_EP_DTOG_TX;
    USBReadPMA((uint16_t *)bufferSetup, USB_EP0_RX, 8);
    USBRequest(&SetupPacket, (uint8_t *)bufferSetup);
    switch((SetupPacket.bmRequestType << 16) | (SetupPacket.bRequest << 8) | SetupPacket.wValue.high){
        case USB_SETUP_DESC_DEVICE:
            descriptor.buff = descDevice;
            descriptor.size = USB_DESC_SIZE_DEVICE;
            break;
        case USB_SETUP_DESC_DEVICE_QUALIFIER:
            descriptor.buff = descDeviceQualifier;
            descriptor.size = USB_DESC_SIZE_DEVICE_QUALIFIER;
            break;
        case USB_SETUP_DESC_CONFIGURATION:
            descriptor.buff = descConfiguration;
            descriptor.size = SetupPacket.wLength.low;
            break;
        case USB_SETUP_DESC_STRING:
            switch(SetupPacket.wValue.low){
                case USB_IDX_LANGID_STR:
                    descriptor.buff = descStringLangID;
                    descriptor.size = USB_STR_SIZE_LANGID;
                    break;
                case USB_IDX_MFC_STR:
                    descriptor.buff = descStringMFC;
                    descriptor.size = USB_STR_SIZE_MFC;
                    break;
                case USB_IDX_PRODUCT_STR:
                    descriptor.buff = descStringProduct;
                    descriptor.size = USB_STR_SIZE_PRODUCT;
                    break;
                case USB_IDX_SERIAL_STR:
                    descriptor.buff = descStringSerialNumber;
                    descriptor.size = USB_STR_SIZE_SERIALNUMBER;
                    break;
                case USB_IDX_CONFIG_STR:
                    descriptor.buff = descStringConfig;
                    descriptor.size = USB_STR_SIZE_CONFIG;
                    break;
                case USB_IDX_INTERFACE_STR:
                    descriptor.buff = descStringInterface;
                    descriptor.size = USB_STR_SIZE_INTERFACE;
                    break;
            }
        case USB_SETUP_SET_ADDRESS:
            devAddress = SetupPacket.wValue.low;
            descriptor.buff = 0;
            descriptor.size = 0;
        break;
        case USB_SETUP_SET_CONFIGURATION:
            descriptor.buff = 0;
            descriptor.size = 0;
        break;
        case USB_SETUP_CLASS_REQ:
            descriptor.buff = 0;
            descriptor.size = 0;
        break;
        case USB_DESC_HID_REPORT:
            descriptor.buff = descHIDReport;
            descriptor.size = USB_DESC_SIZE_HID_REPORT;
        break;
    }
 
    USBWritePMA((uint16_t *)descriptor.buff, USB_EP0_TX, descriptor.size);
    USB_COUNT_TX(USB_EP0) = descriptor.size;
    USB->EP0R = USB_EP_TX_VALID | USB_EP_CONTROL;
    while(!(USB->EP0R & USB_EP_CTR_TX)){}
    if(devAddress > 0 && SetupPacket.wLength.low == 0){
        USB->DADDR = devAddress | USB_DADDR_EF;
    }    
	USB->EP0R = USB_EP_CONTROL | USB_EP_RX_VALID;
}
/*
 ***********************************************************
 ******************* Public functoin ***********************
 ***********************************************************
 */
/*
 * Name: USBConfig
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
/*
 * Name: USBSendData
 * Description: Send on host
 * Parametrs: buff - buffer data for send on host
 */
void USBSendData(uint8_t *buff){
    USBWritePMA((uint16_t *)buff, USB_EP1_TX, sizeof(buff));
    USB_COUNT_TX(USB_EP1) = sizeof(buff);
    while(!(USB->EP1R & USB_EP_CTR_TX)){}
}
/*
 ***********************************************************
 ********************** Interrput **************************
 ***********************************************************
 */
void USB_LP_IRQHandler(void){
    uint32_t num;
	if(USB->ISTR & USB_ISTR_RESET){ 
    	USBReset();
	}
    if(USB->ISTR & USB_ISTR_SUSP){
        USB->CNTR |= USB_CNTR_FSUSP; /* Force Suspend */
        USB->CNTR |= USB_CNTR_LP_MODE; /* Low Power Mode */
    }
    if(USB->ISTR & USB_ISTR_WKUP){  
        USB->CNTR &= ~USB_CNTR_FSUSP;
    }
    while((USB->ISTR & USB_ISTR_CTR) != 0){
        num = USB->ISTR & USB_ISTR_EP_ID;
        if(num == USB_EP0){ /* Endpoint 0 (Control)*/
            if((USB->ISTR & USB_ISTR_DIR) != 0){
                if(USB->EP0R & USB_EP_SETUP){ /* SETUP */
                    USBSetup();
                }else{ /* OUT */

                }
            }else{ /* IN */
                USB->EP0R &= ~USB_EP_CTR_TX;
            }
        }else if(num == USB_EP1){ /* Endpoint 1 (IN)*/
            if((USB->ISTR & USB_ISTR_DIR) == 0){

            }
        }else if(num == USB_EP2){ /* Endpoint 2 (OUT)*/
            if((USB->ISTR & USB_ISTR_DIR) != 0){
                
            }
        }
    }
    USB->ISTR = 0x0;
}
