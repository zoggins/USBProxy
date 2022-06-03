/*
 * This file is part of USBProxy.
 */

#ifndef PACKETFILTER_EVS_H_
#define PACKETFILTER_EVS_H_

#include "PacketFilter.h"

//writes all traffic to a stream
class PacketFilter_EVS : public PacketFilter {
private:
	FILE* file;
	char buffer[41];
public:
	PacketFilter_EVS(ConfigParser *cfg);
	void filter_packet(Packet* packet);
	void filter_setup_packet(SetupPacket* packet,bool direction);
	virtual char* toString() {return (char*)"EVS Filter";}
};
#endif /* PACKETFILTER_EVS_H_ */
