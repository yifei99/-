#include "stdafx.h"
#include "Global.h"
#include "TCPRdtReceiver.h"

TCPRdtReceiver::TCPRdtReceiver() :
	ExpectNextNum(0),
	seqrange((1 << SEQ_BIT) / WINDOW_SIZE * WINDOW_SIZE)
{
	lastAckPacket.acknum = 0;
	lastAckPacket.seqnum = -1;
	lastAckPacket.checksum = 0;
	for (int i = 0; i < Configuration::PAYLOAD_SIZE; i++)
	{
		lastAckPacket.payload[i] = '.';
	}
	lastAckPacket.checksum = pUtils->calculateCheckSum(lastAckPacket);
}

TCPRdtReceiver:: ~TCPRdtReceiver()
{
}

void TCPRdtReceiver::receive(Packet &packet)	//���ձ��ģ�����NetworkService����
{
	int checksum = pUtils->calculateCheckSum(packet);
	if ((checksum == packet.checksum) && (packet.seqnum == ExpectNextNum))
	{
		pUtils->printPacket("���շ���ȷ���յ����ͷ��ı���", packet);
		ExpectNextNum = (ExpectNextNum + 1) % seqrange;
		//ȡ��message����Ӧ�ò�
		Message msg;
		memcpy(msg.data, packet.payload, sizeof(packet.payload));
		pns->delivertoAppLayer(RECEIVER, msg);
		lastAckPacket.acknum = ExpectNextNum;
		lastAckPacket.checksum = pUtils->calculateCheckSum(lastAckPacket);
		pUtils->printPacket("���ܷ�����ȷ�ϱ���", lastAckPacket);
		pns->sendToNetworkLayer(SENDER, lastAckPacket);
	}
	else
	{
		if (checksum != packet.checksum)
		{
			pUtils->printPacket("���շ�û����ȷ�յ����ͷ������ݣ�������", packet);
		}
		else
		{
			pUtils->printPacket("���շ�û����ȷ�յ����ͷ������ݣ�����˳�����", packet);
		}
		pUtils->printPacket("���ܷ�������һ�ε�ȷ�ϱ���", lastAckPacket);
		pns->sendToNetworkLayer(SENDER, lastAckPacket);
	}
}
