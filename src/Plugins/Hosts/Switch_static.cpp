/*
 * This file is part of USBProxy.
 */

#include "HostProxy_Switch.h"

static HostProxy_Switch *proxy;

extern "C" {
	HostProxy * get_hostproxy_plugin(ConfigParser *cfg) {
		proxy = new HostProxy_Switch(cfg);
		return (HostProxy *) proxy;
	}
	
	void destroy_plugin() {
		delete proxy;
	}
}
