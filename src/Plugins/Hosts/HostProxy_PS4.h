/*
 * This file is part of USBProxy.
 */

#ifndef USBPROXY_HOSTPROXY_PS4_H
#define USBPROXY_HOSTPROXY_PS4_H

#include "HostProxy_GadgetFS.h"

class HostProxy_PS4: public HostProxy_GadgetFS {

private:

protected:

	virtual void handle_USB_REQ_SET_CONFIGURATION();

public:
	HostProxy_PS4(ConfigParser *cfg);
	virtual ~HostProxy_PS4();
};

#endif /* USBPROXY_HOSTPROXY_PS4_H */
