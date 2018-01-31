#ifndef USB_H
#define USB_H

#include "../cmsis/inc/stm32f103xb.h"
#include "usb_desc.h"



#define USB_EP_AE_0 	0x0 
#define USB_EP_AE_1 	0x1
#define USB_EP_AE_2 	0x2

#define BTABLE_ADDRESS  0x0

#define USB_ADDR0_TX    *(uint32_t *)(USB_PMAADDR + 0x00)  /* USB_PMAADDR + NUMEP * 16 */
#define USB_COUNT0_TX   *(uint32_t *)(USB_PMAADDR + 0x04)  /* USB_PMAADDR + NUMEP * 16 + 4 */
#define USB_ADDR0_RX    *(uint32_t *)(USB_PMAADDR + 0x08)  /* USB_PMAADDR + NUMEP * 16 + 8 */
#define USB_COUNT0_RX   *(uint32_t *)(USB_PMAADDR + 0x0C)  /* USB_PMAADDR + NUMEP * 16 + 12 */

#define USB_ADDR1_TX    *(uint32_t *)(USB_PMAADDR + 0x10)  /* USB_PMAADDR + NUMEP * 16 */
#define USB_COUNT1_TX   *(uint32_t *)(USB_PMAADDR + 0x14)  /* USB_PMAADDR + NUMEP * 16 + 4 */
#define USB_ADDR1_RX    *(uint32_t *)(USB_PMAADDR + 0x18)  /* USB_PMAADDR + NUMEP * 16 + 8 */
#define USB_COUNT1_RX   *(uint32_t *)(USB_PMAADDR + 0x1C)  /* USB_PMAADDR + NUMEP * 16 + 12 */

#define USB_ADDR2_TX    *(uint32_t *)(USB_PMAADDR + 0x20)  /* USB_PMAADDR + NUMEP * 16 */
#define USB_COUNT2_TX   *(uint32_t *)(USB_PMAADDR + 0x24)  /* USB_PMAADDR + NUMEP * 16 + 4 */
#define USB_ADDR2_RX    *(uint32_t *)(USB_PMAADDR + 0x28)  /* USB_PMAADDR + NUMEP * 16 + 8 */
#define USB_COUNT2_RX   *(uint32_t *)(USB_PMAADDR + 0x2C)  /* USB_PMAADDR + NUMEP * 16 + 12 */

#define  USB_REQ_GET_STATUS                             0x00
#define  USB_REQ_CLEAR_FEATURE                          0x01
#define  USB_REQ_SET_FEATURE                            0x03
#define  USB_REQ_SET_ADDRESS                            0x05
#define  USB_REQ_GET_DESCRIPTOR                         0x06
#define  USB_REQ_SET_DESCRIPTOR                         0x07
#define  USB_REQ_GET_CONFIGURATION                      0x08
#define  USB_REQ_SET_CONFIGURATION                      0x09
#define  USB_REQ_GET_INTERFACE                          0x0A
#define  USB_REQ_SET_INTERFACE                          0x0B
#define  USB_REQ_SYNCH_FRAME                            0x0C

#define USB_VAL_DEVICE									0x01
#define USB_VAL_DEVICE_QUALIFIER						0x06

#define USB_EP0 		0 
#define USB_EP1 		1
#define USB_EP2 		2

#define USB_EP0_TX 		0x080
#define USB_EP0_RX 		0x080 

#define USB_EP1_TX 		0x080
#define USB_EP1_RX 		0x080 

#define USB_EP2_TX 		0x080
#define USB_EP2_RX 		0x080 

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


typedef struct {
    uint32_t a,b,c,d, e,f,g,h, i,j,k,l, m,n,o,p;
} uint32x16_t;

typedef uint32_t uint32x32_t[32];

// #define USBTABLE  ((usbtable_t*) 0x40006000)
// #define USBSTAGE  ((usbstage_t*) 0x40006080)
#define USBTXD0  ((uint32x16_t*) 0x40006100)
#define USBRXD0  ((uint32x16_t*) 0x40006180)
#define USBTXD1  ((uint32x32_t*) 0x40006200)
#define USBRXD1  ((uint32x32_t*) 0x40006280)

// #define EPTxADDR(epNum)  ((uint32_t *)(((uint16_t)epNum * 16)      + USB_PMAADDR))
// #define EPTxCOUNT(epNum) ((uint32_t *)(((uint16_t)epNum * 16 + 4)  + USB_PMAADDR))
// #define EPRxADDR(epNum)  ((uint32_t *)(((uint16_t)epNum * 16 + 8)  + USB_PMAADDR))
// #define EPRxCOUNT(epNum) ((uint32_t *)(((uint16_t)epNum * 16 + 12) + USB_PMAADDR))
// #define EPxREG(x)        (uint32_t *)(USB_BASE + 4 * x)

#define EP0VALID *EPxREG(USB_EP0) |= USB_EP_TX_VALID;

void USBConfig(void);

#endif /* USB_H */