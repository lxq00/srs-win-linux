//
//  Copyright (c)1998-2012, Public Technology
//  All Rights Reserved.
//
//	Description:
//	$Id: ShareMem.h 3 2013-01-21 06:57:38Z  $

#ifndef __BASE_SHAREMEM_H__
#define __BASE_SHAREMEM_H__

#include <stddef.h>		
#include "Base/IntTypes.h"
#include "Base/Shared_ptr.h"
#include "Defs.h"

namespace Public {
namespace Base {

////////////////////////////////////////////////////////////////////////////////
/// \class ShareMem
/// \brief �����ڴ���

class BASE_API ShareMem 
{
	
	ShareMem();
	ShareMem(const std::string &, const size_t, bool ,void*);
	ShareMem(ShareMem const&);
	ShareMem& operator=(ShareMem const&);

public:

	/// ���������ڴ�ͨ��
	/// \param sharename [in] �����ڴ������
	/// \param size [in] �����ڴ�Ĵ�С
	/// \return != NULL ShareMemʵ��ָ��
	///          == NULL ʧ��
	static shared_ptr<ShareMem> create(const std::string &sharename, const size_t size);

	/// �򿪹����ڴ�ͨ��
	/// \param sharename [in] �����ڴ������
	/// \param size [in] �����ڴ�Ĵ�С
	/// \param startAddr[in] �ڴ�ӳ�����ʼ��ַ
	/// \return != NULL ShareMemʵ��ָ��
	///          == NULL ʧ��
	static shared_ptr<ShareMem> open(const std::string &sharename, const size_t size,void* startAddr = NULL);

	/// ��������
	virtual ~ShareMem();

	/// ���buffer�ĵ�ַָ��
	/// \retval ��ַ
	uint8_t *getbuffer();

	/// ���buf�Ĵ�С
	/// \retval buf��С
	size_t getSize();
	
	/// ��ù����ڴ������
	/// \retval ���ع����ڴ����Ƶ�����
	const std::string &getname() const;

	/// ͬ���ڴ档��֤д���ڴ�
	/// \param offset [in] �ڴ������ʼλ�õ�ƫ����
	/// \param len [in] ����
	/// \retval true �ɹ�
	///         false ʧ��
	bool sync(const uint32_t offset, const uint32_t len);
	
private:
	struct Internal;
	Internal *internal;
};


} // namespace Base
} // namespace Public

#endif	// __BASE_SHAREMEM_H__


