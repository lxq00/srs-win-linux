//
//  Copyright (c)1998-2012, Public Technology
//  All Rights Reserved.
//
//	Description:
//	$Id: MemPool.h 255 2014-01-23 03:28:32Z  $
//
#ifndef __DYNAMIC_MEMORYPOOL_H__
#define __DYNAMIC_MEMORYPOOL_H__
#include "Base/Defs.h"
#include "Base/IntTypes.h"
namespace Public{
namespace Base{

///�ڴ���趨������Publicmedia��Ҳ���������ط�ʹ��
class BASE_API DynamicMemPool
{
	class MemPoolInternal;
public:
	DynamicMemPool();
	~DynamicMemPool();

	/// �ڴ���䡢ʧ�ܷ���NULL
	void* Malloc(uint32_t size,uint32_t& realsize);
	
	/// �ڴ��ͷ�
	void Free(void*);

	/// �ڴ�ʹ�ô�ӡ
//	void dump();

	///�����ڴ���ܴ�С��Ĭ��Ϊ128M
//	static void config(uint32_t allSize);

	static DynamicMemPool*	instance();
private:
	MemPoolInternal*	internal;
};

#define gDynamicMemPool							(*DynamicMemPool::instance())
#define Dynamic_Malloc(size,realsize)				gDynamicMemPool.Malloc(size,realsize)
#define Dynamic_Free(addr)							{gDynamicMemPool.Free(addr); addr = NULL;}

class BASE_API DynamicMallocFreeMem:public IMallcFreeMemObjcPtr
{
public:
	DynamicMallocFreeMem(){}
	~DynamicMallocFreeMem(){}

	void* Malloc(uint32_t size,uint32_t& realsize)
	{
		return Dynamic_Malloc(size,realsize);
	}
	void Free(void* addr)
	{
		Dynamic_Free(addr);
	}
};

static DynamicMallocFreeMem dynamicMemObjc;

#define GDynamicMemObjcPtr &dynamicMemObjc

} // namespace Base
} // namespace Public


#endif //__DYNAMIC_MEMORYPOOL_H__
