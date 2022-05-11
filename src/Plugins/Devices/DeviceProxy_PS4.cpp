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
#include "DeviceProxy_PS4.h"
#include "TRACE.h"
#include "HexString.h"

static DeviceProxy_PS4 *proxy;

extern "C" {
	// for handling events of hotploug.
	int hotplug_callback(struct libusb_context *ctx, struct libusb_device *dev, libusb_hotplug_event envet,
		void *user_data) {
		sleep(1);
		kill(0, SIGHUP);
		return 0;
	}

	DeviceProxy * get_deviceproxy_plugin(ConfigParser *cfg) {
		proxy = new DeviceProxy_PS4(cfg);
		return (DeviceProxy *)proxy;
	}

	void destroy_plugin() {
		delete proxy;
	}
}

DeviceProxy_PS4::DeviceProxy_PS4(int vendorId, int productId, bool includeHubs) 
	: DeviceProxy_LibUSB(vendorId, productId, includeHubs) {}

DeviceProxy_PS4::DeviceProxy_PS4(ConfigParser *cfg) 
	: DeviceProxy_LibUSB(cfg) {}

bool DeviceProxy_PS4::swallow_setup_packet_ignore_error(const usb_ctrlrequest* setup_packet)
{
	return setup_packet->bRequestType == 129;
}

