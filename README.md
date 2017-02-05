# Owonoscope

This is an open source attempt at controlling an Owon SDS7102v oscilloscope using
usb commnands discovered using wireshark to monitor the traffic from the
official windows app.

At the moment it is nothing more than a proof of concept to show what can be
done. The current menu is crude but does the job to show how the commands work.

Ultimately I hope to create a QT interface to mimic something similar to the
Owon windows app. QT is something that I have never used before so progress
may be slow :(

Whilst this has only been tested on an SDS7102v scope in theory it will probably
work on other variants.

Build
-----
This project has a dependancy on libusb.

Goto the root directory and run 'make'.

Note: I use Fedora to build and the makefile has fixed include paths. If you
have trouble building you might need to adjust the include paths for your O/S.
