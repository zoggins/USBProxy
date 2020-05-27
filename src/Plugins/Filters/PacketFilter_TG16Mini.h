/*
 * This file is part of USBProxy.
 */

#ifndef PACKETFILTER_TG16MINI_H_
#define PACKETFILTER_TG16MINI_H_

#include "PacketFilter.h"

//writes all traffic to a stream
class PacketFilter_TG16Mini : public PacketFilter {
private:
	FILE* file;
public:
	PacketFilter_TG16Mini(ConfigParser *cfg);
	void filter_packet(Packet* packet);
	void filter_setup_packet(SetupPacket* packet,bool direction);
	virtual char* toString() {return (char*)"TG16 Mini Filter";}
};
#endif /* PACKETFILTER_TG16MINI_H_ */
