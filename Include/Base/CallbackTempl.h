//
//  Copyright (c)1998-2012, Public Technology
//  All Rights Reserved.
//
//	Description:
//	$Id: CallbackTempl.h 3 2013-01-21 06:57:38Z  $

/// \class CallbackX
/// \brief �ź���ģ�顣
///
/// һ���źű�����ʱ��������������ӵ����ϵ�TFunctionN����ֻ֧��
/// ����ֵΪvoid��FunctionN��CALLBACK_TEMPL��һ���꣬���ݲ��������ᱻ�滻��
/// CallbackN���û�ͨ�� CallbackN<T1, T2, T3,..,TN>��ʽ��ʹ�ã�TN��ʾ�������ͣ�
/// N��ʾ��������������Ŀǰ������Ϊ6��

#define CALLBACK_TEMPL MACRO_JOIN(Callback,CALLBACK_NUMBER)
#define FUNCTION_TEMPL MACRO_JOIN(Function, CALLBACK_NUMBER)

#if (CALLBACK_NUMBER != 0)
template <CALLBACK_CLASS_TYPES>
#endif
class CALLBACK_TEMPL
{
	/// �ص��ڵ���Ϣ
	enum NodeState
	{
		nodeStateEmpty,		///< �ڵ�Ϊ��
		nodeStateNormal,	///< �ڵ�������
	};

public:
	/// �ڵ���ص�λ��
	enum NodePosition
	{
		any,				///< ����ط�
		back,				///< ������ĩβ
		front				///< ������ͷ��
	};

	/// ������
	enum ErrorCode
	{
		errorNoFound = -1,		///< û���ҵ��ƶ��Ķ���
		errorExsist = -2,		///< �����Ѿ�����
		errorFull = -3,			///< �Ѿ������ܹ����ӵĶ����������
		errorEmptyProc = -4,	///< ��������ĺ���ָ��Ϊ�գ�û������
	};

	/// ���ź�ģ���������ƥ��ĺ���ָ���������
	typedef FUNCTION_TEMPL<void CALLBACK_TYPES_COMMA> Proc;

private:
	/// ��ṹ
	struct CallbackNode
	{
		Proc proc;
		NodeState state;
		bool running;
		uint32_t cost;
	};

	int numberMax;
	int number;
	CallbackNode* nodes;
	Mutex mutex;
	int	threadId;

public:
	/// ���캯��
	/// \param maxNodes �ܹ����ӵ������ָ�����ĸ���
	CALLBACK_TEMPL(int maxNodes) :
	  numberMax(maxNodes), number(0), threadId(-1)
	{
		nodes = new(std::nothrow) CallbackNode[maxNodes];
		for(int i = 0; i < numberMax; i++)
		{
			nodes[i].state = nodeStateEmpty;
			nodes[i].running = false;
		}
	}

	 /// ��������
	~CALLBACK_TEMPL()
	{
		delete []nodes;
	}

	/// ���غ���ָ�����
	/// \param proc ����ָ�����
	/// \param position �������λ��
	/// \retval >=0 ���ú��Ѿ����ص��źŵĺ���ָ��������
	/// \retval <0 errorCode���͵Ĵ�����
	int attach(Proc proc, NodePosition position = any)
	{
		int i;

		if(proc.empty())
		{
			return errorEmptyProc;
		}

		if(isAttached(proc))
		{
			return errorExsist;
		}

		Guard guard(mutex);

		switch(position)
		{
		case any:
			for(i = 0; i < numberMax; i++)
			{
				if(nodes[i].state == nodeStateEmpty)
				{
					nodes[i].proc  = proc;
					nodes[i].state = nodeStateNormal;

					return ++number;
				}
			}
			break;
		case back:
			for(i = numberMax - 1; i >= 0; i--)
			{
				if(nodes[i].state == nodeStateEmpty)
				{
					for(int j = i; j < numberMax - 1; j++)
					{
						nodes[j] = nodes[j + 1];
					}
					nodes[numberMax - 1].proc  = proc;
					nodes[numberMax - 1].state = nodeStateNormal;

					return ++number;
				}
			}
			break;
		case front:
			for(i = 0; i < numberMax; i++)
			{
				if(nodes[i].state == nodeStateEmpty)
				{
					for(int j = i; j > 0; j--)
					{
						nodes[j] = nodes[j - 1];
					}
					nodes[0].proc  = proc;
					nodes[0].state = nodeStateNormal;

					return ++number;
				}
			}
			break;
		}

		return errorFull;
	}

	/// ж�غ���ָ����󣬸��ݶ����б���ĺ���ָ����ƥ�䡣
	/// \param proc ����ָ�����
	/// \param wait �Ƿ�ȴ����ڽ��еĻص�������һ����ʹ���߶���������ʱ����Ҫ�ȴ���
	///             ������ڻص�������ж�أ����ܵȴ����ȴ�Ҫ�ر�С�ģ���ֹ����.
	/// \retval >=0 ���ú��Ѿ����ص��źŵĺ���ָ��������
	/// \retval <0 errorCode���͵Ĵ�����
	int detach(Proc proc, bool wait = false)
	{
		if (proc.empty())
		{
			return errorEmptyProc;
		}

		Guard guard(mutex);

		for (int i = 0; i < numberMax; i++)
		{
			if(nodes[i].proc ==  proc
				&& nodes[i].state == nodeStateNormal)
			{
				/// �ص��̺߳�stop�̲߳���ͬһ�߳�ʱ������Ҫ�ȴ�������ȴ�����������
				if(wait && nodes[i].running && Thread::getCurrentThreadID() != threadId)
				{
					while(nodes[i].running)
					{
						mutex.leave();
						Thread::sleep(1);
						loginfo("CALLBACK_TEMPL::Detach wait callback exit!\n");
						mutex.enter();
					}
				}

				nodes[i].state = nodeStateEmpty;
				return --number;
			}
		};

		return errorNoFound;
	}

	/// ж������ָ�����
	/// \param wait �Ƿ�ȴ����ڽ��еĻص�������һ����ʹ���߶���������ʱ����Ҫ�ȴ���
	///             ������ڻص�������ж�أ����ܵȴ����ȴ�Ҫ�ر�С�ģ���ֹ����.
	/// \retval >=0 ���ú��Ѿ����ص��źŵĺ���ָ��������
	/// \retval <0 errorCode���͵Ĵ�����
	int detachall(bool wait = false)
	{
		Guard guard(mutex);

		for (int i = 0; i < numberMax; i++)
		{
			if(nodes[i].state == nodeStateNormal)
			{
				/// �ص��̺߳�stop�̲߳���ͬһ�߳�ʱ������Ҫ�ȴ�������ȴ�����������
				if(wait && nodes[i].running && Thread::getCurrentThreadID() != threadId)
				{
					while(nodes[i].running)
					{
						mutex.leave();
						Thread::sleep(1);
						loginfo("CALLBACK_TEMPL::Detach wait callback exit!\n");
						mutex.enter();
					}
				}

				nodes[i].state = nodeStateEmpty;
				--number;
			}
		};
		return number;
	}

	
	/// �ж�ж�غ���ָ������Ƿ���أ����ݶ����б���ĺ���ָ����ƥ�䡣
	/// \param proc ����ָ�����
	bool isAttached(Proc proc)
	{
		Guard guard(mutex);

		if(proc.empty())
		{
			return false;
		}

		for(int i = 0; i < numberMax; i++)
		{
			if(nodes[i].proc ==  proc
				&& nodes[i].state == nodeStateNormal)
			{
				return true;
			}
		}

		return false;
	}

	/// ����()������������Ժ����������ʽ���������ӵ��źŵ����к���ָ�롣
	inline void operator()(CALLBACK_TYPE_ARGS)
	{
		Guard guard(mutex);
		uint64_t us1 = 0, us2 = 0;

		threadId = Thread::getCurrentThreadID(); // ����ص��߳�ID

		for(int i = 0; i < numberMax; i++) // call back functions one by one
		{
			if(nodes[i].state == nodeStateNormal)
			{
				Proc temp = nodes[i].proc;

				nodes[i].running = true;
				mutex.leave();

				// ����ִ��������ͳ��
	 			us1 = Time::getCurrentMicroSecond();
				temp(CALLBACK_ARGS);
				us2 = Time::getCurrentMicroSecond();
				nodes[i].cost = (us1 <= us2) ? uint32_t(us2 - us1) : 1;

				mutex.enter();
				nodes[i].running = false;
			}
		}
	}

	void stat()
	{
		int i;

		Guard guard(mutex);

		for(i = 0; i < numberMax; i++)
		{
			if(nodes[i].state == nodeStateNormal)
			{
				printf("\t%8d us, %p, %s\n",
				 nodes[i].cost,
				 nodes[i].proc.getObject(),
				 nodes[i].proc.getObjectType());
			}
		}
	}
};

#undef CALLBACK_TEMPL
#undef FUNCTION_TEMPL

