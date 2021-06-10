#include "pch.h"			//pre complie header 
#include "packet.h"

PACKETPOINT PACKETPOINT::CreatePacket(int x, int y)
{
	PACKETPOINT packet = { 0, };

	packet.flag = PACK_POINT;
	packet.x = x;
	packet.y = y;

	return packet;
}
