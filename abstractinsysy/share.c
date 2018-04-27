#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "share.h"
#include "oocp.h"


DOMAIN_METHOD(PRIVATE_FLAG, void, share_domain, read, char* buffer, int length)
{
	printf("this is share_domain_t底层的具体实现api read\n");
}

DOMAIN_METHOD(PRIVATE_FLAG, void, share_domain,write,char* buffer, int writelen)
{
	printf("this is share_domain_t底层的具体实现api write\n");
}
DOMAIN_METHOD(PRIVATE_FLAG, void, share_domain, del, char* buffer, int writelen)
{
	printf(" 执行了 share_domain_t底层的具体实现 函数 del\n");
	if (NULL==cthis) return;
	free(cthis);
	printf("释放完毕 准备返回外环 用户态代码\n");
}
DOMAIN_METHOD(PRIVATE_FLAG, void, share_domain, getRecordIndx)
{
	printf("this is share_domain_t底层的具体实现api getRecordIndx\n");
}

DOMAIN_METHOD(PUBLIC_FLAG, void, share_domain, initDomainOpt)
{
	DOMAIN_THIS_METHOD_LOAD(share_domain, del);
	DOMAIN_THIS_METHOD_LOAD(share_domain, read);
	DOMAIN_THIS_METHOD_LOAD(share_domain, write);
	DOMAIN_THIS_METHOD_LOAD(share_domain, getRecordIndx);
}

 