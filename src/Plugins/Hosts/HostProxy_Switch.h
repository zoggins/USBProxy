/*
 * This file is part of USBProxy.
 */

#ifndef USBPROXY_HOSTPROXY_SWITCH_H
#define USBPROXY_HOSTPROXY_SWITCH_H

#include "HostProxy_GadgetFS.h"

class HostProxy_Switch: public HostProxy_GadgetFS {

	int roundNum;

protected:

	virtual bool do_not_send(__u8 endpoint, int* length)

public:
	HostProxy_Switch(ConfigParser *cfg);
	virtual ~HostProxy_Switch();
};

#endif /* USBPROXY_HOSTPROXY_SWITCH_H */
