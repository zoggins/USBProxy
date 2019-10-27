/*
 * This file is part of USBProxy.
 */

#ifndef USBPROXY_HOSTPROXY_XBOX_H
#define USBPROXY_HOSTPROXY_XBOX_H

#include "HostProxy_GadgetFS.h"

class HostProxy_Xbox: public HostProxy_GadgetFS {

protected:

	virtual void handle_USB_REQ_SET_CONFIGURATION();

public:
	HostProxy_Xbox(ConfigParser *cfg);
	virtual ~HostProxy_Xbox();
};

#endif /* USBPROXY_HOSTPROXY_XBOX_H */
