#include <stdio.h>
#include <libusb.h>
#include "main.h"
#include "usb_interface.h"

#define USB_LOCK_VENDOR 0x5345			  // Dev : (5345) Owon Technologies
#define USB_LOCK_PRODUCT 0x1234			  // (1234) PDS Digital Oscilloscope
#define BULK_WRITE_ENDPOINT 0x03
#define BULK_READ_ENDPOINT 0x81

char coupling_data[COUPLING_DATA_SIZE] = {0x3a,0x4d,0x00,0x00,0x00,0x06,0x4d,0x43,0x48,0x00,0x63,0x00};
char probe_scale_data[PROBE_SCALE_DATA_SIZE] = {0x3a,0x4d,0x00,0x00,0x00,0x06,0x4d,0x43,0x48,0x00,0x70,0x00};
char volt_range_data[VOLT_SCALE_DATA_SIZE] = {0x3a,0x4d,0x00,0x00,0x00,0x06,0x4d,0x43,0x48,0x00,0x76,0x00};
char memory_range_data[MEM_RANGE_DATA_SIZE] = {0x3a,0x4d,0x00,0x00,0x00,0x04,0x4d,0x44,0x50,0x00};
char timebase_data[TB_DATA_SIZE] = {0x3a,0x4d,0x00,0x00,0x00,0x05,0x4d,0x48,0x52,0x62,0x00};
char tracepos_data[TRACEPOS_DATA_SIZE] = {0x3a,0x4d,0x00,0x00,0x00,0x09,0x4d,0x43,0x48,0x00,0x7a,0x00,0x00,0x00,0x00};

char hor_trigger_data[HOR_TRIG_DATA_SIZE] = {0x3a,0x4d,0x00,0x00,0x00,0x08,0x4d,0x48,0x52,0x76,0x00,0x00,0x00,0x00}; //4 bytes data signed (/50)
char acqu_mode_data[ACQU_MODE_DATA_SIZE] = {0x3a,0x4d,0x00,0x00,0x00,0x04,0x4d,0x41,0x51,0x00};
char acqu_avg_mode_data[ACQU_AVG_MODE_DATA_SIZE] = {0x3a,0x4d,0x00,0x00,0x00,0x05,0x4d,0x41,0x51,0x02,0x00};

char edge_trigger_data[EDGE_TRIG_DATA_SIZE] = {0x3a,0x4d,0x00,0x00,0x00,0x2e,0x4d,0x54,0x52,0x73,0x00,0x65,0x02,0x00,0x4d,
                                               0x54,0x52,0x73,0x00,0x65,0x03,0x00,0x4d,0x54,0x52,0x73,0x00,0x65,0x04,0x00,
                                               0x00,0x00,0x01,0x4d,0x54,0x52,0x73,0x00,0x65,0x05,0x00,0x4d,0x54,0x52,0x73,
                                               0x00,0x65,0x06,0x00,0x00,0x00,0x00};
/*
                            byte[9] & byte[17] & byte[25] & byte[36] & byte[44] --------- (single = 0x73 alternate = 0x61)
                            byte[10] & byte[18] & byte[26] & byte[37] & byte[45] -------- (CH1 = 0x00 CH2 = 0x01)
                            byte[40] ------------  (Rising edge = 0x00 Falling Edge = 0x01)
                            byte[13] ------------  (dc couple = 0x00 ac couple = 0x01 hf couple 0x02 lf couple 0x03)
                            byte[21] ------------  (auto trigger = 0x00 normal trigger = 0x01 once trigger 0x02)
                            byte[48] & byte[49] & byte[50] & byte[51] -------- (Trigger value 32bit signed)
*/
char force_trig_data[FORCE_TRIG_DATA_SIZE] = {0x3a,0x53,0x44,0x53,0x4c,0x46,0x4f,0x52,0x23};
char set_50pct_trig_data[SET_50PCT_TRIG_DATA_SIZE] = {0x3a,0x53,0x44,0x53,0x4c,0x46,0x35,0x30,0x23};
char set_0_trig_data[SET_0_TRIG_DATA_SIZE] = {0x3a,0x53,0x44,0x53,0x4c,0x54,0x4c,0x30,0x23};

libusb_device_handle *dev_handle;
libusb_context *lusb_ctx = NULL;

int connect_usb(void)
{
    libusb_device **devs;
    int ret = 0;
    int devcount = 0;
    int bytes_written = 0;
    int local_ret;

    /* Initialise the usb interface */
    ret = libusb_init(&lusb_ctx);

    /* Check to see if the lusb_init call failed */
    if ( ret < 0 )
    {
        printf("USB init failed!\n");
        return 1;
    }

    libusb_set_debug(lusb_ctx, 3); //set verbosity level to 3, as suggested in the documentation

    /* Get device list */
    devcount = libusb_get_device_list(lusb_ctx, &devs);

    if(devcount < 0)
    {
        /* error getting a device list */
        printf("Get Device Error\n");
    }

    printf("Num Devices Found :  %d\n", devcount);

    dev_handle = libusb_open_device_with_vid_pid(lusb_ctx, USB_LOCK_VENDOR, USB_LOCK_PRODUCT);
    if(dev_handle == NULL)
    {
        printf("Cannot open OWON device\n");
        return 1;
    }

    /* Free the device list */
    libusb_free_device_list(devs, 1);

    if(libusb_kernel_driver_active(dev_handle, 0) == 1)
    {
        printf("Kernel Driver Active - Requesting Detach\n");

        if(libusb_detach_kernel_driver(dev_handle, 0) == 0) //detach it
        {
            printf("Driver Detached\n");
        }
    }

    ret = libusb_claim_interface(dev_handle, 0); //claim interface 0 (the first) of device (mine had jsut 1)
    if(ret < 0)
    {
        printf("Failed to claim interface. Exiting\n");
        return 1;
    }

    printf("Claimed Interface\n");

    return(0);

}

int disconnect_usb(void)
{
    int ret;

    ret = libusb_release_interface(dev_handle, 0); //release the claimed interface
    if(ret != 0)
    {
        printf("Cannot Release Interface\n");
        return 1;
    }
    printf("Released Interface\n");

    libusb_close(dev_handle);

    /* Close the connection */
    libusb_exit(lusb_ctx);

    return(0);
}

void send_usb_data(char* data, int length)
{
    int local_ret;
    int local_written;

    local_ret = libusb_bulk_transfer(dev_handle, BULK_WRITE_ENDPOINT, data, length, &local_written, 0);
    if( local_ret != 0 ) { printf ("Write Failed\n");}
}
