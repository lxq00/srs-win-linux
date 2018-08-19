//
//  Copyright (c)1998-2014, Public Technology
//  All Rights Reserved.
//
//	Description:
//	$Id: Mutex.h 3 2013-01-21 06:57:38Z  $

#ifndef __BASE_MUTEX_H__
#define __BASE_MUTEX_H__

#include "Defs.h"
#include "IntTypes.h"
namespace Public{
namespace Base{

/// \class Mutex
//// \brief ��
class BASE_API Mutex:public ILockerObjcPtr
{
	Mutex(Mutex const&);
	Mutex& operator=(Mutex const&);

public:
	/// ���캯��,�ᴴ��ϵͳ������
	Mutex();

	/// ��������,������ϵͳ������
	~Mutex();

	/// �����ٽ���
	/// \retval true �ɹ�
	/// \retval false ʧ��
	bool enter();

	/// �뿪�ٽ���
	/// \retval true �ɹ�
	/// \retval false ʧ��
	bool leave();

private:
	struct MutexInternal;
	MutexInternal *internal;
};

} // namespace Base
} // namespace Public

#endif //__BASE_MUTEX_H__

