#include "gbafe.h"
extern u8 ThrowablesList[];
enum 
{ 
CannotDouble = 0, 
ForceDouble = 1, 
NoChange = 2,
}; 

int ThrowablesProperty(struct BattleUnit* battleUnit){
	int i = 0;
	while(true){
		u8 item = ThrowablesList[i];
		if(ITEM_INDEX(battleUnit->weapon) == item){
			if(gBattleStats.range!=1){
				return CannotDouble;
			}
			return NoChange;
		}
		if(item == 0){
			break;
		}
		i++;
	}
	return NoChange;
}