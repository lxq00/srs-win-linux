#ifndef __COREDUMP_H__
#define __COREDUMP_H__
#include "Base/Time.h"
#include "Base/IntTypes.h"
#include "Defs.h"

namespace Public {
namespace Base {


class BASE_API CoreDump
{
public:
	//�Զ�����core dump,save path Ϊdump�ļ�����·��
	static void audoCoreDump(const std::string& savePath="./");

	//ȡ���Զ�dump
	static void cleanAudoCoreDump();

	//��ȡdump������¼
	static bool getCoreDumpRecord(std::list<Time>& record,const std::string& savePath="./");

	static bool cleanAndSyncReocrd(const std::string& savePath="./");

	//���dump��Ϣ��maxDay���������ļ�¼��maxNum������ٸ�dump
	static bool cleanCoreDumpReocrdByTimeout(uint32_t maxDay = 15,uint32_t maxNum = 3,const std::string& savePath="./");

	//�������dump���ȹؼ�¼
	static bool cleanCoreDumpReocrd(const std::string& savePath="./");

	//���ѹ��dump�ļ�
	static bool getCoreDumpFileList(std::list<std::string>& filelist,const std::string& savePath="./");
};


}
}
#endif //__COREDUMP_H__
