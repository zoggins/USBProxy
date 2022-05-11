/*
 * This file is part of USBProxy.
 */

#include "PacketFilter_PS4.h"

PacketFilter_PS4::PacketFilter_PS4(ConfigParser *cfg) {
	file  = (FILE *) cfg->get_pointer("PacketFilter_PS4::file");
}

void PacketFilter_PS4::filter_packet(Packet* packet) {
	if (packet->wLength == 64) {
		
	//	for (int i = 0; i < 64; ++i)
	//		for(int j = 0; j < 8; ++j)
	//			fprintf(file, "%d", (packet->data[i] & (1 << j)) != 0);

		fprintf(file, "000000000000000000000");

		fprintf(file,"%d", (packet->data[5] & 0x0F) == 0x07 
				|| (packet->data[5] & 0x0F) == 0x01 
				|| (packet->data[5] & 0x0F) == 0x00);
		fprintf(file,"%d", (packet->data[5] & 0x0F) == 0x05 
				|| (packet->data[5] & 0x0F) == 0x04 
				|| (packet->data[5] & 0x0F) == 0x03);
		fprintf(file,"%d", (packet->data[5] & 0x0F) == 0x07 
				|| (packet->data[5] & 0x0F) == 0x06 
				|| (packet->data[5] & 0x0F) == 0x05);
		fprintf(file,"%d", (packet->data[5] & 0x0F) == 0x03 
				|| (packet->data[5] & 0x0F) == 0x02 
				|| (packet->data[5] & 0x0F) == 0x01);
			
		fprintf(file,"%d%d%d%d", (packet->data[5] & 0b00100000) != 0,
				   (packet->data[5] & 0b01000000) != 0,
			           (packet->data[5] & 0b00010000) != 0,
				   (packet->data[5] & 0b10000000) != 0);	

		fprintf(file,"%d%d%d%d%d%d", (packet->data[6] & 0b00000001) != 0,
				       (packet->data[6] & 0b00000100) != 0,
			               (packet->data[6] & 0b01000000) != 0 ,
				       (packet->data[6] & 0b00000010) != 0,	
				       (packet->data[6] & 0b00001000) != 0,	
				       (packet->data[6] & 0b10000000) != 0);	

		fprintf(file,"%d%d%d%d", (packet->data[6] & 0b00010000) != 0,
				   (packet->data[6] & 0b00100000) != 0,
			           (packet->data[7] & 0b00000001) != 0,
				   (packet->data[7] & 0b00000010) != 0);	

		fprintf(file,"%d%d", (packet->data[35] & 0b10000000) == 0,
			       (packet->data[39] & 0b10000000) == 0);	

		for(int i = 0; i < 8; ++i)
                        fprintf(file, "%d", (packet->data[1] & (1 << i)) != 0);
		for(int i = 0; i < 8; ++i)
                        fprintf(file, "%d", (packet->data[2] & (1 << i)) != 0);
		for(int i = 0; i < 8; ++i)
                        fprintf(file, "%d", (packet->data[3] & (1 << i)) != 0);
		for(int i = 0; i < 8; ++i)
                        fprintf(file, "%d", (packet->data[4] & (1 << i)) != 0);

		for(int i = 0; i < 8; ++i)
                        fprintf(file, "%d", (packet->data[8] & (1 << i)) != 0);
		for(int i = 0; i < 8; ++i)
                        fprintf(file, "%d", (packet->data[9] & (1 << i)) != 0);

		
		int touchpad_x1 = ((packet->data[37] & 0x0F) << 8) | packet->data[36];
                int touchpad_y1 = (packet->data[38] << 4 )| (packet->data[37] & 0xF0);
		int touchpad_x2 = ((packet->data[41] & 0x0F) << 8) | packet->data[40];
                int touchpad_y2 = (packet->data[42] << 4 )| (packet->data[41] & 0xF0);

		for (int i = 0; i < 16; ++i)
			fprintf(file, "%d", ((touchpad_x1 & 0x0FFF) & (1 << i)) != 0);
		for (int i = 0; i < 16; ++i)
			fprintf(file, "%d", ((touchpad_y1 & 0x0FFF) & (1 << i)) != 0);
		for (int i = 0; i < 16; ++i)
			fprintf(file, "%d", ((touchpad_x2 & 0x0FFF) & (1 << i)) != 0);
		for (int i = 0; i < 16; ++i)
			fprintf(file, "%d", ((touchpad_y2 & 0x0FFF) & (1 << i)) != 0);

		fprintf(file, "\n");
	}
}
void PacketFilter_PS4::filter_setup_packet(SetupPacket* packet,bool direction) {
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

static PacketFilter_PS4 *proxy;

extern "C" {
	int plugin_type = PLUGIN_FILTER;
	
	PacketFilter * get_plugin(ConfigParser *cfg) {
		proxy = new PacketFilter_PS4(cfg);
		return (PacketFilter *) proxy;
	}
	
	void destroy_plugin() {
		delete proxy;
	}
}
