#ifndef USB_REG_H
#define USB_REG_H


#define REG(x)  *(uint32_t *)(x)

#define USB_BASE_ADDR   0x40005C00  /* USB Registers Base Address */
#define USB_PMA_ADDR    0x40006000  /* USB Packet Memory Area Address */


/* Common Registers */
#define CNTR    REG(USB_BASE_ADDR + 0x40)   /* Control Register */
#define ISTR    REG(USB_BASE_ADDR + 0x44)   /* Interrupt Status Register */
#define FNR     REG(USB_BASE_ADDR + 0x48)   /* Frame Number Register */
#define DADDR   REG(USB_BASE_ADDR + 0x4C)   /* Device Address Register */
#define BTABLE  REG(USB_BASE_ADDR + 0x50)   /* Buffer Table Address Register */

/* CNTR: Control Register Bit Definitions */
#define CNTR_CTRM       0x8000      /* Correct Transfer Interrupt Mask */
#define CNTR_PMAOVRM    0x4000      /* Packet Memory Aerea Over/underrun Interrupt Mask */
#define CNTR_ERRM       0x2000      /* Error Interrupt Mask */
#define CNTR_WKUPM      0x1000      /* Wake-up Interrupt Mask */
#define CNTR_SUSPM      0x0800      /* Suspend Mode Interrupt Mask  */
#define CNTR_RESETM     0x0400      /* USB Reset Interrupt Mask   */
#define CNTR_SOFM       0x0200      /* Start of Frame Interrupt Mask */
#define CNTR_ESOFM      0x0100      /* Expected Start of Frame Interrupt Mask */
#define CNTR_RESUME     0x0010      /* Resume Request */
#define CNTR_FSUSP      0x0008      /* Force Suspend */
#define CNTR_LPMODE     0x0004      /* Low-power Mode */
#define CNTR_PDWN       0x0002      /* Power Down */
#define CNTR_FRES       0x0001      /* Force USB Reset */

/* ISTR: Interrupt Status Register Bit Definitions */
#define ISTR_CTR        0x8000      /* Correct Transfer */
#define ISTR_PMAOVR     0x4000      /* Packet Memory Aerea Over/underrun */
#define ISTR_ERR        0x2000      /* Error */
#define ISTR_WKUP       0x1000      /* Wake-up */
#define ISTR_SUSP       0x0800      /* Suspend Mode */
#define ISTR_RESET      0x0400      /* USB Reset */
#define ISTR_SOF        0x0200      /* Start of Frame */
#define ISTR_ESOF       0x0100      /* Expected Start of Frame */
#define ISTR_DIR        0x0010      /* Direction of Transaction */
#define ISTR_EP_ID      0x000F      /* EndPoint Identifier */

/* FNR: Frame Number Register Bit Definitions */
#define FNR_RXDP        0x8000      /* D+ Data Line Status */
#define FNR_RXDM        0x4000      /* D- Data Line Status */
#define FNR_LCK         0x2000      /* Locked */
#define FNR_LSOF        0x1800      /* Lost SOF */
#define FNR_FN          0x07FF      /* Frame Number */

/* DADDR: Device Address Register Bit Definitions */
#define DADDR_EF        0x0080      /* Enable Function */
#define DADDR_ADD       0x007F      /* Device Address */

/* EndPoint Registers */
#define EPxREG(x)       *(uint32_t *)(USB_BASE_ADDR + 4 * x)
#define EP0REG          *(uint32_t *)(USB_BASE_ADDR)

/* EPxREG: EndPoint Registers Bit Definitions */
#define EP_CTR_RX       0x8000      /* Correct RX Transfer */
#define EP_DTOG_RX      0x4000      /* RX Data Toggle */
#define EP_STAT_RX      0x3000      /* RX Status */
#define EP_STAT_RX_1    0x2000      /* RX Status Bit 1 */
#define EP_STAT_RX_0    0x1000      /* RX Status Bit 0 */
#define EP_SETUP        0x0800      /* EndPoint Setup */
#define EP_TYPE         0x0600      /* EndPoint Type */
#define EP_KIND         0x0100      /* EndPoint Kind */
#define EP_CTR_TX       0x0080      /* Correct TX Transfer */
#define EP_DTOG_TX      0x0040      /* TX Data Toggle */
#define EP_STAT_TX      0x0030      /* TX Status */
#define EP_STAT_TX_1    0x0020      /* TX Status Bit 1 */
#define EP_STAT_TX_0    0x0010      /* TX Status Bit 0 */
#define EP_EA           0x000F      /* EndPoint Address */

/* EndPoint Register Mask (No Toggle Fields) */
#define EP_MASK         (EP_CTR_RX|EP_SETUP|EP_TYPE|EP_KIND|EP_CTR_TX|EP_EA)

/* EP_TYPE: EndPoint Types */
#define EP_BULK         0x0000  /* BULK EndPoint */
#define EP_CONTROL      0x0200      /* CONTROL EndPoint */
#define EP_ISOCHRONOUS  0x0400      /* ISOCHRONOUS EndPoint */
#define EP_INTERRUPT    0x0600      /* INTERRUPT EndPoint */

/* EP_KIND: EndPoint Kind */
#define EP_DBL_BUF      EP_KIND     /* Double Buffer for Bulk Endpoint */
#define EP_STATUS_OUT   EP_KIND     /* Status Out for Control Endpoint */

/* EP_STAT_TX: TX Status */
#define EP_TX_DIS       0x0000      /* Disabled */
#define EP_TX_STALL     0x0010      /* Stalled */
#define EP_TX_NAK       0x0020      /* NAKed */
#define EP_TX_VALID     0x0030      /* Valid */

/* EP_STAT_RX: RX Status */
#define EP_RX_DIS       0x0000     /* Disabled */
#define EP_RX_STALL     0x1000      /* Stalled */
#define EP_RX_NAK       0x2000      /* NAKed */
#define EP_RX_VALID     0x3000      /* Valid */

#define EP_T_FIELD      0x0600
#define EPADDR_FIELD    0x000f

/* EndPoint mask */
#define EPTX_STAT      0x0030
#define EPRX_STAT      0x3000
#define EPREG_MASK     (EP_CTR_RX|EP_SETUP|EP_T_FIELD|EP_KIND|EP_CTR_TX|EPADDR_FIELD)

// #define EP_TOGGLE_SET(epr, bits, mask) (*(epr) = (*(epr) ^ (bits)) & (EPREG_MASK | (mask)))
// #define EP_TX_STATUS(epr, stat)    EPxREG(epr) = (EPxREG(epr) ^ (stat & EP_STAT_TX)) & (EP_MASK | EP_STAT_TX)
// #define EP_RX_STATUS(epr, stat)    EPxREG(epr) = (EPxREG(epr) ^ (stat & EP_STAT_RX)) & (EP_MASK | EP_STAT_RX)
// #define TX_VALID(epr)    EP_TOGGLE_SET((epr), EP_TX_VALID, EPTX_STAT)
// #define RX_VALID(epr)    EP_TOGGLE_SET((epr), EP_RX_VALID, EPRX_STAT)
 /* EP_RX_STATUS */

#define EP_RX_STATUS(epr, status) { \
	register uint16_t valReg = EPxREG(epr) & EP_STAT_RX;\
	if(status & EP_STAT_RX_0){\
		valReg ^= EP_STAT_RX_0;\
	}\
	if(status & EP_STAT_RX_1){\
		valReg ^= EP_STAT_RX_1;\
	}\
	EPxREG(epr) = valReg | EP_CTR_RX | EP_CTR_TX;\
}/* EP_TX_STATUS */

#define EP_TX_STATUS(epr, status) { \
	register uint16_t valReg = EPxREG(epr) & EP_STAT_TX;\
	if(status & EP_STAT_TX_0){\
		valReg ^= EP_STAT_TX_0;\
	}\
	if(status & EP_STAT_TX_1){\
		valReg ^= EP_STAT_TX_1;\
	}\
	EPxREG(epr) = valReg | EP_CTR_RX | EP_CTR_TX;\
}/* EP_TX_STATUS */

#define EP_ADDR_MASK    0xFFFE      /* Address Mask */
#define EP_COUNT_MASK   0x03FF      /* Count Mask */



/* Buffer register */
#define EP_ADDR_TX(x)    *(uint32_t *)(USB_PMA_ADDR + 0x00 + 0x10 * x)  /* USB_PMA_ADDR + NUMEP * 16 */
#define EP_COUNT_TX(x)   *(uint32_t *)(USB_PMA_ADDR + 0x04 + 0x10 * x)  /* USB_PMA_ADDR + NUMEP * 16 + 4 */
#define EP_ADDR_RX(x)    *(uint32_t *)(USB_PMA_ADDR + 0x08 + 0x10 * x)  /* USB_PMA_ADDR + NUMEP * 16 + 8 */
#define EP_COUNT_RX(x)   *(uint32_t *)(USB_PMA_ADDR + 0x0C + 0x10 * x)  /* USB_PMA_ADDR + NUMEP * 16 + 12 */

#endif  /* USB_REG_H */