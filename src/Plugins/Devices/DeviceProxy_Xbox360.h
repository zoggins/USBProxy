/*
 * This file is part of USBProxy.
 */

#ifndef USBPROXY_DEVICEPROXY_XBOX360_H
#define USBPROXY_DEVICEPROXY_XBOX360_H

#include "DeviceProxy_LibUSB.h"

class DeviceProxy_Xbox360: public DeviceProxy_LibUSB {
private:

	const char* manufacturer;
	const char* product;
	const char* serialNumber;

	bool isSN30Pro();

public:
	DeviceProxy_Xbox360(int vendorId = LIBUSB_HOTPLUG_MATCH_ANY, int productId = LIBUSB_HOTPLUG_MATCH_ANY,
			bool includeHubs = false);
	DeviceProxy_Xbox360(ConfigParser *cfg);
	virtual ~DeviceProxy_Xbox360();

protected:
	virtual void set_identity(const char* manufacturer, const char* product, const char* serialNumber);
	virutal bool skip_action(const char* action);


};

#endif /* USBPROXY_DEVICEPROXY_XBOX360_H */
