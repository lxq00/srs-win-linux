//
//  Copyright (c)1998-2012, Public Technology
//  All Rights Reserved.
//
//	Description:
//	$Id: SimPipe.h 140 2013-06-27 07:55:35Z  $

#ifndef __BASE_SIMPIPE_H__
#define __BASE_SIMPIPE_H__

#include <string>	
#include <stddef.h>
#include "Base/IntTypes.h"
#include "Defs.h"

namespace Public {
namespace Base {

////////////////////////////////////////////////////////////////////////////////
/// \class SimPipe
/// \brief ����ܵ���

class BASE_API SimPipe 
{
	SimPipe(const std::string &);
	SimPipe(SimPipe const&);
	SimPipe& operator=(SimPipe const&);

public:
	SimPipe();
	/// ��������
	virtual ~SimPipe();

	/// ����Pipeͨ��
	/// \param name [in] Pipe������
	/// \return != NULL SimPipeʵ��ָ��
	///          == NULL ʧ��
	bool creat(const std::string &name);

	/// �ر�pipeͨ��
	/// save �����pipe
	bool destory(bool save = false);

	/// д����
	/// \param buf [in] ���ݵ�ַ
	/// \param len [in] ���ݳ���
	/// \retval  > 0 д�����ݳ���
	///          = 0 δд��
	///          < 0 ʧ��
	int write(const void *buf, size_t len);

	/// ������
	/// \param buf [out] �����ݵ�ַ
	/// \param len [in] ���ݳ���
	/// \retval  > 0 �������ݳ���
	///          = 0 û������
	///          < 0 ʧ��
	/// \note  read ��readEx�����ĵ��� ���̲߳���ȫ��,
	int read(void *buf, size_t len);

	typedef enum {
		seekPos_Cur,
		seekPos_Head,
	} SeekPos;
	
	/// ��λ��Seek
	/// \param offset [in] ƫ��
	/// \param pos [in]λ��
	/// \retval true �ɹ�
	///         false ʧ��
	bool readSeek(const int64_t &offset, SeekPos pos);

	/// дλ��Seek
	/// \param offset [in] ƫ��
	/// \param pos [in]λ��
	/// \retval true �ɹ�
	///         false ʧ��
	bool writeSeek(const int64_t &offset, SeekPos pos);	

	/// ��ö���λ��
	/// \retval ����λ��
	uint64_t getReadPos();

	/// ���д��λ��
	/// \retval д��λ��
	uint64_t getWritePos();

	/// ���Pipe�ļ�������
	/// \retval �����ļ����Ƶ�����
	const std::string getname() const;
	
private:
	struct Internal;
	Internal *internal;
};


} // namespace Base
} // namespace Public

#endif	// __BASE_SIMPIPE_H__



