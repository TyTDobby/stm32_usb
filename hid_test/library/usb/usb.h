#ifndef USB_H
#define USB_H

#include "../cmsis/stm32f10x.h"

#define LOBYTE(x)  ((uint8_t)(x & 0x00FF))
#define HIBYTE(x)  ((uint8_t)((x & 0xFF00) >> 8))

#define USB_EP_AE_0 	0x0 
#define USB_EP_AE_1 	0x1
#define USB_EP_AE_2 	0x2

#define BTABLE_ADDRESS  0x0

#define USB_DESC_DEVICE                          0x800601
#define USB_DESC_CONFIGURATION                   0x800602
#define USB_DESC_STRING                          0x800603
#define USB_DESC_INTERFACE                       0x800604
#define USB_DESC_ENDPOINT                        0x800605
#define USB_DESC_DEVICE_QUALIFIER                0x800606
#define USB_DESC_OTHER_SPEED_CONFIGURATION       0x800607
#define USB_SET_CONFIGURATION                    0x000900
#define USB_SET_ADDRESS                          0x000500
#define USB_CLASS_REQ                            0x210A00

#define EP0 									 0 
#define EP1 									 1
#define EP2 									 2

#define MAX_EP0_SIZE                             64

#define EP0_TX 									 64
#define EP0_RX 									 EP0_TX + MAX_EP0_SIZE

#define EP1_TX 									 MAX_EP0_SIZE + EP0_RX
#define EP1_RX 									 MAX_EP0_SIZE + EP1_TX 

#define EP2_TX 									 0x280
#define EP2_RX 									 0x300 

#define USB_VID     							1155
#define USB_PID     				            22352
#define USB_LANGID_STRING    					1033



#define USB_DESC_SIZE_DEVICE                    18
#define USB_DESC_SIZE_DEVICE_QUALIFIER          10
#define USB_DESC_SIZE_CONFIGURATION             41

#define USB_STR_SIZE_LANGID                     0x04
#define USB_STR_SIZE_PRODUCT                    0x12
#define USB_STR_SIZE_MFC					    0x0e
#define USB_STR_SIZE_SERIALNUMBER 			    0x0e
#define USB_STR_SIZE_CONFIG 	     		    0x13
#define USB_STR_SIZE_INTERFACE 				    0x16

#define USB_IDX_LANGID_STR                      0x00 
#define USB_IDX_MFC_STR                         0x01 
#define USB_IDX_PRODUCT_STR                     0x02
#define USB_IDX_SERIAL_STR                      0x03 
#define USB_IDX_CONFIG_STR                      0x04 
#define USB_IDX_INTERFACE_STR                   0x05 

#define USB_MAX_NUM_CONFIGURATION     		    0x01

/* HID */

#define USB_DESC_SIZE_HID_REPORT     		    79

#define USB_HID_EPIN_ADDR                 	    0x82
#define USB_HID_EPIN_SIZE                 	    0x08

#define USB_HID_EPOUT_ADDR                	    0x02
#define USB_HID_EPOUT_SIZE                	    0x08

#define USB_HID_DESCRIPTOR_TYPE           	    0x21
#define USB_DESC_HID_REPORT               	    0x810622

/* Structs */

typedef struct _BYTE {
	uint8_t		high;
	uint8_t     low;
} BYTE;

/* USB Default Control Pipe Setup Packet */
typedef struct _USB_SETUP_PACKET {
	uint8_t		bmRequestType;
	uint8_t     bRequest;
	BYTE    	wValue;
	BYTE    	wIndex;
	BYTE    	wLength;
} USB_SETUP_PACKET;

typedef struct _HEAP { 
	uint16_t size;
	uint8_t	*buff;
} HEAP;

void USBConfig(void);
void USBSendData(uint8_t *buff);

#endif /* USB_H */