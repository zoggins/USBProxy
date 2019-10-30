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
	rateLocked = false;
	rateLimit = 1;
	roundNum = 0;
	lastNumInFlight = 0;
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
		if (!rateLocked && (roundNum % 100) == 0)
		{
			if (numInFlight < 5)
			{
				rateLocked = true;
			}
			else if (lastNumInFlight > numInFlight)
			{
				rateLocked = true;
			}
			else if (lastNumInFlight == 0 || (lastNumInFlight < numInFlight))
			{
				lastNumInFlight = numInFlight;
				++rateLimit;
			}
		}

		if ((roundNum % rateLimit) == 0)
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
