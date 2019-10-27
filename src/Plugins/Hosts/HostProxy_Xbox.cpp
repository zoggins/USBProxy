/*
 * This file is part of USBProxy.
 */

#include "HostProxy_Xbox.h"

#include <cstring>
#include <iostream>

#include <unistd.h>
#include <poll.h>
#include <math.h>

#include "GadgetFS_helpers.h"
#include "errno.h"
#include "TRACE.h"
#include "HexString.h"

#include "DeviceQualifier.h"
#include "Configuration.h"
#include "Interface.h"
#include "Endpoint.h"


HostProxy_Xbox::HostProxy_Xbox(ConfigParser *cfg)
	: HostProxy_GadgetFS(cfg)
{
}

HostProxy_Xbox::~HostProxy_Xbox() {
	
}

void HostProxy_Xbox::handle_USB_REQ_SET_CONFIGURATION()
{
	return;
}

static HostProxy_Xbox *proxy;

extern "C" {
	HostProxy * get_hostproxy_plugin(ConfigParser *cfg) {
		proxy = new HostProxy_Xbox(cfg);
		return (HostProxy *) proxy;
	}
	
	void destroy_plugin() {
		delete proxy;
	}
}
