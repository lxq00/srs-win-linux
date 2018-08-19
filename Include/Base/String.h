//
//  Copyright (c)1998-2014, Public Technology
//  All Rights Reserved.
//
//
//	Description:
//	$Id: String.h 227 2013-10-30 01:10:30Z  $

#ifndef __BASE_STRING_H__
#define __BASE_STRING_H__

#include <stdio.h>
#include <string.h>
#include "BaseTemplate.h"
#include "Defs.h"
#include <string>
#include "Func.h"


namespace Public {
namespace Base {


///	��ȫ���ַ�������
///	\param [out] dest:Ŀ��buffer,���Ŀ��bufferû��'\0'�������������һ���ַ�Ϊ'\0',����0
///	\param [in]	dstBufLen,Ŀ��buffer�ռ��С,�ú������д��dstBufLen-1���ַ���������д���ַ��������'\0'�ַ�
///	\param [in] src:
///	\param [in] srcCopyCount: ����src�ĳ���
///		ִ����ɺ������copy����ô��Destһ��������0����
///	\retval ���صĽ���Ǵ�src copy��dest�е��ַ���Ŀ
size_t BASE_API strncat(char* dest, size_t dstBufLen, const char* src, const size_t srcCopyCount);

///	��ȫ���ַ���copy����
///	\param [out] dst,Ŀ��buffer
///	\param [in]	dstBufLen,Ŀ��buffer�ռ��С,�ú������д��dstBufLen-1���ַ���������д���ַ��������'\0'�ַ�
///	\param [in]	src,Դbuffer
///	\param [in] srcCopyCount
///	\retval Ҫcopy���ַ�����,��dstBufLen-1�ռ����������£����copy���ַ���ĿΪsrcCopyCount,�����ں������'\0'�ַ�
size_t BASE_API strncpy(char* dst, size_t dstBufLen, const char* src, size_t srcCopyCount);

///	��ǿ��snprintf����֤'\0'������ʵ��д�볤�ȣ�
///	����֧�� len += snprintf_x( buf + len, maxlen - len, "xxxx", ... ); ������д��
///	��ʵ��buffer����ʱ����֤\'0'������maxlen - 1����ԭ��snprintf��VC�᷵��-1�Ҳ���֤'\0'��gcc�᷵�ؼ���buffer�㹻ʱ��д�볤�ȣ�
///	��������maxlen-1ʱ�޷����ֳ��ȸոպû��ǳ����ˣ����Լ򻯶������������߶�������������
///	Ҳ��������Ҫ�޳����ұ�֤'\0'ʱ���ַ���������ȡ��strncpy����ע��ԭ��strncpy����֤'\0'��
///	�� strncpy( dst, src, siz - 1 ); dst[size - 1] = '\0'; �൱�� snprintf( dst, siz, "%s", src );
///	\param [out] buf �������
///	\param [in] maxlen �����������ֽ���
///	\param [in] fmt ��ʽ�ַ���
///	\retval ����ʵ��д�볤��
int  BASE_API snprintf_x(char* buf, int maxlen, const char* fmt, ... );


class BASE_API String
{
public:
	//�ַ���תСд
	static std::string tolower(const std::string& src);

	//�ַ���ת��д
	static std::string toupper(const std::string& src);


	/// Ansi(Gb2312) ת���ַ���Ϊutf8��ʽ ��չ�ӿ�(linux ֻ֧��ת������������1024bytes)
	/// \param [in] src Դ�ַ���
	/// \retval ��string ת��ʧ��
	///         �ǿ�string ת�����
	static std::string ansi2utf8(const std::string& src);

	/// utf8ת���ַ���Ϊ Ansi(Gb2312)��ʽ  ��չ�ӿ�(linux ֻ֧��ת������������1024bytes)
	/// \param [in] src Դ�ַ���
	/// \retval ��string ת��ʧ��
	///         �ǿ�string ת�����
	static std::string utf82ansi(const std::string& src);
};

#ifdef WIN32
#define strcasecmp _stricmp
#define snprintf _snprintf
#define strncasecmp _strnicmp
inline const char* strcasestr(const char* srcstr, const char* substr)
{
	if (srcstr == NULL || substr == NULL)
	{
		return NULL;
	}
	std::string srcstrtmp = String::tolower(srcstr);
	std::string substrtmp = String::tolower(substr);

	const char* ptmp = strstr(srcstrtmp.c_str(), substrtmp.c_str());
	if (ptmp != NULL)
	{
		ptmp = srcstr + (ptmp - srcstrtmp.c_str());
	}
	return ptmp;
}
#endif


} // namespace Base
} // namespace Public

#endif// __BASE_STRING_H__


