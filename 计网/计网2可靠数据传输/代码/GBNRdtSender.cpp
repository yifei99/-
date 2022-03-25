#include "stdafx.h"
#include "Global.h"
#include "GBNRdtSender.h"

GBNRdtSender::GBNRdtSender() :
	N(WINDOW_SIZE),
	base(0),
	nextseqnum(0),
	PacketWaitAck(new Packet[WINDOW_SIZE]),
	full(false),
	seqrange((1 << SEQ_BIT) / WINDOW_SIZE * WINDOW_SIZE)
{
}

GBNRdtSender::~GBNRdtSender()
{
	delete[] PacketWaitAck;
}
//�����ϲ�ĵ���ʱ��GBNЭ���ȼ��鴰���Ƿ��������������������ϲ���Բ��ܷ�������
//���û�����ϲ㴫�ݹ��������ݴ���������ݰ��������кź�������־��Ϣ�������͵�����㡣
//GBNЭ��ֻ��send_baseһ��������м�ʱ�������ͷ������ŵ���send_baseʱ��������ʱ��������������ʱ����
bool GBNRdtSender::send(Message &message)//����Ӧ�ò�������Message����NetworkService����,������ͷ��ɹ��ؽ�Message���͵�����㣬����true;�����Ϊ���ͷ����ڵȴ�ȷ��״̬���ʹ����������ܾ�����Message���򷵻�false
{
	if (full)
	{
		return false;
	}
	else
	{
		PacketWaitAck[nextseqnum%N].seqnum = nextseqnum;
		PacketWaitAck[nextseqnum % N].acknum = -1;
		PacketWaitAck[nextseqnum%N].checksum = 0;
		memcpy(PacketWaitAck[nextseqnum%N].payload, message.data, sizeof(message.data));
		PacketWaitAck[nextseqnum%N].checksum = pUtils->calculateCheckSum(PacketWaitAck[nextseqnum%N]);
		pUtils->printPacket("���ͷ����ͱ���", PacketWaitAck[nextseqnum%N]);
		if (base == nextseqnum)
		{
			pns->startTimer(SENDER, Configuration::TIME_OUT, base);
		}
		pns->sendToNetworkLayer(RECEIVER, PacketWaitAck[nextseqnum%N]);
		nextseqnum = (nextseqnum + 1) % seqrange;
		if (nextseqnum == ((base + N) % seqrange))//����֮�󴰿�����
		{
			full = true;
		}
		return true;
	}
}
//�յ�һ��ACK������յ�����ACKδ�𻵲��ҵ�ACk����send_base����ô��Ҫ��������ǰ����������send_base���������ü�ʱ��
void GBNRdtSender::receive(Packet &ackPkt)//����ȷ��Ack������NetworkService����	
{
	int checksum = pUtils->calculateCheckSum(ackPkt);
	bool ackinwindows;//�յ���ack����Ƿ��ڴ�����
	if (base <= nextseqnum)
	{
		ackinwindows = (base <= ackPkt.acknum) && (ackPkt.acknum < nextseqnum);
	}
	else
	{
		ackinwindows = (ackPkt.acknum < nextseqnum) || (ackPkt.acknum >= base);
	}

	if (checksum == ackPkt.checksum && ackinwindows)
	{
		int bases = base;
		if ((ackPkt.acknum + 1) % seqrange != base)//������˵�����յ�����һ������ack
		{
			pUtils->printPacket("���յ�����ȷ�յ�ȷ��", ackPkt);
			base = (ackPkt.acknum + 1) % seqrange;//��������
			full = false;
		}
		if (base == nextseqnum)//�������
		{
			pns->stopTimer(SENDER, bases);//ֹͣ��ʱ��
		}
		else//������ʱ��
		{
			pns->stopTimer(SENDER, bases);
			pns->startTimer(SENDER, Configuration::TIME_OUT, base);
		}
	}


}
//������ʱʱ���Ͱ�[send_base,next_seqnum-1]��Χ�ڵ��������ݰ����·���һ�顣
//PacketWaitAck�����洢�Ѿ����͵���û��ȷ�ϵ����ݰ�
void GBNRdtSender::timeoutHandler(int seqNum)			//Timeout handler������NetworkService����
{
	int i;
	printf("���ͷ���ʱ����ʱ���ط�֮ǰ���͵ı���\n");
	pns->stopTimer(SENDER, base);
	pns->startTimer(SENDER, Configuration::TIME_OUT, base);
	if (base <= nextseqnum)
	{
		for (i = base; i < nextseqnum; i++)
		{
			pUtils->printPacket("���ͷ���ʱ��ʱ�䵽�����·���֮ǰ�ı���", PacketWaitAck[i%N]);
			pns->sendToNetworkLayer(RECEIVER, PacketWaitAck[i%N]);
		}
	}
	else
	{
		for (i = base; i < seqrange; i++)
		{
			pUtils->printPacket("���ͷ���ʱ��ʱ�䵽�����·���֮ǰ�ı���", PacketWaitAck[i%N]);
			pns->sendToNetworkLayer(RECEIVER, PacketWaitAck[i%N]);
		}
		for (i = 0; i < nextseqnum; i++)
		{
			pUtils->printPacket("���ͷ���ʱ��ʱ�䵽�����·���֮ǰ�ı���", PacketWaitAck[i%N]);
			pns->sendToNetworkLayer(RECEIVER, PacketWaitAck[i%N]);
		}
	}

}
bool GBNRdtSender::getWaitingState()
{
	return full;

}
