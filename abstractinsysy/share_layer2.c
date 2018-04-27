 
#include <stdio.h>
#include <stdlib.h>
#include "share_layer2.h"
#include "share.h"
#include "oocp.h"

DOMAIN_METHOD(PRIVATE_FLAG, void, layer2_share_domain, readBuffer, char * buffer, int size)
{
	printf("this is layer2_share_domain_t 的具体实现api readBuffer\n");
}

DOMAIN_METHOD(PRIVATE_FLAG, void, layer2_share_domain, loadFile,const char* filename)
{
	printf("this is layer2_share_domain_t 的具体实现api loadFile\n");
}


DOMAIN_METHOD(PRIVATE_FLAG, void, layer2_share_domain, del, const char* filename)
{
	printf("this is layer2_share_domain_t 代码执行到二环，提醒准备释放内存 \n");
	DOMAIN_SUPER_METHOD_CALL(del);
}

//我的重写方法
DOMAIN_METHOD(PRIVATE_FLAG, void, layer2_share_domain,doSomethingOverride, const char* filename)
{
	DOMAIN_THIS_OVERRIDE_SUPER_METHOD_DEF(del);
	
}


DOMAIN_METHOD(PUBLIC_FLAG, void, layer2_share_domain, initL2DomainAndRetOpt)
{
	//初始化 装载父类的方法
	DOMAIN_STATIC_METHOD_CALL(share_domain, cthis, initDomainOpt);
	DOMAIN_THIS_METHOD_LOAD(layer2_share_domain, del);
	DOMAIN_THIS_METHOD_LOAD(layer2_share_domain, loadFile);
	DOMAIN_THIS_METHOD_LOAD(layer2_share_domain, readBuffer);
	//layer2_share_domain_t_doSomeOverride(domain);
	DOMAIN_STATIC_METHOD_CALL(layer2_share_domain, cthis, doSomethingOverride, "WENWEPING.TXT");

	//初始化 装载本类的方法
}                                                                    


  layer2_share_domain_t* createLayer2ShareDomain()
 {
	  layer2_share_domain_t* ret = malloc(sizeof(layer2_share_domain_t));
	  memset((char*)ret, 0, sizeof(layer2_share_domain_t));

	  DOMAIN_STATIC_METHOD_CALL(layer2_share_domain,ret, initL2DomainAndRetOpt);
	  return ret;
 }