/*
 * This file is part of USBProxy.
 */

#ifndef USBPROXY_DEVICEPROXY_XBOX_H
#define USBPROXY_DEVICEPROXY_XBOX_H

#include "DeviceProxy_LibUSB.h"

class DeviceProxy_Xbox: public DeviceProxy_LibUSB {

public:
	DeviceProxy_Xbox(int vendorId = LIBUSB_HOTPLUG_MATCH_ANY, int productId = LIBUSB_HOTPLUG_MATCH_ANY,
						bool includeHubs = false);
	DeviceProxy_Xbox(ConfigParser *cfg);
	virtual ~DeviceProxy_Xbox() {};

protected:
	virtual int control_request_timeout_override(int timeout);
	virtual bool swallow_setup_packet_send_error(const usb_ctrlrequest* setup_packet);
	virtual int check_device_response(libusb_device_handle* dev_handle);

};

#endif /* USBPROXY_DEVICEPROXY_XBOX_H */
