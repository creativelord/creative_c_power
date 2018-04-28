#include <stdlib.h>
#include "share_layer3.h"
#include "share_layer2.h"
#include "oocp.h"

DOMAIN_METHOD(PRIVATE_FLAG, void, layer3_share_domain,initL3DomainAndRetOpt)
{
	DOMAIN_STATIC_METHOD_CALL(layer2_share_domain, cthis ,initL2DomainAndRetOpt);

}
 
 layer3_share_domain_t * createLayer3ShareDomain()
{
	layer3_share_domain_t* ret = malloc(sizeof(layer3_share_domain_t));
	memset((char*)ret, 0, sizeof(layer3_share_domain_t));
	
	DOMAIN_STATIC_METHOD_CALL(layer3_share_domain, ret, initL3DomainAndRetOpt,10);

	return ret;
}
