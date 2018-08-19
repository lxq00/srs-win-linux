#ifndef __HTTPPUBLIC_H__
#define __HTTPPUBLIC_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

#ifndef WIN32
#include<string>
#endif

#include "Defs.h"
#include "Base/Base.h"
using namespace Public::Base;

namespace Public {
namespace HTTP {


//���� http://user:pass@host.com:8080/p/a/t/h?query=string#hash
class HTTP_API URL
{
public:
	URL(const std::string& urlstr);
	URL(const URL& url);
	~URL();

	//http://user:pass@host.com:8080/p/a/t/h?query=string#hash
	std::string href() const;

	//http
	std::string protocol() const;

	//user:pass
	std::string auhen() const;

	//host.com:8080
	std::string host() const;
	//host.com
	std::string hostname() const;
	//8080
	uint32_t port() const;

	///p/a/t/h?query=string#hash
	std::string path() const;
	//p/a/t/h
	std::string pathname() const;
	//?query=string#hash
	std::string search() const;

	//<query,string#assh>
	std::map<std::string, std::string> query() const;
private:
	struct URLInternal;
	URLInternal* internal;
};


//HTMLģ���滻
//{{name}}	��������Ϊname
//{{#starttmp}} {{/starttmp}}		ѭ������ʼ�ͽ��� ѭ������Ϊstarttmp
class HTTP_API HTTPTemplate
{
public:
	struct TemplateObject
	{
		TemplateObject() {}
		virtual ~TemplateObject() {}

		//�����������ģ������ֵ std::map<��������,����ֵ> 
		virtual bool toTemplateData(std::map<std::string, URI::Value>& datamap) = 0;
	};
	//ѭ�����������ֵ�
	struct TemplateDirtionary
	{
		TemplateDirtionary() {}
		virtual ~TemplateDirtionary() {}
		virtual TemplateDirtionary* setValue(const std::string& key, const URI::Value&  value) = 0;
	};
public:
	HTTPTemplate(const std::string& tmpfilename);
	~HTTPTemplate();
	//����������ֵ
	HTTPTemplate& setValue(const std::string& key, const URI::Value&  value);
	//ѭ������������ѭ�� HTTPTemplate
	HTTPTemplate& setValue(const std::string& key, const std::vector<TemplateObject*>&  valuelist);
	//���ѭ������
	shared_ptr<TemplateDirtionary> addSectionDirtinary(const std::string& starttmpkey);

	std::string toValue() const;
private:
	struct HTTPTemplateInternal;
	HTTPTemplateInternal* internal;
};


typedef enum
{
	HTTPBufferCacheType_Mem,
	HTTPBufferCacheType_File,
}HTTPBufferCacheType;

class HTTP_API HTTPBuffer
{
public:
	HTTPBuffer(HTTPBufferCacheType type);
	~HTTPBuffer();

	//when end of file return ""
	int read(char* buffer, int len) const;
	int read(std::string& data) const;
	std::string read() const;
	uint64_t totalSize() const;
	bool readToFile(const std::string& filename) const;

	bool write(const char* buffer, int len);
	bool write(const std::string& data);
	bool write(const HTTPTemplate& temp);
	bool writeFromFile(const std::string& filename,bool deleteFile);
private:
	struct HTTPBufferInternal;
	HTTPBufferInternal *internal;
};


}
}

#endif