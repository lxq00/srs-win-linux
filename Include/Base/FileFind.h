//
//  Copyright (c)1998-2012, Public Technology
//  All Rights Reserved.
//
//	Description:
//	$Id: File.h 252 2013-12-18 04:40:28Z  $
//

#ifndef __BASE_FILEFIND_H__
#define __BASE_FILEFIND_H__

#include <string>
#ifdef WIN32
#include <io.h>
#endif

#include "Base/Defs.h"
#include "Base/IntTypes.h"
#include "Base/Shared_ptr.h"

namespace Public {
namespace Base {

/// \class FileFind
/// \brief �ļ�������,֧��'*','?'ͨ�������
class BASE_API FileFind
{
	FileFind(FileFind const&);
	FileFind& operator=(FileFind const&);
public:
	class BASE_API FileFindInfo
	{
		friend class FileFind;
		FileFindInfo(FileFindInfo&);
		FileFindInfo& operator=(const FileFindInfo&);
		FileFindInfo(const std::string& path,void* findinfo);
	public:
		virtual ~FileFindInfo();

		/// �õ����ҵ����ļ��ĳ���
		/// \retval �ļ�����
		virtual size_t getLength();

		/// �õ����ҵ����ļ����ļ���
		/// \retval �ļ�����
		virtual std::string getFileName();

		/// �õ����ҵ����ļ���ȫ·��
		/// \retval ȫ·��
		virtual std::string getFilePath();

		/// �Ƿ�Ϊֻ���ļ�
		/// \retval true ֻ��
		/// \retval false ����ֻ��
		virtual bool isReadOnly();

		/// �Ƿ�ΪĿ¼�ļ�
		/// \retval true ��Ŀ¼
		/// \retval false ����Ŀ¼
		virtual bool isDirectory();

		/// �Ƿ�Ϊ�����ļ�
		/// \retval true ��
		/// \retval false ����
		virtual bool isHidden();

		/// �Ƿ�Ϊ��ͨ�ļ�
		/// \retval true ��
		/// \retval false ����	
		virtual bool isNormal();
	private:
		struct FileFindInfoInternal;
		FileFindInfoInternal* internal;
	};
public:
	/// ���캯��
	FileFind(const std::string& findString);

	/// ��������
	virtual ~FileFind();

	/// ���ҵ�һ���ļ�
	/// \retval object �ҵ�
	/// \retval null û���ҵ�
	shared_ptr<FileFind::FileFindInfo>  find();
private:
	struct FileFindInternal;
	FileFindInternal* internal;
};

} // namespace Base
} // namespace Public

#endif //__BASE_FILE_H__

