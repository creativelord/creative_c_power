 
#include <stdio.h>
#include <stdlib.h>
#include "share_layer2.h"
#include "share.h"
#include "oocp.h"



 void layer2_share_domain_t_readBuffer(layer2_share_domain_t* domain, char * buffer, int size)
{
	printf("this is layer2_share_domain_t 的具体实现api readBuffer\n");

}
 void layer2_share_domain_t_loadFile(layer2_share_domain_t* domain, const char* filename)
{
	printf("this is layer2_share_domain_t的具体实现api loadFile\n");
}
 void layer2_share_domain_t_del(layer2_share_domain_t* domain)
{
	printf("this is layer2_share_domain_t 代码执行到二环，提醒准备释放内存 \n");
	//domain->parent.opt.share_domain_del(domain);
	SUPER_METHOD(domain,del)

}



 void layer2_share_domain_t_doSomeOverride(layer2_share_domain_t *domain) {
	 METHOD_OVERRIDE_STANDARD(domain,del);

	 // domain->self.del(domain)
     // domain->parent.self.del((share_domain*)domain)

	
 
      
	 
}

 void initL2DomainAndRetOpt(layer2_share_domain_t *domain)
{
	 //初始化 装载父类的方法
	initDomainOpt((share_domain_t*)domain);
	INSTANCE_LOAD_SELF_METHOD(layer2_share_domain_t, domain, del);
	INSTANCE_LOAD_SELF_METHOD(layer2_share_domain_t, domain, loadFile);
	INSTANCE_LOAD_SELF_METHOD(layer2_share_domain_t, domain, readBuffer);
	layer2_share_domain_t_doSomeOverride(domain);
	//初始化 装载本类的方法
}




  layer2_share_domain_t* createLayer2ShareDomain()
 {
	  layer2_share_domain_t* ret = malloc(sizeof(layer2_share_domain_t));
	  memset((char*)ret, 0, sizeof(layer2_share_domain_t));
	  initL2DomainAndRetOpt(ret);
 

	  return ret;
 }