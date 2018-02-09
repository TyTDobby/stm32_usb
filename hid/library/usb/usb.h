#ifndef USB_H
#define USB_H

#include "../cmsis/inc/stm32f103xb.h"

#define LOBYTE(x)  ((uint8_t)(x & 0x00FF))
#define HIBYTE(x)  ((uint8_t)((x & 0xFF00) >> 8))

#define USB_EP_AE_0 	0x0 
#define USB_EP_AE_1 	0x1
#define USB_EP_AE_2 	0x2

#define BTABLE_ADDRESS  0x0

#define USB_ADDR_TX(x)    *(uint32_t *)(USB_PMAADDR + 0x00 + 0x10 * x)  /* USB_PMAADDR + NUMEP * 16 */
#define USB_COUNT_TX(x)   *(uint32_t *)(USB_PMAADDR + 0x04 + 0x10 * x)  /* USB_PMAADDR + NUMEP * 16 + 4 */
#define USB_ADDR_RX(x)    *(uint32_t *)(USB_PMAADDR + 0x08 + 0x10 * x)  /* USB_PMAADDR + NUMEP * 16 + 8 */
#define USB_COUNT_RX(x)   *(uint32_t *)(USB_PMAADDR + 0x0C + 0x10 * x)  /* USB_PMAADDR + NUMEP * 16 + 12 */

#define USB_SETUP_DESC_DEVICE                          0x800601
#define USB_SETUP_DESC_CONFIGURATION                   0x800602
#define USB_SETUP_DESC_STRING                          0x800603
#define USB_SETUP_DESC_INTERFACE                       0x800604
#define USB_SETUP_DESC_ENDPOINT                        0x800605
#define USB_SETUP_DESC_DEVICE_QUALIFIER                0x800606
#define USB_SETUP_DESC_OTHER_SPEED_CONFIGURATION       0x800607
#define USB_SETUP_SET_CONFIGURATION                    0x000900
#define USB_SETUP_SET_ADDRESS                          0x000500
#define USB_SETUP_CLASS_REQ                            0x210A00

#define USB_EP0 									   0 
#define USB_EP1 									   1
#define USB_EP2 									   2

#define USB_EP0_TX 									   128
#define USB_EP0_RX 									   256 

#define USB_EP1_TX 									   384
#define USB_EP1_RX 									   512 

#define USB_EP2_TX 									   0x180
#define USB_EP2_RX 									   0x200 

#define USB_VID     								   1155
#define USB_PID     				                   22352
#define USB_LANGID_STRING    						   1033

#define USB_MAX_EP0_SIZE                               32

#define USB_DESC_SIZE_DEVICE                		   18
#define USB_DESC_SIZE_DEVICE_QUALIFIER                 10
#define USB_DESC_SIZE_CONFIGURATION                    41

#define USB_STR_SIZE_LANGID                   		   0x04
#define USB_STR_SIZE_PRODUCT                  		   0x12
#define USB_STR_SIZE_MFC							   0x0e
#define USB_STR_SIZE_SERIALNUMBER 					   0x0e
#define USB_STR_SIZE_CONFIG 	     				   0x13
#define USB_STR_SIZE_INTERFACE 					       0x16

#define USB_IDX_LANGID_STR                             0x00 
#define USB_IDX_MFC_STR                                0x01 
#define USB_IDX_PRODUCT_STR                            0x02
#define USB_IDX_SERIAL_STR                             0x03 
#define USB_IDX_CONFIG_STR                             0x04 
#define USB_IDX_INTERFACE_STR                          0x05 

#define USB_MAX_NUM_CONFIGURATION     				   0x01

/* HID */

#define USB_DESC_SIZE_HID_REPORT     		   	       79

#define USB_HID_EPIN_ADDR                 		       0x81
#define USB_HID_EPIN_SIZE                 		   	   0x08

#define USB_HID_EPOUT_ADDR                		       0x02
#define USB_HID_EPOUT_SIZE                		       0x08

#define USB_HID_DESCRIPTOR_TYPE           		       0x21
#define USB_DESC_HID_REPORT               		       0x810622

/* Structs */

typedef struct _LOW_HIGH_BYTE {
  uint8_t		high;
  uint8_t       low;
} LOW_HIGH_BYTE;

/* USB Default Control Pipe Setup Packet */
typedef struct _USB_SETUP_PACKET {
  uint8_t		   bmRequestType;
  uint8_t          bRequest;
  LOW_HIGH_BYTE    wValue;
  LOW_HIGH_BYTE    wIndex;
  LOW_HIGH_BYTE    wLength;
} USB_SETUP_PACKET;

typedef struct _HEAP { 
	uint16_t size;
	uint8_t	*buff;
} HEAP;

// typedef struct _FLAGS { 
// 	uint8_t overflow;
// 	uint8_t	*buff;
// } FLAGS;

void USBConfig(void);
void USBSendData(uint8_t *buff);

#endif /* USB_H */