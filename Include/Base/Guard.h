//
//  Copyright (c)1998-2014, Public Technology
//  All Rights Reserved.
//
//	Description:
//	$Id: Guard.h 3 2013-01-21 06:57:38Z  $
//


#ifndef __BASE_GUARD_H__
#define __BASE_GUARD_H__

#include "Mutex.h"
#include "RecursiveMutex.h"
#include "ReadWriteMutex.h"
#include "Shared_ptr.h"
namespace Public{
namespace Base{


/// \class Guard
/// \brief �ػ�����.

class Guard
{
	Guard(Guard const&);
	Guard& operator=(Guard const&);

public:
	/// ���캯��,�Զ�����CMutex::enter
	/// \param mutex ����������,CGuard��������������.
	inline Guard(Mutex& mutexparam)
		:mutex(&mutexparam)
	{
		if(mutex != NULL)
		{
			mutex->enter();
		}		
	};
	inline Guard(const shared_ptr<ILockerObjcPtr>& ptr)
		:mutex(ptr.get())
	{
		if (mutex != NULL)
		{
			mutex->enter();
		}
	};
	inline Guard(ILockerObjcPtr* ptr)
		:mutex(ptr)
	{
		if(mutex != NULL)
		{
			mutex->enter();
		}		
	};

	/// ��������,�Զ�����CMutex::leave
	inline ~Guard()
	{
		if(mutex != NULL)
		{
			mutex->leave();
		}
	};

private:
	ILockerObjcPtr *mutex;	///< ��Ҫ�Զ����õĻ���������
};

////////////////////////////////////////////////////////////////////////////////
/// \class RecursiveGuard
/// \brief �ݹ��ػ�����
class RecursiveGuard
{
	RecursiveGuard(RecursiveGuard const&);
	RecursiveGuard& operator=(RecursiveGuard const&);

public:
	/// ���캯��,�Զ�����CMutex::enter
	/// \param mutex [in] ����������,CGuard��������������.
	inline RecursiveGuard(RecursiveMutex& mutexparam)
		:mutex(mutexparam)
	{
		mutex.enter();
	};

	/// ��������,�Զ�����CMutex::leave
	inline ~RecursiveGuard()
	{
		mutex.leave();
	};

private:
	RecursiveMutex &mutex;	///< ��Ҫ�Զ����õĻ���������
};

////////////////////////////////////////////////////////////////////////////////
/// \class GuardReadMutex
/// \brief �����ػ�����
class GuardReadMutex
{
	GuardReadMutex(GuardReadMutex const&);
	GuardReadMutex& operator=(GuardReadMutex const&);

public:
	/// ���캯��,�Զ����� CRwMutex::EnterReading
	/// \param mutex [in]����������,CGuard��������������.
	inline GuardReadMutex(ReadWriteMutex& mutexparam)
		: mutex(mutexparam)
	{
		mutex.enterread();
	};

	/// ��������,�Զ����� CReadWriteMutex::leave
	inline ~GuardReadMutex()
	{
		mutex.leave();
	};

private:
	ReadWriteMutex& mutex;	///< ��Ҫ�Զ����õĻ���������
};

////////////////////////////////////////////////////////////////////////////////
/// \class GuardReadMutex
/// \brief ��д���ػ�����
class GuardWriteMutex
{
	GuardWriteMutex(GuardWriteMutex const&);
	GuardWriteMutex& operator=(GuardWriteMutex const&);

public:
	/// ���캯��,�Զ����� CReadWriteMutex::EnterWriting
	/// \param mutex [in]����������,CGuard��������������.
	inline GuardWriteMutex(ReadWriteMutex& mutexparam)
		: mutex(mutexparam)
	{
		mutex.enterwrite();
	};

	/// ��������,�Զ����� CReadWriteMutex::leave
	inline ~GuardWriteMutex()
	{
		mutex.leave();
	};

private:
	ReadWriteMutex& mutex;	///< ��Ҫ�Զ����õĻ���������
};

} // namespace Base
} // namespace Public

#endif //__BASE_GUARD_H__

