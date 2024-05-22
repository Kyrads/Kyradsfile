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

void TryAddUnitToRescueTargetList(struct Unit* unit) {

    if (!AreUnitsAllied(gSubjectUnit->index, unit->index)) {
        return;
    }

    if (gSubjectUnit->pClassData->number == CLASS_PHANTOM || unit->pClassData->number == CLASS_PHANTOM) {
        return;
    }

    if (unit->statusIndex == UNIT_STATUS_BERSERK) {
        return;
    }

    if (unit->state & (US_RESCUING | US_RESCUED)) {
        return;
    }

    if (!CanUnitRescue(gSubjectUnit, unit)) {
        return;
    }

    if(UNIT_CATTRIBUTES(unit) & (CA_MOUNTED | CA_PEGASUS | CA_WYVERN)){
    	return;
    }

    AddTarget(unit->xPos, unit->yPos, unit->index, 0);

    return;
}
