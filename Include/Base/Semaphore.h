//
//  Copyright (c)1998-2014, Public Technology
//  All Rights Reserved.
//
//	Description:
//	$Id: Semaphore.h 33 2013-02-05 09:43:35Z  $


#ifndef __BASE_SEMAPHORE_H__
#define __BASE_SEMAPHORE_H__

#include "Defs.h"
#include "Base/IntTypes.h"

namespace Public{
namespace Base{
/// \class Semaphore
/// \brief ��ƽ̨�ź�����
class BASE_API Semaphore:public ISemaphoreObjcPtr
{
	Semaphore(Semaphore const&);
	Semaphore& operator=(Semaphore const&);

public:
	/// ���캯�����ᴴ��ϵͳ�ź���
	/// \param initialCount [in] �ź�����ʼ����
	explicit Semaphore(int initialCount = 0);

	/// ����������������ϵͳ������
	~Semaphore();

	/// ����Ѿ����ٵ�0�����������õ��߳�
	/// \return >=0 �ɹ�
	///         <0 ����
	int pend();

	/// �����ź�������������Ǵ�0�ۼӣ��ỽ����ȴ����еĵ�һ���߳�
	/// \timeout [in] ��ʱʱ��,��λ����
	/// \return >=0 �ɹ�
	///         <0  ������߳�ʱ
	int pend(uint32_t timeout);
	
	/// �����ź�������������Ǵ�0�ۼӣ��ỽ����ȴ����еĵ�һ���߳�
	/// \return ��ǰ�ź�������
	int post();

private:
	struct SemaphoreInternal;
	SemaphoreInternal* internal;
};

} // namespace Base
} // namespace Public

#endif //__BASE_SEMAPHORE_H__

