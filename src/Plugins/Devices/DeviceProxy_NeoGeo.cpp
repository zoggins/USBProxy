/*
 * This file is part of USBProxy.
 */
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include "DeviceProxy_NeoGeo.h"
#include "TRACE.h"
#include "HexString.h"

static DeviceProxy_NeoGeo *proxy;

extern "C" {
	// for handling events of hotploug.
	int hotplug_callback(struct libusb_context *ctx, struct libusb_device *dev, libusb_hotplug_event envet,
		void *user_data) {
		sleep(1);
		kill(0, SIGHUP);
		return 0;
	}

	DeviceProxy * get_deviceproxy_plugin(ConfigParser *cfg) {
		proxy = new DeviceProxy_Xbox360(cfg);
		return (DeviceProxy *)proxy;
	}

	void destroy_plugin() {
		delete proxy;
	}
}

DeviceProxy_NeoGeo::DeviceProxy_NeoGeo(int vendorId, int productId,bool includeHubs)
	: DeviceProxy_LibUSB(vendorId, productId, includeHubs) 
{

}

DeviceProxy_NeoGeo::DeviceProxy_NeoGeo(ConfigParser *cfg)
	: DeviceProxy_LibUSB(cfg)
{

}

DeviceProxy_NeoGeo::~DeviceProxy_NeoGeo()
{

}

bool DeviceProxy_NeoGeo::swallow_setup_packet_ignore_error(const usb_ctrlrequest* setup_packet)
{
	return return setup_packet->wValue == 0 && setup_packet->wIndex == 0;
}

virtual int DeviceProxy_NeoGeo::num_interfaces(Configuration* cfg)
{
	return 1;
}