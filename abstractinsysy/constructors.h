#ifndef __CONSTRUCTOR__H__

//访问权限标识  私有
#define PRIVATE_FLAG static
//访问权限标识  公开
#define PUBLIC_FLAG  

#define DOMAIN_METHOD(PREVALLIAGE,RET_TYPE,DOMAIN_TYPE,FUN_NAME,...)\
 PREVALLIAGE RET_TYPE DOMAIN_TYPE##_##FUN_NAME(DOMAIN_TYPE *cthis,##__VA_ARGS__)

#endif // __CONSTRUCTOR__H__
