# OpenClovis TIPC Kernel Module

This TIPC kernel module has been enhanced to include logging whenever a packet is dropped (and other errors).

It also creates some message buffers dedicated to TIPC use.  This allows TIPC to continue to function without packet drops even when the network is heavily utilized.  To customize this, see cl_mem.[c,h].

## Building

This module can be build outside of the kernel tree, but you must have the kernel headers installed in
/lib/modules/$(shell uname -r)/build.

If your kernel headers are installed somewhere else, edit "outbuild.mk" and change this directory.

To build, run:

make V=1 -f outbuild.mk
