//
//  Copyright (c)1998-2014, Public Technology
//  All Rights Reserved.
//
//	Description:
//	$Id: ReadWriteMutex.h 3 2013-01-21 06:57:38Z  $

#ifndef __BASE_RW_MUTEX_H__
#define __BASE_RW_MUTEX_H__

#include "Defs.h"
#include "IntTypes.h"

namespace Public{
namespace Base{


/// \class Mutex
/// \brief ��ƽ̨��������
class BASE_API ReadWriteMutex:public ILockerObjcPtr
{
	ReadWriteMutex(ReadWriteMutex const&);
	ReadWriteMutex& operator=(ReadWriteMutex const&);

public:
	/// ���캯�����ᴴ��ϵͳ������
	ReadWriteMutex();

	/// ����������������ϵͳ������
	~ReadWriteMutex();

	/// �����ٽ�����
	/// \retval true 	�ɹ�
	/// \retval false ʧ��
	bool enterread();

	/// �����ٽ�����
	/// \retval true 	�ɹ�
	/// \retval false ʧ��
	bool enterwrite();

	/// �뿪�ٽ�����
	/// \retval true 	�ɹ�
	/// \retval false ʧ��
	bool leave();

private:
	struct ReadWriteMutexInternal;
	ReadWriteMutexInternal* internal;
};

} // namespace Base
} // namespace Public

#endif //__BASE_RW_MUTEX_H__

