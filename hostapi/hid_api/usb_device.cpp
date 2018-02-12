#include "usb_device.h"

USBDevice::USBDevice(){
    libusb_init(NULL);
    libusb_set_debug(NULL, 1);
    handle = libusb_open_device_with_vid_pid(NULL, VENDOR_ID, PRODUCT_ID);
    if(handle == NULL)
        std::cout << "\tError: Device not found!" << std::endl;
    else
        std::cout << "\tSuccess!" << std::endl;    

#ifdef __linux__
    if(libusb_attach_kernel_driver(handle, 0))
       std::cout << "Driver: " <<  libusb_detach_kernel_driver(handle, 0) << std::endl;
#endif



}
 
USBDevice::~USBDevice(){
    libusb_release_interface(handle, 0); // Освобождаем интерфейс (важно! иначе потом не сможете работать с устройством)
#ifdef __linux__    
    libusb_attach_kernel_driver(handle, 1); // Возвращаем управление драйверу
#endif
    libusb_close(handle); // Закрываем устройство
    libusb_exit(NULL); // Закрываем контекст
}

int USBDevice::get_one(){
    return 1;
}