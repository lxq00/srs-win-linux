//
//  Copyright (c)1998-2012, Public Technology
//  All Rights Reserved.
//
//
//	Description:
//	$Id: Guid.h 89 2013-05-08 10:43:01Z  $
//
//


#ifndef __BASE_GUID_H__
#define __BASE_GUID_H__

#include "Defs.h"
#include "Base/IntTypes.h"
using namespace Public::Base;

namespace Public{
namespace Base {


/// \class Guid
/// \brief ͳһ��Guid
///
class BASE_API Guid
{
public:
	/// ����guid
	static Guid createGuid();

	/// ����guid
	static Guid *createGuidEx();

	/// ȱʡ���캯��
	/// \note "00000000-0000-0000-0000-000000000000" 
    Guid();
		
  	/// ���캯��
  	/// \param guid [in] guid�ĵ�ַ
  	/// \param isstream [in] �Ƿ�������(16bytes) �����ַ���(37 bytes)
	/// \note  �ַ���ģʽ(isstream == false)ʱ,guid ���뱣֤�ڴ�ռ���>=37�����һ��Ϊ'\0'���򼴱�ǰ��36��bytes��ȷ,Ҳ������ʧ��(windows)
	Guid(const char *guid, bool isstream = true);

	/// �������캯��
	Guid(const Guid& other);

	/// ��ֵ
	Guid& operator=(const Guid& other);
	
	/// �Ƚ�
	bool operator<(const Guid& other) const;

	/// ����
	bool operator==(const Guid &other) const;

	/// ���� ����
	bool operator==(const char * other) const;
	
	/// ������
	bool operator!=(const Guid &other) const;

	/// ������ ����
	bool operator!=(const char * other) const;	
	
	/// ��������
	virtual ~Guid();

	/// �Ƿ���Ч
	/// \retval true ��Ч 
	///         false ��Ч
	/// \note ��Ҫ���� ���ô����ַ�����ʽ����󣬼���Ƿ���Ч
	bool valid() const;

	/// ����Guid
  	/// \param guid [in] guid�ĵ�ַ
  	/// \param isstream [in] �Ƿ�������(16bytes) �����ַ���(37 bytes)
	/// \retval true �ɹ�
	///         false ʧ��
	/// \note �ַ���ģʽ(isstream == false) guid ���뱣֤�ڴ�ռ���>=37�����һ��Ϊ'\0',���򼴱�ǰ��36��bytes��ȷ,Ҳ������ʧ��(windows)
	bool setGuid(const char *guid, bool isstream = true);
	
	/// ���Guid
	/// \retval != NULL ����(16bytes)
	///         == NULL ��Ч
	const unsigned char *getBitStream() const;

	/// ���Guid
	/// \retval string.lenth() <= 0 ��Ч	
	///         �����ַ��� (36��bytes)
	std::string getStringStream() const;

	/// ���Guid
	/// \param str [out] �ַ���
	/// \retval true �ɹ�
	///         false ʧ��
	/// \note str ��֤������ 37��bytes�Ŀռ�
	bool getStringStream(char *str) const;
	
private:
	unsigned char buffer[16];
};


} // namespace Base
} // namespace Public

#endif //__BASE_GUID_H__

