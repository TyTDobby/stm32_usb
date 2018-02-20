#ifndef USB_H
#define USB_H

#include "../cmsis/stm32f10x.h"

#define LOBYTE(x) ((uint8_t)(x & 0x00FF))
#define HIBYTE(x) ((uint8_t)((x & 0xFF00) >> 8))
#define MIN(num_1, num_2) num_1 > num_2 ? num_2 : num_1;

#define USB_BASE		0x40005C00
#define USB_PMA_ADDR	0x40006000

#define USB_EP_EA       		((uint16_t)0x000F)	/* Endpoint Address */

#define USB_EP_STAT_TX  		((uint16_t)0x0030)	/* STAT_TX[1:0] bits (Status bits, for transmission transfers) */
#define USB_EP_STAT_TX_0		((uint16_t)0x0010)	/* Bit 0 */
#define USB_EP_STAT_TX_1		((uint16_t)0x0020)	/* Bit 1 */

#define USB_EP_DTOG_TX  		((uint16_t)0x0040)	/* Data Toggle, for transmission transfers */
#define USB_EP_CTR_TX   		((uint16_t)0x0080)	/* Correct Transfer for transmission */
#define USB_EP_KIND  			((uint16_t)0x0100)	/* Endpoint Kind */

#define USB_EP_TYPE  			((uint16_t)0x0600)	/* EP_TYPE[1:0] bits (Endpoint type) */
#define USB_EP_TYPE_0			((uint16_t)0x0200)	/* Bit 0 */
#define USB_EP_TYPE_1			((uint16_t)0x0400)	/* Bit 1 */

#define USB_EP_SETUP    		((uint16_t)0x0800)	/* Setup transaction completed */

#define USB_EP_STAT_RX  		((uint16_t)0x3000)	/* STAT_RX[1:0] bits (Status bits, for reception transfers) */
#define USB_EP_STAT_RX_0		((uint16_t)0x1000)	/* Bit 0 */
#define USB_EP_STAT_RX_1		((uint16_t)0x2000)	/* Bit 1 */

#define USB_EP_DTOG_RX  		((uint16_t)0x4000)	/* Data Toggle, for reception transfers */
#define USB_EP_CTR_RX   		((uint16_t)0x8000)	/* Correct Transfer for reception */
 
/* EP_TYPE: EndPoint Types */
#define USB_EP_BULK         0x0000  /* BULK EndPoint */
#define USB_EP_CONTROL      0x0200      /* CONTROL EndPoint */
#define USB_EP_ISOCHRONOUS  0x0400      /* ISOCHRONOUS EndPoint */
#define USB_EP_INTERRUPT    0x0600      /* INTERRUPT EndPoint */

/* EP_KIND: EndPoint Kind */
#define USB_EP_DBL_BUF      EP_KIND     /* Double Buffer for Bulk Endpoint */
#define USB_EP_STATUS_OUT   EP_KIND     /* Status Out for Control Endpoint */

/* EP_STAT_TX: TX Status */
#define USB_EP_TX_DIS       0x0000      /* Disabled */
#define USB_EP_TX_STALL     0x0010      /* Stalled */
#define USB_EP_TX_NAK       0x0020      /* NAKed */
#define USB_EP_TX_VALID     0x0030      /* Valid */

/* EP_STAT_RX: RX Status */
#define USB_EP_RX_DIS       0x0000     /* Disabled */
#define USB_EP_RX_STALL     0x1000      /* Stalled */
#define USB_EP_RX_NAK       0x2000      /* NAKed */
#define USB_EP_RX_VALID     0x3000      /* Valid */

#define USB_EP_MASK (USB_EP_CTR_RX | USB_EP_SETUP | USB_EP_TYPE | USB_EP_KIND |USB_EP_CTR_TX | USB_EP_EA)

#define USB_EP_RX_DTOGMASK 		(USB_EP_MASK | USB_EP_STAT_RX)
#define USB_EP_TX_DTOGMASK 		(USB_EP_MASK | USB_EP_STAT_TX)
#define USB_EP0                 0
#define USB_EP1                 1
#define USB_EP2                 2

#define USB_COUNT0_TX   *(uint32_t *)(USB_PMA_ADDR + 0x04)

/* USB Request Types */
#define USB_DEVICE 		0x00
#define USB_INTERFACE 	0x01
#define USB_ENDPOINT 	0x02
#define USB_OTHER 		0x03

/* USB Standard Request Codes */
#define USB_GET_STATUS      	0x00
#define USB_CLEAR_FEATURE 		0x01
#define USB_SET_FEATURE 		0x03
#define USB_SET_ADDRESS 		0x05
#define USB_GET_DESCRIPTOR 		0x06
#define USB_SET_DESCRIPTOR 		0x07
#define USB_GET_CONFIGURATION	0x08
#define USB_SET_CONFIGURATION	0x09
#define USB_GET_INTERFACE 		0x0a
#define USB_SET_INTERFACE 		0x0b
#define USB_SYNC_FRAME          0x0c



/* USB Descriptor Types */
#define USB_DEVICE_DESC_TYPE      0x01
#define USB_CFG_DESC_TYPE         0x02
#define USB_STR_DESC_TYPE         0x03
#define USB_IFACE_DESC_TYPE       0x04
#define USB_EP_DESC_TYPE          0x05
#define USB_DEVICE_QR_DESC_TYPE   0x06
#define USB_OSPEED_CFG_DESC_TYPE  0x07
#define USB_IFACE_PWR_DESC_TYPE   0x08
#define USB_HID_DESC_TYPE 		  0x22
/* USB Device Classes */
#define USB_RESERVED 		0x00
#define USB_AUDIO 			0x01
#define USB_COMM 			0x02
#define USB_HID 			0x03
#define USB_MONITOR 		0x04
#define USB_PHYSIC 			0x05
#define USB_POWER 			0x06
#define USB_PRINTER 		0x07
#define USB_STORAGE 		0x08
#define USB_HUB 			0x09
#define USB_VENDOR_SPEC		0xFF

#define USB_MAX_EP0_SIZE    32

#define USB_IDX_LANGID_STR       0x00 
#define USB_IDX_MFC_STR          0x01 
#define USB_IDX_PRODUCT_STR      0x02
#define USB_IDX_SERIAL_STR       0x03 
#define USB_IDX_CONFIG_STR       0x04 
#define USB_IDX_INTERFACE_STR    0x05 

#define USB_VID     			  1155
#define USB_PID     			  22352
#define USB_LANGID_STRING    	  1033



typedef struct
{
	__IO uint32_t EPR[8];         /* USB Endpoint 0...7 register,   Address offset: 0x00 */ 
	__IO uint32_t RESERVED[8];    /* Reserved */     
	__IO uint32_t CNTR;           /* Control register,              Address offset: 0x40 */
	__IO uint32_t ISTR;           /* Interrupt status register,     Address offset: 0x44 */
	__IO uint32_t FNR;            /* Frame number register,         Address offset: 0x48 */
	__IO uint32_t DADDR;          /* Device address register,       Address offset: 0x4C */
	__IO uint32_t BTABLE;         /* Buffer Table address register, Address offset: 0x50 */
     
} USB_TypeDef;

typedef struct
{
	__IO uint32_t ADDR_TX;          /* Interrupt status register,     Address offset: 0x44 */
	__IO uint32_t COUNT_TX;         /* Frame number register,         Address offset: 0x48 */
	__IO uint32_t ADDR_RX;          /* Device address register,       Address offset: 0x4C */
	__IO uint32_t COUNT_RX;         /* Buffer Table address register, Address offset: 0x50 */
     
} USBEpBuf_TypeDef;

typedef struct
{
	uint8_t 	*buffTx;
	uint16_t 	cntTx;

	uint8_t 	*buffRx[64];
	uint16_t 	cntRx;
	
	uint8_t 	*buffSetup[12];
	uint16_t 	cntMaxEp0;
	uint8_t 	devAddress;
 	uint16_t	ep;
 	uint16_t 	istr;

} USBHeap;

typedef struct {
  uint8_t		high;
  uint8_t       low;
} Byte;

/* USB Default Control Pipe Setup Packet */
typedef struct {
  uint8_t	bmRequestType;
  uint8_t   bRequest;
  Byte    	wValue;
  Byte    	wIndex;
  Byte    	wLength;
} USBSetupPacket;

// #define USB 		((USB_TypeDef *)USB_BASE)
#define USBEpBuf 	((USBEpBuf_TypeDef *)USB_PMA_ADDR)

/* Functions */

void USBConfig(void);
void USBRead(uint8_t *buff);
void USBWrite(uint8_t *buff);
#endif /* USB_H */