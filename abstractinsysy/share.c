#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "share.h"
#include "oocp.h"


DOMAIN_METHOD(PRIVATE_FLAG, void, share_domain, read, char* buffer, int length)
{
	printf("this is share_domain_t�ײ�ľ���ʵ��api read\n");
}

DOMAIN_METHOD(PRIVATE_FLAG, void, share_domain,write,char* buffer, int writelen)
{
	printf("this is share_domain_t�ײ�ľ���ʵ��api write\n");
}
DOMAIN_METHOD(PRIVATE_FLAG, void, share_domain, del, char* buffer, int writelen)
{
	printf(" ִ���� share_domain_t�ײ�ľ���ʵ�� ���� del\n");
	if (NULL==cthis) return;
	free(cthis);
	printf("�ͷ���� ׼�������⻷ �û�̬����\n");
}
DOMAIN_METHOD(PRIVATE_FLAG, void, share_domain, getRecordIndx)
{
	printf("this is share_domain_t�ײ�ľ���ʵ��api getRecordIndx\n");
}

DOMAIN_METHOD(PUBLIC_FLAG, void, share_domain, initDomainOpt)
{
	DOMAIN_THIS_METHOD_LOAD(share_domain, del);
	DOMAIN_THIS_METHOD_LOAD(share_domain, read);
	DOMAIN_THIS_METHOD_LOAD(share_domain, write);
	DOMAIN_THIS_METHOD_LOAD(share_domain, getRecordIndx);
}

 