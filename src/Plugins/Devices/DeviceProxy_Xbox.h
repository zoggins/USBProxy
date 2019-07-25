/*
 * This file is part of USBProxy.
 */

#ifndef USBPROXY_DEVICEPROXY_XBOX_H
#define USBPROXY_DEVICEPROXY_XBOX_H

#include "DeviceProxy_LibUSB.h"

class DeviceProxy_Xbox: public DeviceProxy_LibUSB {
protected:
	virtual int control_request_timeout_override(int timeout)
	{
		return 5;
	}

	virtual bool swallow_setup_packet_send_error(const usb_ctrlrequest* setup_packet)
	{
		return setup_packet->wValue == 768;
	}

	virtual int check_device_response(libusb_device_handle* dev_handle)
	{
		// Need to actually think of a way to do this for the xbox
		return 0;
	}

public:
	DeviceProxy_Xbox(int vendorId = LIBUSB_HOTPLUG_MATCH_ANY, int productId = LIBUSB_HOTPLUG_MATCH_ANY,
		bool includeHubs = false) : DeviceProxy_LibUSB(vendorId, productId, includeHubs) {}
	DeviceProxy_Xbox(ConfigParser *cfg) : DeviceProxy_LibUSB(cfg) {} 
	virtual ~DeviceProxy_Xbox() {};
};

#endif /* USBPROXY_DEVICEPROXY_XBOX_H */
