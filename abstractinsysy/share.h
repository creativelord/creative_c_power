#ifndef __SHARE__
#define __SHARE__

struct share_domain;
typedef struct share_domain share_domain_t;
typedef struct share_opt
{
	void(*read)(share_domain_t*  domain,char* buffer, int length);
	void(*write)(share_domain_t* domain,char* buffer, int writelen);
	void(*del)(share_domain_t** domain);
	void(*getRecordIndx)(share_domain_t* domain);

}share_opt_t;




 struct share_domain
{
	int index;//Ë÷Òý
	int recordIndex_DB;
	//other p
	share_opt_t metaOpt;
	share_opt_t opt;
	
};

extern void initDomainOpt(share_domain_t* domain);

#endif