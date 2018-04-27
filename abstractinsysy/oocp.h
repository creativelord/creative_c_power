#ifndef __OOPC__H__
#define __OOPC__H__

#include "constructors.h"


//������д����ķ���
#define DOMAIN_THIS_OVERRIDE_SUPER_METHOD_DEF(fun_Name)\
cthis->parent.opt.fun_Name = cthis->opt.fun_Name

//���ر��෽��
#define DOMAIN_THIS_METHOD_LOAD(domainName,funName)\
cthis->opt.funName=##domainName##_##funName;\
cthis->metaOpt.funName = ##domainName##_##funName;

//���෽������
#define DOMAIN_SUPER_METHOD_CALL(funname,...)\
cthis->parent.metaOpt.funname(cthis,##__VA_ARGS__);

//���෽������(��ʾ����ת��,��ֹ��Щ������ �Բ�ͬ���͵�ָ��ת�� �о��棺���� Sub *sub��ָ��ת��ΪBase *�Ĺ���)
//GNU�ṩ�� typeof(value) ��̬ʶ���������ͺ�c++11��decltype(value)����
#define DOMAIN_SUPER_METHOD_EXPLICT_CALL(superClassName,funname,...)\
cthis->parent.metaOpt.funname((superClassName*)cthis,##__VA_ARGS__);


//���෽������
#define DOMAIN_THIS_METHOD_CALL(funname,...)\
cthis->opt.funname(cthis,##__VA_ARGS__)


//��̬�������������
#define DOMAIN_STATIC_METHOD_CALL(className,cthis,funname,...)\
className##_##funname(cthis,##__VA_ARGS__)
 

//�����ֶη���
#define DOMAIN_SUPER_FIELD(filedname)\
cthis->parent.filedname

//�����ֶη���
#define DOMAIN_THIS_FIELD(filedname)\
cthis->filedname






#endif // __OOPC__H__
