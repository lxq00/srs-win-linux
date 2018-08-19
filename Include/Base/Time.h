//
//  Copyright (c)1998-2014, Public Technology
//  All Rights Reserved.
//
//
//	Description:
//	$Id: Time.h 226 2013-10-29 09:10:03Z  $


#ifndef __BASE_TIME_H__
#define __BASE_TIME_H__

#include <string>
#include "Defs.h"
#include "IntTypes.h"


namespace Public {
namespace Base {



/// ʱ��ṹ��
typedef struct
{
	int  year;		///< �ꡣ
	int  month;		///< �£�January = 1, February = 2, and so on.
	int  day;		///< �ա�
	int  wday;		///< ���ڣ�Sunday = 0, Monday = 1, and so on
	int  hour;		///< ʱ��
	int  minute;	///< �֡�
	int  second;	///< �롣
	int  timeZone;	 //��ʾ����ʱ����UTCʱ��Ĳ��λ���ӣ����й�+08:00�� Ϊ +480
}SystemTime;

/// \class Time
/// \brief ʱ����
class BASE_API Time : public SystemTime
{
public:
	/// ����˳���ʽ
	enum DateFormat
	{
		ymd,
		mdy,
		dmy
	};

	/// ��ʽ��ģʽѡ��
	enum FormatMask
	{
		fmGeneral = 0,		///< ָֻ���Ƿ���ʾ�Լ���ʼֵ
		fmSeparator = 1,	///< ָ���ָ���
		fmDateFormat = 2,	///< ָ��������˳��
		fmHourFormat = 4,	///< ָ��Сʱ��ʽ

		fmAll = fmSeparator | fmDateFormat | fmHourFormat	///< ָ�����и�ʽѡ��
	};

	/// ȱʡ���캯��
	Time();

	/// ���ʱ�乹�캯��
	/// \param time [in] ���ʱ��
	Time(uint64_t time);

	Time(const SystemTime& time);

	/// ��ͨʱ�乹�캯��
	/// \param vyear 	[in] ��
	/// \param vmonth [in] ��
	/// \param vday 	[in]����
	/// \param vhour 	[in] Сʱ
	/// \param vmin [in] ��
	/// \param vsec [in] ��
	/// \param tzdiff[in] ��UTC������ʱ��Ĭ��Ϊ��������Ϊ-8*60
	Time(int vyear, int vmonth, int vday, int vhour, int vmin, int vsec);

	/// �õ�UTCʱ�䣬���ʱ��ָ��GMT 1970-1-1 00:00:00 ��ĳ��ʱ�̾���������
	/// \retval ���ʱ��
	uint64_t makeTime() const;

	/// �ֽ�UTCʱ��
	/// \param time [in] ���ʱ��
	void breakTime(uint64_t time);

	/// ʱ�����
	/// \param seconds [in] ���ڵ�����
	/// \retval ���ں��µ�ʱ�����
	Time operator +( int64_t seconds ) const;

	/// ʱ�����
	/// \param seconds [in] ���ڵ�����
	/// \retval ���ں��µ�ʱ�����
	Time operator -( int64_t seconds ) const;

	/// ʱ�������
	/// \param time [in] ��Ƚϵ�ʱ��
	/// \retval �ȽϵĽ����Ϊ(*this - time)�õ�������
	int64_t operator -( const Time& time ) const;

	/// ʱ�����
	/// \param seconds [in] ���ڵ�����
	/// \retval ������
	Time& operator +=( int64_t seconds );

	/// ʱ�����
	/// \param seconds [in] ���ڵ�����
	/// \retval ������
	Time& operator -=( int64_t seconds );

	/// ʱ��Ƚ�
	/// \param time  [in]��Ƚϵ�ʱ��
	/// \retval true ��ȣ�
	/// \retval false ����
	bool operator == (const Time& time) const;

	/// ʱ��Ƚ�
	/// \param time  [in]��Ƚϵ�ʱ��
	/// \retval true ����
	/// \retval false ���
	bool operator != (const Time& time) const;

	/// ʱ��Ƚ�
	/// \param time  [in] ��Ƚϵ�ʱ��
	/// \retval true С�� 
	/// \retval false ��С��
	bool operator < (const Time& time) const;

	/// ʱ��Ƚ�
	/// \param time  [in] ��Ƚϵ�ʱ��
	/// \retval true С�ڵ���
	/// \retval false ����
	bool operator <= (const Time& time) const;

	/// ʱ��Ƚ�
	/// \param time  [in] ��Ƚϵ�ʱ��
	/// \retval true ����
	/// \retval false ������
	bool operator > (const Time& time) const;

	/// ʱ��Ƚ�
	/// \param time [in] ��Ƚϵ�ʱ��
	/// \retval true ���ڵ���
	/// \retval false С��
	bool operator >= (const Time& time) const;

	/// ʱ���ʽ��
	/// \param buf  	[in]�ַ������壬һ��Ҫ�㹻��
	/// \param format [in] ��ʽ���ַ�������"yyyy-MM-dd HH:mm:ss tt"
	///									yy = �꣬�������� yyyy = �꣬������
	/// 								M = ��0��ʼ�� MM = 0��ʼ�� MMMM = ������
	/// 								d = ��0��ʼ�� dd = 0��ʼ��
	/// 								H = ��0��ʼ24Сʱ HH = 0��ʼ24Сʱ h = ��0��ʼ12Сʱ hh = 0��ʼ12Сʱ
	/// 								tt = ��ʾ���������
	/// \param mask 	[in] ��ʽѡ�ָ�����ڷָ�����������˳��Сʱ��ʽ�Ƿ���ͳһ�ĸ�
	///									ʽ��������Ӧλ��0����ʾʹ��ͳһ��ʽ����1����ʾʹ��formatָ���ĸ�ʽ
	std::string format(const std::string& format = "yyyy-MM-dd HH:mm:ss", int mask = fmGeneral) const;

	/// ʱ���ַ�������
	/// \param buf   [out] ������ַ�������
	/// \param format [in] ��ʽ���ַ�������ʱֻ֧��Ĭ�ϵ�"yyyy-MM-dd HH:mm:ss"
	/// \param mask [in] ��ʽѡ�ָ�����ڷָ�����������˳��Сʱ��ʽ�Ƿ���ͳһ�ĸ�
	///        					ʽ��������Ӧλ��0����ʾʹ��ͳһ��ʽ����1����ʾʹ��formatָ���ĸ�ʽ
	/// \retval  true �ɹ�
	/// \retval  false ʧ��
	bool parse(const std::string& buf, const std::string& format = "yyyy-MM-dd HH:mm:ss", int mask = fmGeneral);
	
	/// �õ����ص�ǰϵͳʱ��
	/// \retval Time����
	static Time getCurrentTime();

	/// ���ñ��ص�ǰϵͳʱ��
	/// \param time [in] �µ�ʱ��
	/// \param toleranceSeconds [in] �ݲ��ʾ��������ʱ��͵�ǰ��������ڲ����޸�
	static void setCurrentTime(const Time& time, int toleranceSeconds = 0);

	/// �õ���ϵͳ���������ڵĺ�����
	/// \retval ��ǰ�ĺ���ʱ��
	/// \notice ����Ƚ�ʱ�䣬���ܰ�getCurrentMilliSecond�� getCurrentMicroSecond��ֵ���жԱ�
	static uint64_t getCurrentMilliSecond();

	/// �õ���ϵͳ���������ڵ�΢����
	/// \retval  	��ǰ��΢��ʱ��
	/// \notice 	����Ƚ�ʱ�䣬���ܰ�getCurrentMilliSecond�� getCurrentMicroSecond��ֵ���жԱ�
	static uint64_t getCurrentMicroSecond();

	/// ����ʱ���ʽ����Ӱ��Format��������ַ�����ʽ����"yyyy-MM-dd HH:mm:ss"
	///  \param format [in] ��ʽ
	static void setFormat(const std::string& format);

	/// ��ȡʱ���ʽ
	///  \retval ʱ���ʽ���ַ���
	static const std::string getFormat();

	/// ��ȡ���ڸ�ʽ
	/// \retval ���ڸ�ʽ
	static DateFormat getDateFormat();

	/// ��ȡ��ǰ�Ƿ���12Сʱ��
	/// \retval true ��12Сʱ��
	/// \retval false ����12Сʱ��
	static bool get12Hour();

	/// ��ȡ���ڷָ��
	/// \retval �ָ��
	static char getSeparator();
};

} // namespace Base
} // namespace Public

#endif // __BASE_TIME_H__


