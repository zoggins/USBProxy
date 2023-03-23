/*
 * This file is part of USBProxy.
 */

#include "HostProxy_PS4.h"

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

HostProxy_PS4::HostProxy_PS4(ConfigParser *cfg)
	: HostProxy_GadgetFS(cfg)
{
}

HostProxy_PS4::~HostProxy_PS4() {
	
}

void HostProxy_PS4::handle_USB_REQ_SET_CONFIGURATION()
{
	return;
}
static HostProxy_PS4 *proxy;

extern "C" {
	HostProxy * get_hostproxy_plugin(ConfigParser *cfg) {
		proxy = new HostProxy_PS4(cfg);
		return (HostProxy *) proxy;
	}
	
	void destroy_plugin() {
		delete proxy;
	}
}
