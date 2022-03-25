#ifndef SR_RDT_SENDER_H
#define SR_RDT_SENDER_H
#include "RdtSender.h"
class SRRdtSender : public RdtSender
{
private:
	int sendbase;
	const int N;
	int nextseqnum;
	const int seqrange;
	bool full;
	Packet* packetWaitAck;//�洢û��ȷ�ϵı���
	int* flag;
public:
	SRRdtSender();
	virtual ~SRRdtSender();
	bool getWaitingState();
	bool send(Message &message);
	void receive(Packet &ackPkt);
	void timeoutHandler(int seqNum);
};
#endif

