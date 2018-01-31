#ifndef USB_DESC_H
#define USB_DESC_H

#include "../cmsis/inc/stm32f103xb.h"

#define LOBYTE(x)  ((uint8_t)(x & 0x00FF))
#define HIBYTE(x)  ((uint8_t)((x & 0xFF00) >> 8))

#define  USB_VID     					1155
#define  USB_LANGID_STRING    			1033
#define  USB_MANUFACTURER_STRING        "TEst"
#define  USB_PID     				    22352
#define  USB_PRODUCT_STRING_FS          "STM32 Custom HID"
#define  USB_SERIALNUMBER_STRING_FS     "00000000001A"
#define  USB_CONFIGURATION_STRING_FS    "Custom HID Config"
#define  USB_INTERFACE_STRING_FS        "Custom HID Interface"

#define  USB_MAX_EP0_SIZE                              0x40

#define  USB_DESC_TYPE_DEVICE                          0x01
#define  USB_DESC_TYPE_CONFIGURATION                   0x02
#define  USB_DESC_TYPE_STRING                          0x03
#define  USB_DESC_TYPE_INTERFACE                       0x04
#define  USB_DESC_TYPE_ENDPOINT                        0x05
#define  USB_DESC_TYPE_DEVICE_QUALIFIER                0x06
#define  USB_DESC_TYPE_OTHER_SPEED_CONFIGURATION       0x07

#define  USB_DESC_SIZE_DEVICE                		   0x12
#define  USB_DESC_SIZE_DEVICE_QUALIFIER                0x0A
#define  USB_DESC_SIZE_CONFIGURATION                   0x29


#define  USB_STR_SIZE_LANGID                   		   0x04
#define  USB_STR_SIZE_PRODUCT                  		   0x12
#define  USB_STR_SIZE_MFC							   0x0e
#define  USB_STR_SIZE_SERIALNUMBER 					   0x0e
#define  USB_STR_SIZE_CONFIG 	     				   0x13
#define  USB_STR_SIZE_INTERFACE 					   0x16

#define  USB_IDX_LANGID_STR                            0x00 
#define  USB_IDX_MFC_STR                               0x01 
#define  USB_IDX_PRODUCT_STR                           0x02
#define  USB_IDX_SERIAL_STR                            0x03 
#define  USB_IDX_CONFIG_STR                            0x04 
#define  USB_IDX_INTERFACE_STR                         0x05 

#define  USB_MAX_NUM_CONFIGURATION     				   0x01

/* HID */

#define USB_DESC_SIZE_HID_REPORT     		   	       0x02

#define USB_HID_EPIN_ADDR                 		       0x01
#define USB_HID_EPIN_SIZE                 		   	   0x02

#define USB_HID_EPOUT_ADDR                		       0x02
#define USB_HID_EPOUT_SIZE                		       0x02
#define USB_HID_DESCRIPTOR_TYPE           		       0x21
#define USB_DESC_HID_REPORT               		       0x22




#endif /* USB_DESC_H */