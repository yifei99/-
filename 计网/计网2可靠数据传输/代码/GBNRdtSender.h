#ifndef GBN_RDT_SENDER_H
#define GBN_RDT_SENDER_H
#include "RdtSender.h"
class GBNRdtSender :public RdtSender
{
private:
	const int N;//���ڳ���
	int base;//����ţ�����δȷ�Ϸ�������
	int nextseqnum;//��һ��������������
	const int seqrange;//��ŵķ�Χ
	bool full;//�����Ƿ���
	Packet* PacketWaitAck;
public:
	bool send(Message &message);						//����Ӧ�ò�������Message����NetworkService����,������ͷ��ɹ��ؽ�Message���͵�����㣬����true;�����Ϊ���ͷ����ڵȴ�ȷ��״̬���ʹ����������ܾ�����Message���򷵻�false
	void receive(Packet &ackPkt);						//����ȷ��Ack������NetworkService����	
	void timeoutHandler(int seqNum);					//Timeout handler������NetworkService����
	bool getWaitingState();
	GBNRdtSender();
	virtual ~GBNRdtSender();
};

#endif