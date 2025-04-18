#include "gbafe.h"
#include "formulachanges.h"

//Default Options
void InitPlayConfig(int isDifficult, s8 unk) {
    CpuFill16(0, &gPlaySt, sizeof(gPlaySt));

    gPlaySt.chapterIndex = 0;

    if (isDifficult)
        gPlaySt.chapterStateBits |= PLAY_FLAG_HARD;

    // TODO: WHAT ARE THOSE
    gPlaySt.config.controller = unk;
    gPlaySt.config.animationType = 0;
    gPlaySt.config.disableTerrainDisplay = 0;
    gPlaySt.config.unitDisplayType = 0;
    gPlaySt.config.autoCursor = 0;
    gPlaySt.config.textSpeed = 2; // TODO: (DEFAULT?) TEXT SPEED DEFINITIONS
    gPlaySt.config.gameSpeed = 0;
    gPlaySt.config.disableBgm = 0;
    gPlaySt.config.disableSoundEffects = 0;
    gPlaySt.config.windowColor = 0;
    gPlaySt.config.disableAutoEndTurns = 0;
    gPlaySt.config.noSubtitleHelp = 0;
    gPlaySt.config.battleForecastType = 0;
    gPlaySt.config.debugControlRed = 0;
    gPlaySt.config.debugControlGreen = 0;
    gPlaySt.config.unitColor = 0;
    gPlaySt.config.unk41_5 = 0;
}

void MiscIncrementFatigue(struct Unit* unit){
     switch(gActionData.unitActionType) {
        case UNIT_ACTION_RESCUE:
        case UNIT_ACTION_SHOVE:
        case UNIT_ACTION_PIVOT:
        case UNIT_ACTION_SWAP:
        case UNIT_ACTION_REPOSITION:
        case UNIT_ACTION_SWARP:
        switch(GetFatigueLevel(unit)){
            case 0 : unit->fatigue += 1; break;
            case 1 : unit->fatigue += 2; break;
            case 2 : unit->fatigue += 2; break;
        }
     }
}

void BeginUnitPoisonDamageAnim(struct Unit* unit, int damage) {

    BattleInitItemEffect(unit, -1);

    AddUnitHp(&gBattleActor.unit, -damage);

    if (gBattleActor.unit.curHP < 0) {
        gBattleActor.unit.curHP = 0;
    }

    if (gBattleActor.unit.curHP != 0){
        switch(GetFatigueLevel(unit)){
            case 0 : unit->fatigue += 1; break;
            case 1 : unit->fatigue += 2; break;
            case 2 : unit->fatigue += 2; break;
        }
    }

    gBattleHitIterator->hpChange = gBattleActor.hpInitial - gBattleActor.unit.curHP;

    if (gBattleActor.unit.curHP == 0) {
        gBattleHitIterator->info |= BATTLE_HIT_INFO_FINISHES;
    }

    BattleHitTerminate();

    BeginMapAnimForPoisonDmg();

    RenderMapForFogFadeIfUnitDied(unit);

    return;
}