#include <stdlib.h>
#include <stdlib.h>
#include "share_layer3.h"
#include "share_layer2.h"
extern void initL3DomainAndRetOpt(layer3_share_domain_t *domain)
{
	initL2DomainAndRetOpt((layer2_share_domain_t*)domain);
}

 layer3_share_domain_t * createLayer3ShareDomain()
{
	layer3_share_domain_t* ret = malloc(sizeof(layer3_share_domain_t));
	memset((char*)ret, 0, sizeof(layer3_share_domain_t));
	initL3DomainAndRetOpt(ret);
	return ret;
}


void(*read)(layer3_share_domain_t*  domain, char* buffer, int length);
void(*write)(layer3_share_domain_t* domain, char* buffer, int writelen);
void(*loop)(layer3_share_domain_t * domain);