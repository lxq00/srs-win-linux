//
//  Copyright (c)1998-2014, Public Technology
//  All Rights Reserved.
//
//
//	Description:
//	$Id: Version.h 3 2013-01-21 06:57:38Z  $

#ifndef __BASE_VERSION_H__
#define __BASE_VERSION_H__

#include "Base/Defs.h"
#include "Base/Time.h"
#include "Base/String.h"
#include <stdio.h>

namespace Public {
namespace Base {


///�汾��Ϣ.
struct BASE_API Version
{
	int Major; //��Ҫ�汾.
	int Minor; //��Ҫ�汾.
	int Build; //�޶���.
	std::string Revision; //�޶���.

public:
	Version();
	std::string toString() const;
	bool parseString(const std::string& versionstr);
	bool operator < (const Version& version) const;
	bool operator > (const Version& version) const;
	bool operator == (const Version& version) const;
};

/// \class Version
/// \brief �汾�࣬ÿ�����������ģ�鶼Ӧ�ö�����Եİ汾�ṹ����
class BASE_API AppVersion:public Version
{
public:
	
	std::string	name;			///< ���������ģ������
	SystemTime date;		///< �������ڣ�ʹ��__DATE__��

	static	SystemTime appDate;		///< Ӧ�ó����������

	/// ���캯�����汾����һ����Ϊȫ�ֶ�����
	/// \param name 	[in] ���������ģ������
	/// \param major 	[in] ���汾��
	/// \param minor 	[in] �ΰ汾��
	/// \param revision 	[in] �޶��汾��
	/// \param svnString 	[in] svn�汾�ŵ��ַ���
	/// \param dataString	[in]	ʱ���ַ���
	AppVersion(const std::string& name, int major, int minor, int build, const std::string& revision, const std::string& dateString);

	/// �汾��Ϣ��ӡ
	void print() const;

	/// ����Ӧ�ó����������
	/// \param dateString [in] ʱ���ַ���
	static void setAppDate(const std::string& dateString);

};

} // namespace Base
} // namespace Public

#endif //__BASE_VERSION_H__


