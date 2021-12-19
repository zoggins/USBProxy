/*
 * This file is part of USBProxy.
 */

#ifndef PACKETFILTER_VCS_H_
#define PACKETFILTER_VCS_H_

#include "PacketFilter.h"

//writes all traffic to a stream
class PacketFilter_VCS : public PacketFilter {
private:
	FILE* file;
	char buffer[41];
public:
	PacketFilter_VCS(ConfigParser *cfg);
	void filter_packet(Packet* packet);
	void filter_setup_packet(SetupPacket* packet,bool direction);
	virtual char* toString() {return (char*)"VCS Filter";}
};
#endif /* PACKETFILTER_VCS_H_ */
