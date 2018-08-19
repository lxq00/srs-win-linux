//
//  Copyright (c)1998-2012,  Public Technology
//  All Rights Reserved.
//
//	Description:
//	$Id: tcpclient.h 216 2015-12-15 11:33:55Z  $
//
#ifndef __NETWORK_TCPCLIENT_H__
#define __NETWORK_TCPCLIENT_H__

#include "Network/Socket.h"

namespace Public{
namespace Network{


class NETWORK_API TCPClient:public Socket
{
	struct TCPClientInternal;
	TCPClient(const TCPClient&);
	TCPClient();
public:
	static Public::Base::shared_ptr<Socket> create(const Public::Base::shared_ptr<IOWorker>& worker);
	virtual ~TCPClient();

	///�Ͽ�socket���ӣ�ֹͣsocket�ڲ��������ر�socket�����
	///UDP/TCP����ʹ�øýӿ��ͷ���Դ���ر�socket
	virtual bool disconnect();

	///�󶨴�����Ϣ
	///param[in]		addr		��Ҫ�󶨵Ķ˿�
	///param[in]		reusedAddr	�˿��Ƿ�������Ҫ�ظ���
	///return		true �ɹ���false ʧ�� 
	///ע����������ʹ�øú������жϴ����Ƿ�ռ�ã��˿��ж��ƽ�ʹ��host::checkPortIsNotUsed�ӿ�
	virtual bool bind(const NetAddr& addr,bool reusedAddr = true);

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


	///��ȡsocket��������С
	///param[in]		readSize		���Ļ�������С
	///param[in]		sendSize		���ͻ�������С
	///retun		 true �ɹ���false ʧ�� 
	virtual bool getSocketBuffer(uint32_t& recvSize,uint32_t& sendSize) const;

	///����socket��������С
	///param[in]		readSize		���Ļ�������С
	///param[in]		sendSize		���ͻ�������С
	///retun		 true �ɹ���false ʧ�� 
	virtual bool setSocketBuffer(uint32_t recvSize = -1,uint32_t sendSize = -1);

	///���첽������TCP����
	///param[in]		addr			�������ĵ�ַ
	///param[in]		callback		connect�ɹ���Ļص�������Ϊ��
	///retun		 true �ɹ���false ʧ��  ����ֵΪ�첽Ͷ����Ϣ���
	///ע��
	/// 1:ֻ��tcpclient��֧��
	virtual bool async_connect(const NetAddr& addr,const ConnectedCallback& callback);

	///��ͬ����TCP����
	///param[in]		addr			�������ĵ�ַ
	///retun		 true �ɹ���false ʧ��  ����ֵΪ���ӵĽ��
	///ע��
	/// 1:ֻ��tcpclient��֧��
	virtual bool connect(const NetAddr& addr);

	///����TCP�Ͽ��ص�֪ͨ
	///param[in]		disconnected	�Ͽ��ص�֪ͨ
	///retun		 true �ɹ���false ʧ�� 
	///ע��
	/// 1:ֻ��TCP��֧��
	virtual bool setDisconnectCallback(const DisconnectedCallback& disconnected);

	///���첽��Ͷ��TCP���������¼�
	///param[in]		buf				���յ������ݴ洢��ַ
	///param[in]		len				���յ������ݴ洢�ռ����ֵ
	///param[in]		received		�ɹ����ܵ����ݺ�Ļص�������ΪNULL
	///retun		 true �ɹ���false ʧ�� ������Ͷ����Ϣ���
	///ע��
	///	1:ֻ�����ӳɹ����TCP��֧��
	virtual bool async_recv(char *buf , uint32_t len,const ReceivedCallback& received);

	///��ͬ����TCP����
	///param[in]		buf				���յ������ݴ洢��ַ
	///param[in]		len				���յ������ݴ洢�ռ����ֵ
	///retun		 ����ֱ�ӽ��ܵ���Ϣ�ĳ���
	///ע��
	///	1:ֻ�����ӳɹ����TCP��֧��
	/// 2:�ýӿڵĵ���ʱ���setSocketTimeout/nonBlocking������������
	virtual int recv(char *buf , uint32_t len);

	///���첽��Ͷ��TCP���ݷ����¼�
	///param[in]		buf				�������ݻ����ַ���õ�ַ�ռ����ݷ��͹����в��ܱ��޸�ɾ����ֱ��sended���ú���ܲ���
	///param[in]		len				���������������ֵ
	///param[in]		sended			���ݷ��ͳɺ���첽֪ͨ������ΪNULL
	///retun		 true �ɹ���false ʧ�� ������Ͷ����Ϣ���
	///ע��
	///  1:ֻ�����ӳɹ����TCP��֧��
	virtual bool async_send(const char * buf, uint32_t len,const SendedCallback& sended);

	///��ͬ����TCP����
	///param[in]		buf				�������ݻ����ַ
	///param[in]		len				���������������ֵ
	///retun		��������ֱ�ӷ��͵ĳ���
	///ע��
	///  1:ֻ�����ӳɹ����TCP��֧��
	///  2:�ýӿڵĵ���ʱ���setSocketTimeout/nonBlocking������������
	virtual int send(const char * buf, uint32_t len);
	
	///��ȡSocket���
	///return ���	����socket����ʧ�� -1
	virtual int getHandle() const;

	///��ȡSocket��������
	///param in		
	///return ��������
	virtual NetType getNetType() const;

	///��ȡSocket����ĵ�ַ
	///param in		
	///return ����bind�ĵ�ַ��δbindΪ��
	virtual NetAddr getMyAddr() const;

	///��ȡSocket�Է��ĵ�ַ
	///param in		
	///return TCPConnectionʹ��
	virtual NetAddr getOhterAddr() const;

	bool nonBlocking(bool nonblock);

	NetStatus getStatus() const;
private:
	TCPClientInternal* internal;
};


};
};




#endif //__NETWORK_SOCKET_H__

