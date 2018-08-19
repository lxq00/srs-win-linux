//
//  Copyright (c)1998-2014, Public Technology
//  All Rights Reserved.
//
//	Description:
//	$Id: PrintLog.h 3 2013-01-21 06:57:38Z  $
//

#ifndef __BASE_PRINT_LOG_H__
#define __BASE_PRINT_LOG_H__

#include <stdio.h>
#include "Defs.h"
#include "Func.h"
#include "IntTypes.h"
#include <string>

namespace Public{
namespace Base{

enum LOG_Level{
	LOG_Level_FATAL,
	LOG_Level_ERROR,
	LOG_Level_WARN,
	LOG_Level_INFO,
	LOG_Level_TRACE,
	LOG_Level_DEBUG
};


/// ��ӡ����ص���������
/// ����ΪҪ��ӡ���ַ���
typedef Function2<void,LOG_Level,char const*> LogPrinterProc;

std::string BASE_API getLogTimeAndLevelString(LOG_Level lev);


///���ô�ӡ�ȼ�
//0:off 1:fatal 2:error 3:warn 4:info 5:trace 6:debug
void BASE_API setprintloglevel(int level);

/// ���ô�ӡ������ص�����
/// \param printer [in]  ����ص�����, Ϊ��ʱ���ô�ӡ�������׼����豸
/// \retval 0 �ɹ�
/// \retval -1 ʧ��
int BASE_API setlogprinter(const LogPrinterProc& printer);

/// �����ӡ������ص�����
int BASE_API cleanlogprinter(const LogPrinterProc& printer);

/// ��¼������Ϣ������6����ֱ�ӵ��ã�����ʵ��debgf��
/// \return ���ش�ӡ���ֽ���
int BASE_API logdebug(const char* fmt, ...);

/// ��¼������Ϣ������5����ֱ�ӵ��ã�����ʵ��tracef��
/// \return ���ش�ӡ���ֽ���
int BASE_API logtrace(const char* fmt, ...);

/// ��¼������Ϣ������4����ֱ�ӵ��ã�����ʵ��infof��
/// \return ���ش�ӡ���ֽ���
int BASE_API loginfo(const char* fmt, ...);

/// ��¼������Ϣ������3����ֱ�ӵ��ã�����ʵ��warnf��
/// \return ���ش�ӡ���ֽ���
int BASE_API logwarn(const char* fmt, ...);

/// ��¼������Ϣ������2����ֱ�ӵ��ã�����ʵ��errorf��
/// \return ���ش�ӡ���ֽ���
int BASE_API logerror(const char* fmt, ...);

/// ��¼����������Ϣ������1����ֱ�ӵ��ã�����ʵ��fatalf��
/// \return ���ش�ӡ���ֽ���
int BASE_API logfatal(const char* fmt, ...);


} // namespace Base
} // namespace Public

#endif //__BASE_PRINT_LOG_H__


