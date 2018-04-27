#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "share.h"
#include "oocp.h"

static void share_domain_read(share_domain_t*  domain, char* buffer, int length)
{
	printf("this is share_domain_t�ײ�ľ���ʵ��api read\n");

}
static void share_domain_write(share_domain_t* domain, char* buffer, int writelen)
{
	printf("this is share_domain_t�ײ�ľ���ʵ��api write\n");
}
static void share_domain_del(share_domain_t** domain)
{
	printf(" ִ���� share_domain_t�ײ�ľ���ʵ�� ���� del\n");
	if (NULL==domain || NULL == *domain) return;
	free(*domain);
	*domain = NULL;
	
	printf("�ͷ���� ׼�������⻷ �û�̬����\n");
}
static void share_domain_getRecordIndx(share_domain_t* domain)
{
	printf("this is share_domain_t�ײ�ľ���ʵ��api getRecordIndx\n");
}

void initDomainOpt(share_domain_t *domain)
{
	INSTANCE_LOAD_SELF_METHOD(share_domain, domain, del);
	INSTANCE_LOAD_SELF_METHOD(share_domain, domain, read);
	INSTANCE_LOAD_SELF_METHOD(share_domain, domain, write);
	INSTANCE_LOAD_SELF_METHOD(share_domain, domain, getRecordIndx);
	 
	
}