//
//  Copyright (c)1998-2012, Public Technology
//  All Rights Reserved.
//
//	Description:
//	$Id: Process.h 3 2013-01-21 06:57:38Z  $

#ifndef __BASE_PROCESS_H__
#define __BASE_PROCESS_H__
#include "Base/Shared_ptr.h"
#ifdef WIN32
	#include <Windows.h>
#else
	#include <sys/types.h>
#endif

#include "Defs.h"
namespace Public{
namespace Base{


/// \interface Process 
/// \brief ����������
#ifdef WIN32
	#define ProcessHandle HANDLE 
#else
	#define ProcessHandle pid_t  
#endif
	
class BASE_API Process
{
public:
	/// ���캯��
	Process() {};

	/// ����������
	virtual ~Process() {};

	/// ��������
	/// \param name [in] �������� 
	/// \param argc [in] ��������
	/// \param argv [in] �����б�
	/// \param relation ��ϵ���̣����������̹رպ��ӽ����Զ��˳�
	/// \retval != NULL �ɹ�
	/// \retval == NULL ʧ��
	static shared_ptr<Process> createProcess(const std::string& name, int argc  = 0, const char *argv[] = NULL,bool relation = true);

	/// ��ý��̵ľ��
	/// \retval ���
	virtual ProcessHandle getHandle() = 0;
	

	///��ȡ����Pid
	virtual int getPid() = 0;

	///�жϽ����Ƿ����
	virtual bool exists() = 0;

	/// 
	/// ɱ������
	/// \retval true �ɹ�
	/// \retval false ʧ��
	virtual bool kill() = 0;

	/// 
	/// ɱ������
	/// \retval true �ɹ�
	/// \retval false ʧ��
	/// \param pid [in] ����pid 
	static bool killByPid(int pid);

	/// 
	/// �������Ƿ����
	/// \retval true �ɹ�
	/// \retval false ʧ��
	/// \param pid [in] ����pid 
	static bool existByPid(int pid);
};


class BASE_API ProcessInfo
{
public:
	ProcessInfo(){}
	virtual ~ProcessInfo(){}

	//��ȡָ�����̵Ľ�����Ϣ,process ���̶���
	static shared_ptr<ProcessInfo> getProcessInfo(const shared_ptr<Process>& process,uint32_t timeout = 100);

	//���ݽ���ID��ȡ������Ϣ,pidΪ����ID��
	static shared_ptr<ProcessInfo> getProcessInfo(int pid,uint32_t timeout = 100);

	//��ȡ��ǰ���̵Ľ�����Ϣ
	static shared_ptr<ProcessInfo> getCurrProcessInfo(uint32_t timeout = 100);

	//�ύ�ڴ棬��λM
	virtual bool pagefileMemory(uint32_t& mem) = 0;

	//�����ڴ棬��λM
	virtual bool workMemory(uint32_t& mem) = 0;

	//�����߳���
	virtual bool threadNum(uint16_t& num) = 0;

	//��ǰCPUʹ���� 0 ~ 100,timeout ʹ�ó�ʱʱ�� ��λms
	virtual bool cpuUsage(uint16_t& usage) = 0;
};


} // namespace Base
} // namespace Public

#endif //__BASE_PROCESS_H__

