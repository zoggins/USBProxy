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
#include "DeviceProxy_Xbox.h"
#include "TRACE.h"
#include "HexString.h"

static DeviceProxy_Xbox *proxy;

extern "C" {
	// for handling events of hotploug.
	int hotplug_callback(struct libusb_context *ctx, struct libusb_device *dev, libusb_hotplug_event envet,
		void *user_data) {
		sleep(1);
		kill(0, SIGHUP);
		return 0;
	}

	DeviceProxy * get_deviceproxy_plugin(ConfigParser *cfg) {
		proxy = new DeviceProxy_Xbox(cfg);
		return (DeviceProxy *)proxy;
	}

	void destroy_plugin() {
		delete proxy;
	}
}

DeviceProxy_Xbox::DeviceProxy_Xbox(int vendorId = LIBUSB_HOTPLUG_MATCH_ANY, int productId = LIBUSB_HOTPLUG_MATCH_ANY,
	bool includeHubs = false) : DeviceProxy_LibUSB(vendorId, productId, includeHubs) {}

DeviceProxy_Xbox::DeviceProxy_Xbox(ConfigParser *cfg) : DeviceProxy_LibUSB(cfg) {}

int DeviceProxy_Xbox::control_request_timeout_override(int timeout)
{
	return 10;
}

bool DeviceProxy_Xbox::swallow_setup_packet_send_error(const usb_ctrlrequest* setup_packet)
{
	return setup_packet->wValue == 768;
}

int DeviceProxy_Xbox::check_device_response(libusb_device_handle* dev_handle)
{
	return 0;
}
