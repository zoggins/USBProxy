/*
 * This file is part of USBProxy.
 */

#ifndef USBPROXY_DEVICEPROXY_PS4_H
#define USBPROXY_DEVICEPROXY_PS4_H

#include "DeviceProxy_LibUSB.h"

class DeviceProxy_PS4: public DeviceProxy_LibUSB {

public:
	DeviceProxy_PS4(int vendorId = LIBUSB_HOTPLUG_MATCH_ANY, int productId = LIBUSB_HOTPLUG_MATCH_ANY,
						bool includeHubs = false);
	DeviceProxy_PS4(ConfigParser *cfg);
	virtual ~DeviceProxy_PS4() {};

protected:
	bool swallow_setup_packet_ignore_error(const usb_ctrlrequest* setup_packet);

};

#endif /* USBPROXY_DEVICEPROXY_PS4_H */
