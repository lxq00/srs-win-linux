#ifndef __EXPRESSION_H__EVAL_H__
#define __EXPRESSION_H__EVAL_H__
#include "Base/IntTypes.h"
namespace Public {
namespace Base {

///������ʽִ�п�
class BASE_API Expression
{
public:
	///ִ�б��ʽ������ֵΪbool,�� (1>=2 || 2 >= 0)
	static bool evalBool(const std::string& expression);

	//ִ�б��ʽ������ֵ,�� 1 + 2 * 3
	static std::string evalVal(const std::string& expression);
};

}
}

#endif //__EXPRESSION_H__EVAL_H__
