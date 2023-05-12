#include "gbafe.h"

void ComputeBattleUnitAttack(struct BattleUnit* attacker, struct BattleUnit* defender) {
    short attack;

    attacker->battleAttack = GetItemMight(attacker->weapon) + attacker->wTriangleDmgBonus;
    attack = attacker->battleAttack;

    if (IsUnitEffectiveAgainst(&attacker->unit, &defender->unit) == TRUE)
        attack = attacker->battleAttack * 3;

    if (IsItemEffectiveAgainst(attacker->weapon, &defender->unit) == TRUE) {
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

    attacker->battleAttack = attack;
    attacker->battleAttack += attacker->unit.pow;

    if (GetItemIndex(attacker->weapon) == ITEM_MONSTER_STONE)
        attacker->battleAttack = 0;
}

void ComputeBattleUnitSpeed(struct BattleUnit* bu) {
    int effWt = GetItemWeight(bu->weaponBefore);

    effWt -= bu->unit.conBonus;

    if (effWt < 0)
        effWt = 0;

    bu->battleSpeed = bu->unit.spd - effWt;

    if (bu->battleSpeed < 0)
        bu->battleSpeed = 0;
}
