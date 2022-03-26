/*
 * This file is part of USBProxy.
 */

#ifndef USBPROXY_DEVICEPROXY_EVS_H
#define USBPROXY_DEVICEPROXY_EVS_H

#include "DeviceProxy_LibUSB.h"

class DeviceProxy_EVS: public DeviceProxy_LibUSB {

public:
	DeviceProxy_EVS(int vendorId = LIBUSB_HOTPLUG_MATCH_ANY, int productId = LIBUSB_HOTPLUG_MATCH_ANY,
						bool includeHubs = false);
	DeviceProxy_EVS(ConfigParser *cfg);
	virtual ~DeviceProxy_EVS() {};

protected:
	bool swallow_setup_packet_ignore_error(const usb_ctrlrequest* setup_packet);
	bool ignore_endpoints(uint8_t endpoint);

};

#endif /* USBPROXY_DEVICEPROXY_EVS_H */
