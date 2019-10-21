/*
 * This file is part of USBProxy.
 */

#ifndef PACKETFILTER_PS3_H_
#define PACKETFILTER_PS3_H_

#include "PacketFilter.h"

//writes all traffic to a stream
class PacketFilter_PS3 : public PacketFilter {
private:
	FILE* file;
public:
	PacketFilter_PS3(ConfigParser *cfg);
	void filter_packet(Packet* packet);
	void filter_setup_packet(SetupPacket* packet,bool direction);
	virtual char* toString() {return (char*)"PS3 Log Filter";}
};
#endif /* PACKETFILTER_PS3_H_ */
