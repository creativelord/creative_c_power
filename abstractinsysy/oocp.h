#ifndef __OOPC__H__
#define __OOPC__H__


//��׼�ķ������Ƿ���
#define METHOD_OVERRIDE_STANDARD(instance,fun_Name)\
instance->parent.opt.fun_Name = instance->opt.fun_Name

//���ر��෽��
#define INSTANCE_LOAD_SELF_METHOD(domainName,instancePtr,funName)\
instancePtr->opt.funName=##domainName##_##funName;\
instancePtr->metaOpt.funName = ##domainName##_##funName;

//��������
#define SUPER_METHOD(domain,funname,...)\
domain->parent.metaOpt.funname(domain,##__VA_ARGS__);


#define THIS_METHOD(domain,funname,...)\
domain->opt.funname(domain,##__VA_ARGS__)



//�ֶη���
//#define SUPER_FIELD(domain,filedname)

//#define THIS_FIELD(domain,filedname)\



#endif // __OOPC__H__
