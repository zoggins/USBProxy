/*
 * This file is part of USBProxy.
 */

#ifndef USBPROXY_HOSTPROXY_GENMINI_H
#define USBPROXY_HOSTPROXY_GENMINI_H

#include "HostProxy_Switch.h"

class HostProxy_GenMini: public HostProxy_Switch {

protected:
	virtual int send_descriptor(int p_device_file, char* descriptor, int descriptorLength, Device* device);
public:
	HostProxy_GenMini(ConfigParser *cfg);
	virtual ~HostProxy_GenMini();
};

#endif /* USBPROXY_HOSTPROXY_GENMINI_H */
