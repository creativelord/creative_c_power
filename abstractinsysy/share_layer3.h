#ifndef   __SHARE_LAYER3_H__
#define  __SHARE_LAYER3_H__
#include "share_layer2.h"

 struct layer3_share_domain;
 typedef struct layer3_share_domain layer3_share_domain;
 typedef struct layer3_share_domain  layer3_share_domain_t;

  typedef struct layer3_share_opt {
	  void(*read)(layer3_share_domain_t*  domain, char* buffer, int length);
	  void(*write)(layer3_share_domain_t* domain, char* buffer, int writelen);
	  void(*loop)(layer3_share_domain_t * domain);
}layer3_share_opt_t;

 struct layer3_share_domain {
	  layer2_share_domain_t parent;
	  layer3_share_opt_t opt;
	  layer3_share_opt_t metaOpt;   
  };

extern struct layer3_share_domain* createLayer3ShareDomain();
#endif