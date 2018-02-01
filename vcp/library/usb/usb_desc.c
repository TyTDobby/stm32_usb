#include "usb_desc.h"
/************** Descriptor of device ****************/
uint8_t descDevice[USB_DESC_SIZE_DEVICE] = 
{  
    0x12,                       /* bLength */
    USB_DESC_TYPE_DEVICE,       /* bDescriptorType */
    0x00,                       /* bcdUSB */  
    0x02,
    USB_CLASS,                  /* bDeviceClass */
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
uint8_t descDeviceQualifier[USB_DESC_SIZE_DEVICE_QUALIFIER] = 
{  
    0x0A,                       /* bLength */
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
uint8_t descConfiguration[USB_DESC_SIZE_CONFIGURATION] =
{
/************** Descriptor of configuration ****************/ 
  0x09,                             /* bLength: Configuration Descriptor size */
  USB_DESC_TYPE_CONFIGURATION,      /* bDescriptorType: Configuration */
  USB_DESC_SIZE_CONFIGURATION,      /* wTotalLength:no of returned bytes */
  0x00,
  0x02,   /* bNumInterfaces: 2 interface */
  0x01,   /* bConfigurationValue: Configuration value */
  0x00,   /* iConfiguration: Index of string descriptor describing the configuration */
  0xC0,   /* bmAttributes: self powered */
  0x32,   /* MaxPower 0 mA */

/************** Interface Descriptor ****************/   

  0x09,   /* bLength: Interface Descriptor size */
  USB_DESC_TYPE_INTERFACE,  /* bDescriptorType: Interface */
  /* Interface descriptor type */
  0x00,   /* bInterfaceNumber: Number of Interface */
  0x00,   /* bAlternateSetting: Alternate setting */
  0x01,   /* bNumEndpoints: One endpoints used */
  0x02,   /* bInterfaceClass: Communication Interface Class */
  0x02,   /* bInterfaceSubClass: Abstract Control Model */
  0x01,   /* bInterfaceProtocol: Common AT commands */
  0x00,   /* iInterface: */

/************** Header Functional Descriptor ****************/   

  0x05,   /* bLength: Endpoint Descriptor size */
  0x24,   /* bDescriptorType: CS_INTERFACE */
  0x00,   /* bDescriptorSubtype: Header Func Desc */
  0x10,   /* bcdCDC: spec release number */
  0x01,

/************** Call Management Functional Descriptor ****************/   

  0x05,   /* bFunctionLength */
  0x24,   /* bDescriptorType: CS_INTERFACE */
  0x01,   /* bDescriptorSubtype: Call Management Func Desc */
  0x00,   /* bmCapabilities: D0+D1 */
  0x01,   /* bDataInterface: 1 */

/************** ACM Functional Descriptor ****************/   

  0x04,   /* bFunctionLength */
  0x24,   /* bDescriptorType: CS_INTERFACE */
  0x02,   /* bDescriptorSubtype: Abstract Control Management desc */
  0x02,   /* bmCapabilities */

/************** Union Functional Descriptor ****************/ 

  0x05,   /* bFunctionLength */
  0x24,   /* bDescriptorType: CS_INTERFACE */
  0x06,   /* bDescriptorSubtype: Union func desc */
  0x00,   /* bMasterInterface: Communication class interface */
  0x01,   /* bSlaveInterface0: Data Class Interface */

/************** Endpoint 2 Descriptor ****************/ 
 
  0x07,                           /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,         /* bDescriptorType: Endpoint */
  CDC_CMD_EP,                     /* bEndpointAddress */
  0x03,                           /* bmAttributes: Interrupt */
  LOBYTE(USB_VCP_CMD_PACKET_SIZE),/* wMaxPacketSize: */
  HIBYTE(USB_VCP_CMD_PACKET_SIZE),
  0x10,                           /* bInterval: */ 

/************** Data class interface descriptor ****************/ 

  0x09,   /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_INTERFACE,  /* bDescriptorType: */
  0x01,   /* bInterfaceNumber: Number of Interface */
  0x00,   /* bAlternateSetting: Alternate setting */
  0x02,   /* bNumEndpoints: Two endpoints used */
  0x0A,   /* bInterfaceClass: CDC */
  0x00,   /* bInterfaceSubClass: */
  0x00,   /* bInterfaceProtocol: */
  0x00,   /* iInterface: */

/************** Endpoint OUT Descriptor ****************/ 

  0x07,                                 /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,               /* bDescriptorType: Endpoint */
  CDC_OUT_EP,                           /* bEndpointAddress */
  0x02,                                 /* bmAttributes: Bulk */
  LOBYTE(USB_VCP_DATA_HS_MAX_PACKET_SIZE),  /* wMaxPacketSize: */
  HIBYTE(USB_VCP_DATA_HS_MAX_PACKET_SIZE),
  0x00,                                 /* bInterval: ignore for Bulk transfer */

/************** Endpoint IN Descriptor ****************/ 

  0x07,                                 /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,               /* bDescriptorType: Endpoint */
  CDC_IN_EP,                            /* bEndpointAddress */
  0x02,                                 /* bmAttributes: Bulk */
  LOBYTE(USB_VCP_DATA_HS_MAX_PACKET_SIZE),  /* wMaxPacketSize: */
  HIBYTE(USB_VCP_DATA_HS_MAX_PACKET_SIZE),
  0x00                                  /* bInterval: ignore for Bulk transfer */
} ;

uint8_t descStringLangID[USB_STR_SIZE_LANGID] = 
{
	USB_STR_SIZE_LANGID,
	USB_DESC_TYPE_STRING,
	LOBYTE(USB_LANGID_STRING),
	HIBYTE(USB_LANGID_STRING)
};

uint8_t descStringProduct[USB_STR_SIZE_PRODUCT] = 
{
	USB_STR_SIZE_LANGID,
	USB_DESC_TYPE_STRING,
	'S','T','M','3','2',' ','C','u','s','t','o','m',' ','H','I','D'
};

uint8_t descStringMFC[USB_STR_SIZE_MFC] = 
{
	USB_STR_SIZE_MFC, 
	USB_DESC_TYPE_STRING,
	'S','T','M','3','2',' ','D','e','v','i','c','e'
};
 
uint8_t descStringSerialNumber[USB_STR_SIZE_SERIALNUMBER] = 
{
	USB_STR_SIZE_SERIALNUMBER,  
	USB_DESC_TYPE_STRING,
	'0','0','0','0','0','0','0','0','0','0','1','A'
};

uint8_t descStringConfig[USB_STR_SIZE_CONFIG] = 
{
	USB_STR_SIZE_CONFIG,  
	USB_DESC_TYPE_STRING,
	'C','u','s','t','o','m',' ','H','I','D',' ','C','o','n','f','i','g'
};

uint8_t descStringInterface[USB_STR_SIZE_INTERFACE] = 
{
	USB_STR_SIZE_INTERFACE,  
	USB_DESC_TYPE_STRING,
	'C','u','s','t','o','m',' ','H','I','D',' ','I','n','t','e','r','f','a','c','e'
};

// uint8_t descHIDReport[USB_DESC_SIZE_HID_REPORT] = 
// {
// 	0x00,  
// 	0xc0
// };

// uint8_t descHIDReport[USB_DESC_SIZE_HID_REPORT] = 
// {
//   0x06, 0x00, 0xff,              /* USAGE_PAGE (Generic Desktop) */
//   0x09, 0x01,                    /* USAGE (Vendor Usage 1) */
//   0xa1, 0x01,                    /* COLLECTION (Application) */
//   0x85, 0x01,                    /* REPORT_ID (1) */
//   0x09, 0x01,                    /* USAGE (Vendor Usage 1) */
//   0x15, 0x00,                    /* LOGICAL_MINIMUM (0) */
//   0x25, 0x01,                    /* LOGICAL_MAXIMUM (1) */
//   0x75, 0x08,                    /* REPORT_SIZE (8) */
//   0x95, 0x01,                    /* REPORT_COUNT (1) */
//   0xb1, 0x82,                    /* FEATURE (Data,Var,Abs,Vol) */
//   0x85, 0x01,                    /* REPORT_ID (1) */
//   0x09, 0x01,                    /* USAGE (Vendor Usage 1) */
//   0x91, 0x82,                    /* OUTPUT (Data,Var,Abs,Vol) */
//   0x85, 0x02,                    /* REPORT_ID (2) */
//   0x09, 0x02,                    /* USAGE (Vendor Usage 2) */
//   0x15, 0x00,                    /* LOGICAL_MINIMUM (0) */
//   0x25, 0x01,                    /* LOGICAL_MAXIMUM (1) */
//   0x75, 0x08,                    /* REPORT_SIZE (8) */
//   0x95, 0x01,                    /* REPORT_COUNT (1) */
//   0xb1, 0x82,                    /* FEATURE (Data,Var,Abs,Vol) */
//   0x85, 0x02,                    /* REPORT_ID (2) */
//   0x09, 0x02,                    /* USAGE (Vendor Usage 2) */
//   0x91, 0x82,                    /* OUTPUT (Data,Var,Abs,Vol) */
//   0x85, 0x03,                    /* REPORT_ID (3) */
//   0x09, 0x03,                    /* USAGE (Vendor Usage 3) */
//   0x15, 0x00,                    /* LOGICAL_MINIMUM (0) */
//   0x26, 0xff, 0x00,              /* LOGICAL_MAXIMUM (255) */
//   0x75, 0x08,                    /* REPORT_SIZE (8) */
//   0x95, 0x01,                    /* REPORT_COUNT (N) */
//   0xb1, 0x82,                    /* FEATURE (Data,Var,Abs,Vol) */
//   0x85, 0x03,                    /* REPORT_ID (3) */
//   0x09, 0x03,                    /* USAGE (Vendor Usage 3) */
//   0x91, 0x82,                    /* OUTPUT (Data,Var,Abs,Vol) */
//   0x85, 0x04,                    /* REPORT_ID (4) */
//   0x09, 0x04,                    /* USAGE (Vendor Usage 4) */
//   0x75, 0x08,                    /* REPORT_SIZE (8) */
//   0x95, 0x04,                    /* REPORT_COUNT (N) */
//   0x81, 0x82,                    /* INPUT (Data,Var,Abs,Vol) */
//   0xc0                           /* END_COLLECTION */
// };