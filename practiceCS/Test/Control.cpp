//control.cpp
#include "pch.h"
#include <stdio.h>

#include "Control.h"
#include "packet.h"
#include "TestDlg.h"


Control* Control::instance = NULL;

Control::Control()
{
	client.CreateSocket("192.168.0.93", 9000);
}

void Control::ParentForm(CTestDlg* pDlg)
{
	pForm = pDlg;
}

void Control::RecvData(const char* msg, int size)
{
	printf(">> [���ŵ�����] %dbyte\n", size);
	int* p = (int*)msg;

	if (*p == ACK_POINT)
	{
		PACKETPOINT* pDraw = (PACKETPOINT*)msg; //�ڽ��� ���·� ��ȯ ��Ŷ!
		pForm->Draw(pDraw->x, pDraw->y, pDraw->width, pDraw->r, pDraw->g, pDraw->b);

	}
}

void Control::Draw(CPoint p)
{
	//���� ����(1. ��Ŷ ����, 2. ����)
	PACKETPOINT pack = PACKETPOINT::CreatePacket(p.x, p.y);
	client.SendData((const char*)&pack, sizeof(pack));

}