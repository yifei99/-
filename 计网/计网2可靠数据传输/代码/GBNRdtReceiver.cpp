#include "stdafx.h"
#include "Global.h"
#include "GBNRdtReceiver.h"

GBNRdtReceiver::GBNRdtReceiver() :expectedseqnum(0), seqrange((1 << SEQ_BIT) / WINDOW_SIZE * WINDOW_SIZE)
{
	int i;
	lastAckPacket.seqnum = -1;
	lastAckPacket.acknum = -1;
	lastAckPacket.checksum = 0;
	for (i = 0; i < Configuration::PAYLOAD_SIZE; i++)
	{
		lastAckPacket.payload[i] = '.';
	}
	lastAckPacket.checksum = pUtils->calculateCheckSum(lastAckPacket);
}
GBNRdtReceiver:: ~GBNRdtReceiver()
{
}
//���ܷ���һ��������һ���յ��İ������expectedseqnum
//�����ܷ����յ�һ�����ݰ���������ݰ�û���𻵣��������ݰ�����ź�ExpectNextPacketNum��ȵĻ���
//���շ��ͽ����ݴ��ݸ��ϲ㣬����һ��Ϊexpectedseqnum��ACK��
//Ȼ��expectedsequm��һ���ȴ���һ�����ĵ�������������Ͷ�������
void GBNRdtReceiver::receive(Packet &packet)
{
	int checksum = pUtils->calculateCheckSum(packet);
	if ((checksum == packet.checksum) && (packet.seqnum == expectedseqnum))
	{
		pUtils->printPacket("���շ���ȷ���յ����ͷ��ı���", packet);
		Message msg;
		memcpy(msg.data, packet.payload, sizeof(packet.payload));
		pns->delivertoAppLayer(RECEIVER, msg);

		lastAckPacket.acknum = packet.seqnum;
		lastAckPacket.checksum = pUtils->calculateCheckSum(lastAckPacket);
		pUtils->printPacket("���շ�����ȷ�ϱ���", lastAckPacket);
		pns->sendToNetworkLayer(SENDER, lastAckPacket);
		expectedseqnum = (expectedseqnum + 1) % seqrange;
	}
	else
	{
		if (checksum != packet.checksum)
		{
			pUtils->printPacket("���շ�û����ȷ�յ����ͷ��ı��ģ�����У�����", packet);
		}
		else
		{
			pUtils->printPacket("���շ�û����ȷ�յ����ͷ��ı��ģ�������Ŵ���", packet);
		}
		pUtils->printPacket("���շ����������ϴε�ȷ�ϱ���", lastAckPacket);
		pns->sendToNetworkLayer(SENDER, lastAckPacket);
	}


}