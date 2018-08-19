//
//  Copyright (c)1998-2012, Public Technology
//  All Rights Reserved.
//
//	Description:
//	$Id: Md5.h 3 2013-01-21 06:57:38Z  $
//

#ifndef __BASE_MD5_H__
#define __BASE_MD5_H__

#include <stddef.h>
#include "Base/IntTypes.h"
#include "Defs.h"


namespace Public {
namespace Base {


/// \class MD5 
/// \brief MD5 �㷨������
class BASE_API Md5
{
	Md5(Md5 const&);
	Md5& operator=(Md5 const&);

public:
	/// ���캯��
	Md5();

	/// ��������
	~Md5();

	///	��ʼ��
	void init();

	///	׷��Ҫ��MD5ժҪ�����ݣ��ýӿڿɵ��ö�Σ��ֱ�׷�����ݡ�
	///	\param [in] data ����ָ��
	/// \param [in] size ���ݳ���
	void update(uint8_t const* data, size_t size);

	///	����16�ֽ�MD5ժҪ
	///	\param [out]  ժҪ������棬����С��16�ֽڣ�
	std::string final();

	///	����32�ֽ�MD5ժҪ��ϣ(16����Сд�ַ���)
	///	\param [out] hash ժҪ��ϣ������棬����С��32�ֽڣ�
	std::string hex();

private:
	struct Md5Internal;
	Md5Internal* internal;

};


} // namespace Base
} // namespace Public

#endif// __BASE_MD5_H__


