/*
 * This file is part of USBProxy.
 */

#include "HexString.h"
#include "PacketFilter_Xbox.h"

PacketFilter_Xbox::PacketFilter_Xbox(ConfigParser *cfg) {
	file  = (FILE *) cfg->get_pointer("PacketFilter_Xbox::file");
}

void PacketFilter_Xbox::filter_packet(Packet* packet) {
	if (packet->wLength<=64) {
		char* hex=hex_string((void*)packet->data,packet->wLength);
		fprintf(file,"%02x[%d]: %s\n",packet->bEndpoint,packet->wLength,hex);
		free(hex);
	}
}
void PacketFilter_Xbox::filter_setup_packet(SetupPacket* packet,bool direction) {
	return;
}

static PacketFilter_Xbox *proxy;

extern "C" {
	int plugin_type = PLUGIN_FILTER;
	
	PacketFilter * get_plugin(ConfigParser *cfg) {
		proxy = new PacketFilter_Xbox(cfg);
		return (PacketFilter *) proxy;
	}
	
	void destroy_plugin() {
		delete proxy;
	}
}
