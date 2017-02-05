#include <stdio.h>
#include <libusb.h>
#include "main.h"
#include "menu.h"
#include "usb_interface.h"

int main (void)
{
    int ret;

    ret = connect_usb();

    if(0 == ret)
    {
        display_menu();
    }

    ret = disconnect_usb();

    return 0;
}
