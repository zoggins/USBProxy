/*
 * This file is part of USBProxy.
 */

#ifndef USBPROXY_HOSTPROXY_GENMINI_H
#define USBPROXY_HOSTPROXY_GENMINI_H

#include "HostProxy_GadgetFS.h"

class HostProxy_GenMini: public HostProxy_GadgetFS {

private:
        int lastNumInFlight;
        bool rateLocked;
        int roundNum;
        int rateLimit;

protected:
	virtual int send_descriptor(int p_device_file, char* descriptor, int descriptorLength, Device* device);
	virtual bool do_not_send(__u8 endpoint, int* length);
public:
	HostProxy_GenMini(ConfigParser *cfg);
	virtual ~HostProxy_GenMini();
};

#endif /* USBPROXY_HOSTPROXY_GENMINI_H */
