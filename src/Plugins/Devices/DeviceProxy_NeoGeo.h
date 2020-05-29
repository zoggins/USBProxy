/*
 * This file is part of USBProxy.
 */

#ifndef USBPROXY_DEVICEPROXY_NEOGEO_H
#define USBPROXY_DEVICEPROXY_NEOGEO_H

#include "DeviceProxy_LibUSB.h"

class DeviceProxy_NeoGeo: public DeviceProxy_LibUSB {

public:
	DeviceProxy_NeoGeo(int vendorId = LIBUSB_HOTPLUG_MATCH_ANY, int productId = LIBUSB_HOTPLUG_MATCH_ANY,
			bool includeHubs = false);
	DeviceProxy_NeoGeo(ConfigParser *cfg);
	virtual ~DeviceProxy_NeoGeo();

protected:
	virtual bool swallow_setup_packet_ignore_error(const usb_ctrlrequest* setup_packet);
	virtual int num_interfaces(Configuration* cfg);


};

#endif /* USBPROXY_DEVICEPROXY_XBOX360_H */
