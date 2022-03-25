#include"stdafx.h"
#include "Global.h"
#include "TCPRdtSender.h"

TCPRdtSender::TCPRdtSender() :
	sendbase(0),
	seqrange((1 << SEQ_BIT) / WINDOW_SIZE * WINDOW_SIZE),
	nextseqnum(0),
	full(false),
	OverAck(0),
	N(WINDOW_SIZE),
	PacketWaitAck(new Packet[WINDOW_SIZE])
{
}
TCPRdtSender:: ~TCPRdtSender()
{
	delete[] PacketWaitAck;
}
bool TCPRdtSender::getWaitingState()
{
	return full;
}
//�ϲ����ʱ���ȼ�鴰���Ƿ����������������򷵻���Ϣ�������ϲ㲻�ܷ������ݡ�
//��û�������ݴ��������У��ͣ����кţ�ȷ�Ϻŵ���Ϣ��
//TCPֻ��һ����ʱ����������͵����ݰ������кŵ���sendbase��������ʱ��
bool TCPRdtSender::send(Message &message)						//����Ӧ�ò�������Message����NetworkServiceSimulator����,������ͷ��ɹ��ؽ�Message���͵�����㣬����true;�����Ϊ���ͷ����ڵȴ���ȷȷ��״̬���ܾ�����Message���򷵻�false
{
	if (full)
	{
		return false;
	}
	PacketWaitAck[nextseqnum%N].acknum = -1;
	PacketWaitAck[nextseqnum%N].seqnum = nextseqnum;
	PacketWaitAck[nextseqnum%N].checksum = 0;
	memcpy(PacketWaitAck[nextseqnum%N].payload, message.data, sizeof(message.data));
	PacketWaitAck[nextseqnum%N].checksum = pUtils->calculateCheckSum(PacketWaitAck[nextseqnum%N]);


	if (sendbase == nextseqnum)
	{
		pns->startTimer(SENDER, Configuration::TIME_OUT, 0);
	}
	pUtils->printPacket("���ͷ����ͱ���", PacketWaitAck[nextseqnum%N]);
	pns->sendToNetworkLayer(RECEIVER, PacketWaitAck[nextseqnum%N]);

	nextseqnum = (nextseqnum + 1) % seqrange;
	if (nextseqnum == (sendbase + N) % seqrange)
	{
		full = true;
	}
	return true;
}
//����յ�ACK����Ƚ�sendbase��ACK�����
//�����Ŵ���sendbase����ô��sendbase����Ϊ��š�
//�����ǰ����δȷ�ϵı��Ķ�����Ҫ������ʱ����
//����յ��������3��ACK������п����ش���
void TCPRdtSender::receive(Packet &ackPkt)						//����ȷ��Ack������NetworkServiceSimulator����	
{
	int checksum = pUtils->calculateCheckSum(ackPkt);
	bool inwindow;
	if (sendbase <= nextseqnum)
	{
		inwindow = (ackPkt.acknum > sendbase) && (ackPkt.acknum <= nextseqnum);
	}
	else
	{
		inwindow = (ackPkt.acknum >= sendbase) || (ackPkt.acknum <= nextseqnum);
	}

	if ((checksum == ackPkt.checksum) && (inwindow))
	{
		pUtils->printPacket("���ͷ���ȷ�յ����շ�ȷ�ϱ���", ackPkt);
		sendbase = ackPkt.acknum;
		pns->stopTimer(SENDER, 0);
		OverAck = 0;
		full = false;
		if (sendbase != nextseqnum)
		{
			pns->startTimer(SENDER, Configuration::TIME_OUT, 0);
		}
	}
	else
	{
		if ((checksum == ackPkt.checksum) && (!inwindow))
		{
			OverAck++;
			if (OverAck == 3)
			{
				OverAck = 0;
				pUtils->printPacket("�����ش�", PacketWaitAck[sendbase%N]);
				pns->stopTimer(SENDER, 0);
				pns->startTimer(SENDER, Configuration::TIME_OUT, 0);
				pns->sendToNetworkLayer(RECEIVER, PacketWaitAck[sendbase%N]);
			}
		}
	}
}
//��ʱʱ��TCP�ش�����ʱ�����ݰ��������ü�ʱ��
void TCPRdtSender::timeoutHandler(int seqNum)
{
	printf("���ͷ���ʱ����ʱ�����·���֮ǰ���͵ı���\n");
	pns->stopTimer(SENDER, 0);
	pUtils->printPacket("���ͷ���ʱ����ʱ���ط�֮ǰ�ı���", PacketWaitAck[sendbase%N]);
	pns->sendToNetworkLayer(RECEIVER, PacketWaitAck[sendbase%N]);
	pns->startTimer(SENDER, Configuration::TIME_OUT, 0);
}