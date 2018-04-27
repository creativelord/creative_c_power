#ifndef __SHARE_LAYER_H__
#define  __SHARE_LAYER_H__

#include "share.h"

struct layer2_share_domain;
typedef struct layer2_share_domain layer2_share_domain_t;
typedef struct layer2_share_opt {
	void(*readBuffer)(layer2_share_domain_t* domain, char * buffer, int size);
	void(*loadFile)(layer2_share_domain_t* domain,const char* filename);
	void (*del)(layer2_share_domain_t* domain);
}layer2_share_opt_t;

 struct layer2_share_domain {
	share_domain_t  parent;
	layer2_share_opt_t opt;
	layer2_share_opt_t metaOpt;
 
};

extern void initL2DomainAndRetOpt(layer2_share_domain_t *domain);
extern layer2_share_domain_t* createLayer2ShareDomain();


 
#endif // __SHARE_LAYER_H__
