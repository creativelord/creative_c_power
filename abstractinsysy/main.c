#include <stdio.h>
#include "share_layer3.h"
#include "share_layer2.h"


int main() {
	
	layer2_share_domain_t *domain2 = createLayer2ShareDomain();
	//domain2->opt.del(domain2);

	share_domain_t *super = (share_domain_t*)domain2;
	super->opt.del(super);

	system("pause");
	return 0;
}
