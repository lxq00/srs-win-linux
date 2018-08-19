//
//  Copyright (c)1998-2012, Public Technology
//  All Rights Reserved.
//
//
//	Description:
//	$Id: AtomicCount.h 80 2013-04-11 07:05:56Z  $
//

#ifndef __BASE_ATOMIC_COUNT_H__
#define __BASE_ATOMIC_COUNT_H__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#include <Windows.h>
#endif
#include "Base/Defs.h"

namespace Public {
namespace Base {
	
/// \class AtomicCount
/// \brief ԭ�Ӽ�����


class BASE_API AtomicCount
{
		/// ��ֹ�������캯���͸�ֵ����
    AtomicCount( AtomicCount const & );
    AtomicCount & operator=( AtomicCount const & );
public:
	typedef int	ValueType;
public:
	AtomicCount();
	/// ԭ�Ӽ��㹹�캯��
	/// \param v [in] ��ʼ��ʱԭ�Ӽ�����ֵ
	explicit AtomicCount( ValueType initValue);
	~AtomicCount();

	/// ǰֵ������������
    ValueType operator++();

	/// ��ֵ������������
	ValueType operator++(int);

	/// ǰֵ�ݼ�ȥ��������
    ValueType operator--();

	/// ��ֵ�ݼ�ȥ��������
	ValueType operator--(int);

	ValueType value() const;

	/// ���غ������ò���
    operator ValueType() const;

	///�ж�ԭ�Ӽ�����0
	bool operator !() const;
private:
#ifdef WIN32
	typedef volatile LONG  countType;
#else
	typedef int countType;
#endif
	countType		count;
};

} // namespace Base
} // namespace Public

#endif // __BASE_ATOMIC_COUNT_H__


