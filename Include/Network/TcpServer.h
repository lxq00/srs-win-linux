//
//  Copyright (c)1998-2012,  Public Technology
//  All Rights Reserved.
//
//	Description:
//	$Id: tcpserver.h 216 2015-12-15 11:33:55Z  $
//
#ifndef __NETWORK_TCPSERVER_H__
#define __NETWORK_TCPSERVER_H__

#include "Network/Socket.h"

namespace Public{
namespace Network{

class NETWORK_API TCPServer:public Socket
{
	struct TCPServerInternal;
	TCPServer(const TCPServer&);
	TCPServer();
public:
	static Public::Base::shared_ptr<Socket> create(const shared_ptr<IOWorker>& worker);

	virtual ~TCPServer();

	///�Ͽ�socket���ӣ�ֹͣsocket�ڲ��������ر�socket�����
	///UDP/TCP����ʹ�øýӿ��ͷ���Դ���ر�socket
	virtual bool disconnect();

	///�󶨴�����Ϣ
	///param[in]		addr		��Ҫ�󶨵Ķ˿�
	///param[in]		reusedAddr	�˿��Ƿ�������Ҫ�ظ���
	///return		true �ɹ���false ʧ�� 
	///ע����������ʹ�øú������жϴ����Ƿ�ռ�ã��˿��ж��ƽ�ʹ��host::checkPortIsNotUsed�ӿ�
	virtual bool bind(const NetAddr& addr,bool reusedAddr = true);

	
	///���첽��������������
	///param[in]		callback		accept������socket֪ͨ�ص�������ΪNULL
	///retun		 true �ɹ���false ʧ�� 
	///ע��
	/// 1:ֻ��tcpserver��֧��
	///	2:�첽accept��accept�����Ľ��ͨ��callback����
	/// 3:��accept��������ͬʱʹ��
	virtual bool async_accept(const AcceptedCallback& callback);


	///��ͬ����ͬ��accept����socket
	///param[in]		��
	///return		�����²�����socket���󣬵�NULLʱ��ʾʧ�ܣ�����ֵ��Ҫ�ⲿ�ͷ���Դ
	///ע��
	/// 1:ֻ��tcpserver��֧��
	///	2:��startListen����ͬʱʹ��
	///	3:�ýӿڵĵ���ʱ���setSocketTimeout/nonBlocking������������
	virtual Public::Base::shared_ptr<Socket> accept();

	///��ȡSocket���
	///return ���	����socket����ʧ�� -1
	virtual int getHandle() const ;

	///��ȡSocket��������
	///param in		
	///return ��������
	virtual NetType getNetType() const;

	///��ȡSocket����ĵ�ַ
	///param in		
	///return ����bind�ĵ�ַ��δbindΪ��
	virtual NetAddr getMyAddr() const;

	///����socket���ͽ��ܳ�ʱʱ��
	///param[in]		recvTimeout		���ճ�ʱ ��λ������,-1������
	///param[in]		sendTimeout		���ͳ�ʱ ��λ������,-1������
	///retun		 true �ɹ���false ʧ�� 
	virtual bool setSocketTimeout(uint32_t recvTimeout = -1, uint32_t sendTimeout = -1);

	///��ȡsocket���ͽ��ܳ�ʱʱ��
	///param[in]		recvTimeout		���ճ�ʱ ��λ������
	///param[in]		sendTimeout		���ͳ�ʱ ��λ������
	///retun		 true �ɹ���false ʧ�� 
	///ע���첽IO��֧��
	virtual bool getSocketTimeout(uint32_t& recvTimeout, uint32_t& sendTimeout) const;

	bool nonBlocking(bool nonblock);
private:
	TCPServerInternal* internal;
};


};
};




#endif //__NETWORK_TCPSERVER_H__

