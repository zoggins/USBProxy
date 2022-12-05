/*
 * This file is part of USBProxy.
 */

#include "HostProxy_GenMini.h"

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

HostProxy_GenMini::HostProxy_GenMini(ConfigParser *cfg)
	: HostProxy_Switch(cfg)
{ }

HostProxy_GenMini::~HostProxy_GenMini() {}

int HostProxy_GenMini::send_descriptor(int p_device_file, char* descriptor, int descriptorLength, Device* device)
{
	char* orig_descriptor = new char[descriptorLength];
	memcpy(orig_descriptor, descriptor, descriptorLength);

	// find start of high speed descriptor
	int pos = 4;
	int numCfg = orig_descriptor[descriptorLength-1];
	int numIntr;
	int numEndpoints;

	for (int x = 0; x < 2; ++x)
	{
		// process configs
		for(int i = 0; i < numCfg; ++i)
		{
			numIntr = orig_descriptor[pos+4];
			pos += orig_descriptor[pos];
		
			// process interfaces
			for(int j = 0; j < numIntr; ++j)
			{
				numEndpoints = orig_descriptor[pos+4];
				pos += orig_descriptor[pos];

				// eat the HID
				pos += orig_descriptor[pos];

				// process endpoints
				for(int k = 0; k < numEndpoints; ++k)
				{
					pos+= orig_descriptor[pos];
				}
			}

		}

		if (x == 0)
		{
			descriptorLength = pos;
			memcpy(descriptor, orig_descriptor, descriptorLength);
		} 
	}
	
	char* newDeviceDescriptorPos = &descriptor[descriptorLength];
	descriptorLength += orig_descriptor[pos];
	memcpy(newDeviceDescriptorPos, &orig_descriptor[pos], orig_descriptor[pos]);

	return write(p_device_file, descriptor, descriptorLength);
}

static HostProxy_GenMini *proxy;

extern "C" {
	HostProxy * get_hostproxy_plugin(ConfigParser *cfg) {
		proxy = new HostProxy_GenMini(cfg);
		return (HostProxy *) proxy;
	}
	
	void destroy_plugin() {
		delete proxy;
	}
}
