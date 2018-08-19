//
//  Copyright (c)1998-2012,  Public Technology
//  All Rights Reserved.
//
//	Description:
//	$Id: network.h 216 2015-12-15 11:33:55Z  $
//
#ifndef __PublicNETWORK_H__
#define __PublicNETWORK_H__
#include "Network/Defs.h"
#include "Network/NetAddr.h"
#include "Network/Socket.h"
#include "Network/TcpClient.h"
#include "Network/TcpServer.h"
#include "Network/Udp.h"

namespace Public{
namespace Network{

class NETWORK_API NetworkSystem
{
public:
	/// ��ӡ Base�� �汾��Ϣ
	static void  printVersion();

	//��ʼ�������
	//��maxcpuCorePerTherad ��= 0 NETWORK�߳���ʹ�� maxcpuCorePerTherad*CPUCore 
	//��maxcpuCorePerTherad == 0  ��threadNum ��= 0 Networkʹ���߳��� threadNum
	//��maxcpuCorePerTherad == 0  ��threadNum == 0 ʱ��networkʹ���߳���Ĭ��Ϊ1
	static void init();

	//����ʼ�������
	static void uninit();
};

}
}



#endif //__PublicNETWORK_H__
