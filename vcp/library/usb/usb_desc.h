#ifndef USB_DESC_H
#define USB_DESC_H

#include "../cmsis/inc/stm32f103xb.h"

#define LOBYTE(x)  ((uint8_t)(x & 0x00FF))
#define HIBYTE(x)  ((uint8_t)((x & 0xFF00) >> 8))

#define  USB_VID     								   1155
#define  USB_PID     				                   22352
#define  USB_LANGID_STRING    						   1033

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
#define  USB_DESC_SIZE_CONFIGURATION                   67


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

/* VCP */

#define USB_CLASS									   0x02

// #define USB_VCP_DESC_SIZE		     		   	       67

#define USB_VCP_EPIN_ADDR                 		       0x01
#define USB_VCP_EPIN_SIZE                 		   	   0x08

#define USB_VCP_EPOUT_ADDR                		       0x01
#define USB_VCP_EPOUT_SIZE                		       0x08

#define USB_VCP_DESCRIPTOR_TYPE           		       0x21
#define USB_VCP_CMD_PACKET_SIZE                        8
#define USB_VCP_DATA_HS_MAX_PACKET_SIZE                512

#define CDC_IN_EP                                   0x81  /* EP1 for data IN */
#define CDC_OUT_EP                                  0x01  /* EP1 for data OUT */
#define CDC_CMD_EP                                  0x82  /* EP2 for CDC commands */

#endif /* USB_DESC_H */