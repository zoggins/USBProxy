/*
 * This file is part of USBProxy.
 */

#include "HostProxy_GadgetFS.h"

static HostProxy_GadgetFS *proxy;

extern "C" {
	HostProxy * get_hostproxy_plugin(ConfigParser *cfg) {
		proxy = new HostProxy_GadgetFS(cfg);
		return (HostProxy *) proxy;
	}
	
	void destroy_plugin() {
		delete proxy;
	}
}
