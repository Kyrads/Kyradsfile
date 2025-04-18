#include "gbafe.h"

#include "formulachanges.h"

//Damage Formula
void ComputeBattleUnitAttack(struct BattleUnit* attacker, struct BattleUnit* defender) {
    short attack;

    attacker->battleAttack = GetItemMight(attacker->weapon);
    attack = attacker->battleAttack;

    if (IsUnitEffectiveAgainst(&attacker->unit, &defender->unit) == TRUE)
        attack = attacker->battleAttack * 3;

    if (IsItemEffectiveAgainst(attacker->weapon, &defender->unit) != 0) {
        attack = attacker->battleAttack;

        switch (GetItemIndex(attacker->weapon)) {

        case ITEM_SWORD_AUDHULMA:
        case ITEM_LANCE_VIDOFNIR:
        case ITEM_AXE_GARM:
        case ITEM_BOW_NIDHOGG:
        case ITEM_ANIMA_EXCALIBUR:
        case ITEM_LIGHT_IVALDI:
        case ITEM_SWORD_SIEGLINDE:
        case ITEM_LANCE_SIEGMUND:
            attack *= 2;
            break;

        default:
            attack *= 3;
            break;

        } // switch (GetItemIndex(attacker->weapon))
    }

    attack += attacker->wTriangleDmgBonus;

    attacker->battleAttack = attack;
	if((GetItemAttributes(attacker->weapon) & IA_MAGIC)){
		attacker->battleAttack += attacker->unit.mag;	
	}
	//else if((GetItemAttributes(attacker->weapon) & IA_MAGICDAMAGE)){
		//attacker->battleAttack += attacker->unit.mag;	
	//}
    else
		attacker->battleAttack += attacker->unit.pow;

    if (GetItemIndex(attacker->weapon) == ITEM_MONSTER_STONE)
        attacker->battleAttack = 0;
}

//Hit Formula Skill*2

void ComputeBattleUnitHitRate(struct BattleUnit* bu) {
    //bu->battleHitRate = (bu->unit.skl + (bu->unit.skl / 2)) + GetItemHit(bu->weapon) + bu->unit.lck + bu->wTriangleHitBonus; // dex 1.5
    bu->battleHitRate = (bu->unit.skl *2 ) + GetItemHit(bu->weapon) + bu->unit.lck + bu->wTriangleHitBonus; // dex 2
    //bu->battleHitRate = ((bu->unit.skl * 2) + (bu->unit.skl / 2)) + GetItemHit(bu->weapon) + bu->unit.lck + bu->wTriangleHitBonus; //dex 2.5
    }

//Avoid Formula Spd*1.5
void ComputeBattleUnitAvoidRate(struct BattleUnit* bu) {
    bu->battleAvoidRate = (bu->battleSpeed + (bu->battleSpeed / 2) + bu->terrainAvoid + (bu->unit.lck)); //spe 1.5
    //bu->battleAvoidRate = (bu->battleSpeed * 2) + bu->terrainAvoid + (bu->unit.lck); //spe 2
    //bu->battleAvoidRate = ((bu->battleSpeed * 2) + (bu->battleSpeed / 2) + bu->terrainAvoid + (bu->unit.lck)); //spe 2.5

    if (bu->battleAvoidRate < 0)
        bu->battleAvoidRate = 0;
    }

//Temporary support disable
//Breaks some skill list stuff for some reason?
/*void UnitLoadSupports(struct Unit* unit) {
    return;
}

void ProcessTurnSupportExp(void){
    return;
}*/

//Exp Changes
//LegendofLoog
int GetBattleUnitExpGain(struct BattleUnit* actor, struct BattleUnit* target){
    
    if (CanBattleUnitGainExp(actor, target)){

        // tinked or missed
        if (!(actor->nonZeroDamage)){
            return 1;
        }

        int levelDiff = GetLevelDifference(actor, target);
        // killed
        if (target->unit.curHP == 0){       
            int initialKillExp = 25 + 4 * levelDiff;
            int fatigueState = GetFatigueLevel(&actor->unit);
            if(fatigueState == 1){
                initialKillExp = initialKillExp / 2;
            }
            else if(fatigueState == 2){
               initialKillExp = initialKillExp / 4; 
            }

            if(initialKillExp <= 5){
                return 5;
            }
            else if (initialKillExp >= 50){
                return 50;
            }
            else{
                return initialKillExp; //50 kill exp cap
            }
        }

        // hit
        int initialHitExp = 8 + 1 * levelDiff;
        int fatigueState = GetFatigueLevel(&actor->unit);
            if(fatigueState == 1){
                initialHitExp = initialHitExp / 2;
            }
            else if(fatigueState == 2){
               initialHitExp = initialHitExp / 4; 
            }

            if(initialHitExp <= 1){
                return 1;
            }
            else if(initialHitExp >= 15){
                return 15;
            }
            else{
                return initialHitExp;
            }

    }

    return 0;
}

bool CanBattleUnitGainExp(struct BattleUnit* actor, struct BattleUnit* target){

    // is the unit exp maxed
    if (!CanBattleUnitGainLevels(actor)){
        return false;
    }

    // is the unit alive
    if (actor->unit.curHP == 0){
        return false;
    }

    // does the opponent prevent exp gain
    if (((target->unit.pCharacterData->attributes) | (target->unit.pClassData->attributes)) & CA_NO_EXP){
        return false;
    }

    return true;

}

int GetUnitEffectiveLevel(struct Unit* unit){

    int effectiveLevel = unit->level;

    if (unit->pClassData->attributes & CA_PROMOTED){
        effectiveLevel += 20;
    }

    return effectiveLevel;

}

int GetLevelDifference(struct BattleUnit* actor, struct BattleUnit* target){

    int diff = GetUnitEffectiveLevel(&target->unit) - GetUnitEffectiveLevel(&actor->unit);
    return diff;

}

bool CanBattleUnitGainLevels(struct BattleUnit* battleUnit) {
    if (battleUnit->unit.exp == 0xFF){
        return false;
    }

    if (UNIT_FACTION(&battleUnit->unit) != FACTION_BLUE){
        return false;
    }

    return true;
}

int GetEndurance(struct Unit* unit){
    int endurance = (unit->maxHP >> 1) + (UNIT_CON(unit));
    return endurance;
}

int GetFatigueLevel(struct Unit* unit){
    int endurance = GetEndurance(unit);
    if (unit->fatigue < endurance){
      return 0;
    }
    if (endurance*2 < unit->fatigue){
      return 2;
    }
    return 1;
}

int GetBattleUnitStaffExp(struct BattleUnit* actor){
    if (!CanBattleUnitGainLevels(actor)){
        return 0;
    }

    // is the unit alive
    if (actor->unit.curHP == 0){
        return 0;
    }
    
    const struct ItemData* staffData = GetItemData(GetItemIndex(actor->weapon));
    int staffRank = staffData->weaponRank;

    int exp = 0;
    if (staffRank == WPN_EXP_E){
        exp += 15;
    }
    else if (staffRank == WPN_EXP_D){
        exp += 18;
    }
    else if (staffRank == WPN_EXP_C){
        exp += 21;
    }
    else if (staffRank == WPN_EXP_B){
        exp += 24;
    }
    else if (staffRank == WPN_EXP_A){
        exp += 30;
    }
    else{
        exp += 34;
    }

    int levelDiff = GetLevelDifference(actor, &gBattleTarget);

    if (levelDiff < 0){ //if the target is lower level than actor, reduce exp by 2 * level diff
        exp += levelDiff * 3;
    }
    int fatigueState = GetFatigueLevel(&actor->unit);

    if(fatigueState == 1){
        exp = exp / 2;
    }
    else if(fatigueState == 2){
        exp = exp / 4; 
    }

   
    if (exp <= 3){
        return 3;
    }
    else{
        return exp;
    }
}

void BattleApplyMiscActionExpGains(void) {
    if (UNIT_FACTION(&gBattleActor.unit) != FACTION_BLUE)
        return;

    if (!CanBattleUnitGainLevels(&gBattleActor))
        return;

    if (gPlaySt.chapterStateBits & PLAY_FLAG_EXTRA_MAP)
        return;

int fatigueState = GetFatigueLevel(&gBattleActor.unit);

    switch (gActionData.unitActionType){
        case UNIT_ACTION_STEAL:
        if(fatigueState == 1){
            gBattleActor.expGain = 10;
            gBattleActor.unit.exp += 10;
        }
        else if(fatigueState == 2){
            gBattleActor.expGain = 5;
            gBattleActor.unit.exp += 5; 
        }
        else{
            gBattleActor.expGain = 20;
            gBattleActor.unit.exp += 20;
        }
        break;
        case UNIT_ACTION_SUMMON:
        if(fatigueState == 1){
            gBattleActor.expGain = 10;
            gBattleActor.unit.exp += 10;
        }
        else if(fatigueState == 2){
            gBattleActor.expGain = 5;
            gBattleActor.unit.exp += 5; 
        }
        else{
            gBattleActor.expGain = 20;
            gBattleActor.unit.exp += 20;
        }
        break;
        case UNIT_ACTION_DANCE:
        if(fatigueState == 1){
            gBattleActor.expGain = 10;
            gBattleActor.unit.exp += 10;
        }
        else if(fatigueState == 2){
            gBattleActor.expGain = 5;
            gBattleActor.unit.exp += 5; 
        }
        else{
            gBattleActor.expGain = 20;
            gBattleActor.unit.exp += 20;
        }
        break;
        default:
        gBattleActor.expGain = 5;
        gBattleActor.unit.exp += 5;
        break;
    }

    CheckBattleUnitLevelUp(&gBattleActor);
}