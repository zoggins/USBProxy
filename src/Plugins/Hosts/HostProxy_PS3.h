/*
 * This file is part of USBProxy.
 */

#ifndef USBPROXY_HOSTPROXY_PS3_H
#define USBPROXY_HOSTPROXY_PS3_H

#include "HostProxy_GadgetFS.h"

class HostProxy_PS3: public HostProxy_GadgetFS {

protected:

	virtual void handle_USB_REQ_SET_CONFIGURATION();
	virtual int send_descriptor(int p_device_file, char* descriptor, int descriptorLength, Device* device);

public:
	HostProxy_PS3(ConfigParser *cfg);
	virtual ~HostProxy_PS3();
};

#endif /* USBPROXY_HOSTPROXY_PS3_H */
