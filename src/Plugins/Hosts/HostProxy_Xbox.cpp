/*
 * This file is part of USBProxy.
 */

#include "HostProxy_Xbox.h"

#include <cstring>
#include <iostream>

#include <unistd.h>
#include <poll.h>
#include <math.h>

#include "GadgetFS_helpers.h"
#include "errno.h"
#include "TRACE.h"
#include "HexString.h"

#include "DeviceQualifier.h"
#include "Configuration.h"
#include "Interface.h"
#include "Endpoint.h"

pthread_mutex_t HostProxy_Xbox::lock;

void HostProxy_Xbox::xbox_aio_send_completion_handler(sigval _sigval)
{
	struct aiocb* aio;
	aio = (struct aiocb*)_sigval.sival_ptr;
	pthread_mutex_lock(&lock);
	if (aio->aio_buf != NULL)
	{
		free((void*)aio->aio_buf);
		aio->aio_buf = NULL;
	}
	pthread_mutex_unlock(&lock);

}

HostProxy_Xbox::HostProxy_Xbox(ConfigParser *cfg)
	: HostProxy_GadgetFS(cfg)
{
}

HostProxy_Xbox::~HostProxy_Xbox() {
	
}

void HostProxy_Xbox::handle_USB_REQ_SET_CONFIGURATION()
{
	return;
}

bool HostProxy_Xbox::init_lock()
{
	if (pthread_mutex_init(&lock, NULL) != 0)
	{
		fprintf(stderr, "mutex init has failed\n");
		return false;
	}

	return true;
}

void HostProxy_Xbox::destroy_lock()
{
	pthread_mutex_destroy(&lock);
}

struct aiocb* HostProxy_Xbox::get_aiocp(int number)
{
	aiocb* aio = p_epin_async[number];

	pthread_mutex_lock(&lock);
	if (aio->aio_buf != NULL)
	{
		free((void*)aio->aio_buf);
		aio->aio_buf = NULL;
	}
	pthread_mutex_unlock(&lock);

	return aio;
}

send_completion_handler HostProxy_Xbox::ret_free_aio_callback_function()
{
	return &xbox_aio_send_completion_handler;
}

static HostProxy_Xbox *proxy;

extern "C" {
	HostProxy * get_hostproxy_plugin(ConfigParser *cfg) {
		proxy = new HostProxy_Xbox(cfg);
		return (HostProxy *) proxy;
	}
	
	void destroy_plugin() {
		delete proxy;
	}
}
