#ifndef SR_RDT_RECEIVER_H
#define SR_RDT_RECEIVER_H
#include "RdtReceiver.h"
class SRRdtReceiver : public RdtReceiver
{
	int rcvbase;//��һ��ϣ���յ��ı��ı��
	const int N;
	const int seqrange;
	Packet lastAckPacket;
	Packet* const PacketReceived;//�洢�������Ѿ��յ���packet
	int* const flag;//��ʶpacketReceived�������Ƿ�����Ч��

	bool inwindow(int num);
	bool oldpacket(int num);

public:
	SRRdtReceiver();
	virtual ~SRRdtReceiver();
	void receive(Packet &packet);
};

#endif


