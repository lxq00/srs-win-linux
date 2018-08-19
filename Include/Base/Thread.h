//
//  Copyright (c)1998-2012, Public Technology
//  All Rights Reserved.
//
//
//	Description:
//	$Id: Thread.h 159 2013-09-03 05:37:51Z  $


#ifndef __BASE_THREAD_H_
#define __BASE_THREAD_H_
#include <stdio.h>
#include <string>
#include "Base/Defs.h"
#include "Defs.h"
#include "Func.h"

namespace Public{
namespace Base{


typedef struct
{
	int errorCode;				///������
	std::string info;			///������Ϣ
	std::string stacks;			///�����ջ
} XM_ErrorInfo;

/// ���߳��������Ĵ�����
/// \param errCode [in] ������
/// \param info [in] �������������Ϣ
/// \retval true �ɹ�
/// \retval false ʧ��	
bool BASE_API XM_SetLastError(int errCode, const char *info);

bool BASE_API XM_SetLastErrorInfo(int errCode, const char *fmt, ...);


/// ���߳��������Ĵ�����
/// \param errCode [in] ������
/// \param info [in] �������������Ϣ
/// \retval true �ɹ�
/// \retval false ʧ��	
bool BASE_API XM_SetLastErrorEx(const XM_ErrorInfo &lastinfo);

/// ������Ĵ�����
/// \param errinfo [out] ������
/// \retval true �ɹ�
/// \retval false ʧ��	
bool BASE_API XM_GetLastError(XM_ErrorInfo &errinfo);

/// ������Ĵ�����
/// \retval true �ɹ�
/// \retval false ʧ��
bool BASE_API XM_ClearLastError();

/// ��������Ϣ����Ӹ��ӵĵ���ջ��Ϣ
/// \param detail [in] ������Ϣ
/// \retval true �ɹ�
/// \retval false ʧ��	
bool BASE_API XM_AddLastErrorStack(const char *detail);


struct ThreadInternal;

/// \class Thread
/// \brief ��ƽ̨�߳���; �ṩ�̳з�ʽ�����߳�
class BASE_API Thread
{
	Thread(Thread const&);
	Thread& operator=(Thread const&);

public:
	enum Priority
	{
		priorTop = 1,
		priorBottom = 127,
		priorDefault = 64,
	};

	enum Policy
	{
		policyNormal = 0,			///< ��ͨ�߳�
		policyRealtime = 1		///< ʵʱ�߳�
	};

	/// ���캯��,��û�д���ϵͳ�߳�
	/// \param name [in]�߳������ַ���,���Ʋ�һ���ᴫ������ϵͳ,��CThreadManager
	///		   �����߳�ʱ���õ�.
	/// \param priority [in]�߳����ȼ�,ֵԽС��ʾ���ȼ�Խ��,�ᱻת���ɶ�Ӧ����ϵͳ
	///        ƽ̨�����ȼ�.ȡֵpriorTop��priorBottom,Ĭ��ֵpriorDefault.
	/// \param policy [in] �̵߳��Ȳ���
	/// \param stackSize [in] Ϊ�߳�ָ���Ķ�ջ��С,�������0����С��ƽ̨Ҫ������ֵ,
	///        ��ʹ��ƽ̨ȱʡֵ.
	Thread(const std::string& name, int priority = priorDefault, int policy = policyNormal, int stackSize = 0);

	/// ��������,����̻߳���ִ��,�������߳�
	virtual ~Thread();

	/// �߳�ִ����,��һ���麯��,�������߳��������ش˺���,ʵ�ָ��Ե���Ϊ.
	virtual void threadProc() = 0;

	/// �����߳�
	/// \retval ture �ɹ�
	/// \retval false ʧ��
	bool createThread();

	/// �����߳�,�����˳���־,�̵߳�ִ������Ҫ�ڸ��˳����ж������־.
	/// \retval true �ɹ�
	/// \retval false ʧ��
	bool destroyThread();

	/// ��ֹ�߳�,�������̲߳�ͬ���������ɲ���ϵͳǿ�������߳�,����֤�û����ݰ�ȫ.
	/// \retval true �ɹ�
	/// \retval false ʧ�� 
	bool terminateThread();

	/// ȡ���߳�,�����߳��˳���־,��������ʽ,���ȴ��߳̽���
	/// \retval true �ɹ�
	/// \retval false ʧ��
	bool cancelThread();

	/// �ж��߳��Ѿ�������������ִ��
	/// \retval true �Ѿ�����
	/// \retval false ����ִ��
	bool isThreadOver();

	/// �õ��߳�ID
	/// \retval �߳�ID
	int	getThreadID();

	/// �����߳�����
	/// \param name [in] �µ��߳�����
	void setThreadName(const std::string& name);

	/// ���ó�ʱʱ��
	/// \param milliSeconds [in] ��ʱ������,����Ϊ0��ʾ�������
	void setTimeout(int milliSeconds);

	/// �ж��Ƿ�ʱ,Ҳ�����жϴ����һ��SetTimeout����ε���IsTimeout��ʱ����
	/// �Ƿ��Ѿ��ڳ�ʱʱ��֮��.�������ӿ�Ŀ�����ṩ���û����Ӻ͵����̵߳ķ���,
	/// CThread�ಢ��������Ƿ�ʱ���߳�ִ�����κθ�Ԥ.CThreadManager��ӡ����
	/// �߳�״̬ʱ���������ӿ�.
	/// \retval true �Ѿ���ʱ
	/// \retval false û�г�ʱ
	bool isTimeout();

	/// �߳��˳���־, �߳�����������־�˳�
	/// \retval true �ɹ�
	/// \retval false ʧ��
	bool looping() const;

	/// �õ������̵߳�ID,������ĳ���̶߳����ID,��һ����̬����.
	/// \retval �߳�ID
	static int getCurrentThreadID();

	/// �õ����߳�����һ��ʱ��
	/// \param milliSeconds [in] ���������ĺ�����
	static void sleep(int milliSeconds);

public:
	ThreadInternal* internal;
};

} // namespace Base
} // namespace Public


#ifndef MAX_PATH
#define MAX_PATH 260 // add by ,no fond by linux
#endif

#ifndef WIN32
namespace {
#include <stdio.h>
inline void GetModuleFileName(char *name, char *path, int len)
{
	FILE *stream = fopen("/proc/self/cmdline", "r");
	fgets(path, len, stream);
	fclose(stream);
}
}

#endif


#endif //_BASE_THREAD_H_

