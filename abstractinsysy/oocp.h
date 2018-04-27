#ifndef __OOPC__H__
#define __OOPC__H__

#include "constructors.h"


//本类重写父类的方法
#define DOMAIN_THIS_OVERRIDE_SUPER_METHOD_DEF(fun_Name)\
cthis->parent.opt.fun_Name = cthis->opt.fun_Name

//加载本类方法
#define DOMAIN_THIS_METHOD_LOAD(domainName,funName)\
cthis->opt.funName=##domainName##_##funName;\
cthis->metaOpt.funName = ##domainName##_##funName;

//父类方法调用
#define DOMAIN_SUPER_METHOD_CALL(funname,...)\
cthis->parent.metaOpt.funname(cthis,##__VA_ARGS__);

//父类方法调用(显示向父类转型,防止有些编译器 对不同类型的指针转型 有警告：例如 Sub *sub的指针转换为Base *的过程)
//GNU提供了 typeof(value) 动态识别数据类型和c++11的decltype(value)类似
#define DOMAIN_SUPER_METHOD_EXPLICT_CALL(superClassName,funname,...)\
cthis->parent.metaOpt.funname((superClassName*)cthis,##__VA_ARGS__);


//本类方法调用
#define DOMAIN_THIS_METHOD_CALL(funname,...)\
cthis->opt.funname(cthis,##__VA_ARGS__)


//静态方法调用类对象
#define DOMAIN_STATIC_METHOD_CALL(className,cthis,funname,...)\
className##_##funname(cthis,##__VA_ARGS__)
 

//父类字段访问
#define DOMAIN_SUPER_FIELD(filedname)\
cthis->parent.filedname

//本类字段访问
#define DOMAIN_THIS_FIELD(filedname)\
cthis->filedname






#endif // __OOPC__H__
