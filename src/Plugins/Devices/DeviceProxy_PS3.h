/*
 * This file is part of USBProxy.
 */

#ifndef USBPROXY_DEVICEPROXY_PS3_H
#define USBPROXY_DEVICEPROXY_PS3_H

#include "DeviceProxy_LibUSB.h"

class DeviceProxy_PS3: public DeviceProxy_LibUSB {

public:
	DeviceProxy_PS3(int vendorId = LIBUSB_HOTPLUG_MATCH_ANY, int productId = LIBUSB_HOTPLUG_MATCH_ANY,
			bool includeHubs = false);
	DeviceProxy_PS3(ConfigParser *cfg);
	virtual ~DeviceProxy_PS3();

protected:
	virtual bool swallow_setup_packet_ignore_error(const usb_ctrlrequest* setup_packet);

};

#endif /* USBPROXY_DEVICEPROXY_PS3_H */
