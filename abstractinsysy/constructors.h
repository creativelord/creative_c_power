#ifndef __CONSTRUCTOR__H__

//����Ȩ�ޱ�ʶ  ˽��
#define PRIVATE_FLAG static
//����Ȩ�ޱ�ʶ  ����
#define PUBLIC_FLAG  

#define DOMAIN_METHOD(PREVALLIAGE,RET_TYPE,DOMAIN_TYPE,FUN_NAME,...)\
 PREVALLIAGE RET_TYPE DOMAIN_TYPE##_##FUN_NAME(DOMAIN_TYPE *cthis,##__VA_ARGS__)

#endif // __CONSTRUCTOR__H__
