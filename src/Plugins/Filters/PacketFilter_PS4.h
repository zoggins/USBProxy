/*
 * This file is part of USBProxy.
 */

#ifndef PACKETFILTER_PS4_H_
#define PACKETFILTER_PS4_H_

#include "PacketFilter.h"

//writes all traffic to a stream
class PacketFilter_PS4 : public PacketFilter {
private:
	FILE* file;
public:
	PacketFilter_PS4(ConfigParser *cfg);
	void filter_packet(Packet* packet);
	void filter_setup_packet(SetupPacket* packet,bool direction);
	virtual char* toString() {return (char*)"PS4 Filter";}
};
#endif /* PACKETFILTER_PS4_H_ */
