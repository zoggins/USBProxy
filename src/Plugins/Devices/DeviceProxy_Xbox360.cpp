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
#include "DeviceProxy_Xbox360.h"
#include "TRACE.h"
#include "HexString.h"

static DeviceProxy_Xbox360 *proxy;

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

bool DeviceProxy_Xbox360::isSN30Pro()
{
	return manufacturer != NULL && strcmp(manufacturer, "Controller") == 0
		&& product != NULL && strcmp(product, "Controller") == 0
		&& serialNumber != NULL && strcmp(serialNumber, "Controller") == 0;
		
}

DeviceProxy_Xbox360::DeviceProxy_Xbox360(int vendorId, int productId,bool includeHubs) 
	: DeviceProxy_LibUSB(vendorId, productId, includeHubs) 
{
	manufacturer = NULL;
	product = NULL;
	serialNumber = NULL;
}

DeviceProxy_Xbox360::DeviceProxy_Xbox360(ConfigParser *cfg) 
	: DeviceProxy_LibUSB(cfg)
{
	manufacturer = NULL;
	product = NULL;
	serialNumber = NULL;
}

DeviceProxy_Xbox360::~DeviceProxy_Xbox360()
{
	free((void*)manufacturer);
	free((void*)product);
	free((void*)serialNumber);
}

void DeviceProxy_Xbox360::set_identity(const char* manufacturer, const char* product, const char* serialNumber)
{
	if (this->manufacturer == NULL)	
		this->manufacturer = manufacturer;
	if (this->product == NULL)
		this->product = product;	
	if (this->serialNumber == NULL)
		this->serialNumber = serialNumber;
}

bool DeviceProxy_Xbox360::skip_action(const char* action)
{
	if (strcmp(action, "AddInterfaceString") == 0)
		return isSN30Pro();

	return false;
}