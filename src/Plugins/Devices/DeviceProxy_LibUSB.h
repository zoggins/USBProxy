/*
 * This file is part of USBProxy.
 */

#ifndef USBPROXY_DEVICEPROXY_LIBUSB_H
#define USBPROXY_DEVICEPROXY_LIBUSB_H

#ifndef LIBUSB_HOTPLUG_MATCH_ANY
#define LIBUSB_HOTPLUG_MATCH_ANY -1
#endif

#include <libusb-1.0/libusb.h>
#include "DeviceProxy.h"

#include <vector>

class DeviceProxy_LibUSB: public DeviceProxy {
private:
	libusb_context* context;
	libusb_hotplug_callback_handle callback_handle;
	libusb_device_handle* dev_handle;
	bool privateContext;
	bool privateDevice;
	int desired_vid;
	int desired_pid;
	bool desired_hubs;

	struct
	{
		uint8_t interface;
		bool defined;
		bool claimed;
	} epInterfaces[0x10];

	bool endpoint_interface_claimed(uint8_t endpoint);

protected:
	virtual int control_request_timeout_override(int timeout);
	virtual bool swallow_setup_packet_send_error(const usb_ctrlrequest* setup_packet);
	virtual bool swallow_setup_packet_ignore_error(const usb_ctrlrequest* setup_packet);
	virtual int check_device_response(libusb_device_handle* dev_handle);
	virtual void set_identity(const char* manufacturer, const char* product, const char* serialNumber);
	virtual bool skip_action(const char* action);
	virtual bool ignore_endpoints(uint8_t endpoint);
	virtual void patch_ctrlrequest_response(const usb_ctrlrequest *setup_packet, int* rc, unsigned char* dataptr);


public:
	DeviceProxy_LibUSB(int vendorId = LIBUSB_HOTPLUG_MATCH_ANY, int productId = LIBUSB_HOTPLUG_MATCH_ANY,
			bool includeHubs = false);
	DeviceProxy_LibUSB(ConfigParser *cfg);
	virtual ~DeviceProxy_LibUSB();

	int connect(int timeout = 250);
	int connect(int vendorId, int productId, bool includeHubs);
	int connect(libusb_device* dvc, libusb_context* _context = NULL);
	int connect(libusb_device_handle* devh, libusb_context* _context = NULL);
	void disconnect();
	void reset();
	bool is_connected();
	bool is_highspeed();

	int control_request(const usb_ctrlrequest *setup_packet, int *nbytes, uint8_t* dataptr, int timeout = 500);
	void send_data(uint8_t endpoint, uint8_t attributes, uint16_t maxPacketSize, uint8_t* dataptr, int length);
	void receive_data(uint8_t endpoint, uint8_t attributes, uint16_t maxPacketSize, uint8_t** dataptr, int* length,
			int timeout = 500);

	void setConfig(Configuration* fs_cfg, Configuration* hs_cfg, bool hs) {
	}

	void set_endpoint_interface(uint8_t endpoint, uint8_t interface);
	void claim_interface(uint8_t interface);
	void release_interface(uint8_t interface);
	int num_interfaces(Configuration* cfg);

	uint8_t get_address();
	char* toString();
};

#endif /* USBPROXY_DEVICEPROXY_LIBUSB_H */
