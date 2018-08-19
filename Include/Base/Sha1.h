//
//  Copyright (c)1998-2012, Public Technology
//  All Rights Reserved.
//
//	Description:
//	$Id: Md5.h 3 2013-01-21 06:57:38Z  $
//

#ifndef __BASE_SHA1_H__
#define __BASE_SHA1_H__

#include <stddef.h>
#include "Base/IntTypes.h"
#include "Defs.h"


namespace Public {
namespace Base {


/// \class Sha1 
/// \brief Sha1 �㷨������
class BASE_API Sha1
{
public:
	typedef enum
	{
		REPORT_Normal = 0,
		REPORT_HEX,
		REPORT_DIGIT,
		REPORT_HEX_SHORT
	}REPORT_TYPE;
public:
	Sha1();
	~Sha1();

	static std::string hashFile(const std::string& file, REPORT_TYPE type);

	///	���ݱ��롣
	///	\param [in] data ����ָ��
	/// \param [in] size ���ݳ���
	bool input(char const* data, size_t size);

	///��ʽ�����ֵ
	std::string report(REPORT_TYPE type);
private:
	class Sha1Internal;
	Sha1Internal* internal;
};


} // namespace Base
} // namespace Public

#endif// __BASE_SHA1_H__


