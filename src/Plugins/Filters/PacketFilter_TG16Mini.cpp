/*
 * This file is part of USBProxy.
 */

#include "PacketFilter_TG16Mini.h"

PacketFilter_TG16Mini::PacketFilter_TG16Mini(ConfigParser *cfg) {
	file  = (FILE *) cfg->get_pointer("PacketFilter_TG16Mini::file");
}

void PacketFilter_TG16Mini::filter_packet(Packet* packet) {
	if (packet->wLength >= 3) {
		printf("%d%d%d%d%d%d%d%d\n",
			(packet->data[0] & 0b00000010) != 0,
			(packet->data[0] & 0b00000100) != 0,
			(packet->data[1] & 0b00000001) != 0,
			(packet->data[1] & 0b00000010) != 0,
			(packet->data[2] == 0 || packet->data[2] == 1 || packet->data[2] == 7),
			(packet->data[2] == 1 || packet->data[2] == 2 || packet->data[2] == 3),
			(packet->data[2] == 3 || packet->data[2] == 4 || packet->data[2] == 5),
			(packet->data[2] == 5 || packet->data[2] == 6 || packet->data[2] == 7));
	}
}
void PacketFilter_TG16Mini::filter_setup_packet(SetupPacket* packet,bool direction) {
/*	if (packet->ctrl_req.wLength && packet->data) {
		char* hex_setup=hex_string(&(packet->ctrl_req),sizeof(packet->ctrl_req));
		char* hex_data=hex_string((void*)(packet->data),packet->ctrl_req.wLength);
		fprintf(file,"[%s]: %s\n",hex_setup,hex_data);
		free(hex_data);
		free(hex_setup);
	} else {
		char* hex_setup=hex_string(&(packet->ctrl_req),sizeof(packet->ctrl_req));
		fprintf(file,"[%s]\n",hex_setup);
		free(hex_setup);
	}*/
}

static PacketFilter_TG16Mini *proxy;

extern "C" {
	int plugin_type = PLUGIN_FILTER;
	
	PacketFilter * get_plugin(ConfigParser *cfg) {
		proxy = new PacketFilter_TG16Mini(cfg);
		return (PacketFilter *) proxy;
	}
	
	void destroy_plugin() {
		delete proxy;
	}
}
