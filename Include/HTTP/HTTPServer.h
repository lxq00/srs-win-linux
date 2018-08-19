#ifndef __HTTPSERVER_H__
#define __HTTPSERVER_H__
#include "HTTPPublic.h"
#include "Base/Base.h"
using namespace Public::Base;
namespace Public {
namespace HTTP {

class HTTP_API HTTPServer
{
public:
	class HTTP_API HTTPRequest
	{
		friend class HTTPServer;
	public:
		HTTPRequest(HTTPBufferCacheType type);
		~HTTPRequest();

		std::string header(const std::string& key) const;
		std::string method() const;
		shared_ptr<URL> url() const;
		shared_ptr<HTTPBuffer> buffer() const;
	private:
		struct HTTPRequestInternal;
		HTTPRequestInternal* internal;
	};

	class HTTP_API HTTPResponse
	{
		friend class HTTPServer;
	public:
		HTTPResponse(HTTPBufferCacheType type);
		~HTTPResponse();

		bool statusCode(uint32_t code, const std::string& statusMessage = "");

		//����ͷ�ظ���ͷ��Ϣ��Content-Length ��Ч
		bool setHeader(const std::string& key, const URI::Value& val);

		shared_ptr<HTTPBuffer> buffer();

		//end�󽫻ᷢ�����ݣ�buffer����������Ч
		bool end();
	private:
		struct HTTPResponseInternal;
		HTTPResponseInternal* internal;
	};

	typedef Function2<void,const shared_ptr<HTTPRequest>&,shared_ptr<HTTPResponse>&> HttpListenCallback;
public:

	HTTPServer(const std::string& webrootpath,const std::string& cachedir="./", HTTPBufferCacheType type = HTTPBufferCacheType_Mem);
	~HTTPServer();	
	
	// path Ϊ �����url,*Ϊ����  ,callback������Ϣ�Ļص�,�����߳����ݣ�����run����
	bool listen(const std::string& path,const HttpListenCallback& callback);

	//�첽����
	bool run(uint32_t httpport);
private:
	struct HTTPServrInternal;
	HTTPServrInternal* internal;
};


}
}


#endif //__HTTPSERVER_H__