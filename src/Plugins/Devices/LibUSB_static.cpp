/*
 * This file is part of USBProxy.
 */
#include "DeviceProxy_LibUSB.h"
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

static DeviceProxy_LibUSB *proxy;

extern "C" {
	// for handling events of hotploug.
	int hotplug_callback(struct libusb_context *ctx, struct libusb_device *dev, libusb_hotplug_event envet,
		void *user_data) {
		sleep(1);
		kill(0, SIGHUP);
		return 0;
	}

	DeviceProxy * get_deviceproxy_plugin(ConfigParser *cfg) {
		proxy = new DeviceProxy_LibUSB(cfg);
		return (DeviceProxy *)proxy;
	}

	void destroy_plugin() {
		delete proxy;
	}
}
