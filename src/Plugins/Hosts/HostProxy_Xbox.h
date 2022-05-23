/*
 * This file is part of USBProxy.
 */

#ifndef USBPROXY_HOSTPROXY_XBOX_H
#define USBPROXY_HOSTPROXY_XBOX_H

#include "HostProxy_GadgetFS.h"

class HostProxy_Xbox: public HostProxy_GadgetFS {

private:
	static void xbox_aio_send_completion_handler(sigval_t sigval);

protected:

	virtual void handle_USB_REQ_SET_CONFIGURATION();

	virtual bool init_lock();
	virtual void destroy_lock();
	virtual struct aiocb* get_aiocp(int number);
	virtual send_completion_handler ret_free_aio_callback_function();

public:
	HostProxy_Xbox(ConfigParser *cfg);
	virtual ~HostProxy_Xbox();
};

#endif /* USBPROXY_HOSTPROXY_XBOX_H */
