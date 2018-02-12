#ifndef USB_DEVICE_H
#define USB_DEVICE_H

#include <iostream>
#include <libusb-1.0/libusb.h>

#define VENDOR_ID       0x0483
#define PRODUCT_ID      0x5750

class USBDevice{

public:
    USBDevice();
    ~USBDevice();
    int get_one();
private:
    libusb_device_handle *handle;

};

#endif /* USB_DEVICE_H */