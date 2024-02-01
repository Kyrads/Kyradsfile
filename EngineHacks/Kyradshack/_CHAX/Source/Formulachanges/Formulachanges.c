#include "gbafe.h"


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
	else if((GetItemAttributes(attacker->weapon) & IA_MAGICDAMAGE)){
		attacker->battleAttack += attacker->unit.mag;	
	}
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
void UnitLoadSupports(struct Unit* unit) {
    return;
}

void ProcessTurnSupportExp(void){
    return;
}