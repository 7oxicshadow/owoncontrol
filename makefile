owoncontrol: main.c menu.c owon_commands.c usb_interface.c
	gcc -c main.c -I./includes -I/usr/include/libusb-1.0
	gcc -c menu.c -I./includes -I/usr/include/libusb-1.0
	gcc -c owon_commands.c -I./includes -I/usr/include/libusb-1.0
	gcc -c usb_interface.c -I./includes -I/usr/include/libusb-1.0
	gcc -o owoncontrol main.o menu.o owon_commands.o usb_interface.o -lusb-1.0
