#include "usb_desc.h"
/************** Descriptor of device ****************/
uint8_t descDevice[USB_DESC_SIZE_DEVICE] = 
{  
    0x12,                       /* bLength */
    USB_DESC_TYPE_DEVICE,       /* bDescriptorType */
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
  0x09, 	                      /* bLength: Configuration Descriptor size */
  USB_DESC_TYPE_CONFIGURATION,  /* bDescriptorType: Configuration */
  USB_DESC_SIZE_CONFIGURATION,  /* wTotalLength: Bytes returned */
  0x00,
  0x01,         				        /* bNumInterfaces: 1 interface */
  0x01,        				          /* bConfigurationValue: Configuration value */
  0x00,         				        /* iConfiguration: Index of string descriptor describing the configuration */
  0xC0,         				        /* bmAttributes: bus powered */
  0x32,         				        /* MaxPower 100 mA: this current is used for detecting Vbus */
/************** Descriptor of interface ****************/
  0x09,         				        /* bLength: Interface Descriptor size */
  USB_DESC_TYPE_INTERFACE, 		  /* bDescriptorType: Interface descriptor type */
  0x00,         				        /* bInterfaceNumber: Number of Interface */
  0x00,         				        /* bAlternateSetting: Alternate setting */
  0x02,         				        /* bNumEndpoints */
  0x03,         				        /* bInterfaceClass: USB_HID */
  0x00,         				        /* bInterfaceSubClass : 1=BOOT, 0=no boot */
  0x00,         				        /* nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse */
  0,            				        /* iInterface: Index of string descriptor */
  /******************** Descriptor of USB_HID *************************/
  0x09,         				        /* bLength: USB_HID Descriptor size */
  USB_HID_DESCRIPTOR_TYPE,      /* bDescriptorType: USB_HID */ 
  0x01,         				        /* bUSB_HIDUSTOM_HID: USB_HID Class Spec release number */
  0x01,
  0x00,         				        /* bCountryCode: Hardware target country */
  0x01,         				        /* bNumDescriptors: Number of USB_HID class descriptors to follow */
  0x22,         				        /* bDescriptorType */
  USB_DESC_SIZE_HID_REPORT,		  /* wItemLength: Total length of Report descriptor */ 
  0x00,
  /******************** Descriptor of endpoint (IN) ********************/
  0x07,          				        /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT, 		  /* bDescriptorType: */
  USB_HID_EPIN_ADDR,     	      /* bEndpointAddress: Endpoint Address (IN) */
  0x03,          				        /* bmAttributes: Interrupt endpoint */
  USB_HID_EPIN_SIZE, 		        /* wMaxPacketSize: 2 Byte max */
  0x00,
  0x20,          				        /* bInterval: Polling Interval (20 ms) */
  /******************** Descriptor of endpoint (OUT) ********************/
  0x07,          				        /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,   	  /* bDescriptorType: */
  USB_HID_EPOUT_ADDR,  		      /* bEndpointAddress: Endpoint Address (OUT) */
  0x03, 						            /* bmAttributes: Interrupt endpoint */
  USB_HID_EPOUT_SIZE,    	      /* wMaxPacketSize: 2 Bytes max */
  0x00,
  0x20, 						            /* bInterval: Polling Interval (20 ms) */
};

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

uint8_t descHIDReport[USB_DESC_SIZE_HID_REPORT] = 
{
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