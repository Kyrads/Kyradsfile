#include "gbafe.h"
extern int(*gprGotoConGetter)(struct Unit* unit);

int GetAidFromUnit(struct Unit* unit){
	if(unit->pClassData->attributes&(CA_MOUNTED|CA_WYVERN)){
		return 25-gprGotoConGetter(unit);
		}
	if(unit->pClassData->attributes&CA_PEGASUS){
		return 20-gprGotoConGetter(unit);
		}
	return gprGotoConGetter(unit)-1;
	}
