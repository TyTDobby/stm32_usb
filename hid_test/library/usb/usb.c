#include "usb.h"
#include "usb_reg.h"
/* 
 ***********************************************************
 ********************** Variables **************************
 ***********************************************************
 */
uint8_t descDevice[USB_DESC_SIZE_DEVICE] = 
{  
    0x12,                       /* bLength */
    USB_DESC_DEVICE & 0xff,/* bDescriptorType */
    0x00,                       /* bcdUSB */  
    0x02,
    0x00,                       /* bDeviceClass */
    0x00,                       /* bDeviceSubClass */
    0x00,                       /* bDeviceProtocol */
    MAX_EP0_SIZE,               /* bMaxPacketSize */
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
uint8_t descDeviceQualifier[USB_DESC_SIZE_DEVICE_QUALIFIER] = 
{  
    USB_DESC_SIZE_DEVICE_QUALIFIER,/* bLength */
    0x06,                       /* bDescriptorType */
    0x00,                       /* bcdUSB */  
    0x02,
    0x00,                       /* bDeviceClass */
    0x00,                       /* bDeviceSubClass */
    0x00,                       /* bDeviceProtocol */
    MAX_EP0_SIZE,               /* bMaxPacketSize */
    USB_MAX_NUM_CONFIGURATION,  /* bNumConfigurations */
    0x0                         /* bReserve */ 
};
/************** Descriptor of configuration ****************/ 
uint8_t descConfiguration[USB_DESC_SIZE_CONFIGURATION] =
{
  0x09,                                 /* bLength: Configuration Descriptor size */
  USB_DESC_CONFIGURATION & 0xff,  /* bDescriptorType: Configuration */
  USB_DESC_SIZE_CONFIGURATION,          /* wTotalLength: Bytes returned */
  0x00,
  0x01,                                 /* bNumInterfaces: 1 interface */
  0x01,                                 /* bConfigurationValue: Configuration value */
  0x00,                                 /* iConfiguration: Index of string descriptor describing the configuration */
  0xC0,                                 /* bmAttributes: bus powered */
  0x32,                                 /* MaxPower 100 mA: this current is used for detecting Vbus */
/************** Descriptor of interface ****************/
  0x09,                                 /* bLength: Interface Descriptor size */
  USB_DESC_INTERFACE & 0xff,         /* bDescriptorType: Interface descriptor type */
  0x00,                                 /* bInterfaceNumber: Number of Interface */
  0x00,                                 /* bAlternateSetting: Alternate setting */
  0x01,                                 /* bNumEndpoints */
  0x03,                                 /* bInterfaceClass: USB_HID */
  0x00,                                 /* bInterfaceSubClass : 1=BOOT, 0=no boot */
  0x00,                                 /* nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse */
  USB_IDX_INTERFACE_STR,                /* iInterface: Index of string descriptor */
  /******************** Descriptor of USB_HID *************************/
  0x09,                                 /* bLength: USB_HID Descriptor size */
  USB_HID_DESCRIPTOR_TYPE,              /* bDescriptorType: USB_HID */ 
  0x01,                                 /* bUSB_HIDUSTOM_HID: USB_HID Class Spec release number */
  0x01,
  0x00,                                 /* bCountryCode: Hardware target country */
  0x01,                                 /* bNumDescriptors: Number of USB_HID class descriptors to follow */
  0x22,                                 /* bDescriptorType */
  USB_DESC_SIZE_HID_REPORT,             /* wItemLength: Total length of Report descriptor */ 
  0x00,
  /******************** Descriptor of endpoint (IN) ********************/
  0x07,                                 /* bLength: Endpoint Descriptor size */
  USB_DESC_ENDPOINT & 0xff,       /* bDescriptorType: */
  USB_HID_EPIN_ADDR,                    /* bEndpointAddress: Endpoint Address (IN) */
  0x03,                                 /* bmAttributes: Interrupt endpoint */
  USB_HID_EPIN_SIZE,                    /* wMaxPacketSize: 2 Byte max */
  0x00,
  0x20,                                 /* bInterval: Polling Interval (20 ms) */
  /******************** Descriptor of endpoint (OUT) ********************/
  0x07,                                 /* bLength: Endpoint Descriptor size */
  USB_DESC_ENDPOINT & 0xff,       /* bDescriptorType: */
  USB_HID_EPOUT_ADDR,                   /* bEndpointAddress: Endpoint Address (OUT) */
  0x03,                                 /* bmAttributes: Interrupt endpoint */
  USB_HID_EPOUT_SIZE,                   /* wMaxPacketSize: 2 Bytes max */
  0x00,
  0x20,                                 /* bInterval: Polling Interval (20 ms) */
};

uint8_t descStringLangID[USB_STR_SIZE_LANGID] = 
{
    USB_STR_SIZE_LANGID,
    USB_DESC_STRING & 0xff,
    LOBYTE(USB_LANGID_STRING),
    HIBYTE(USB_LANGID_STRING)
};

uint8_t descStringProduct[USB_STR_SIZE_PRODUCT] = 
{
    USB_STR_SIZE_LANGID,
    USB_DESC_STRING & 0xff,
    'S','T','M','3','2',' ','C','u','s','t','o','m',' ','H','I','D'
};

uint8_t descStringMFC[USB_STR_SIZE_MFC] = 
{
    USB_STR_SIZE_MFC, 
    USB_DESC_STRING & 0xff,
    'S','T','M','3','2',' ','D','e','v','i','c','e'
};
 
uint8_t descStringSerialNumber[USB_STR_SIZE_SERIALNUMBER] = 
{
    USB_STR_SIZE_SERIALNUMBER,  
    USB_DESC_STRING & 0xff,
    '0','0','0','0','0','0','0','0','0','0','1','A'
};

uint8_t descStringConfig[USB_STR_SIZE_CONFIG] = 
{
    USB_STR_SIZE_CONFIG,  
    USB_DESC_STRING & 0xff, 
    'C','u','s','t','o','m',' ','H','I','D',' ','C','o','n','f','i','g'
};

uint8_t descStringInterface[USB_STR_SIZE_INTERFACE] = 
{
    USB_STR_SIZE_INTERFACE,  
    USB_DESC_STRING & 0xff,
    'C','u','s','t','o','m',' ','H','I','D',' ','I','n','t','e','r','f','a','c','e'
};

uint8_t descHIDReport[USB_DESC_SIZE_HID_REPORT] = 
{
    //     0x06, 0x00, 0xff,              // USAGE_PAGE (Vendor Defined Page 1)
    // 0x09, 0x01,                    // USAGE (Vendor Usage 1)
    // 0xa1, 0x01,                    // COLLECTION (Application)
    // 0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    // 0x26, 0xff, 0x00,              //   LOGICAL_MAXIMUM (255)
    // 0x75, 0x08,                    //   REPORT_SIZE (8)
    // 0x95, 0x40,                    //   REPORT_COUNT (64)
    // 0x09, 0x01,                    //   USAGE (Vendor Usage 1)
    // 0x81, 0x00,                    //   INPUT (Data,Ary,Abs)
    // 0x09, 0x01,                    //   USAGE (Vendor Usage 1)
    // 0x91, 0x00,                    //   OUTPUT (Data,Ary,Abs)
    // 0xc0                           // END_COLLECTION
  0x06, 0x00, 0xff,              /* USAGE_PAGE (Generic Desktop) */
  0x09, 0x01,                    /* USAGE (Vendor Usage 1) */
  0xa1, 0x01,                    /* COLLECTION (Application) */
  0x85, 0x01,                    /* REPORT_ID (1) */
  0x09, 0x01,                    /* USAGE (Vendor Usage 1) */
  0x15, 0x00,                    /* LOGICAL_MINIMUM (0) */
  0x25, 0x01,                    /* LOGICAL_MAXIMUM (1) */
  0x75, 0x08,                    /* REPORT_SIZE (8) */
  0x95, 0x01,                    /* REPORT_COUNT (1) */
  0xb1, 0x82,                    /* FEATURE (Data,Var,Abs,Vol) */
  0x85, 0x01,                    /* REPORT_ID (1) */
  0x09, 0x01,                    /* USAGE (Vendor Usage 1) */
  0x91, 0x82,                    /* OUTPUT (Data,Var,Abs,Vol) */
  0x85, 0x02,                    /* REPORT_ID (2) */
  0x09, 0x02,                    /* USAGE (Vendor Usage 2) */
  0x15, 0x00,                    /* LOGICAL_MINIMUM (0) */
  0x25, 0x01,                    /* LOGICAL_MAXIMUM (1) */
  0x75, 0x08,                    /* REPORT_SIZE (8) */
  0x95, 0x01,                    /* REPORT_COUNT (1) */
  0xb1, 0x82,                    /* FEATURE (Data,Var,Abs,Vol) */
  0x85, 0x02,                    /* REPORT_ID (2) */
  0x09, 0x02,                    /* USAGE (Vendor Usage 2) */
  0x91, 0x82,                    /* OUTPUT (Data,Var,Abs,Vol) */
  0x85, 0x03,                    /* REPORT_ID (3) */
  0x09, 0x03,                    /* USAGE (Vendor Usage 3) */
  0x15, 0x00,                    /* LOGICAL_MINIMUM (0) */
  0x26, 0xff, 0x00,              /* LOGICAL_MAXIMUM (255) */
  0x75, 0x08,                    /* REPORT_SIZE (8) */
  0x95, 0x01,                    /* REPORT_COUNT (N) */
  0xb1, 0x82,                    /* FEATURE (Data,Var,Abs,Vol) */
  0x85, 0x03,                    /* REPORT_ID (3) */
  0x09, 0x03,                    /* USAGE (Vendor Usage 3) */
  0x91, 0x82,                    /* OUTPUT (Data,Var,Abs,Vol) */
  0x85, 0x04,                    /* REPORT_ID (4) */
  0x09, 0x04,                    /* USAGE (Vendor Usage 4) */
  0x75, 0x08,                    /* REPORT_SIZE (8) */
  0x95, 0x04,                    /* REPORT_COUNT (N) */
  0x81, 0x82,                    /* INPUT (Data,Var,Abs,Vol) */
  0xc0                           /* END_COLLECTION */
};

uint16_t cntBytes = 0;
uint8_t devAddress = 0;
USB_SETUP_PACKET SetupPacket;
HEAP heap;
uint8_t *bufferSetup[12];

uint16_t over = 0;

/*
 ***********************************************************
 ***************** Prototype functoin **********************
 ***********************************************************
 */
void USBReset(void);
void USBRequest(USB_SETUP_PACKET *req, uint8_t *pdata);
void USBReadPMA(uint8_t *buff, uint16_t offset, uint16_t numBytes);
void USBWritePMA(uint16_t *buff, uint16_t offset, uint16_t numBytes);
void USBDataInEP0(void);
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
 * Returns: none
 */
void USBReset(void){
    
    ISTR &= ~ISTR_RESET;

    BTABLE = BTABLE_ADDRESS; /* Set a address table buffer in memory USB */
    
    CNTR = CNTR_RESETM | CNTR_CTRM;
    
    /* Set a address buffer */
    EP_ADDR_TX(EP0) = EP0_TX; 
    EP_ADDR_RX(EP0) = EP0_RX;
    EP_COUNT_RX(EP0) = 0xbc00;

    EPxREG(EP0) = EP_CONTROL;
    EPxREG(EP0) ^= 0xB0A0; /* RX: valid TX: nak */
    
    DADDR = 0x80;   /* Activation device */
}
/*
 * Name: USBRequest
 * Description: Send zero length packet to host
 * Parametrs: req - structure SETUP packet
 *            pdata - buffer SETUP packet
 * Returns: none
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
 * Returns: none
 */
void USBReadPMA(uint8_t *buff, uint16_t offset, uint16_t numBytes){
    uint32_t nBytes = (numBytes + 1) >> 1;
    uint32_t *addrRx = (uint32_t *)(offset * 2 + USB_PMA_ADDR);
    uint16_t *temp = (uint16_t *)buff;
    while(nBytes--)
        *temp++ = *addrRx++;
}
/* 
 * Name: USBWritePMA
 * Description: Write data in PMA
 * Parametrs: buff - buffer data
 *            offset - offset adress
 *            numBytes - number bytes for write
 * Returns: none
 */
void USBWritePMA(uint16_t *buff, uint16_t offset, uint16_t numBytes){
    uint32_t nBytes = (numBytes + 1) >> 1;
    uint32_t *addrTx = (uint32_t *)(offset * 2 + USB_PMA_ADDR);
    // uint32_t *temp = (uint32_t *)(offset * 2 + USB_PMA_ADDR);
    while(nBytes--)
        *addrTx++ = *buff++;
} 

void USBDataInEP0(void){
    uint32_t cnt = 0;
    if(heap.size > MAX_EP0_SIZE){
        cnt = MAX_EP0_SIZE;
        over = 1;
    }else{
        cnt = heap.size;
        over = 0;
    }

    USBWritePMA((uint16_t *)heap.buff, EP0_TX, cnt);
    EP_COUNT_TX(EP0) = cnt;
    EP_TX_STATUS(0, EP_TX_VALID);
    while(!(EPxREG(EP0) & EP_CTR_TX)){}

    // heap.buff += cnt;
    // heap.size -= cnt;    
}
/*
 * Name: USBSetup
 * Description: Hanbler SETUP packet
 * Parametrs: none
 * Returns: none
 */ 
void USBSetup(void){
    // ISTR &= ~ISTR_CTR;
    // EPxREG(EP0) &= ~EP_CTR_RX;
    // EPxREG(EP0) |= EP_DTOG_TX;
    USBReadPMA((uint8_t *)bufferSetup, EP0_RX, 8);
    USBRequest(&SetupPacket, (uint8_t *)bufferSetup);
    switch((SetupPacket.bmRequestType << 16) | (SetupPacket.bRequest << 8) | SetupPacket.wValue.high){
        case USB_DESC_DEVICE:
            heap.buff = descDevice;
            heap.size = USB_DESC_SIZE_DEVICE;
            break;
        case USB_DESC_DEVICE_QUALIFIER:
            heap.buff = descDeviceQualifier;
            heap.size = USB_DESC_SIZE_DEVICE_QUALIFIER;
            break;
        case USB_DESC_CONFIGURATION:
            heap.buff = descConfiguration;
            heap.size = SetupPacket.wLength.low;
            break;
        case USB_DESC_STRING:
            switch(SetupPacket.wValue.low){
                case USB_IDX_LANGID_STR:
                    heap.buff = descStringLangID;
                    heap.size = USB_STR_SIZE_LANGID;
                    break;
                case USB_IDX_MFC_STR:
                    heap.buff = descStringMFC;
                    heap.size = USB_STR_SIZE_MFC;
                    break;
                case USB_IDX_PRODUCT_STR:
                    heap.buff = descStringProduct;
                    heap.size = USB_STR_SIZE_PRODUCT;
                    break;
                case USB_IDX_SERIAL_STR:
                    heap.buff = descStringSerialNumber;
                    heap.size = USB_STR_SIZE_SERIALNUMBER;
                    break;
                case USB_IDX_CONFIG_STR:
                    heap.buff = descStringConfig;
                    heap.size = USB_STR_SIZE_CONFIG;
                    break;
                case USB_IDX_INTERFACE_STR:
                    heap.buff = descStringInterface;
                    heap.size = USB_STR_SIZE_INTERFACE;
                    break;
            }
        case USB_SET_ADDRESS:
            devAddress = SetupPacket.wValue.low;
            heap.buff = 0;
            heap.size = 0;
            break;
        case USB_SET_CONFIGURATION:
            heap.buff = 0;
            heap.size = 0;
            break;
        case USB_CLASS_REQ:
            heap.buff = 0;
            heap.size = 0;
            break;
        case USB_DESC_HID_REPORT:
            heap.buff = descHIDReport;
            heap.size = USB_DESC_SIZE_HID_REPORT;
            break;
    }

    USBDataInEP0();

    // if(devAddress > 0 && SetupPacket.wLength.low == 0){
    //     DADDR = devAddress | DADDR_EF;
    // }
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
 * Returns: none
 */
void USBConfig(void){
   

	CNTR = CNTR_FRES;/* CNTR_FRES = 1 */
     
    CNTR = 0; /* CNTR_FRES = 0 */

	CNTR |= CNTR_PDWN; 

	/* Reset driver */
	CNTR = 0x0;

    /* Reset registr flag interrput */
	ISTR = 0x0;

    /* Allow interrput */
    //CNTR |= USB_CNTR_RESETM | USB_CNTR_SUSPM | USB_CNTR_WKUPM | USB_CNTR_SOFM | USB_CNTR_ESOFM | USB_CNTR_CTRM | USB_CNTR_ERRM | USB_CNTR_PMAOVRM;
	CNTR = CNTR_RESETM | CNTR_SUSPM | CNTR_WKUPM | CNTR_CTRM;

   	/* Activation interrput */
	NVIC_EnableIRQ(USBWakeUp_IRQn);
	// NVIC_EnableIRQ(USB_HP_CAN1_TX_IRQn);
	NVIC_EnableIRQ(USB_LP_CAN1_RX0_IRQn);

}
/*
 * Name: USBSendData
 * Description: Send on host
 * Parametrs: buff - buffer data for send on host
 * Returns: none
 */
void USBSendData(uint8_t *buff){
    // USBWritePMA((uint16_t *)buff, USB_EP1_TX, sizeof(buff));
    // USB_COUNT_TX(USB_EP1) = sizeof(buff);
    // while(!(EP1R & USB_EP_CTR_TX)){}
}
/*
 ***********************************************************
 ********************** Interrput **************************
 ***********************************************************
 */
void USB_LP_CAN1_RX0_IRQHandler(void){
    uint32_t num;
	if(ISTR & ISTR_RESET){ 
        USBConfig();
    	USBReset();
	}
    if(ISTR & ISTR_SUSP){ 
        CNTR |= CNTR_FSUSP; /* Force Suspend */
        CNTR |= CNTR_LPMODE; /* Low Power Mode */
    }
    if(ISTR & ISTR_WKUP){  
        CNTR &= ~CNTR_FSUSP;
    }
    if(ISTR & ISTR_CTR){
        num = ISTR & ISTR_EP_ID;
        if(num == EP0){ /* Endpoint 0 (Control)*/
            if((ISTR & USB_ISTR_DIR) == 0){ /* IN */

                EPxREG(EP0) &= ~EP_CTR_TX;

                if(over == 1){
                    heap.size = EP_COUNT_TX(EP0) & EP_COUNT_MASK;
                    heap.buff += heap.size;

                    USBDataInEP0();
                }
                // EP_TX_STATUS(EP0, EP_TX_VALID); 
                // EPxREG(EP0) |= EP_CONTROL;

            }else{
                if((EPxREG(EP0) & EP_SETUP) != 0){ /* SETUP */

                    USBSetup();
                    EP_RX_STATUS(EP0, EP_RX_VALID); 
                    // EPxREG(EP0) |= EP_CONTROL;

                }else if ((EPxREG(EP0) & EP_CTR_RX) != 0){ /* OUT */

                    EPxREG(EP0) &= ~EP_CTR_RX;

                    heap.size = EP_COUNT_TX(EP0) & EP_COUNT_MASK;

                    if(heap.size != 0)
                        USBReadPMA((uint8_t *)heap.buff, EP0_RX, heap.size);

                    EP_RX_STATUS(EP0, EP_RX_VALID); 
                    EPxREG(EP0) |= EP_CONTROL;   

                } 
            }
        }else if(num == EP1){ /* Endpoint 1 (IN)*/
            if((ISTR & ISTR_DIR) == 0){

            }
        }else if(num == EP2){ /* Endpoint 2 (OUT)*/
            if((ISTR & ISTR_DIR) != 0){
                
            }
        }

    }
    ISTR = 0x0;
}
