//
//  Copyright (c)1998-2012,  Public Technology
//  All Rights Reserved.
//
//  Description:
//  $Id: NetAddr.h 17 2013-01-22 09:26:19Z   $
//

#ifndef __NET_NETADDR_H__
#define __NET_NETADDR_H__
#include <string>
#include "Defs.h"
#include "Base/IntTypes.h"

#ifdef WIN32
#include <winsock.h>
#else
#include <netinet/in.h>
#endif

using namespace Public::Base;

namespace Public{
namespace Network{

typedef  sockaddr 		SockAddr;
typedef  sockaddr_in 	SockAddrIPv4;
#ifdef SUPPORT_IPV6
typedef  struct sockaddr_in6	SockAddrIPv6;
#endif
class NETWORK_API NetAddr{
	struct NetAddrInternal;
public:
	NetAddr();
	NetAddr(const NetAddr& addr);
	NetAddr(const std::string& addr,int port);
	NetAddr(uint16_t port );
	NetAddr(const SockAddrIPv4& ipv4);
	NetAddr(const SockAddr& addr);

	~NetAddr();
	/// ���ʵ�����SockAddrָ��
	/// \param addr [out]  ָ��
	/// \param len  [in]  addr�ĳ���
	/// \retval !=NULL ��Ч�ĵ�ַ
	/// \retval ==NULL ��Ч��ַ
	SockAddr * getAddr() const;

	SockAddrIPv4* getAddrV4() const;

	/// ���ʵ�����SockAddr��ַ�ĳ���
	/// \retval  >  0 ��ַ����
	/// \reval   == 0 ��ַ��Ч
	uint32_t getAddrLen() const;

	/// ��õ��ʮ���Ƶ�ַ�ַ��� ���� ·������(UnixSocketʱ)
	/// \param  buf [out]    �ַ�����ַ
	/// \param  size [in]     buf�ַ����ĳ���
	/// \retval  != NULL �����ַ������׵�ַ
	/// \reval   == NULL ʧ��
	std::string getIP() const;

	
	/// ��ö˿�
	/// \reval > 0 ��Ч�˿ں�
	/// \reval = 0 ��Ч�˿ں�
	uint16_t getPort() const;
	
	
	/// �����ַ������
	enum NetAddrType{ 
		netaddr_unknown = 0,   //��Ч��ַ���� 
		netaddr_ipv4,      //IPv4��ַ����
		netaddr_ipv6,      //IPv6��ַ����
	};
		
	/// ��������ַ������
	NetAddrType getType() const;

	/// ����IP��ַ
	/// \param addr [in] ���ʮ����IPv4�ַ��� ���� ����
	/// \param port [in]  �˿ں�	
	/// \reval  >=0 �ɹ�
	/// \reval  < 0 ʧ��
	int setAddr( const std::string& addr, uint16_t port);

	/// ����IP��ַ
	/// \param [in] addr SockAddrIPv4
	/// \reval  >=0 �ɹ�
	/// \reval  < 0 ʧ��	
	int setAddr( const SockAddrIPv4 & addr );

	/// ����IP��ַ
	/// \param [in] addr SockAddrIPv4
	/// \reval  >=0 �ɹ�
	/// \reval  < 0 ʧ��	
	int setAddr( const SockAddr & addr );

	/// ֻ���ö˿�
	/// \param port [in]  �˿�
	/// \reval  >=0 �ɹ�
	/// \reval  < 0 ʧ��	
	int setPort( uint16_t port );
	
	// ��ǰ�������ַ�Ƿ�Ϊ��Ч��
	bool isValid() const;

#ifdef SUPPORT_IPV6
	NetAddr(const SockAddrIPv6& ipv6);
	SockAddrIPv6* getAddrV6() const;
	int setAddr( const SockAddrIPv6 & addr );
	NetAddr& operator=( NetAddrIPv6 const & other );
#endif	

	/// ��ֵ����
	NetAddr& operator=( NetAddr const & other );

	/// ��ϵ����:����
	bool operator==( NetAddr & other) const;
	/// ��ϵ����:����
private:
	NetAddrInternal* internal;
};

} // namespace Net
} // namespace Public

#endif// __NET_NETFRAME_H__



