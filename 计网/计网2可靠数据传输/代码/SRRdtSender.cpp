#include"stdafx.h"
#include "Global.h"
#include "SRRdtSender.h"

SRRdtSender::SRRdtSender() :
	sendbase(0),
	N(WINDOW_SIZE),
	nextseqnum(0),
	full(false),
	seqrange((1 << SEQ_BIT) / WINDOW_SIZE * WINDOW_SIZE)
{
	packetWaitAck = new Packet[WINDOW_SIZE];
	flag = new int[WINDOW_SIZE];
	for (int i = 0; i < WINDOW_SIZE; i++)
	{
		flag[i] = 0;
	}
}
SRRdtSender :: ~SRRdtSender()
{
	delete[] flag;
	delete[] packetWaitAck;
}

bool SRRdtSender::getWaitingState()
{
	return full;//��ʾ�����Ѿ�����
}
//�����ϲ����ʱ����鴰���Ƿ������������������������ϲ��ʱ���ܷ������ݡ�
//�������ݴ�����������кš�У��͵ȱ�־��Ϣ�������ݰ����͵�����㲢�Ҷ�������ݰ�����һ����ʱ����
//SRЭ���ÿһ�����ݰ�����һ��ר�ŵļ�ʱ����
bool SRRdtSender::send(Message &message)
{
	if (full)
	{
		return false;
	}
	else
	{
		packetWaitAck[nextseqnum % N].acknum = -1;
		packetWaitAck[nextseqnum % N].seqnum = nextseqnum;
		packetWaitAck[nextseqnum % N].checksum = 0;
		memcpy(packetWaitAck[nextseqnum % N].payload, message.data, sizeof(message.data));
		packetWaitAck[nextseqnum % N].checksum = pUtils->calculateCheckSum(packetWaitAck[nextseqnum % N]);

		pUtils->printPacket("���ͷ����ͱ���", packetWaitAck[nextseqnum%N]);
		pns->startTimer(SENDER, Configuration::TIME_OUT, nextseqnum);
		pns->sendToNetworkLayer(RECEIVER, packetWaitAck[nextseqnum%N]);
		nextseqnum = (nextseqnum + 1) % seqrange;
		if (nextseqnum == (sendbase + N) % seqrange)
		{
			full = true;
		}
		return true;
	}

}
//����յ�һ��ACK�����ACKδ�𻵲���ACK������ڽ��շ��������ڲ���
//˵�����͵�һ��������ȷ�Ľ��յ��ˣ�����������Ϊ�Ѿ��յ���
//���ACK����ź�send_base��ȣ���ѽ�send_base�ƶ�����һ����δȷ�ϵ���š�
//���򲢲����̻������ڡ�
void SRRdtSender::receive(Packet &ackPkt)
{
	int checksum = pUtils->calculateCheckSum(ackPkt);
	bool inwindow;
	if (sendbase <= nextseqnum)
	{
		inwindow = (sendbase <= ackPkt.acknum) && (ackPkt.acknum < nextseqnum);
	}
	else
	{
		inwindow = (ackPkt.acknum < nextseqnum) || (sendbase <= ackPkt.acknum);
	}

	if ((checksum == ackPkt.checksum) && inwindow)
	{
		pUtils->printPacket("���ͷ���ȷ���յ�ȷ����Ϣ", ackPkt);
		if (flag[ackPkt.acknum%N] == 0)
		{
			pns->stopTimer(SENDER, ackPkt.acknum);
		}
		flag[ackPkt.acknum%N] = 1;//ȷ���յ�
		if (ackPkt.acknum == sendbase)//�ƶ�����
		{
			while (flag[sendbase%N] == 1)
			{
				flag[sendbase%N] = 0;
				sendbase = (sendbase + 1) % seqrange;
			}
			full = false;
		}
	}
}
//���ĳ�����ļ�ʱ����ʱ����ֻ�ش��������������������ļ�ʱ����
void SRRdtSender::timeoutHandler(int seqNum)
{
	printf("���ͷ���ʱ����ʱ���ط�֮ǰ�����ı���\n");

	pns->stopTimer(SENDER, seqNum);
	pUtils->printPacket("���ͷ���ʱ����ʱ�����·���֮ǰ�ı���", packetWaitAck[seqNum%N]);
	pns->startTimer(SENDER, Configuration::TIME_OUT, seqNum);
	pns->sendToNetworkLayer(RECEIVER, packetWaitAck[seqNum%N]);

}