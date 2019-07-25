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
