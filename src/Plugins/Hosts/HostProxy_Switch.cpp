/*
 * This file is part of USBProxy.
 */

#include "HostProxy_Switch.h"

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

HostProxy_Switch::HostProxy_Switch(ConfigParser *cfg)
	: HostProxy_GadgetFS(cfg)
{
	roundNum = 0;
}

HostProxy_Switch::~HostProxy_Switch() {}

bool HostProxy_Switch::do_not_send(__u8 endpoint, int* length)
{
	// Switch can't seem to handle high-speed transfers, which we convert
	// everything to high speed because gadgetfs is weird.
	// So here is a simple rate limiter that seems to work.

	if (endpoint == 0x81)
	{
		roundNum++;
		if (roundNum <= 100 || (roundNum % 4) == 0)
		{
			return false;
		}
		else
		{
			*length = 0;
			return true;
		}
	}

	return false;
}

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
