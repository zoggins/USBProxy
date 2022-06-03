/*
 * This file is part of USBProxy.
 */

#ifndef PACKETFILTER_A500_H_
#define PACKETFILTER_A500_H_

#include "PacketFilter.h"

//writes all traffic to a stream
class PacketFilter_A500 : public PacketFilter {
private:
	FILE* file;
	char buffer[41];
public:
	PacketFilter_A500(ConfigParser *cfg);
	void filter_packet(Packet* packet);
	void filter_setup_packet(SetupPacket* packet,bool direction);
	virtual char* toString() {return (char*)"A500 Filter";}
};
#endif /* PACKETFILTER_A500_H_ */
