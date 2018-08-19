#ifndef __NETWORK_UDP_H__
#define __NETWORK_UDP_H__

//
//  Copyright (c)1998-2012,  Public Technology
//  All Rights Reserved.
//
//	Description:
//	$Id: udp.h 216 2015-12-15 11:33:55Z  $
//
#include "Network/Socket.h"

using namespace std;
namespace Public{
namespace Network{
	
class NETWORK_API UDP:public Socket
{
	struct UDPInternal;
	UDP(const UDP&);
	UDP();
public:	
	static Public::Base::shared_ptr<Socket> create(const  Public::Base::shared_ptr<IOWorker>& worker);
	virtual ~UDP();
	
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

	///���첽��Ͷ��UDP���ݽ����¼� 
	///param[in]		buf				���յ������ݴ洢��ַ
	///param[in]		len				���յ������ݴ洢�ռ����ֵ
	///param[in]		received		�ɹ����ܵ����ݺ�Ļص�������ΪNULL
	///retun		 true �ɹ���false ʧ�� ������Ͷ���첽��Ϣ������
	///ע��
	///	1:ֻ��UDP������Bind���֧��/
	///	2:received����Ϊ��
	virtual bool async_recvfrom(char *buf , uint32_t len,const RecvFromCallback& received);


	///��ͬ����UDP����
	///param[in]		buf				���յ������ݴ洢��ַ
	///param[in]		len				���յ������ݴ洢�ռ����ֵ
	///retun		����ʵ�ʽ������ݵĳ���
	///ע��
	///	1:ֻ��UDP������Bind���֧��/
	///	2:received����Ϊ��
	/// 3:�ýӿڵĵ���ʱ���setSocketTimeout/nonBlocking������������
	virtual int recvfrom(char *buf , uint32_t len ,NetAddr& other);

	///���첽��Ͷ��UDP���ݷ����¼�
	///param[in]		buf				�������ݻ����ַ���õ�ַ�ռ����ݷ��͹����в��ܱ��޸�ɾ����ֱ��sended���ú���ܲ���
	///param[in]		len				���������������ֵ
	///param[in]		other			���ݷ��͵�Ŀ��
	///param[in]		sended			���ݷ��ͳɺ���첽֪ͨ������ΪNULL
	///retun		����Ͷ�ݷ�������������
	///ע��
	///  1:ֻ��UDP��֧��
	virtual bool async_sendto(const char * buf, uint32_t len,const NetAddr& other,const SendedCallback& sended);

	///��ͬ����UDP����
	///param[in]		buf				�������ݻ����ַ
	///param[in]		len				���������������ֵ
	///param[in]		other			���ݷ��͵�Ŀ��
	///retun		����ʵ�ʷ������ݵĳ���
	///ע��
	/// 1:ֻ��UDP��֧��
	///	2:�ýӿڵĵ���ʱ���setSocketTimeout/nonBlocking������������
	virtual int sendto(const char * buf, uint32_t len,const NetAddr& other);


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

	bool disconnect();

	bool nonBlocking(bool nonblock);
private:
	UDPInternal* internal;
};


};
};




#endif //__NETWORK_SOCKET_H__
