#ifndef __VGSII_URI_H__
#define __VGSII_URI_H__
#include "Base/Defs.h"
#include "Base/IntTypes.h"
#include <string>
#include <list>
using namespace std;
namespace Public{
namespace Base{


class BASE_API URI
{
	struct URIInternal;
public:
	class BASE_API Value
	{
	public:
		typedef enum 
		{
			Type_String,
			Type_Char,
			Type_Int32,
			Type_Double,
			Type_Bool,
			Type_Int64,
		}Type;
	public:
		Value() {}
		Value(const std::string& val);
		Value(char val);
		Value(const char* val);
		Value(const unsigned char* val);
		Value(int val);
		Value(double val);
		Value(bool val);
		Value(long long val);
		Value(uint32_t val);
		Value(uint64_t val);
		Value(const Value& val);
		~Value();

		Value& operator = (const Value& val)
		{
			valuestring = val.valuestring; 
			return*this;
		}

		std::string readString() const;
		int readInt() const;
		float readFloat() const;
		long long readInt64() const;
		bool readBool() const;
		uint32_t readUint32() const;
		uint64_t readUint64() const;
		Type type() const;

		bool isEmpty() const;
	private:
		std::string valuestring;
		Type		valuetype;
	};
	struct BASE_API URIObject
	{
		std::string	key;
		Value		val;
		//������Identifier
		std::string toStringAsIdentifier();
		//������ExtParameter��Parameter
		std::string toStringAsParameter();
	};
public:
	//protocol Э�� �磺HTTP/FTP/VDR��
	URI(const std::string& protocol,const Value& host,int port = 0);
	URI(const URI& uri);
	~URI();

	bool setProtocol(const std::string& protocol);
	
	bool setHost(const std::string& host,int port = 0);


	//��ӵ�ַ��ʶ�� val����Ϊ��
	//VDR://local/dvsid/610001/Storages/C?camera=camera/1&date=2012-3-5
	//dvsid/storages
	bool addIdentifier(const std::string& mark,const Value& val);

	//��Ӳ���
	//VDR://local/dvsid/610001/Storages/C?camera=camera/1&date=2012-3-5
	//camera /date
	bool addParameter(const std::string& key,const Value& val);
		

	//ɾ��һ����ַ��ʶ������Ӧ��ֵ
	bool removeIndentifier(const std::string& mark);
	//ɾ��һ����������Ӧ��ֵ
	bool removeParameter(const std::string& key);

	//��ȡ�����ַ���
	std::string getParmeterString() const;
	//���ַ��ķ�ʽ��Ӹ��Ӳ���
	bool addParmeterString(const std::string& exstring);

	//��ȡһ����ַ��ʶ��  NULL��ʾʧ��
	Value* getIdentifier(const std::string& mark) const;
	//��ȡһ������ NULL��ʾʧ��
	Value* getParameter(const std::string& key) const;


	//��ȡ��ַ��ʶ������
	std::list<URIObject> getIndentifierList() const;
	//��ȡ��������
	std::list<URIObject> getParmeterList() const;

	
	//��ȡЭ��
	std::string& getProtocol() const;
	//��ȡЭ��
	Value getHost() const;

	//��ȡ�˿�		0��ʾ��
	int getPort() const;
	
	//ת��uri�ַ���
	std::string toString() const;

	///��ȡ��������ַ�������������������չ����
	std::string getBasicString() const;

	//Э��uri�ַ���
	bool parse(const std::string& uri);

	URI& operator = (const URI& uri);
private:
	URIInternal* internal;
};


}
}

#endif //__VGSII_URI_H__
