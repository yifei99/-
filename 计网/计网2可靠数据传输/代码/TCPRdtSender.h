#ifndef TCP_SENDER_H
#define TCP_SENDER_H
#include "RdtSender.h"
class TCPRdtSender :public RdtSender
{
private:
	int sendbase;
	const int N;
	const int seqrange;
	int nextseqnum;
	bool full;
	Packet* PacketWaitAck;
	int OverAck;//��¼����ACK
public:

	bool getWaitingState();
	bool send(Message &message);						//����Ӧ�ò�������Message����NetworkServiceSimulator����,������ͷ��ɹ��ؽ�Message���͵�����㣬����true;�����Ϊ���ͷ����ڵȴ���ȷȷ��״̬���ܾ�����Message���򷵻�false
	void receive(Packet &ackPkt);						//����ȷ��Ack������NetworkServiceSimulator����	
	void timeoutHandler(int seqNum);					//Timeout handler������NetworkServiceSimulator����

public:
	TCPRdtSender();
	virtual ~TCPRdtSender();
};

#endif

