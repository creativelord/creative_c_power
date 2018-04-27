#ifndef __OOPC__H__
#define __OOPC__H__


//标准的方法覆盖方法
#define METHOD_OVERRIDE_STANDARD(instance,fun_Name)\
instance->parent.opt.fun_Name = instance->opt.fun_Name

//加载本类方法
#define INSTANCE_LOAD_SELF_METHOD(domainName,instancePtr,funName)\
instancePtr->opt.funName=##domainName##_##funName;\
instancePtr->metaOpt.funName = ##domainName##_##funName;

//方法调用
#define SUPER_METHOD(domain,funname,...)\
domain->parent.metaOpt.funname(domain,##__VA_ARGS__);


#define THIS_METHOD(domain,funname,...)\
domain->opt.funname(domain,##__VA_ARGS__)



//字段访问
//#define SUPER_FIELD(domain,filedname)

//#define THIS_FIELD(domain,filedname)\



#endif // __OOPC__H__
