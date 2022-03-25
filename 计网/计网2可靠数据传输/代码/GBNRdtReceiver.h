#ifndef GBN_RDT_RECEIVER_H
#define GBN_RDT_RECEIVER_H
#include "RdtReceiver.h"
class GBNRdtReceiver :public RdtReceiver
{
private:
	int expectedseqnum;//������һ���������
	Packet lastAckPacket;
	const int seqrange;
public:
	GBNRdtReceiver();
	virtual ~GBNRdtReceiver();
	void receive(Packet &packet);
};

#endif