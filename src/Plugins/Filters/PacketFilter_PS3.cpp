/*
 * This file is part of USBProxy.
 */

#include "HexString.h"
#include "PacketFilter_PS3.h"

PacketFilter_PS3::PacketFilter_PS3(ConfigParser *cfg) {
	file  = (FILE *) cfg->get_pointer("PacketFilter_PS3::file");
}

void PacketFilter_PS3::filter_packet(Packet* packet) {
	if (packet->wLength == 49 && packet->bEndpoint == 0x81) {
		
		// digital buttons
		for (int j = 2; j < 5; ++j)
			for (int i = 0; i < 8; ++i)
				fprintf(file, "%d", (packet->data[j] & (1 << i)) != 0);

		// sticks
		for (int j = 6; j < 10; ++j)
			for (int i = 0; i < 8; ++i)
				fprintf(file, "%d", (packet->data[j] & (1 << i)) != 0);
 
		// analog buttons
		for (int j = 14; j < 26; ++j)
			for (int i = 0; i < 8; ++i)
				fprintf(file, "%d", (packet->data[j] & (1 << i)) != 0);

		fprintf(file, "\n");
	}
}
void PacketFilter_PS3::filter_setup_packet(SetupPacket* packet,bool direction) {
	//if (packet->ctrl_req.wLength && packet->data) {
	//	char* hex_setup=hex_string(&(packet->ctrl_req),sizeof(packet->ctrl_req));
	//	char* hex_data=hex_string((void*)(packet->data),packet->ctrl_req.wLength);
	//	fprintf(file,"[%s]: %s\n",hex_setup,hex_data);
	//	free(hex_data);
	//	free(hex_setup);
	//} else {
	//	char* hex_setup=hex_string(&(packet->ctrl_req),sizeof(packet->ctrl_req));
	//	fprintf(file,"[%s]\n",hex_setup);
	//	free(hex_setup);
	//}
}

static PacketFilter_PS3 *proxy;

extern "C" {
	int plugin_type = PLUGIN_FILTER;
	
	PacketFilter * get_plugin(ConfigParser *cfg) {
		proxy = new PacketFilter_PS3(cfg);
		return (PacketFilter *) proxy;
	}
	
	void destroy_plugin() {
		delete proxy;
	}
}
